#pragma once
#include "Game/GameObject.h"

namespace My
{
	class Lobby : public My::Object
	{
	protected:
		friend class Game;
		Lobby(IDType);
		~Lobby();
		void Chat(std::string&) override;
	};
}