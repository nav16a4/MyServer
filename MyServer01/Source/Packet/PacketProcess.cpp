#include "Precompiled.h"
#include "PacketProcess.h"
#include "Packet/Packet.h"
void My::PacketProcess::ConvertPacket( Packet& buffer ,unsigned long long client)
{
	const auto target = client;
	My::Packet packet(buffer);

	for (auto iter : m_function)
	{
		iter(packet);
	}
	PacketFunction( packet,target);
	
}

void My::PacketProcess::Update(My::Packet& packet, const unsigned long long id)
{
	//PacketProcess(id, packet);
	ConvertPacket( packet ,id);
}

void My::PacketProcess::PacketFunction( Packet& packet,unsigned long long client)
{
	/*size_t size = packet.GetSize();
	int type = packet.GetType();*/

	Notify( packet, client);
	
	
	
}

void My::PacketProcess::ResisterFunc(std::function<void(Packet&)> func)

{
	m_function.push_back(func);
}
