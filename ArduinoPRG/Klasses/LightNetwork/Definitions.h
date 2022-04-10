/**
	\file Definitions.h
	\brief	Заголовочный файл определения макросов
*/

/*! \mainpage	
	\section intro_sec Введение
 
	LightNetwork - библиотека для сетевого взаимодействия. Поддерживает протоколы TCP и UDP.
	\warning При компиляции на ОС Windows необходимо определить макрос WINDOWS, при компиляции на ОС семейства Linux необходимо
	определить макрос LINUX
	
	\section classes_desc Краткое описание классов	
	\subsection TcpClient TCP клиент 
	TcpClient - класс клиента в сетевом взаимодействии. Используется протокол TCP. Реализует функции подключения/отключения,
	а также обмена данными с сервером. Описание класса \link LightNetwork::TcpClient \endlink
	
	\subsection TcpServer TCP сервер 
	TcpServer - класс сервера в сетевом взаимодействии. Используется протокол TCP. Описание класса \link LightNetwork::TcpServer \endlink
	
	\subsection NetworkStream TCP поток для чтения/записи 
	NetworkStream - класс, обеспечивающий чтение данных из сокета, а также запись данных в сокет. Используется протокол TCP. 
	Создание объекта этого класса вручную не требуется. Доступ к объекту этого класса осуществляется через 
	метод Stream() класса TcpClient (для клиента) и NextPendingConnection() класса TcpServer (для сервера).
	Описание класса \link LightNetwork::NetworkStream \endlink	
	
	\subsection UdpClient UDP клиент 
	UdpClient - класс клиента в сетевом взаимодействии. Используется протокол UDP. Реализует функции подключения/отключения,
	а также обмена данными с сервером. Описание класса \link LightNetwork::UdpClient \endlink
	
	\subsection UdpServer UDP сервер 
	UdpServer - класс сервера в сетевом взаимодействии. Используется протокол UDP. Описание класса \link LightNetwork::UdpServer \endlink
	
	\subsection NetworkStreamUdp UDP поток для чтения/записи
	NetworkStreamUdp - класс, обеспечивающий чтение данных из сокета, а также запись данных в сокет. Используется протокол UDP. 
	Создание объекта этого класса вручную не требуется. Доступ к объекту этого класса осуществляется через 
	метод Stream() класса UdpClient (для клиента) и NextPendingConnection() класса UdpServer (для сервера).
	Описание класса \link LightNetwork::NetworkStreamUdp \endlink	
	
	\section code_example Примеры кода
	\subsection tcp_client_example Пример TCP клиента
	\code
	#include "TcpClient.h"
	#define BUFFER_SIZE	1024
	
	using namespace std;
	using namespace LightNetwork; 	

	int main(int argc, char** argv)
	{
		TcpClient tcpClient;
		string ipAddress = "127.0.0.1";
		unsigned ipPort = 9999;
		
		// Подключение клиента к серверу
		if (!tcpClient.Connect(ipAddress, ipPort))
		{
			cout << tcpClient.ErrorString();	
			return 0;
		}
		
		char buf[BUFFER_SIZE];
		// Отправка данных на сервер
		if (tcpClient.Stream()->Write(buf, BUFFER_SIZE) <= 0)
		{
			cout << "Write error: " << tcpClient.ErrorString() << "\n";
			break;
		}
		
		// Ожидание данных от сервера
		bool hasError = false;
		if (tcpClient.Stream()->WaitDataForReading(5000, &hasError))
		{		
			// Данные в сокете, считаем их
			int result = tcpClient.Stream()->Read(buf, BUFFER_SIZE);
			if (result <= 0)
			{
				cout << "Read error:" << tcpClient.ErrorString() << "\n";
				break;
			}
			else
				cout << "Server said: " << buf << "\n";
		}
		else if (hasError)
		{
			cout << "Read error:" << tcpClient.ErrorString() << "\n";
			break;
		}	
		
		// Отключение клиента от сервера
		tcpClient.Disconnect();
	}
	\endcode
		
	\subsection tcp_server_example Пример TCP сервера
	\code
	#include "TcpServer.h"
	#define BUFFER_SIZE	1024

	using namespace std;
	using namespace LightNetwork;

	int main(int argc, char** argv)
	{
		string ipAddress = "127.0.0.1";
		unsigned ipPort = 9999;
		
		TcpServer tcpServer;
		// Задаем максимальное количество одновременных подключений
		tcpServer.SetMaxPendingConnections(2);

		// Пробуем слушать порт
		if (!tcpServer.Listen(ipAddress, ipPort))
		{
			cout << tcpServer.ErrorString();		
			return 0;
		}	

		char buf[BUFFER_SIZE];
		
		NetworkStream* stream;
		bool hasError = false;

		while (true)
		{
			// Проверяем сервер на предмет подключений клиентов
			if (tcpServer.HasPendingConnections())
			{
				// Получаем объект для обмена данными с клиентом
				stream = tcpServer.NextPendingConnection();		
				break;
			}	
		}
		
		// Ожидаем сообщения от клиента
		if (!stream->WaitDataForReading(5000, &hasError))
		{
			// Если в момент ожидания произошла ошибка сокета
			if (hasError)
			{
				cout << "Socket error: " << stream->ErrorString().c_str() << "\n";
				return 0;
			}	
		}
		
		// Данные в сокете, считаем их
		int result = stream->Read(buf, BUFFER_SIZE);
		if (result == 0)
		{
			cout << "Client disconnected: " << stream->ErrorString().c_str() << "\n";
			return 0;
		}
		if (result < 0)
		{
			cout << "Socket error: " << stream->ErrorString().c_str() << "\n";
			return 0;
		}

		cout << "Client said: " << buf << "\n";
		string buf2{ "This is simple server. You request: " };
		buf2.append(buf);

		// Отправляем сообщение клиенту
		if (stream->Write(buf2.c_str(), buf2.size()) <= 0)
		{
			cout << "Socket error: " << stream->ErrorString().c_str() << "\n";
			return 0;
		}

		// Закрываем сервер
		tcpServer.Close();
	}
	\endcode
	
	\subsection udp_client_example Пример UDP клиента
	\code
	#include "UdpClient.h"

	using namespace std;
	using namespace LightNetwork;

	#define BUFFER_SIZE	1024

	int main(int argc, char** argv)
	{
		UdpClient udpClient;
		string ipAddress = "127.0.0.1";
		unsigned ipPort = 9999;
		
		// Подключение клиента к серверу
		if (!udpClient.Connect(ipAddress, ipPort))
		{
			cout << udpClient.ErrorString();	
			return 0;
		}
		
		char buf[BUFFER_SIZE];
		// Отправка данных на сервер
		if (udpClient.Stream()->Write(buf, BUFFER_SIZE) <= 0)
		{
			cout << "Write error: " << udpClient.ErrorString() << "\n";
			break;
		}
		
		// Ожидание данных от сервера
		bool hasError = false;
		if (udpClient.Stream()->WaitDataForReading(5000, &hasError))
		{		
			// Данные в сокете, считаем их
			int result = udpClient.Stream()->Read(buf, BUFFER_SIZE);
			if (result <= 0)
			{
				cout << "Read error:" << udpClient.ErrorString() << "\n";
				break;
			}
			else
				cout << "Server said: " << buf << "\n";
		}
		else if (hasError)
		{
			cout << "Read error:" << udpClient.ErrorString() << "\n";
			break;
		}	
		
		// Отключение клиента от сервера
		udpClient.Disconnect();
	}
	\endcode
	
	\subsection udp_server_example Пример UDP сервера
	\code
	#include "UdpServer.h"
	#define BUFFER_SIZE	1024

	using namespace std;
	using namespace LightNetwork;

	int main(int argc, char** argv)
	{
		string ipAddress = "127.0.0.1";
		unsigned ipPort = 9999;
		
		UdpServer udpServer;	

		// Пробуем связать ip адрес и порт с сервером
		if (!udpServer.Bind(ipAddress, ipPort))
		{
			cout << udpServer.ErrorString();		
			return 0;
		}	

		char buf[BUFFER_SIZE];
		bool hasError = false;
		
		// Ожидаем сообщения от клиента
		if (!udpServer.Stream()->WaitDataForReading(5000, &hasError))
		{
			// Если в момент ожидания произошла ошибка сокета
			if (hasError)
			{
				cout << "Socket error: " << udpServer.Stream()->ErrorString().c_str() << "\n";
				return 0;
			}	
		}
		
		// Данные в сокете, считаем их
		int result = udpServer.Stream()->Read(buf, BUFFER_SIZE);
		if (result == 0)
		{
			cout << "Client disconnected: " << udpServer.Stream()->ErrorString().c_str() << "\n";
			return 0;
		}
		if (result < 0)
		{
			cout << "Socket error: " << udpServer.Stream()->ErrorString().c_str() << "\n";
			return 0;
		}

		cout << "Client said: " << buf << "\n";
		string buf2{ "This is simple server. You request: " };
		buf2.append(buf);

		// Отправляем сообщение клиенту
		if (udpServer.Stream()->Write(buf2.c_str(), buf2.size()) <= 0)
		{
			cout << "Socket error: " << udpServer.Stream()->ErrorString().c_str() << "\n";
			return 0;
		}

		// Закрываем сервер
		udpServer.Close();
	}
	\endcode
 */
 
