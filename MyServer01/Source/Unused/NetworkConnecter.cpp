#include "Precompiled.h"
#include "NetworkConnecter.h"
#include "DefaultValue.h"
#include "Util/Log.h"
My::IOCPbuilder::Builder::Builder(My::DefaultValue* value, My::Network* net) : threadcount(value->IOCPThreadCount()) , network(net) 
{
	
}

void My::IOCPbuilder::Builder::Set(std::vector<std::thread*>* thread)
{
	iocpthreads = thread;
}

void My::IOCPbuilder::Builder::Set(std::thread* thread)
{
	acceptthread = thread;
}

void My::IOCPbuilder::Builder::Set(std::function<void(char*)> func)
{
	packetprocess = func;
}


void My::IOCPbuilder::Builder::Set(My::LogStream* log)
{
	logstream = log;
}

//void My::IOCPbuilder::Builder::Set(HANDLE _handle)
//{
//	handle = _handle;
//}

My::IOCPbuilder My::IOCPbuilder::Builder::Build()
{
	return IOCPbuilder(*network,*iocpthreads,*acceptthread,packetprocess,threadcount,*logstream/*,handle*/);
}

My::IOCPbuilder::IOCPbuilder(My::Network& net, std::vector<std::thread*>& iocpthreads, std::thread& acceptthread, std::function<void(char*)>& packetfunc, size_t threadcount, My::LogStream& log/*, HANDLE& handle*/) :				m_threadcount(threadcount),
	m_acceptthread(acceptthread),
	m_iocpthreads(iocpthreads),
	packetprocess(packetfunc),
	m_logstream(log),
	m_network(net)/*,
	m_handle(handle)*/
{
	
}

My::IOCP* My::IOCPbuilder::operator=(Network& network)
{






	
	return nullptr;
}
