#include "Precompiled.h"
#include "Player.h"

My::Player::Player(IDType id) : Object(id)
{
	std::cout << "Player : " << m_id << " : " << "»ý¼º" << std::endl;
}

My::Player::~Player()
{
}

void My::Player::Chat(std::string& str)
{
	std::cout << "Player : " << m_id << " : " << str << std::endl;
}