#ifndef LIGHTNETWORK_DEFINITIONS_H
#define LIGHTNETWORK_DEFINITIONS_H

/// время на подключение к серверу в секундах
#define CONNECT_TIME	5 
#include <cstdio>

#if defined(WINDOWS)
	#undef UNICODE
    #undef _UNICODE
	#define _WINSOCK_DEPRECATED_NO_WARNINGS

	#include <WinSock2.h>
	#include <WS2tcpip.h>
	#include <atlbase.h>
#include <winbase.h>
	#include <stdint.h>
    #include <string>
	#pragma comment(lib, "Ws2_32.lib")

	#ifdef LIGHT_NETWORK_LIB
		#define LIGHT_NETWORK_EXPORT __declspec(dllexport)
	#else
        #ifdef LIGHT_NETWORK_SRC
            #define LIGHT_NETWORK_EXPORT
        #else
            #define LIGHT_NETWORK_EXPORT __declspec(dllimport)
        #endif
	#endif

	#define DEF_SOCKET			SOCKET
	#define DEF_INVALID_SOCKET	INVALID_SOCKET
	#define DEF_SOCKET_ERROR	SOCKET_ERROR
	#define DEF_ERROR_CODE		WSAGetLastError()
	#define SHUT_RDWR	SD_BOTH
	#define CLOSESOCKET(socket)	closesocket(socket)
	#define SLEEP(ms) Sleep(ms)	

	inline int64_t MillisecondsSinceEpoch()
	{
		// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
		// This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
		// until 00:00:00 January 1, 1970 
		static const int64_t EPOCH = ((int64_t) 116444736000000000ULL);

		SYSTEMTIME  system_time;
		FILETIME    file_time;
		int64_t    time;

		GetSystemTime( &system_time );
		SystemTimeToFileTime( &system_time, &file_time );
		time =  ((int64_t)file_time.dwLowDateTime )      ;
		time += ((int64_t)file_time.dwHighDateTime) << 32;

		return static_cast<int64_t>((time - EPOCH) / 10000L) +
			static_cast<int64_t>(system_time.wMilliseconds);		
	}
