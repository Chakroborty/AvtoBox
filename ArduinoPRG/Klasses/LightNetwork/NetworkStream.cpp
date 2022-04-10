#include "NetworkStream.h"
using namespace LightNetwork;
using namespace std;

// скорость считывания данных
#define DATA_RATE	1024*1024*4

NetworkStream::NetworkStream(DEF_SOCKET socketId) : _socketId(socketId), _innerBuf(NULL)
{
#ifdef LIGHT_NETWORK_ENABLE_CANCEL_WRITE
	_cancelWrite = false;
#endif
}

NetworkStream::~NetworkStream()
{
	if (_innerBuf)
		free(_innerBuf);
}

DEF_SOCKET NetworkStream::SocketId() const
{
	return _socketId;
}

string NetworkStream::ErrorString() const
{
	return _error;
}

long long NetworkStream::Read(char* data, unsigned int size)
{
	_clearErrorMsg();
	if (_socketId == DEF_SOCKET_ERROR)
		return -1;
	
	unsigned int bytesToRead = size, totalBytes = 0;	

	int result;
	while (bytesToRead > 0 && WaitDataForReading(0))
	{
		result = recv(_socketId, data, bytesToRead, 0);
		if (result == DEF_SOCKET_ERROR)
		{
			if (_tryErrorMsgLock())
			{
				ErrMsg(DEF_ERROR_CODE, _error);
				_unlockErrorMutex();
			}
			return -1;
		}
		if (result == 0)
			return 0;

		data += result;
		bytesToRead -= result;
		totalBytes += result;
	}
	
	return totalBytes;
}

long long NetworkStream::Write(const char* data, unsigned int size)
{
	_clearErrorMsg();
	if (_socketId == DEF_SOCKET_ERROR)
		return -1;

	unsigned int bytesToSend = size, totalBytes = 0;
	int result;

#ifdef LIGHT_NETWORK_ENABLE_CANCEL_WRITE
	_mutex.lock();
	_cancelWrite = false;
	_mutex.unlock();
#endif

	while (bytesToSend > 0)
	{
		result = send(_socketId, data, bytesToSend, 0);

		if (result == DEF_SOCKET_ERROR)
		{
			if (_tryErrorMsgLock())
			{
				ErrMsg(DEF_ERROR_CODE, _error);
				_unlockErrorMutex();
			}
			
			return -1;
		}						

		data += result;
		bytesToSend -= result;
		totalBytes += result;

#ifdef LIGHT_NETWORK_ENABLE_CANCEL_WRITE
		_mutex.lock();
		if (_cancelWrite)
		{
			_mutex.unlock();
			break;
		}
		_mutex.unlock();
#endif

	}

	return totalBytes;
}

bool NetworkStream::WaitDataForReading(unsigned int msecs, bool* hasError)
{
	int64_t prevMilliSeconds = MillisecondsSinceEpoch();
	int64_t currMilliseconds = prevMilliSeconds;
	bool hasErrorPrivate = false;
	if (hasError != NULL)
		*hasError = false;
	while ((currMilliseconds - prevMilliSeconds) <= msecs)
	{
		SLEEP(1);

		if (_checkDataForReading(&hasErrorPrivate))
			return true;
		if (hasErrorPrivate)
		{
			if (hasError != NULL)
				*hasError = true;
				
			return false;
		}
		currMilliseconds = MillisecondsSinceEpoch();
	}

	return false;
}

void NetworkStream::Clear()
{	
	if (_innerBuf == NULL)
		_innerBuf = (char*)malloc(DATA_RATE);
	if (_innerBuf == NULL)
	{
        printf("Clear socket error: temp buffer is not created\n");
		return;
	}

    long long currSize;
	bool hasError = false;

	while (true)
	{
		if (!WaitDataForReading(0, &hasError) || hasError)
			break;

		currSize = Read(_innerBuf, DATA_RATE);
		if (currSize == DEF_SOCKET_ERROR || currSize == 0)
			break;
	}
}

bool LightNetwork::NetworkStream::IsDisconnected()
{
	if (_socketId == DEF_SOCKET_ERROR)
		return true;
	if (_checkDataForReading())
	{
		char buf[1];
		int result = recv(_socketId, buf, 1, (int)MSG_PEEK);
		return result == DEF_SOCKET_ERROR || result == 0;
	}
	return false;
}

void NetworkStream::SetSendTime(unsigned milliseconds)
{			
#ifdef WINDOWS
	setsockopt(_socketId, SOL_SOCKET, SO_SNDTIMEO, (char*)&milliseconds, sizeof(milliseconds));
#else
	struct timeval tv;
	tv.tv_sec = milliseconds / 1000;
	setsockopt(_socketId, SOL_SOCKET, SO_SNDTIMEO, (struct timeval*)&tv, sizeof(struct timeval));
#endif
}

#ifdef LIGHT_NETWORK_ENABLE_CANCEL_WRITE
void NetworkStream::CancelWrite()
{
	std::lock_guard<std::mutex> lg(_mutex);
	_cancelWrite = true;
}
#endif

bool NetworkStream::_tryErrorMsgLock()
{
#ifdef LIGHT_NETWORK_ENABLE_CANCEL_WRITE
	int counter = 0;
	while (counter++ < 100)
	{
		if (_mutexErrorMsg.try_lock())
			return true;
		SLEEP(1);
	}
	return false;
#else
	return true;
#endif
}

bool NetworkStream::_checkDataForReading(bool* hasError)
{
	if (_socketId == DEF_SOCKET_ERROR)
		return false;

	_clearErrorMsg();
	if (hasError != NULL)
		*hasError = false;
	fd_set readfs;
	FD_ZERO(&readfs);
	FD_SET(_socketId, &readfs);
	timeval timeout;
	memset(&timeout, 0, sizeof(timeval));
	timeout.tv_usec = 1000;

#ifdef WINDOWS
#pragma warning( disable : 4244 )
#endif

	int selectId = select(_socketId + 1, &readfs, NULL, NULL, &timeout);
	if (selectId == DEF_SOCKET_ERROR)
	{
		if (_tryErrorMsgLock())
		{
			ErrMsg(DEF_ERROR_CODE, _error);
			_unlockErrorMutex();
		}
		if (hasError != NULL)
			*hasError = true;
		return false;
	}

	if (selectId == 0)
	{
		return false;
	}

	if (selectId > 0 && FD_ISSET(_socketId, &readfs))
	{
		return true;
	}

	return false;
}

void NetworkStream::_clearErrorMsg()
{
	if (_tryErrorMsgLock())
	{
		_error.clear();
		_unlockErrorMutex();
	}
}

void NetworkStream::_unlockErrorMutex()
{
#ifdef LIGHT_NETWORK_ENABLE_CANCEL_WRITE
	_mutexErrorMsg.unlock();
#endif
}
