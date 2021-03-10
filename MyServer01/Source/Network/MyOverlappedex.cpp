#include "Precompiled.h"
#include "MyOverlappedex.h"

int staticID = 0;

My::Overlapped::Overlapped(SOCKET& sock) : m_id(-1)
{
	Initialize(sock);
}

My::Overlapped::Overlapped(void) : m_id(staticID++)
{
	Initialize();
}

My::Overlapped::~Overlapped()
{
}

int My::Overlapped::Recv()
{
	operation = My::OPERATION::OP_RECV;
	wsabuf.buf = reinterpret_cast<char*>(buffer);
	wsabuf.len = m_buffersize;

	DWORD flag = 0;
	int wsarecv_result = 0;
	wsarecv_result = ::WSARecv(
		this->m_socket,
		&this->wsabuf,
		1,
		NULL,
		&flag,
		&this->overlapped,
		NULL
	);
	if(0 != wsarecv_result)
	{
		int error = ::WSAGetLastError();
		if (WSA_IO_PENDING != error)
		{
			throw error;
		}
	}
	return wsarecv_result;
}

int My::Overlapped::Send(const char* packet, const int size)
{
	operation = My::OPERATION::OP_SEND;
	memcpy_s(buffer, size, packet, size);
	wsabuf.buf = reinterpret_cast<char*>(buffer);
	wsabuf.len = size;

	int result = 0;

	if (m_buffersize < size)
	{
		std::string s;
		s.append( std::to_string(m_id));
		s.append("Overlapped Overflow");
		s.append(std::to_string(m_buffersize));
		s.append("/");
		s.append(std::to_string(size));
		s.append("\n");
		throw s.data();
	}

	result = ::WSASend(
		m_socket,
		&wsabuf,
		1,
		NULL,
		0,
		&overlapped,
		NULL
	);
	if(0!=result)
	{
		int error = ::WSAGetLastError();
		if(WSA_IO_PENDING!=error)
		{
			throw error;
		}
	}
	
	return result;
}

int My::Overlapped::CloseSocket(void)
{
	int result = 0;
	result = ::closesocket(m_socket);
	this->Initialize();
	return result;
}

void My::Overlapped::Initialize(void)
{
	memset(&overlapped, 0, sizeof(overlapped));
	memset(&wsabuf, 0, sizeof(wsabuf));
	memset(&operation, 0, sizeof(operation));
	memset(buffer, 0, sizeof(buffer));
	memset(&m_socket, 0, sizeof(m_socket));
}

void My::Overlapped::Initialize(SOCKET socket)
{
	Initialize();
	m_socket = socket;
}

My::OverlappedManager::OverlappedManager() : m_overlapped{}
{
	
}

OVERLAPPED* My::OverlappedManager::operator()(int id)
{
	return &m_overlapped.at(id).overlapped;
}

void My::OverlappedManager::operator()(int id, SOCKET sock)
{
	m_overlapped.at(id).Initialize(sock);
}

void My::OverlappedManager::Recv(int id)
{
	
	m_overlapped.at(id).Recv();
}

void My::OverlappedManager::Send(const int id, const char* packet, const int size)
{
	m_overlapped.at(id).Send(packet, size);
}

void My::OverlappedManager::Close(int id)
{
	m_overlapped.at(id).CloseSocket();
}

