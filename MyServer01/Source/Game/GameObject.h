#pragma once
#include <any>
#include <array>
#include <functional>
#include <shared_mutex>
namespace My {
	using ObjectFunction = std::function<void(std::vector<std::any>)>;

	class Game;
	class Object
	{
	protected:
		using IDType = unsigned long long;
		friend class Game;
		const IDType m_id;
		
		std::shared_mutex m_mutex;

		Object* m_parent = nullptr;
		//Object* m_child = nullptr;
		std::vector<Object*> m_child;
		
		Object() = delete;
		Object(IDType id);
		~Object();
		
		virtual void Add(Object*);
		virtual void Move(Object*);
		virtual void Delete(Object*);
		virtual void Delete();
		//virtual void Update() = 0;
		virtual void Chat(std::string&);
		std::vector<Object*> GetChild();
		Object* GetParent();
		
	};




}
