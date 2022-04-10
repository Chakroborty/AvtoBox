/**	
	\class UdpClient UdpClient.h
	\brief Класс клиента в сетевом взаимодействии. Используется протокол UDP. Реализует функции подключения/отключения,
	а также обмена данными с сервером	
*/

#pragma once
#include "Definitions.h"
#include "NetworkStreamUdp.h"

namespace LightNetwork
{
	class LIGHT_NETWORK_EXPORT UdpClient
	{
	public:
		/**
			Конструктор
		*/
		UdpClient();
		/**
			Деструктор
		*/
		~UdpClient();
		/**
			Подключение к серверу
			\param[in] ipAddress IP адрес сервера
			\param[in] port IP порт сервера			
			\return Возвращает true, если подключение установлено
		*/
		bool Connect(std::string ipAddress, unsigned short port);
		/**
			Отключение от сервера
		*/
		void Disconnect();
		/**
			Возвращает указатель на объект чтения/записи данных в сокет.
			Эту функцию необходимо вызывать после вызова функции Connect().
			Если подключения нет, тогда возвращается NULL.
			Объект удаляется автоматически при отключении от сервера
		*/		
		NetworkStreamUdp* Stream() const;
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
		unsigned short _ipPort;
		NetworkStreamUdp* _stream;
	};
}