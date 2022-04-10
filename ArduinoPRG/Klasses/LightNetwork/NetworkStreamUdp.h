/**	
	\class NetworkStreamUdp NetworkStreamUdp.h 
	\brief Класс, обеспечивающий чтение данных из сокета, а также запись данных в сокет. Используется протокол UDP. 
	Создание объекта этого класса вручную не требуется. Доступ к объекту этого класса осуществляется через 
	метод Stream() класса UdpClient (для клиента) и NextPendingConnection() класса UdpServer (для сервера)
*/
#pragma once
#include "Definitions.h"
#include <string>
#include <cstdlib>


// устранение ошибки с4251
//template class LIGHT_NETWORK_EXPORT basic_string<char, std::char_traits<char>, std::allocator<char>>;

namespace LightNetwork
{
	class LIGHT_NETWORK_EXPORT NetworkStreamUdp
	{
	public:
		/**
			Конструктор
			\param[in] socketId Дескриптор сокета
			\param[in] ipAddress IP адрес
			\param[in] ipPort IP порт
		*/
		NetworkStreamUdp(DEF_SOCKET socketId, std::string ipAddress, unsigned short int ipPort);
		/**
			Деструктор
		*/
		~NetworkStreamUdp();
		/**
			Возвращает дескриптор сокета
			\return Дескриптор сокета
		*/		
		DEF_SOCKET SocketId() const;
		/**
			Возвращает последнее сообщение об ошибке
			\return Сообщение об ошибке
		*/
		std::string ErrorString() const;
		/**
			Читает данные из сокета в буфер data. Функция неблокирующая. Перед началом чтения из сокета
			проверяется наличие данных в сокете. Если данных нет, возвращается 0.
			\param[in] data Указатель на пользовательский буфер
			\param[in] size Максимальный размер считываемых данных. Если в сокете данных меньше, чем размер size,
			функция не блокируется, а досрочно завершается.
			\return Возвращает количество считанных байт или -1 в случае ошибки.			
		*/
		long long Read(char* data, unsigned int size);
		/**
			Записывает данные в сокет. Функция блокирующая. Для досрочного
			выхода из функции записи следует воспользоваться функцией CancelWrite()
			\param[in] data Указатель на пользовательский буфер
			\param[in] size Количество записываемых данных
			\return Возвращает количество записанных данных или -1 в случае ошибки
		*/	
		long long Write(const char* data, unsigned int size);
		/**
			Ожидает появления новых данных в сокете в течение заданного времени
			\param[in] msecs Время ожидания новых данных в миллисекундах
			\param[in] hasError Указатель на переменную, которая информирует о том, 
			что произошла ошибка в сокете в момент проверки новых данных (опционально)
			\return Возвращает true, если доступны новые данные для считывания или false в противном случае
		*/	
		bool WaitDataForReading(unsigned int msecs = 10000, bool* hasError = NULL);		
	private:
		DEF_SOCKET _socketId;
		struct sockaddr_in _serverInfo;
		struct sockaddr* _addrInfoPtr;
		socklen_t _sockAddrLen;
		std::string _error;
		bool _checkDataForReading(bool* hasError = NULL);		
	};
}
