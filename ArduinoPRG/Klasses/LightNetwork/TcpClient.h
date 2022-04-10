/**	
	\class TcpClient TcpClient.h
	\brief Класс клиента в сетевом взаимодействии. Используется протокол TCP. Реализует функции подключения/отключения,
	а также обмена данными с сервером	
*/

#pragma once
#include "Definitions.h"
#include "NetworkStream.h"

namespace LightNetwork
{
	class LIGHT_NETWORK_EXPORT TcpClient
	{
	public:
		/**
			Конструктор
		*/
		TcpClient();
		/**
			Деструктор
		*/
		~TcpClient();
		/**
			Подключение к серверу
			\param[in] ipAddress IP адрес сервера
			\param[in] port IP порт сервера
			\param[in] sndBufSize Размер буфера для отправки данных. Указывается опционально. Как правило, ОС автоматически регулирует 
			величину этого параметра, в зависимости от пропускной способности сети. Подробнее см. описание параметра сокета SO_SNDBUF
			\return Возвращает true, если подключение установлено
		*/
		bool Connect(std::string ipAddress, unsigned short port, unsigned int sndBufSize = 0);
		/**
			Отключение от сервера
		*/
		// отключение от хоста
		void Disconnect();
		/**
			Позволяет определить, подключен ли клиент в данный момент к серверу
		*/		
		bool IsConnected() const;
		/**
			Возвращает указатель на объект чтения/записи данных в сокет.
			Эту функцию необходимо вызывать после вызова функции Connect().
			Если подключения нет, тогда возвращается NULL.
			Объект удаляется автоматически при отключении от сервера
		*/		
		NetworkStream* Stream() const;
		/**
			Возвращает последнее сообщение об ошибке
			\return Сообщение об ошибке
		*/
		std::string ErrorString() const;				

		/**
		Возвращает текущий IP адрес, по которому было установлено успешное соединение. Если не было ни одного подключения к серверу, то возвращается пустая строка
		\return Сообщение об ошибке
		*/
		std::string IPAddress() const;

		/**
		Возвращает текущий IP порт, по которому было установлено успешное соединение. Если не было ни одного подключения к серверу, то возвращается 0
		\return Сообщение об ошибке
		*/
		unsigned short IPPort() const;
	private:
		std::string _error, _ipAddress;
		DEF_SOCKET _socketId;
		NetworkStream* _stream;
		unsigned short _ipPort;
		bool _setSocketBlockingEnabled(DEF_SOCKET fd, bool blocking);		
	};
}