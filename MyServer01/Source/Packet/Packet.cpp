#include "Precompiled.h"
#include "Packet.h"

int My::Packet::ReadData(char* c)
{
	return 0;
}

int My::Packet::ReadData(char* c, std::string& s)
{
	s.append(c);
    return strlen(c)+1;
}

//int My::Packet::ReadData(char* c, Packet& p)
//{
//	
//	return 0;
//}
