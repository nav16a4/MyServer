#pragma once
#include "DefaultValue.h"
namespace My {
	class OverlappedManager;
	
	typedef enum class Operation
	{
		OP_RECV,
		OP_SEND
	} OPERATION;
	struct Overlapped
	{
	public:
		
		OVERLAPPED overlapped;
		WSABUF wsabuf;
		My::OPERATION operation;
		SOCKET m_socket;
		const int m_id;
		static const int m_buffersize = My::DefaultValue::OverlappedBufferSize();
		char buffer[m_buffersize];
		std::mutex m_mutex;
	public:
		Overlapped(SOCKET& sock);
		~Overlapped();
		int Recv();
		int Send(const char* packet, const int size);
		int CloseSocket(void);
		void Initialize(SOCKET socket);
	private:
		friend class OverlappedManager;
		Overlapped(void);
		void Initialize(void);
	};


	class OverlappedManager
	{
	private:
		static const int m_maxcount = My::DefaultValue::MaxClientCount();
		std::array<Overlapped, m_maxcount> m_overlapped;
	public:
		OverlappedManager();
		OVERLAPPED* operator()(int id);
		void operator()(int n,SOCKET sock);
		void Recv(int id);
		void Send(const int id, const char* packet, const int size);
		void Close(int id);
	};
}
