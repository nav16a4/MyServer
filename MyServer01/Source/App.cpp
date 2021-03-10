#include "Precompiled.h"
#include "DefaultValue.h"
#include "App.h"
#include "Util/Log.h"
#include "Util/String.h"
//#include "Network/NetworkConnecter.h"
#include "Network/NetworkBuilder.h"
#include "Network/Socket.h"
#include "ExternalLibrary/fmt/core.h"
#include "Network/IOCP.h"
#include "Network/ClientIDmanager.h"
#include "Network/MyOverlappedex.h"
#include "Packet/PacketProcess.h"
#include "Packet/PacketAssembler.h"
#include "Packet/PacketExtractor.h"
#include "Util/Ringbuffer01.h"
#include "Game/Game.h"
My::ServerApp::ServerApp()
{
	Initialize();
}

My::ServerApp::~ServerApp()
{
}

void My::ServerApp::Initialize()
{
	std::string logfilename = My::GetCurrTimeString().append(".txt");
	std::ofstream logfile(logfilename.c_str());
	//My::LogStream logstream(&std::cout, &logfile);
	//auto logstream = LogStream::GetInstance(&std::cout, &logfile);
	auto logstream = LogStream::GetInstance(&std::cout, &logfile);

	//My::LogStream DummylogStream;
	My::DefaultValue defined;
	
	My::IOCPSocket socket;
	socket.SetSockType(SOCK_STREAM);
	socket.SetSocketAddress(nullptr, 44004, AF_INET);

	std::vector<std::thread> workerthreads;
	std::thread acceptthread;
	
	My::IOCPbuilder iocpbuilder(&socket);
	iocpbuilder.SetLog(logstream);
	iocpbuilder.SetAcceptThread(&acceptthread);
	iocpbuilder.SetWorkerThread(&workerthreads,16);
	IOCP* iocpserver = iocpbuilder.Build();
	
	const int maxclient = My::DefaultValue::MaxClientCount();
	std::array<My::Util::RingBuffer ,maxclient>* ringbuffer = new std::array<My::Util::RingBuffer,maxclient> ;

	
	PacketAssembler* packetassembler = new PacketAssembler(ringbuffer);
	PacketProcess* recvpacketprocesser = new PacketProcess();
	PacketProcess* sendpacketprocesser = new PacketProcess();
	
	
	Game* game = new Game;
	
	iocpserver->Subscribe(packetassembler);
	packetassembler->Subscribe(recvpacketprocesser);
	recvpacketprocesser->Subscribe(game);




	
	
	for(auto& iter : workerthreads)
	{
		iter.join();
	}
	acceptthread.join();
	
}

void My::ServerApp::Run()
{
}
