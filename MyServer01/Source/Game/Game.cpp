#include "Precompiled.h"
#include "Game.h"
#include "Util/Log.h"
#include "Game/Player.h"
#include "Game/Lobby.h"
#include "Game/Room.h"
#include "DefaultValue.h"
//void My::Game::Update( My::Packet& source, const unsigned long long id)
//{
//	
//
//	
//	
//}


My::Game::Game()
{
	m_function = new My::PacketExtractor<int>;
	Initialize();
	InitFunc();
}

My::Game::~Game()
{
	if (nullptr!=m_function)
	{
		delete m_function;
		m_function = nullptr;
	}



	
}

void My::Game::Initialize()
{
	m_rootGameObj = new My::Lobby(My::DefaultValue::MaxClientCount()+1);
	
;
}

void My::Game::InitFunc()
{
	m_function->ResisterFunc(0, stdfunction(&Game::Chat, this));
	//ResistFunction(0, My::makeClassStdFuntion(&Game::Chat, this));
	m_function->ResisterFunc(1, stdfunction(&Game::Login, this));
	m_function->ResisterFunc(2, stdfunction(&Game::Logout, this));

	
}

void My::Game::Test()
{
	
}

void My::Game::Chat(int n,std::string str)
{
	std::cout << "from : "<<n<<" - "<<str<<std::endl;
}

void My::Game::Login(int n)
{
	std::cout << "login : " << n << std::endl;
	/*const typename Object::IDType  id= n;
	auto newclient = new My::Player(id);
	m_players[n] = newclient;
	m_rootGameObj->Add(m_players[n]);*/
	
}

void My::Game::Logout(int n)
{
	std::cout << "logout : " << n << std::endl;
	/*const typename Object::IDType id = n;

	m_players[n]->Delete();
	delete m_players[n];
	m_players[n] = nullptr;*/
}

void My::Game::Update(Packet& source, const unsigned long long id)
{
	
	/*if(nullptr == m_players[id])
	{
		m_players[id] = new My::Player(id);
	}*/
	const int type = source.GetType();
	const int target = id;
	(*m_function)[type](target, source);
	

	
}
