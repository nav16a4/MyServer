#ifndef IOCP_H
#define IOCP_H
#include <optional>
//#include "Network/Network.h"

#include "DesignPattern/Singleton.h"
#include "DesignPattern/Observer.h"
#include "Network/Socket.h"
#include "MyOverlappedex.h"
#include "Util/Log.h"

namespace My {

	enum class IOCP_OP : char
	{
		OP_Send,
		OP_Recv
	};
	class ClientIDmanager;
	class OverlappedManager;
	class PacketProcess;
	class IOCPbuilder;
	class IOCP : public Singleton<IOCP> , public Observable<My::Overlapped,const unsigned long long, const int>
	{
		friend class IOCPbuilder;
		//ก่=================Builder================
	public:
		IOCP(My::LogStream* ls, SOCKET* sock, HANDLE* handle);
	/*	IOCP(My::LogStream* ls, SOCKET* sock, HANDLE* handle, ClientIDmanager* clientidmanager,
			OverlappedManager* overlappedmanager,
			PacketProcess* packetprocess);*/
		~IOCP();
		private:
		
		//===============Initialize======================
	public:
	protected:
	private:
		//===============memberVariable======================
	public:
	protected:
	private:
		My::LogStream& m_logstream;
		SOCKET& m_socket;
		HANDLE& m_handle;
		bool m_isserverrunning=false;

		ClientIDmanager* m_idmanager;
		OverlappedManager* m_overlapped;
		PacketProcess* m_packetprocess;

		/*ClientIDmanager& m_idmanager;
		OverlappedManager& m_overlapped;
		PacketProcess& m_packetprocess;*/
		
		
		//===============MemberFuntion======================
	public:
	protected:
	private:
		void Accept(SOCKET);
		void WorkerThread(const int, HANDLE);
		HANDLE CreateIOCPport(HANDLE serverhandle, const int id, HANDLE clienthandle);
		char* GetErrorMessage(const int size,char* charptr,int error);

		std::optional<int> GetClientID();
		void ReleaseClientID(int id);
		
		void Recv(int id);
		void Send(int id,char* ptr, int n);
		void NewClientProcess(SOCKET& sock);
		void DelClientProcess(int id);
	};
}

#endif