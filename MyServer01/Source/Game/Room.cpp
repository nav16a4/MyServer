#include "Precompiled.h"
#include "Room.h"

Room::Room(IDType id) : Object(id)
{
	std::cout << "Room : " << m_id << " : " << "»ý¼º" << std::endl;
}

Room::~Room()
{
}

void Room::Chat(std::string& str)
{
	std::cout << "Room : " << m_id << " : " << str << std::endl;
}
