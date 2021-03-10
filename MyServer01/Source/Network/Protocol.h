#pragma once
enum class PacketType : unsigned char
{
	PT_TEST,
	PT_BEGIN,
	PT_LOGIN,
	PT_LOGOUT,
	PT_END
};