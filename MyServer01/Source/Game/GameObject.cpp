#include "Precompiled.h"
#include "GameObject.h"

My::Object::Object(IDType id) : m_id(id)
{
	
	
}

My::Object::~Object()
{

	if(nullptr!=m_parent)
	{
		//자식이 있으면 모두 부모에게 전달해준다.
		
		
	}

	
	
}

void My::Object::Add(Object* obj)
{
	std::lock_guard<std::shared_mutex> lockguard(m_mutex);
	m_child.push_back(obj);
}

void My::Object::Move(Object*)
{


	
}

void My::Object::Delete(Object* obj)
{
	std::lock_guard<std::shared_mutex> lockguard(m_mutex);
}

void My::Object::Delete()
{
}

void My::Object::Chat(std::string& str)
{
	std::cout << "ServerObject : " << m_id << " : " << str << std::endl;
}

std::vector<My::Object*> My::Object::GetChild()
{
	std::vector<My::Object*> v;
	{
		std::shared_lock<std::shared_mutex> lockguard(m_mutex);
		v = m_child;
	}
	return v;
}

My::Object* My::Object::GetParent()
{
	std::shared_lock<std::shared_mutex> lockguard(m_mutex);
	return m_parent;
}


