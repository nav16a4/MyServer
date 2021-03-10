#include "Precompiled.h"
#include "Socket.h"

void My::IOCPSocket::SetSocketAddress(const char* ip, unsigned short port,int addressfamily)
{
	m_adressfamily = addressfamily;
	
	m_socketaddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	m_socketaddr.sin_port = ::htons(port);
	m_socketaddr.sin_family = m_adressfamily;

	return;
}

//example : SOCK_STREAM
void My::IOCPSocket::SetSockType(int value)
{
	m_sockettype = value;
}

void My::IOCPSocket::SetListenbacklog(int value)
{
	m_listenbacklog = value;
}

bool My::IOCPSocket::IsAllSet()
{
	return (0 != m_wsaversion) &&
		(0 != m_sockettype) &&
		(0 != m_adressfamily) &&
		(0 != m_listenbacklog);
	
}
