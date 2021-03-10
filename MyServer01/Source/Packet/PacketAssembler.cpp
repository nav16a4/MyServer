#include "Precompiled.h"
#include "PacketAssembler.h"
#include <algorithm>
#include "Util/Ringbuffer01.h"
#include "ExternalLibrary/fmt/core.h"
My::PacketAssembler::PacketAssembler(std::array<My::Util::RingBuffer, m_max>* ringbuffer):	m_ringbuffer(*ringbuffer)
{
}

void My::PacketAssembler::Update(My::Overlapped& overlapped, const unsigned long long id, const int size)
{
	static const size_t maxpacketsize = My::DefaultValue::OverlappedBufferSize();
	char packet[maxpacketsize] = "\0,";
	My::Util::RingBuffer& buffer = m_ringbuffer[id];
	const char* ptr = overlapped.buffer;
	
	buffer.Push(ptr,size);
	size_t result = buffer.Pull(packet, sizeof(packet));
	if (0 < result)
	{
		Packet pck(packet);
		Notify(pck, id);
		/*
		std::cout << fmt::format("ID: {} Packet size : {} \n",id,result);

		if(packet[1]==0)
		{
			std::cout << fmt::format("Size:{},Type:{},Message:{}", (int)packet[0], (int)packet[1], packet + 2);
		}*/
		
	}
	
	
}
