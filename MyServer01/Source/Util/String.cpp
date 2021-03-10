#include "Precompiled.h"
#include "String.h"

std::string My::GetCurrTimeString()
{
	const static char date[7][4] = {
	"SUN","MON","TUE","WED","THU","FRI","SAT"
	};

	std::string returnString;
	const int UTC = +9;

	std::stringstream ss;
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::tm today;
	__time64_t t = std::chrono::system_clock::to_time_t(now);
	_localtime64_s(&today, &t);

	ss << "[" << (today.tm_year + 1900) << '-'
		<< (today.tm_mon + 1) << '-'
		<< today.tm_mday << " "
		<< date[(today.tm_wday)] << " ";

	auto duration = now.time_since_epoch();

	typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<UTC>	>::type> Days;
	Days days = std::chrono::duration_cast<Days>(duration);
	duration -= days;
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	duration -= hours;
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
	duration -= minutes;
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
	duration -= seconds;
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
	duration -= milliseconds;
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
	//duration -= microseconds;
	//auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

	ss << today.tm_hour << "H"
		<< minutes.count() << "M"
		<< seconds.count() << "."
		<< milliseconds.count() << microseconds.count()/* << nanoseconds.count()*/ << "S]";

	returnString = ss.str();

	return returnString;
}

size_t My::MyString::Size(void) { return 0; }
size_t My::MyString::Size(const char* c) { return ::strlen(c); }
size_t My::MyString::Size(std::string& str) {
	return str.size();
}
size_t My::MyString::Size(bool) { return 6; }
std::string My::MyString::MakeString(void) { return std::string(); }

std::string My::MyString::MakeString(int integer) { return std::to_string(integer); }
std::string My::MyString::MakeString(long integer) { return std::to_string(integer); }
std::string My::MyString::MakeString(unsigned long integer) { return std::to_string(integer); }
std::string My::MyString::MakeString(long long integer) { return std::to_string(integer); }
std::string My::MyString::MakeString(unsigned long long integer) { return std::to_string(integer); }

std::string My::MyString::MakeString(float decimal) { return std::to_string(decimal); }
std::string My::MyString::MakeString(double decimal) { return std::to_string(decimal); }
std::string My::MyString::MakeString(long double decimal) { return std::to_string(decimal); }

std::string My::MyString::MakeString(const char* ch) { return std::string(ch); }
std::string My::MyString::MakeString(char* ch) { return std::string(ch); }
std::string My::MyString::MakeString(std::string str) { return str; }
std::string My::MyString::MakeString(std::string& str) { return std::string(str); }
std::string My::MyString::MakeString(bool trueorfalse) { return std::string((trueorfalse ? "true" : "false")); }

void My::MyString::Append(std::string& dest)
{
	return;
}