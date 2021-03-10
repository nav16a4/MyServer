#pragma once
#include <vector>
#include <shared_mutex>
template <class Type,class... Args>
struct Observer
{
	virtual ~Observer() {}
	virtual  void Update(Type& source,Args...) = 0;
};
template <class Type,class... Args>
struct Observable
{
	
	void Notify(Type& source,Args... args)
	{
		std::shared_lock<std::shared_mutex> lockquard(mutex);
		for (auto iter : observers)
		{
			iter->Update(source, args...);
		}
	}
	void Subscribe(Observer<Type,Args...>* f)
	{
		std::lock_guard<std::shared_mutex> lockquard(mutex);
		observers.push_back(f);
	}
	void Unsubscribe(Observer<Type,Args...>* f)
	{
		std::lock_guard<std::shared_mutex> lockquard(mutex);
		auto iter = std::find(observers.begin(), observers.end(), f);
		if (observers.end()!= iter)
		{
			observers.erase(iter);
		}
	}
private:
	std::vector<Observer<Type,Args...>*> observers;
	std::shared_mutex mutex;
};
