#include "Precompiled.h"
#include "Lobby.h"

My::Lobby::Lobby(IDType id) : Object(id)
{
	std::cout << "Lobby : " << m_id << " : " << "»ý¼º" << std::endl;
}

My::Lobby::~Lobby()
{
}

void My::Lobby::Chat(std::string& str)
{
	std::cout << "Lobby : "<< m_id << " : " << str << std::endl;
	
}
