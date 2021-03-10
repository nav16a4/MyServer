#pragma once


namespace My
{
	class Network 
	{
	private:
		constexpr int WSAStartupSuccess() { return 0; }

	public:
		Network(std::string ip, unsigned short port);
	protected:
	private:
		
	public:
	protected:
	private:
		std::string m_ipaddress;
		unsigned short m_portnumber;
		SOCKET m_socket;
		WSADATA m_wsa;
		int m_highversion;
		int m_lowversion;
		int m_sockstream;
		int m_adressfamily;
	public:
		bool WSAstartup(WSADATA& wsa,int hign,int low);
		WSADATA& GetWSA() { return m_wsa; }
		WORD GetWinSockversion() { return  MAKEWORD(m_highversion, m_lowversion); }
		int GetStream() { return m_sockstream; }
		int GetProtocol() { return m_adressfamily; }
	protected:
	private:
	
		
	};
	class Socket
	{
	private:
		std::string m_ipaddress;
		unsigned short m_port;
		SOCKET m_socket;
		WSADATA m_wsa;
		WORD m_wsaversion = MAKEWORD(2, 2);
		int m_socketstream;
		int m_adressfamily;
		int m_listenbacklog = SOMAXCONN;
		SOCKADDR_IN sockaddr;
	public:
		void SetIPaddress(std::string& address);
		void SetPortNumber(unsigned short port);
		void SetAddressFamily(int address_family);
		
	};
}