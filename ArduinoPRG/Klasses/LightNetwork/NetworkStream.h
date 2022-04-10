/**	
	\class NetworkStream NetworkStream.h 
	\brief Класс, обеспечивающий чтение данных из сокета, а также запись данных в сокет. Используется протокол TCP. 
	Создание объекта этого класса вручную не требуется. Доступ к объекту этого класса осуществляется через 
	метод Stream() класса TcpClient (для клиента) и NextPendingConnection() класса TcpServer (для сервера)
*/

#pragma once
#include "Definitions.h"
#include <string>
#include <cstdlib>

#ifdef LIGHT_NETWORK_ENABLE_CANCEL_WRITE
#include <mutex>
#endif

namespace LightNetwork
{
#if defined(WINDOWS) && defined(LIGHT_NETWORK_ENABLE_CANCEL_WRITE)
    class LIGHT_NETWORK_EXPORT std::mutex;
#endif

	class LIGHT_NETWORK_EXPORT NetworkStream
	{	
	public:
		/**
		  Конструктор
		  \param[in] socketId Дескриптор сокета
		*/
        NetworkStream(DEF_SOCKET socketId);
		/**
			Деструктор
		*/
		~NetworkStream();
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
		/**
			Очищает сокет от всех входящих данных 
		*/		
		void Clear();
		/**
			Позволяет проверить статус сокета
		*/
		bool IsDisconnected();
		/**
			Задает максимальное время ожидания поступления данных в сокет. Время задается в миллисекундах.
			Функцию необходимо вызывать после успешного вызова функции Connect класса TcpClient
		*/		
		void SetSendTime(unsigned milliseconds);
#if LIGHT_NETWORK_ENABLE_CANCEL_WRITE
		/**
			Позволяет досрочно выйти из блокирующей функции записи данных в сокет
		*/		
		void CancelWrite();		
#endif
	private:
		DEF_SOCKET _socketId;
		std::string _error;
		char *_innerBuf;

#ifdef LIGHT_NETWORK_ENABLE_CANCEL_WRITE
		std::mutex _mutex, _mutexErrorMsg;
		bool _cancelWrite;		
#endif

		bool _tryErrorMsgLock();
		bool _checkDataForReading(bool* hasError = NULL);

		void _clearErrorMsg();
        void _unlockErrorMutex();
	};
}
