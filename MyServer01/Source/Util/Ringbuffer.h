#pragma once
#include <array>
#include <optional>
#include <mutex>
namespace My
{


	template <class T, int MAX>
	class RingBuffer
	{
		const static int arraySize = MAX;
		std::array<T, arraySize> m_buffer;
		int m_readPos = 0;
		int m_WritePos = 0;
		std::mutex m_mutex;
		//ó�� ���������ǰ� ����Ʈ�����ǿ� ���� ó���� ��ü�� �߰��ϴ°��� ��ȿ�����ΰ� ������ ���� ���� ����
		int m_count = 0;
	public:
		RingBuffer() { Initialize(); }
		~RingBuffer() = default;
	protected:
	private:
		void Initialize()
		{
			for (int i = 0; i < arraySize; ++i)
			{
				m_buffer[i] = T();
			}
		}
	public:
		std::optional<T> Pull()
		{
			T returnvalue = T();
			{
				std::lock_guard<std::mutex> lockguard(m_mutex);
				if (0 < m_count)
				{
					--m_count;
					returnvalue = m_buffer[m_readPos];
					m_buffer[m_readPos] = T();
					m_readPos = (m_readPos + 1) % arraySize;
				}
				else
				{
					return std::nullopt;
				}
			}
			return returnvalue;
		}
		bool Push(T object)
		{
			{
				std::lock_guard<std::mutex> lockguard(m_mutex);
				if (m_count < (MAX))
				{
					//assert(m_buffer[m_WritePos] == T());
					++m_count;
					m_buffer[m_WritePos] = object;
					m_WritePos = (m_WritePos + 1) % arraySize;
					return true;
				}
				else
				{
					return false;
				}
			}

		}
	protected:
	private:
	};
}