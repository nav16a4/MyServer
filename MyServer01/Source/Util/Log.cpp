#include "Precompiled.h"
#include "Log.h"

void My::printvalue(std::stringstream& ss)
{
	return;
}
//===============================================================

void My::LogStream::LogToConsole(std::string& s){	*m_os << s;}

void My::LogStream::LogToFile(std::string& s){	*m_ofs << s;}

void My::LogStream::LogToConsoleAndFile(std::string& s)
{
	*m_os << s;
	*m_ofs << s;
}

void My::LogStream::LogNothing(std::string& s){}

My::LogStream::LogStream() : m_os(nullptr), m_ofs(nullptr)
{
	func = std::bind(&LogStream::LogNothing, this, std::placeholders::_1);
}

My::LogStream::LogStream(std::ostream* os) : m_os(os), m_ofs(nullptr)
{
	func = std::bind(&LogStream::LogToConsole, this, std::placeholders::_1);
}

My::LogStream::LogStream(std::ofstream* ofs)
	: m_os(nullptr), m_ofs(ofs)
{
	func = std::bind(&LogStream::LogToFile, this, std::placeholders::_1);
}

My::LogStream::LogStream(std::ofstream* ofs, std::ostream* os)
{
	LogStream(os, ofs);
}

My::LogStream::LogStream(std::ostream* os, std::ofstream* ofs) : m_os(os), m_ofs(ofs)
{
	func = std::bind(&LogStream::LogToConsoleAndFile, this, std::placeholders::_1);
}

void My::LogStream::Write(std::string& s)
{
	func(s);
}
void My::LogStream::Write(std::string&& s)
{
	func(s);
}


My::LogStream& My::operator<<(LogStream& ls, std::string& s)

{
	ls.Write(s);
	return ls;
}
My::LogStream& My::operator<<(LogStream& ls, std::string&& s)
{
	ls.Write(s);
	return ls;
}
My::LogStream& My::operator<<(LogStream& ls, const char* c)
{
	std::string s = std::string(c);
	ls.Write(s);
	return ls;
}


