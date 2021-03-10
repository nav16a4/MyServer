#pragma once
#include "Network.h"
#include <array>
#include <thread>
#include <vector>
#include <functional>
namespace My
{
	class DefaultValue;
	class LogStream;
	class IOCP;
}

namespace My
{
	class NetworkConnecter
	{
		
	public:
		NetworkConnecter(My::Network& net);
		virtual ~NetworkConnecter();
	protected:
		NetworkConnecter() = default;
		My::Network& m_network;
		const LogStream& logstream;
		const std::function<void(char*)> packetprocess;
	private:
	public:
	protected:

	private:

	};

	class IOCPbuilder// : public NetworkConnecter
	{
	public:
		static class Builder
		{
		private:
			HANDLE handle;
			size_t threadcount;
			 std::thread* acceptthread = nullptr;
			 std::vector<std::thread*>*iocpthreads=nullptr;
			std::function<void(char*)> packetprocess=nullptr;
			My::Network* network = nullptr;
			My::LogStream* logstream = nullptr;
		public:
			Builder(My::DefaultValue* value,My::Network* net);
			void Set(std::vector<std::thread*>* iocpthreads);
			void Set(std::thread* acceptthread);
			void Set(std::function<void(char*)> func);
			void Set(My::LogStream* log);
			//void Set(HANDLE _handle);
			IOCPbuilder Build();
		};
		//===============Initialize======================
	public:
		IOCPbuilder(
			My::Network& net,
			std::vector<std::thread*>& iocpthreads,
			std::thread& acceptthread,
			std::function<void(char*)>& packetfunc,
			size_t threadcount,
			My::LogStream& log/*,
			HANDLE& _handle*/
		);
		IOCPbuilder(const IOCPbuilder&) = delete;
		IOCPbuilder()=default;
		//IOCPbuilder operator=(const IOCPbuilder&&) = default;
		//IOCPbuilder operator=(const IOCPbuilder&) = delete;

	protected:
	private:
		//===============Member_Variable======================
	public:
	protected:
		//const HANDLE& m_handle;
		const size_t m_threadcount;
		const std::thread& m_acceptthread;
		 std::vector<std::thread*>& m_iocpthreads;
		const std::function<void(char*)> packetprocess;
		My::Network& m_network;
		const My::LogStream& m_logstream;
	private:
		//===============Member_Funtion======================
	public:
		IOCP* operator=(Network& network);
	protected:
		bool CreateIOCPort();
		bool WSAStartUP(SOCKET& sock);
		bool Socket(SOCKET& sock);
		bool Bind(SOCKET& sock, std::string& ip, unsigned short port);
		bool Listen(SOCKET& sock);
		bool Accept(SOCKET& sock, std::thread* thread);
	private:


	};
}