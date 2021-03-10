#pragma once
#include <unordered_map>
#include <string>
#include "Util/Log.h"
//정적으로 이용해야만 하는 데이터는 constexr 활용
//동적으로 이용해도 되는 애는 별도 
namespace My
{
	using ClientIDType = short;

	
	class DefaultValue
	{
		//=================Initialize=======================
	private:
		const char* m_defaultFile = "test.ini";
	public:

		DefaultValue() { /*DefaultValue(m_defaultFile);*/ }
		DefaultValue(const char*);
	protected:
	private:
		void Initializer();



		//====================Member_Variable=============
	public:
	protected:
	private:
		std::unordered_map<std::string, int> m_definedint;
		std::unordered_map<std::string, std::string> m_definedstring;
		//My::LogStream m_defaultLog;
		//=====================Member_Funtion=============
	public:
		int GetInt(std::string s);
		std::string& GetString(std::string s);
	protected:
	private:

		//======================△동적=====▽정적================
	public:
		static constexpr int MaxClientCount() { return 1024; }
		static constexpr int IOCPThreadCount() { return 16; }
		static constexpr int OverlappedBufferSize() { return 1024; }
		LogStream& DefaultLog();


	};
}
