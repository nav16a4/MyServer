#include "Precompiled.h"
#include "Network.h"

My::Network::Network(std::string ip, unsigned short port)
{
	
}

bool My::Network::WSAstartup(WSADATA& wsa, int high, int low)
{
	bool returnvalue = false;
	WSADATA& wsadata = wsa;
	int wsaresult = 0;
	wsaresult = ::WSAStartup(MAKEWORD(high,low),&wsadata);

	if(WSAStartupSuccess()==wsaresult)
	{
		returnvalue = true;
	}
	else
	{
		returnvalue = false;
	}
	return returnvalue;	
}
