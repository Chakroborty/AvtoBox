#include "NetworkStreamUdp.h"

using namespace std;
using namespace LightNetwork;


NetworkStreamUdp::NetworkStreamUdp(DEF_SOCKET socketId, string ipAddress, unsigned short ipPort) : _socketId(socketId)
{
	memset(&_serverInfo, 0, sizeof(_serverInfo));

	_serverInfo.sin_family = AF_INET;
	_serverInfo.sin_port = htons(ipPort);
	_serverInfo.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	_sockAddrLen = sizeof(struct sockaddr_in);
	_addrInfoPtr = (struct sockaddr*)&_serverInfo;
}

NetworkStreamUdp::~NetworkStreamUdp()
{
	
}

DEF_SOCKET NetworkStreamUdp::SocketId() const
{
	return _socketId;
}

string NetworkStreamUdp::ErrorString() const
{
	return _error;
}

long long NetworkStreamUdp::Read(char* data, unsigned int size)
{
	_error.clear();
	if (_socketId == DEF_SOCKET_ERROR)
		return -1;

	unsigned int bytesToRead = size, totalBytes = 0;
	int result;

	while (bytesToRead > 0 && WaitDataForReading(0))

	{
		result = recvfrom(_socketId, data, bytesToRead, 0, _addrInfoPtr, &_sockAddrLen);

		if (result == DEF_SOCKET_ERROR)
		{
			ErrMsg(DEF_ERROR_CODE, _error);
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

long long NetworkStreamUdp::Write(const char* data, unsigned int size)
{
	_error.clear();
	if (_socketId == DEF_SOCKET_ERROR)
		return -1;

	unsigned int bytesToSend = size, totalBytes = 0;
	int result;

	while (bytesToSend > 0)
	{
		result = sendto(_socketId, data, bytesToSend, 0, _addrInfoPtr, _sockAddrLen);

		if (result == DEF_SOCKET_ERROR)
		{
			ErrMsg(DEF_ERROR_CODE, _error);
			return -1;
		}

		data += result;
		bytesToSend -= result;
		totalBytes += result;
	}

	return totalBytes;
}

bool NetworkStreamUdp::WaitDataForReading(unsigned int msecs, bool* hasError)
{
	int64_t prevMilliSeconds = MillisecondsSinceEpoch();
	int64_t currMilliseconds = prevMilliSeconds;
	
	bool hasErrorPrivate = false;
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

bool NetworkStreamUdp::_checkDataForReading(bool* hasError)
{
	if (_socketId == DEF_SOCKET_ERROR)
		return false;

	_error.clear();
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
		ErrMsg(DEF_ERROR_CODE, _error);
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
