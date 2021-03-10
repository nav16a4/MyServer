#pragma once
#include "GameObject.h"
class Room : public My::Object
{
	friend class Room;
	Room(IDType);
	~Room();
	void Chat(std::string&) override;
	
};

