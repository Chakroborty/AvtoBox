#include "UdpServer.h"

using namespace std;
using namespace LightNetwork;

UdpServer::UdpServer():
						_stream(NULL),
						_binding(false),
						_socketId(DEF_INVALID_SOCKET)
{
	
}

UdpServer::~UdpServer()
{
	Close();
}

bool UdpServer::Bind(std::string ipAddress, unsigned short ipPort)
{
	_error.clear();
	if (_binding)
		return true;
	
#ifdef WINDOWS
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		return false;
	}
#endif

	_socketId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_socketId == DEF_INVALID_SOCKET)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		return false;
	}	

	struct sockaddr_in serverInfo;
	memset(&serverInfo, 0, sizeof(serverInfo));	

	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(ipPort);
	serverInfo.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	int sockAddrLen = sizeof(struct sockaddr_in);
	struct sockaddr* serverAddrInfoPtr = (struct sockaddr*)&serverInfo;
	
	if (bind(_socketId, serverAddrInfoPtr, sockAddrLen) == DEF_SOCKET_ERROR)
	{
		ErrMsg(DEF_ERROR_CODE, _error);
		return false;
	}

	_stream = new NetworkStreamUdp(_socketId, ipAddress, ipPort);
	_binding = true;

	return true;
}

void UdpServer::Close()
{
	_error.clear();

	if (!_binding)
		return;

	if (_socketId != DEF_INVALID_SOCKET)
	{
		shutdown(_socketId, SHUT_RDWR);
		CLOSESOCKET(_socketId);
		_socketId = DEF_INVALID_SOCKET;
	}

	if (_stream != NULL)
	{
		delete _stream;
		_stream = NULL;
	}
	
#ifdef WINDOWS
	WSACleanup();
#endif
	_binding = false;
}

string UdpServer::ErrorString() const
{
	return _error;
}

NetworkStreamUdp* UdpServer::Stream() const
{
	return _stream;
}