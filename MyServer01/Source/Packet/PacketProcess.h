#pragma once
#include <vector>
#include <functional>
#include "DesignPattern/Observer.h"
#include "Network/MyOverlappedex.h"
//#include <Packet/Packet.h>

//����� ��ȯ, �Ϻ�ȣȭ���� �ϴ� ��
//�ʿ��� �Լ��� �ܺο��� ����� ����Ѵ�.

namespace My {
	class Packet;
	class PacketProcess :public Observer<My::Packet,const unsigned long long> , public Observable<My::Packet, const unsigned long long>
	{
	public:
		PacketProcess() = default;
		~PacketProcess() = default;
		std::vector < std::function<void(Packet&)>> m_function;
		
		void ConvertPacket(Packet&,const unsigned long long  );
		void PacketFunction(Packet& packet,const unsigned long long);
		void ResisterFunc(std::function<void(Packet&) > func);
		
	private:
		virtual  void Update( My::Packet& packet,  const unsigned long long id);


	};

}