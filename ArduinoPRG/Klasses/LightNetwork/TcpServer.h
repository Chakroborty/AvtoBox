/**	
	\class TcpServer TcpServer.h
	\brief Класс сервера в сетевом взаимодействии. Используется протокол TCP
*/

#pragma  once
#include "Definitions.h"
#include "NetworkStream.h"
#include <vector>

namespace LightNetwork
{
	class LIGHT_NETWORK_EXPORT TcpServer
	{	
	public:
		/**
			Конструктор
		*/
		TcpServer();
		/**
			Деструктор
		*/
		~TcpServer();
		/**
			Указывает серверу прослушивать порт на предмет входящих подключений
			\param[in] ipAddress IP адрес сервера
			\param[in] port IP порт сервера, который необходимо прослушивать
			\param[in] rcvBufSize Размер буфера для получения данных. Указывается опционально. Как правило, ОС автоматически регулирует 
			величину этого параметра, в зависимости от пропускной способности сети. Подробнее см. описание параметра сокета SO_RCVBUF
			\return Возвращает true, если удалось поставить порт на прослушивание
		*/
		// 
		bool Listen(std::string ipAddress, unsigned short port, unsigned int rcvBufSize = 0);
		/**
			Закрывает сервер. Сервер больше не будет прослушивать порт на предмет входящих соединений
		*/		
		void Close();
		/**
			Возвращает последнее сообщение об ошибке
			\return Сообщение об ошибке
		*/
		std::string ErrorString() const;
		/**
			Проверяет, есть ли новые подключения
			\return Возвращает true, если есть новые подключения, ожидающие обработки
		*/		
		bool HasPendingConnections();
		/**
			Возвращает указатель на объект чтения/записи в сокет для ожидающего подключения клиента.
			Функция блокирующая. Перед вызовом этой функции, необходимо убедиться в присутствии клиентов, ожидающих подключения
			с помощью функции HasPendingConnections().
			Объекты NetworkStream удаляются автоматически при закрытии сервера			
		*/		
		NetworkStream* NextPendingConnection();
		/**
			Задает максимальное количество подключаемых клиентов
		*/		
		void SetMaxPendingConnections(unsigned int numConnections);
		/**
			Закрывает сокет, без закрытия самого сервера.
			\param[in] socketId Дескриптор сокета. Может быть получен с помощью функции SocketId() класса NetworkStream
		*/		
		void CloseSocket(DEF_SOCKET socketId);
	private:
		std::string _error;
		unsigned int _maxPendingConnections;
		bool _listening;
		DEF_SOCKET _socketId;
		std::vector<NetworkStream*> _networkStreamList;
	};
}
