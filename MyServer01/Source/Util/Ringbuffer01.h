#pragma once
#include <mutex>
#include <array>
#include "DefaultValue.h"
namespace My
{
	namespace Util
	{
		struct RingBuffer
		{
			//패킷 헤더 사이즈 길이 달라질때..나중에
			static const int sizesize = 1;
			static const int max = My::DefaultValue::MaxClientCount();
			char buffer[max];
			//std::array<char, max> m_buffer;
			
			unsigned int readPosition = 0;
			unsigned int writePosition = 0;

			unsigned int saved = 0;
			std::mutex mutex;
			

			bool IsPacketMaked() const;
			int GetReadPosition() const { return readPosition; }
			int GetWritePosition() const { return writePosition; }
			int GetMovePosition(int& position, const int movesize)
			{
				return (position + movesize) % max;
			}
			int GetPacketSize()
			{
				if (0 == saved) return 0;
				return static_cast<int>(buffer[readPosition]);
			}
			unsigned int GetSize()
			{
				return saved;
			}
			unsigned int Push(const char* source, unsigned int size);

			unsigned int Pull(char* dest, const int destbuffersize);

		};

		
	}
	

}
