#pragma once
#include <thread>
#include <vector>
namespace My
{
	//class Socket
	//{
	//private:
	//	SOCKADDR_IN m_socketaddr;
	//	SOCKET m_socket;
	//	WORD m_wsaversion = MAKEWORD(2, 2);
	//	int m_sockettype;
	//	int m_adressfamily;
	//	int m_listenbacklog = SOMAXCONN;
	//	
	//public:
	//	virtual void SetSocketAddress(const char* ip, unsigned short port);
	//	void SetAddressFamily(int address_family);
	//	void SetSockType(int value);
	//	void SetListenbacklog(int value);
	//};


	
	class IOCPbuilder;
	class IOCPSocket //final : public Socket
	{
	private:
		friend class My::IOCPbuilder;
		SOCKADDR_IN m_socketaddr;
		SOCKET m_socket;
		WORD m_wsaversion = MAKEWORD(2, 2);
		int m_sockettype=0;
		int m_adressfamily=0;
		int m_listenbacklog = SOMAXCONN;
		WSADATA m_wsadata;
		HANDLE m_handle;
	public:
		IOCPSocket() = default;
		~IOCPSocket() = default;
		IOCPSocket& operator=(const IOCPSocket&) = delete;
		IOCPSocket& operator=(const IOCPSocket&&) = delete;
		IOCPSocket(const IOCPSocket&) = delete;
		
		/*virtual*/ void SetSocketAddress(const char* ip, unsigned short port,int addressfamily);
		
		void SetSockType(int value);
		void SetListenbacklog(int value);
		
		bool IsAllSet(void);
	};
}