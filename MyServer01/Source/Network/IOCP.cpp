#include "Precompiled.h"
#include "Protocol.h"

#include "ClientIDmanager.h"

#include "IOCP.h"

#include "Packet/PacketProcess.h"


#include "DesignPattern/MayBe.h"
#include "ExternalLibrary/fmt/core.h"




//My::IOCP::IOCP(
//	My::LogStream* ls,
//	SOCKET* sock,
//	HANDLE* handle,
//	ClientIDmanager* clientidmanager,
//	OverlappedManager* overlappedmanager,
//	PacketProcess* packetprocess
//) :
//	m_logstream(*ls),
//	m_socket(*sock),
//	m_handle(*handle),
//	m_idmanager(*clientidmanager),
//	m_overlapped(*overlappedmanager),
//	m_packetprocess(*packetprocess)
//{
//	m_isserverrunning = true;
//
//}
My::IOCP::IOCP(
	My::LogStream* ls,
	SOCKET* sock,
	HANDLE* handle
) :
	m_logstream(*ls),
	m_socket(*sock),
	m_handle(*handle)
	
{
	m_isserverrunning = true;
	 
	m_overlapped = new My::OverlappedManager;
	m_idmanager = new My::ClientIDmanager;
	m_packetprocess = new My::PacketProcess;

}

My::IOCP::~IOCP()
{
	delete m_overlapped;
	delete m_idmanager;
	delete m_packetprocess;
}

std::optional<int> My::IOCP::GetClientID()
{
	return m_idmanager->Acquire();
}

void My::IOCP::ReleaseClientID(int id)
{
	m_idmanager->Release(id);
}




void My::IOCP::Accept(SOCKET sock)
{
	const SOCKET acceptfail = INVALID_SOCKET;
	
	SOCKET serversocket = sock;

	SOCKET clientsocket;
	memset(&clientsocket, 0, sizeof(clientsocket));

	SOCKADDR_IN clientaddr;
	memset(&clientaddr, 0, sizeof(clientaddr));
	SOCKADDR* clientaddrptr = reinterpret_cast<SOCKADDR*>(&clientaddr);
	
	int addrlength = sizeof(clientaddr);
	int result = 0;
	int error = 0;

	char ipstring[16] = "";
	
	while(true==m_isserverrunning)
	{
		clientsocket = ::WSAAccept(serversocket, clientaddrptr, &addrlength,NULL,NULL);

		if(acceptfail==clientsocket)
		{
			error = ::WSAGetLastError();
			if (WSA_IO_PENDING != error)
			{
				std::array<char, 64> message;
				GetErrorMessage(message.size(),message.data(), error);
				message[63] = '\0';

				m_logstream << message.data();
				continue;
			}
		}
		else
		{
			inet_ntop(AF_INET, &clientaddr.sin_addr, ipstring, sizeof(ipstring));
			m_logstream << fmt::format("New Client IP:{} PORT:{}\n",ipstring,ntohs(clientaddr.sin_port) );

			this->NewClientProcess(clientsocket);
		}
	}
}
void My::IOCP::NewClientProcess(SOCKET& sock)
{
	SOCKET& socket = sock;

	auto IDfuncptr = makeClassStdFuntion(&IOCP::GetClientID, this);
	auto IDfunclogger = makelog(m_logstream,IDfuncptr);
	auto createiocpportptr = makeClassStdFuntion(&IOCP::CreateIOCPport, this);
	auto createiocpportlogger = makelog(m_logstream, createiocpportptr);

	IDfunclogger << __MYFUNCNAME(GETClientID());
	auto id = IDfunclogger();
	auto idoper = maybe(id);
	try
	{
		idoper.Do(
			[&](int idvalue)
			{
				m_logstream << fmt::format("{}번 유저 로그인\n", idvalue);
				createiocpportlogger << __MYFUNCNAME(CreateIOCPport());
				createiocpportlogger(m_handle, idvalue, reinterpret_cast<HANDLE>(socket));
				m_overlapped->operator()(idvalue, socket);
				m_overlapped->Recv(idvalue);
			},
			[&](int idvalue)
			{
				const char* message = "  서버 인원 초과";
				Overlapped* overlapped = new Overlapped(socket);
				overlapped->Send(message, strlen(message));
				::closesocket(sock);
			}
			);
	}
	catch(int error)
	{
		char errormessage[256];
		GetErrorMessage(sizeof(errormessage),errormessage, error);
		errormessage[255] = '\0';
		m_logstream << fmt::format("{}번 유저 통신 에러 : {}\n\0", id.value_or(-2), errormessage);
	}
	
}

void My::IOCP::DelClientProcess(int id)
{
	const char* message = "  접속 종료\n";
	m_overlapped->Send(id,message,strlen(message));
	m_overlapped->Close(id);
}



HANDLE My::IOCP::CreateIOCPport(HANDLE serverhandle, const int id, HANDLE clienthandle)
{
	return (::CreateIoCompletionPort(clienthandle, serverhandle, id, 0));
}

char* My::IOCP::GetErrorMessage(const int size,char* ptr,int error)
{
	char* multibyte = ptr;
	
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)lpMsgBuf, -1, multibyte, size, NULL, NULL);

	LocalFree(lpMsgBuf);
	return multibyte;
}



void My::IOCP::WorkerThread(const int number, HANDLE handle)
{
	std::cout << fmt::format("{} {}", number, "WorkerThread Start\n");

#ifdef _WIN64
		unsigned long long key = 0;
		typedef unsigned long long WSAKeyType;
#else
		unsigned long key = 0;
		typedef unsigned long WSAKeyType;
#endif

	DWORD iosize = 0;
	SOCKET clientsock = NULL;
	My::Overlapped* overlapped = nullptr;
	int ioresult = 0;
	LPOVERLAPPED* lpoverlapped = reinterpret_cast<LPOVERLAPPED*>(&overlapped);
	
	while (true == m_isserverrunning)
	{

		ioresult = ::GetQueuedCompletionStatus(handle, &iosize, &key, lpoverlapped, INFINITE);

		if(0==iosize)
		{
			m_logstream << fmt::format("{}번 유저 접속종료\n\0", key);
			m_overlapped->Close(key);
		}
		
		if(0==ioresult)
		{
			
			int error = WSAGetLastError();
			if(64==error)
			{
				m_logstream << fmt::format("{}번 유저 강제접속종료 : {}\n\0", key);
				m_overlapped->Close(key);
				continue;
			}
			char errormessage[256];
			GetErrorMessage(sizeof(errormessage),errormessage, error);
			m_logstream << fmt::format("{}번 유저 통신 에러 : {}\n\0", key, errormessage);
			continue;
		}
	
		switch(overlapped->operation)
		{
		case My::OPERATION::OP_RECV:
			Notify( *overlapped,key, iosize);
			m_overlapped->Recv(key);
			break;
		case My::OPERATION::OP_SEND:
			delete overlapped;
			overlapped = nullptr;
			break;

			default:
				std::cout << "뭔가 문제가 있는데...";
				break;
		}
		
	}
}