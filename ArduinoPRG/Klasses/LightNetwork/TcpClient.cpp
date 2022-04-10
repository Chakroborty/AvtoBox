#include "TcpClient.h"

using namespace LightNetwork;
using namespace std;

TcpClient::TcpClient() : _socketId(DEF_INVALID_SOCKET), _stream(NULL), _ipPort(0)
{
}

TcpClient::~TcpClient()
{
	Disconnect();
}

bool TcpClient::_setSocketBlockingEnabled(DEF_SOCKET fd, bool blocking)
{
	if (fd == DEF_SOCKET_ERROR)
		return false;

	int result = 0;

#ifdef WINDOWS
	unsigned long mode = blocking ? 1 : 0;
	result = ioctlsocket(fd, FIONBIO, &mode);
	if (result != 0)
	{
		ErrMsg(result, _error);
		return false;
	}
	return true;
#else
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0)
	{
		ErrMsg(result, _error);
		return false;
	}

	flags = blocking ? (flags | O_NONBLOCK) : (flags&~O_NONBLOCK);
	result = fcntl(fd, F_SETFL, flags);
	if (result < 0)
	{
		ErrMsg(result, _error);
		return false;
	}
	return true;
#endif
}

bool TcpClient::Connect(string ipAddress, unsigned short ipPort, unsigned int sndBufSize)
{
	_error.clear();
	if (IsConnected())
		return true;	

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(ipPort);
	local.sin_addr.s_addr = inet_addr(ipAddress.c_str());

#ifdef WINDOWS
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		return false;
	}
#endif

	_socketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socketId == DEF_INVALID_SOCKET)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		Disconnect();
		return false;
	}

	// указываем размер буфера для отправки данных
	if (sndBufSize > 0)
		if (setsockopt(_socketId, SOL_SOCKET, SO_SNDBUF, (char*)&sndBufSize, sizeof(unsigned int)) != 0)
		{
			ErrMsg(DEF_ERROR_CODE, _error);
			Disconnect();
			return false;
		}

	// задаем неблокирующий режим перед подключением
	if (!_setSocketBlockingEnabled(_socketId, true))
	{
		Disconnect();
		return false;
	}

	connect(_socketId, (struct sockaddr*)&local, sizeof(local));

	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(_socketId, &fdset);
	struct timeval tv;
	tv.tv_sec = CONNECT_TIME;   // время на подключение в секундах          
	tv.tv_usec = 0;


	int connectResult = select(_socketId + 1, NULL, &fdset, NULL, &tv);
	if (connectResult == DEF_SOCKET_ERROR)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		Disconnect();
		return false;
	}

	if (connectResult == 0)
	{
		Disconnect();
		return false;
	}

	int so_error = 0;
	socklen_t len = sizeof(so_error);

	getsockopt(_socketId, SOL_SOCKET, SO_ERROR, (char*)&so_error, &len);

	if (so_error != 0)
	{
		ErrMsg(so_error, _error);
		Disconnect();
		return false;
	}

#ifdef WINDOWS	
#pragma warning( disable : 4244 )		
#endif

	// возвращаем блокирующий режим после подключения
	if (!_setSocketBlockingEnabled(_socketId, false))
	{
		Disconnect();
		return false;
	}

	int flag = 1;
	setsockopt(_socketId, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(int));
	setsockopt(_socketId, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));	

	_stream = new NetworkStream(_socketId);
	_ipAddress = ipAddress;
	_ipPort = ipPort;
	return true;
}

void TcpClient::Disconnect()
{	
	if (IsConnected())
	{
		shutdown(_socketId, SHUT_RDWR);
		CLOSESOCKET(_socketId);
		_socketId = DEF_INVALID_SOCKET;

		if (_stream != NULL)
		{
			delete _stream;
			_stream = NULL;
		}
	}
#ifdef WINDOWS
	WSACleanup();
#endif
}

bool TcpClient::IsConnected() const
{
	return _socketId != DEF_INVALID_SOCKET;		
}

NetworkStream* TcpClient::Stream() const
{
	return _stream;
}

string TcpClient::ErrorString() const
{
	return _error;
}

string TcpClient::IPAddress() const
{
	return _ipAddress;
}

unsigned short TcpClient::IPPort() const
{
	return _ipPort;
}