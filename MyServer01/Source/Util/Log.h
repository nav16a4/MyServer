#ifndef LOG_H
#define LOG_H
#include <fstream>
#include <functional>
#include <mutex>
#include <string>
#include <typeinfo>
#include "Util/String.h"
#include "DesignPattern/Singleton.h"
namespace My {

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define __MYFUNCNAME__ fmt::format("File:{} Func:{} Line:{}",__FILENAME__,__FUNCTION__,__LINE__)
#define __MYFUNCNAME(name) fmt::format("File:{} Func:{} Line:{} call: {}",__FILENAME__,__FUNCTION__,__LINE__,#name)

	void printvalue(std::stringstream& ss);
	template <class T>
	void printvalue(std::stringstream& ss, T&& t)
	{
		char* ptr = reinterpret_cast<char*>(&t);
		const size_t size = sizeof(T);
		ss << "[";
		ss << typeid(t).name();
		ss << " :";
		ss << size << " bytes :";
		for (int i = 0; i < sizeof(t); ++i)
		{
			ss << std::hex<<std::uppercase<<std::setw(2) << std::setfill('0') <<  (0xff&(static_cast<unsigned char>(*(ptr + i))));
			ss << ".";
		}
		ss << "]";
		return;
	}
	template <class T, int N>
	void printvalue(std::stringstream& ss, const std::array<T, N>& array)
	{

		ss << " array " << N << " \n";
		int i = 0;
		for (auto iter = array.cbegin(); iter < array.cend(); ++iter)
		{
			if (0 == (i) % 16) { ss << i << "\t||"; }
			ss << i % 16 << "[" << (int)*iter << "]";
			if (0 == (++i) % 16) { ss << "\n\n"; }
		}
		return;
	}
	
	template <class T, class... Ts>
	void printvalue(std::stringstream& ss, T&& t, Ts&&... ts)
	{
		printvalue(ss, t);
		printvalue(ss, ts...);
		return;
	}
	
	class LogStream : public Singleton<LogStream>
	{
	protected:
		std::ostream* m_os;
		std::ofstream* m_ofs;
		std::function<void(std::string&)> func = nullptr;

		void LogToConsole(std::string& s);
		void LogToFile(std::string& s);
		void LogToConsoleAndFile(std::string& s);
		void LogNothing(std::string& s);
	public:
		LogStream();
		LogStream(std::ostream* os);
		LogStream(std::ofstream* ofs);
		LogStream(std::ofstream* ofs ,std::ostream* os);
		LogStream(std::ostream* os, std::ofstream* ofs);
		void Write(std::string& s);
		void Write(std::string&& s);
	};
	LogStream& operator<<(LogStream& ls, std::string& s);
	LogStream& operator<<(LogStream& ls, std::string&& s);
	LogStream& operator<<(LogStream& ls, const char* c);

	static void Type(std::stringstream& ss, char ch);
	void Type(std::stringstream& ss, int n);
	void Type(std::stringstream& ss, WSADATA wsadata);


	
	//class MyStringFunc
	//{
	//private:
	//	const std::function<std::string(void)> func;
	//	const std::string str;
	//public:
	//	MyStringFunc(std::function<std::string(void)> str_func) : func(str_func), str(std::string("")) {}
	//	MyStringFunc(std::string const_str) : func(nullptr), str(const_str) {}
	//	MyStringFunc(const char* ch) : func(nullptr), str(std::string(ch)) {}

	//	std::string operator()(void)
	//	{
	//		return func != nullptr ? func() : str;
	//	}
	//};

	template<class ReturnT, class C, class... Args>
	std::function<ReturnT(Args...)> makeClassStdFuntion(
		ReturnT(C::*&& func)(Args...), C*&& c)
	{
		std::function<ReturnT(Args...)> t = [&c, &func](Args&&... args)
		{
			return (*c.*func)(args...);
		};
		return t;
	}
	template< class C, class... Args>
	std::function<void(Args...)> makeClassStdFuntion(
		void (C::*&& func)(Args...), C*&& c)
	{
		std::function<void(Args...)> t = [&c, &func](Args&&... args)
		{
			(*c.*func)(args...);
			return;
		};
		return t;
	}
	
	template <typename ReturnType, typename... Args>
	class Logger 
	{
	public:
		LogStream& m_logstream;
		//std::vector<MyStringFunc> makeString;
		std::function<std::string(void)> m_timestring = GetCurrTimeString;
		std::vector<std::string> makeString;
		std::function<ReturnType(Args ...)> func;

	public:
	private:
	public:
		Logger(LogStream& logstream, std::function<ReturnType(Args...)> func) : func{ func }, m_logstream(logstream)
		{

		}
		Logger(LogStream& logstream, std::function<ReturnType(Args...)> func, std::function<std::string(void)> timestring) : func{ func }, m_logstream(logstream), m_timestring(timestring)
		{

		}
		template <class T>
		Logger& operator<<(T t)
		{
			//PushBackStrFunc(t);
			makeString.push_back(std::string(t));
			return *this;
		}
	private:
	
