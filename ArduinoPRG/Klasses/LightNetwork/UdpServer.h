/**	
	\class UdpServer UdpServer.h
	\brief Класс сервера в сетевом взаимодействии. Используется протокол UDP
*/

#pragma  once
#include "Definitions.h"
#include "NetworkStreamUdp.h"

namespace LightNetwork
{
	class LIGHT_NETWORK_EXPORT UdpServer
	{
	public:
		/**
			Конструктор
		*/
		UdpServer();
		/**
			Деструктор
		*/
		~UdpServer();
		/**
			Привязывает адрес и порт к сокету
			\param[in] ipAddress IP адрес сервера
			\param[in] port IP порт сервера
			\return Возвращает true, если привязка удалась
		*/		
		bool Bind(std::string ipAddress, unsigned short port);
		/**
			Закрывает сервер
		*/		
		void Close();
		/**
			Возвращает последнее сообщение об ошибке
			\return Сообщение об ошибке
		*/
		std::string ErrorString() const;
		/**
			Возвращает указатель на объект чтения/записи в сокет.			
			Объект NetworkStreamUdp удаляется автоматически при закрытии сервера			
		*/	
		NetworkStreamUdp* Stream() const;				
	private:
		NetworkStreamUdp *_stream;
		std::string _error;
		bool _binding;
		DEF_SOCKET _socketId;				
	};
}
