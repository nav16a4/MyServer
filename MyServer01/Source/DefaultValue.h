#pragma once
#include <unordered_map>
#include <string>
#include "Util/Log.h"
//�������� �̿��ؾ߸� �ϴ� �����ʹ� constexr Ȱ��
//�������� �̿��ص� �Ǵ� �ִ� ���� 
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

		//======================�⵿��=====������================
	public:
		static constexpr int MaxClientCount() { return 1024; }
		static constexpr int IOCPThreadCount() { return 16; }
		static constexpr int OverlappedBufferSize() { return 1024; }
		LogStream& DefaultLog();


	};
}
