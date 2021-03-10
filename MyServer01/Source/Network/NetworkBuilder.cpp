#include "Precompiled.h"
#include "ExternalLibrary/fmt/core.h"
#include "NetworkBuilder.h"
#include "IOCP.h"
#include "Network/Socket.h"

My::IOCPbuilder::IOCPbuilder(My::IOCPSocket* socket)
{
	m_socket = socket;
}

void My::IOCPbuilder::SetAcceptThread(std::thread* accept)
{
	if (nullptr != accept){
		m_acceptThread = accept;
	}
}

void My::IOCPbuilder::SetWorkerThread(std::vector<std::thread>* worker, int count)
{
	if (nullptr != worker) {
		m_workerthreads = worker;
	}
	if(0<count)
	{
		m_workerthreadcount = count;
	}
}

void My::IOCPbuilder::SetLog(LogStream* logstream)
{
	m_logstream = logstream;
}

std::string My::IOCPbuilder::GetErrorMessage(int error)
{
	LPVOID lpMsgBuf = nullptr;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	char multibyte[64];
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)lpMsgBuf, -1, multibyte, sizeof(multibyte), NULL, NULL);

	std::string str(multibyte);
	LocalFree(lpMsgBuf);

	return str;
}

void My::IOCPbuilder::WSAStartUp(WSADATA& wsadata, WORD wsavirsion)
{
	const int success = 0;

	int result = ::WSAStartup(wsavirsion, &wsadata);
	if (success != result)
	{
		throw result;
	}
	return;
}

void My::IOCPbuilder::Socket(SOCKET& sock, int family, int type)
{
	const SOCKET socketfail = INVALID_SOCKET;
	SOCKET& socket = sock;

	socket = ::WSASocket(family, type, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (socketfail == socket)
	{
		throw WSAGetLastError();
	}
}

void My::IOCPbuilder::Bind(SOCKET& sock, SOCKADDR_IN& sockaddr)
{
	const int bindfail = SOCKET_ERROR;
	SOCKET& socket = sock;
	SOCKADDR_IN& sockaddr_in = sockaddr;
	SOCKADDR* bindaddr = reinterpret_cast<SOCKADDR*>(&sockaddr_in);

	int result = ::bind(socket, bindaddr, sizeof(sockaddr));
	if (bindfail == result)
	{
		throw WSAGetLastError();
	}
	return;
}

void My::IOCPbuilder::Listen(SOCKET& sock, const int backlog)
{
	const int listenfail = SOCKET_ERROR;

	int result = 0;
	SOCKET& socket = sock;
	const int listenbacklog = backlog;

	result = ::listen(socket, listenbacklog);
	if (listenfail == result)
	{
		throw WSAGetLastError();
	}

}
//
//void My::IOCPbuilder::SetClientIDmanager(ClientIDmanager* manager)
//{
//	if (nullptr!=manager)
//	{
//		m_idmanager = manager;
//	}
//}
//
//void My::IOCPbuilder::SetOverlappedManager(OverlappedManager* manager)
//{
//	if (nullptr != manager)
//	{
//		m_overlapped = manager;
//	}
//}
//
//
//void My::IOCPbuilder::SetPacketProcess(PacketProcess* manager)
//{
//	if (nullptr != manager)
//	{
//		m_packetprocess = manager;
//	}
//}

void My::IOCPbuilder::CreateIOCPport(std::function<void(IOCP*, const int, const HANDLE)> func,
	std::vector<std::thread>& worker, int size, IOCP* iocp, HANDLE& handle)
{
	HANDLE iocphandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if(NULL==iocphandle)
	{
		throw  "CreateIoCompletionPort() Failed\n";
	}
	else
	{
		handle = iocphandle;
	}
	for (int i = 0; i < size; ++i)
	{
		worker.push_back(std::thread(func, iocp, i, handle));
	}
}

void My::IOCPbuilder::Accept(std::function<void(IOCP* iocp, SOCKET socket)> acceptfunc, std::thread& acceptthread, IOCP* iocp, SOCKET socket)
{
	acceptthread = std::thread(acceptfunc, iocp, socket);
}


My::IOCP* My::IOCPbuilder::Build()
{
	My::LogStream& log = *m_logstream;

	WSADATA& wsadata = m_socket->m_wsadata;
	SOCKET& socket = m_socket->m_socket;
	HANDLE& handle = m_socket->m_handle;
	SOCKADDR_IN& sockaddr = m_socket->m_socketaddr;
	const WORD wsaversion = m_socket->m_wsaversion;
	const int& socktype = m_socket->m_sockettype;
	const int& addressfamily = m_socket->m_adressfamily;
	const int backlog = m_socket->m_listenbacklog;

	std::vector<std::thread>& workerthreads = *m_workerthreads;
	const size_t workerthreadcount = m_workerthreadcount;
	std::thread& acceptthread = *m_acceptThread;
		My::IOCP* iocp = new IOCP(m_logstream,&socket,&handle);
	//My::IOCP* iocp = new IOCP(m_logstream, &socket, &handle, m_idmanager, m_overlapped, m_packetprocess);
	
	std::function<void(IOCP*, const int, HANDLE)> workerfunc = [](IOCP* iocp, const int count, HANDLE handle)
	{
		return iocp->WorkerThread(count, handle);
	};
	std::function<void(IOCP*,SOCKET)> acceptfunc= [](IOCP* iocp,SOCKET socket)
	{
		return iocp->Accept(socket);
	};
	
	auto wsastartup_ptr = makeClassStdFuntion(&IOCPbuilder::WSAStartUp, this);
	auto createiocpport_ptr = makeClassStdFuntion(&IOCPbuilder::CreateIOCPport, this);
	auto socket_ptr = makeClassStdFuntion(&IOCPbuilder::Socket, this);
	auto bind_ptr = makeClassStdFuntion(&IOCPbuilder::Bind, this);
	auto listen_ptr= makeClassStdFuntion(&IOCPbuilder::Listen, this);

	auto wsastartuplogger = makelog(log,wsastartup_ptr);
	auto createiocpportlogger = makelog(log, createiocpport_ptr);
	auto socketlogger = makelog(log, socket_ptr);
	auto bindlogger = makelog(log, bind_ptr);
	auto listenlogger = makelog(log, listen_ptr);

	
	try 
	{
		wsastartuplogger << __MYFUNCNAME(WSAStartUp());
		wsastartuplogger(wsadata, wsaversion);
		
		createiocpportlogger << __MYFUNCNAME(CreateIOCPport());
		createiocpportlogger(workerfunc, workerthreads, workerthreadcount,iocp,handle);

		socketlogger << __MYFUNCNAME(Socket());
		socketlogger(socket,addressfamily,socktype);

		bindlogger << __MYFUNCNAME(Bind());
		bindlogger(socket,sockaddr);

		listenlogger << __MYFUNCNAME(Listen());
		listenlogger(socket,backlog);
	}
	catch(std::exception& e)
	{
		std::cout << e.what();
	}
	log << fmt::format("{}\n", __MYFUNCNAME(Accetp()));
	this->Accept(acceptfunc,acceptthread,iocp, socket);
	
	return iocp;
}



