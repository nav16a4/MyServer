#pragma once
#include <any>
#include <vector>
#include "Packet/Packet.h"
#include "DesignPattern/Observer.h"
#include <functional>
#include <iostream>
#include <map>
#include "Game/GameObject.h"
#include "Util/MyFunction.h"
#include "Packet/PacketExtractor.h"
#include "DefaultValue.h"
//Object 게임 오브젝트에 필요한 기능 구현
//Game 게임에서 사용하는 기능을 Object 멤버 함수로 구현
//TaskManager 역할이 바뀌면서 이름도 바꿔야하는데...지금은 패킷에서 데이터 뽑아 함수로 넘겨주는 역할


namespace My {
	class Game : //public Observer<My::Packet, const unsigned long long>
		public Observer<My::Packet, const unsigned long long>
	{
	public:
		//==========================

		
		std::array<My::Object*, My::DefaultValue::MaxClientCount()> m_players={nullptr,};
		
		Game();
		~Game();
		void Initialize();
		void InitFunc();
		void Test();
		void Chat(int ,std::string);
		void Login(int );
		void Logout(int);                      
		std::vector<My::Object*> m_gameObjects;
		Object* m_rootGameObj = nullptr;
		//===========================
		My::PacketExtractor<int>* m_function;
		template <class T>
		void ResistFunction(const int num, T t )
		{
			auto func = std::bind([this](T t, std::vector<std::any> arg)
				{
					Execute(t, arg);
				}, t, std::placeholders::_1);
			My::Object::m_funcion[num] = func;
		}

		void Update(std::vector<std::any>& value, const int tasktype, const unsigned long long client);

		template < class... Args >
		std::any Excute(std::function<void(Args...)> func, Args... args)
		{
			function(args...);
			return;
		}
		
		template < class... Args >
		void Excute(std::any& func, std::function<void(Args...)>, Args... args)
		{
			auto function = std::any_cast<std::function<void(Args...)>>(func);
			function(args...);
			return;
		}
		template <class R, class... Args >
		R Excute(std::any& func,std::function<R(Args...)>,Args... args)
		{
			auto function = std::any_cast<std::function<R(Args...)>>(func);
			return function(args...);
		}
	virtual void Update(Packet& source, const unsigned long long) override;

	};
	
}
