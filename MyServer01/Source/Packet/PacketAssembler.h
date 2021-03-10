#pragma once
#include <array>
#include "Packet.h"
#include "DesignPattern/Observer.h"
#include "Network/MyOverlappedex.h"
#include "Util/Ringbuffer01.h"

namespace My {
	class PacketAssembler : public Observer<My::Overlapped,const unsigned long long ,const int >, public Observable<My::Packet,const unsigned long long>
	{static const int m_max = My::DefaultValue::MaxClientCount();
	public:
		PacketAssembler(std::array<My::Util::RingBuffer, m_max>* ringbuffer);
	protected:
	private:

	public:
	protected:
	private:
		
		std::array<My::Util::RingBuffer, m_max>& m_ringbuffer;


	public:
	protected:
	private:
		virtual  void Update(My::Overlapped& overlapped, const unsigned long long id, const int size) ;

	};
}

