#pragma once
#include <mutex>
#include "Util/Ringbuffer.h"
#include "DefaultValue.h"

namespace My
{
	class ClientIDmanager final
	{
	public:
		
		
		
		ClientIDmanager();
		~ClientIDmanager() = default;
	private:
		ClientIDmanager(const ClientIDmanager& n) = delete;
		ClientIDmanager(const ClientIDmanager&& n) = delete;
		ClientIDmanager& operator=(const ClientIDmanager& n) = delete;
		ClientIDmanager& operator=(const ClientIDmanager&& n) = delete;

		void Initialize(void);

	public:
		using IDType = My::ClientIDType;
	private:
		static const int m_maxclientcount = My::DefaultValue::MaxClientCount();
		
		My::RingBuffer<IDType, m_maxclientcount> m_idbuffer;
		std::mutex m_mutex;

		constexpr int CheckMaxsize(int size);
	public:
		std::optional<IDType> Acquire(void);
		bool Release(IDType id);
	};

}