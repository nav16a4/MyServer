#include "Precompiled.h"
#include "DefaultValue.h"

My::DefaultValue::DefaultValue(const char* filename)
{
	std::fstream file(filename);
	if (false == file.is_open())
	{
		std::cout << filename << " 파일이 없습니다.\n";
		return;
	}

	
}

void My::DefaultValue::Initializer()
{
	//m_defaultLog = LogStream();
	
}
