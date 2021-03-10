#include "Precompiled.h"
#include "ClientIDmanager.h"

using IDType = My::ClientIDmanager::IDType;

constexpr int My::ClientIDmanager::CheckMaxsize(int size)
{
	int returnvalue = 1;
	for(int i=0;i<size*8;++i)
	{
		returnvalue *= 2;
	}
	return returnvalue;
}

My::ClientIDmanager::ClientIDmanager()
{
	IDType test = 0;

	
	
	[&](const int max)
	{
		if(CheckMaxsize(sizeof(IDType)) <m_maxclientcount)
		{
			std::string str;
			str.append(std::to_string(sizeof(IDType)));
			str.append("bytes 데이터로는 최대 클라이언트 수 표현 못 함\n");
			throw str.data();
		}
		else
		{
			return;
		}
	}(m_maxclientcount);

	
	std::lock_guard<std::mutex> lockguard(m_mutex);
	for (int i = 0; i < m_maxclientcount; ++i)
	{
		m_idbuffer.Push(i);
	}
}
std::optional<IDType> My::ClientIDmanager::Acquire(void)
{
	std::lock_guard<std::mutex> lockguard(m_mutex);
	auto id = m_idbuffer.Pull();
	return id;
}

bool My::ClientIDmanager::Release(IDType id)
{
	std::lock_guard<std::mutex> lockguard(m_mutex);
	bool returnvalue = m_idbuffer.Push(id);
	return returnvalue;
}
