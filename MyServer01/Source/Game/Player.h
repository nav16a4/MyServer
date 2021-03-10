#pragma once
#include "Game/GameObject.h"
namespace My {
	class Player : public My::Object
	{
		friend class Game;
		Player(IDType);
		~Player();
		void Chat(std::string&) override;
	};

}