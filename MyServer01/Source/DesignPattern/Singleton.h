#ifndef SINGLETON_H
#define SINGLETON_H

template <class Type>
class Singleton
{
public:
protected:
private:
	//=================
public:
protected:
private:
	static Type* m_Instance;
	//================
public:
	template <class... Types>
	static Type* GetInstance(Types... args)
	{
		if (nullptr == m_Instance)
		{
			m_Instance = new Type(args...);
		}
		return m_Instance;
	}
	
	static Type* GetInstance()
	{
		if(nullptr==m_Instance)
		{
			m_Instance = new Type;
		}
		return m_Instance;
	}
	static void ReleaseInstance()
	{
		if(nullptr!=m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
protected:
private:
};

template <class Type>
Type* Singleton<Type>::m_Instance = nullptr;

#endif
