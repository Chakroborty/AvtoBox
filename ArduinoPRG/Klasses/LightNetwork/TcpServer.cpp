#include "TcpServer.h"
using namespace LightNetwork;

TcpServer::TcpServer() 
			: _maxPendingConnections(1),
			_listening(false),
			_socketId(DEF_INVALID_SOCKET)
{
}

TcpServer::~TcpServer()
{
	Close();
}

bool TcpServer::Listen(std::string ipAddress, unsigned short ipPort, unsigned int rcvBufSize)
{
	_error.clear();
	if (_listening)
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
		return false;
	}

	int flag = 1;
	setsockopt(_socketId, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(int));
	setsockopt(_socketId, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));

	// указываем размер буфера для отправки данных
	if (rcvBufSize > 0)
		if (setsockopt(_socketId, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBufSize, sizeof(unsigned int)) != 0)
		{
			ErrMsg(DEF_ERROR_CODE, _error);
			return false;
		}		

	int iResult = ::bind(_socketId, (struct sockaddr *)&local, sizeof(local));
	if (iResult == DEF_SOCKET_ERROR)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		return false;
	}
	iResult = listen(_socketId, _maxPendingConnections);
	if (iResult == DEF_SOCKET_ERROR)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		return false;
	}

	_listening = true;
	return true;
}

void TcpServer::Close()
{
	_error.clear();
	if (_socketId != DEF_INVALID_SOCKET)
	{
		shutdown(_socketId, SHUT_RDWR);
		CLOSESOCKET(_socketId);
		_socketId = DEF_INVALID_SOCKET;
	}
	
    for (unsigned int i = 0; i < _networkStreamList.size(); i++)
	{
		DEF_SOCKET clientSocketId = _networkStreamList[i]->SocketId();
		if (clientSocketId != DEF_INVALID_SOCKET)
		{
			shutdown(clientSocketId, SHUT_RDWR);
			CLOSESOCKET(clientSocketId);			
		}

		delete _networkStreamList[i];
	}
	
	_networkStreamList.clear();
	
#ifdef WINDOWS
	WSACleanup();
#endif
	_listening = false;
}

std::string TcpServer::ErrorString() const
{
	return _error;
}

bool TcpServer::HasPendingConnections()
{
	_error.clear();
	fd_set readfs;
	FD_ZERO(&readfs);
	FD_SET(_socketId, &readfs);
	timeval timeout;
	memset(&timeout, 0, sizeof(timeval));	

#ifdef WINDOWS
#pragma warning( disable : 4244 )
#endif

	int selectId = select(_socketId + 1, &readfs, NULL, NULL, &timeout);
	if (selectId == DEF_SOCKET_ERROR)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		return false;
	}

	if ((selectId > 0) && FD_ISSET(_socketId, &readfs))
	{
		return true;
	}
	return false;
}

NetworkStream* TcpServer::NextPendingConnection()
{
	_error.clear();
	DEF_SOCKET acceptSocket = accept(_socketId, NULL, NULL);
	if (acceptSocket == DEF_INVALID_SOCKET)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		return NULL;
	}
	NetworkStream* stream = new NetworkStream(acceptSocket);
	_networkStreamList.push_back(stream);

	return stream;
}

void TcpServer::SetMaxPendingConnections(unsigned int numConnections)
{
	_error.clear();
	_maxPendingConnections = numConnections;
}

void LightNetwork::TcpServer::CloseSocket(DEF_SOCKET socketId)
{
	shutdown(socketId, SHUT_RDWR);
	CLOSESOCKET(socketId);
}