#elif LINUX
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <arpa/inet.h>
	#include <errno.h>
	#include <cstring>
	#include <unistd.h>
	#include <fcntl.h>
	#include <stdint.h>

	#define CLOSESOCKET(socket)	close(socket)
	#define LIGHT_NETWORK_EXPORT
	#define UnixMsg(errCode, msg)	msg = strerror_r(errCode, NULL, 0);
	#define DEF_SOCKET			int
	#define DEF_INVALID_SOCKET	-1
	#define DEF_SOCKET_ERROR	-1
	#define DEF_ERROR_CODE		errno
	#define SLEEP(ms) usleep(ms*1000)

	inline int64_t MillisecondsSinceEpoch()
	{
		struct timeval tv;

		gettimeofday(&tv, NULL);

		return (int64_t)(tv.tv_sec) * 1000 +
			(int64_t)(tv.tv_usec) / 1000;
	}
#else
	#error Not specified target platform. Please specify WINDOWS or LINUX in preprocessor directives.
#endif 

#include <string>
namespace LightNetwork
{
	inline void ErrMsg(int errCode, std::string& msg)
	{
#if defined(WINDOWS)
		LPTSTR lpMsg = NULL;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsg, 100, NULL);
		msg = T2A(lpMsg);
		LocalFree(lpMsg);
#elif LINUX
		msg = strerror(errCode);
#endif
	}
}
#endif //LIGHTNETWORK_DEFINITIONS_H