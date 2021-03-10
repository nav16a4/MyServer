#pragma once
namespace My
{


	class App
	{
	public:
		App() = default;
		virtual  ~App() = default;
 
	public:
	protected:
		virtual void Initialize() {}
	private:

	public:
		virtual void Run() {}
	protected:
	private:
		
	};

	class ServerApp final :public App
	{
		
		class DefinedInitlizer;
		class Server;
		class Network;
		class LogStream* logstream;
		class LogStream* dummylogstream;

		//class 
		//class Game* game;
	public:
		ServerApp();
		virtual ~ServerApp();
		
		ServerApp(const ServerApp&) = delete;
		ServerApp(const ServerApp&&) = delete;
		ServerApp operator=(const ServerApp&) = delete;
	private:
		virtual void Initialize() override;




	//===================================================
	public:
	protected:
	private:
		DefinedInitlizer* m_definedinitializer;
		

	//=============================================
	public:
		virtual void Run() override;
	private:
		
	};
	class ClientApp final: public App
	{
	public:
	protected:
	private:
		
	};

}