	public:
		ReturnType operator() (Args... args)
		{
			ReturnType result;
			memset(&result, 0, sizeof(result));
			std::stringstream ss;
			ss.str("");
			ss << m_timestring();

			for (auto& iter : makeString)
			{
				ss << iter;
				ss << " ";
			}
			printvalue(ss, args...);
			ss << " Begin\n";

			m_logstream.Write(ss.str());
			try
			{
				result = func(args...);

				ss.str("");
				ss << m_timestring();

				for (auto& iter : makeString)
				{
					ss << iter;
					ss << " ";
				}
				printvalue(ss, args...);
				ss << "return";
				printvalue(ss, result);
				ss << " End\n";

				m_logstream.Write(ss.str());
				ss.str("");
			}
			catch (std::exception& ex)
			{
				ss.str("");
				ss << m_timestring();

				for (auto& iter : makeString)
				{
					ss << iter;
					ss << " ";
				}
				printvalue(ss, args...);
				ss << " Fail\n";
				m_logstream.Write(ss.str());
			}
			return result;
		};
	};


	template <typename... Args>
	class Logger<void, Args...>
	{
	public:
		LogStream& m_logstream;
		std::function<std::string(void)> m_timestring = GetCurrTimeString;
		std::vector<std::string> makeString;
		std::function<void(Args ...)> func;
	public:

		Logger(LogStream& logstream, std::function<void(Args...)> func) : func{ func }, m_logstream(logstream){	}
		Logger(LogStream& logstream, std::function<void(Args...)> func, std::function<std::string(void)> timestring) : func{ func }, m_logstream(logstream), m_timestring(timestring)	{	}
		template <class T>
		Logger& operator<<(T t)
		{
			makeString.push_back(std::string(t));
			return *this;
		}
	private:
		
	public:
		void operator() (Args... args)
		{
			std::stringstream ss;
			ss.str("");
			ss << m_timestring();

			for (auto& iter : makeString)
			{
				ss << iter;
				ss << " ";
			}
			printvalue(ss, args...);
			ss << " Begin\n";
			
			m_logstream.Write(ss.str());
			try
			{
				func(args...);

				ss.str("");
				ss << m_timestring();

				for (auto& iter : makeString)
				{
					ss << iter;
					ss << " ";
				}
				printvalue(ss, args...);
				ss << " End\n";

				m_logstream.Write(ss.str());
				ss.str("");
			}
			catch (std::exception& ex)
			{
				ss.str("");
				ss << m_timestring();

				for (auto& iter : makeString)
				{
					ss << iter;
					ss << " ";
				}
				printvalue(ss, args...);
				ss << " Fail\n";
				m_logstream.Write(ss.str());
			}
			return;
		};
	};
	
	template <class R, class... Args>
	auto makelog(LogStream& logstream, std::function<R(Args...)> func)
	{
		return Logger<R, Args...>(logstream, std::function<R(Args...)>(func));
	};
	template <class R, class... Args>
	auto makelog(LogStream& logstream, R(*func)(Args...))
	{
		std::function<R(Args...)> function = func;
		return Logger<R, Args...>(logstream, function);
	};
	template <class R, class... Args, class... T>
	auto makelog(LogStream& logstream, std::function<R(Args...)> func, T... strfuncs)
	{
		return Logger<R, Args...>(logstream, std::function<R(Args...)>(func), strfuncs...);
	};
	template <class R, class... Args, class... T>
	auto makelog(LogStream& logstream, R(*func)(Args...), T... strfuncs)
	{
		std::function<R(Args...)> function = func;
		return Logger<R, Args...>(logstream, function, strfuncs...);
	};
	
	//template <class... Args>
	//auto makelog(LogStream& logstream, std::function<void(Args...)> func)
	//{
	//	return Logger<void, Args...>(logstream, std::function<void(Args...)>(func));
	//};
	//template <class... Args>
	//auto makelog(LogStream& logstream, void(*func)(Args...))
	//{
	//	std::function<void(Args...)> function = func;
	//	return Logger< void, Args...>(logstream, function);
	//};
	//template < class... Args, class... T>
	//auto makelog(LogStream& logstream, std::function<void(Args...)> func, T... strfuncs)
	//{
	//	return Logger< void, Args...>(logstream, std::function<void(Args...)>(func), strfuncs...);
	//};
	//template < class... Args, class... T>
	//auto makelog(LogStream& logstream, void(*func)(Args...), T... strfuncs)
	//{
	//	std::function<void(Args...)> function = func;
	//	return Logger< void, Args...>(logstream, function, strfuncs...);
	//};

	

}
#endif

