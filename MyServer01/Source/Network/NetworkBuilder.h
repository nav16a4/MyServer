#pragma once
#include <vector>
#include <thread>
#include <functional>
#include "Socket.h"
namespace My
{
	class LogStream;
	class Socket;
	class IOCP;
	class ClientIDmanager;
	class OverlappedManager;
	class PacketProcess;
	
	class IOCPbuilder //: public NetworkBuilder
	{
		IOCPSocket* m_socket = nullptr;
		std::vector<std::thread>* m_workerthreads=nullptr;
		size_t m_workerthreadcount;
		std::thread* m_acceptThread=nullptr;
		LogStream* m_logstream=nullptr;
		/*ClientIDmanager* m_idmanager=nullptr;
		OverlappedManager* m_overlapped=nullptr;
		PacketProcess* m_packetprocess=nullptr;*/
		
	public:
		IOCPbuilder(IOCPSocket* socket);
		void SetAcceptThread(std::thread* accept);
		void SetWorkerThread(std::vector<std::thread>* 
			worker,int count);
		void SetLog(LogStream* logstream);
	/*	void SetClientIDmanager(ClientIDmanager* manager);
		void SetOverlappedManager(OverlappedManager* manager);
		void SetPacketProcess(PacketProcess* manager);*/
		
		IOCP* Build(void);

	public:
		std::string GetErrorMessage(int error);
		void WSAStartUp(WSADATA& wsadata, WORD wsavirsion);
		void Socket(SOCKET& sock,int af ,int at);
		void Bind(SOCKET& sock, SOCKADDR_IN&);
		void Listen(SOCKET& sock,const int backlog);
		void CreateIOCPport( std::function<void(IOCP*,const int,const HANDLE)>,std::vector<std::thread>& worker, int size,IOCP*,HANDLE&);
		void Accept(std::function<void(IOCP*,SOCKET socket)> acceptfunc,std::thread& acceptthread,IOCP*,SOCKET socket);
	};
}
