#include "UdpClient.h"

using namespace std;
using namespace LightNetwork;

UdpClient::UdpClient() : _socketId(DEF_INVALID_SOCKET), _stream(NULL), _ipPort(0)
{
}

UdpClient::~UdpClient()
{
	Disconnect();
}

bool UdpClient::Connect(string ipAddress, unsigned short ipPort)
{
	_error.clear();
	if (_socketId != DEF_INVALID_SOCKET)
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
		Disconnect();
		#ifdef WINDOWS
			WSACleanup();
		#endif
		return false;
	}
	
	_stream = new NetworkStreamUdp(_socketId, ipAddress, ipPort);
	_ipAddress = ipAddress;
	_ipPort = ipPort;
	return true;
}

void UdpClient::Disconnect()
{
	if (_socketId != DEF_INVALID_SOCKET)
	{
		shutdown(_socketId, SHUT_RDWR);
		CLOSESOCKET(_socketId);
		_socketId = DEF_INVALID_SOCKET;

		if (_stream != NULL)
		{
			delete _stream;
			_stream = NULL;
		}

	#ifdef WINDOWS
		WSACleanup();
	#endif
	}
}

NetworkStreamUdp* UdpClient::Stream() const
{
	return _stream;
}

string UdpClient::ErrorString() const
{
	return _error;
}

string UdpClient::IPAddress() const
{
	return _ipAddress;
}

unsigned short UdpClient::IPPort() const
{
	return _ipPort;
}