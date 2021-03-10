#pragma once
#include <array>
#include <functional>
#include <vector>
#include <array>
#include <any>
#include "Packet.h"
#include "DesignPattern/Observer.h"
#include "Game/GameObject.h"
#include "Util/Log.h"
#include "Util/MyFunction.h"
#include "ExternalLibrary/fmt/core.h"
//패킷으로 부터 필요한 데이터를 뽑아 전달해 주는 역할인데....
//
//임의의 데이터를 


namespace My {

	template <class... Types>
	class PacketExtractor
	{
		friend class Game;
		std::array< std::function< std::any(Types... args,  Packet&) >,128 > m_function;
		//std::array < std::function<std::vector<std::any>(const Packet&)>, 128> m_argmaker;
		template <class Func>
		auto ResisterFunc(int num,  Func function)
		{
			std::function<std::any(Types..., Packet&)> func = [this,function](Types... args, Packet& packet)->std::any
			{
				return ExecuteFromPacket(args...,packet,function);
			};

			m_function[num] = func;
			return;
		}

	public:
		std::function<std::any(Types... args, Packet&)>& operator[](int n)
		{
			return m_function[n];
		}
		
		PacketExtractor();
		void Initialize();
	
		//void Execute(Packet&, const unsigned long long);

		//std::array<std::function<std::vector<std::any>(Packet&)>, 128> temp;

	
		//void ResistFunc(int )

		//template <class T>
		//auto makepakcetextractor(T t)
		//{
		//	return [t](Types... args, const Packet& packet)
		//	{
		//		return makestdAnyVector(args...,packet, t);
		//	};
		//}
		//template <class... Args>
		//auto makepakcetextractor(std::function<void(Args...)> t)
		//{
		//	return [t](Types... args,const Packet& packet)
		//	{
		//		makestdAnyVector(args...,packet, t);
		//		return;
		//	};
		//}


		template <class R,class... Args>
		auto execute(std::function<R(Args...)>,Args... args )
		{
			return func(args);
		}
		template < class... Args>
		void execute(std::function<void(Args...)>func ,Args... args)
		{
			func(args);
			return;
		}

		template <class T, class... Args>
		inline std::any returnanywithlog(std::function<T(Args...)>func, Args&... args)
		{
			/*static*/ auto logger = makelog(*LogStream::GetInstance(), func);
			logger << __MYFUNCNAME(LAMBDA());
			std::any retval = logger(args...);
			return retval;

		}
		template < class... Args>
		inline std::any returnanywithlog(std::function<void(Args...)>func, Args&... args)
		{
			/*static*/ auto logger = makelog(*LogStream::GetInstance(), func);
			logger << __MYFUNCNAME(LAMBDA());
			logger(args...);
			std::any dummy = nullptr;
			return dummy;
		}

	
		template <class R>
		auto ExecuteFromPacket( Types... args, Packet& packet, std::function<R(Types...)> func  )
		{
			//func(args...);
			return returnanywithlog(func,args...);
		}

		template <class R,class T0>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types...,T0)> func)
		{
			
			T0 t0;
			packet.ReadPacket(t0);
			return returnanywithlog(func,args...,t0);
		}
		template <class R, class T0, class T1>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1)> func)
		{
			T0 t0;
			T1 t1;
			packet.ReadPacket(t0, t1);
			return returnanywithlog(func,args...,t0, t1);
		}

		template <class R, class T0, class T1, class T2>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			packet.ReadPacket(t0, t1, t2);
			return returnanywithlog(func,args...,t0, t1, t2);
		}

		template <class R, class T0, class T1, class T2, class T3>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			packet.ReadPacket(t0, t1, t2, t3);
			return returnanywithlog(func, args..., t0, t1, t2, t3);
		}

		template <class R, class T0, class T1, class T2, class T3, class T4>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;

			packet.ReadPacket(t0, t1, t2, t3, t4);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4);
		}

		template <class R, class T0, class T1, class T2, class T3, class T4, class T5>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;

			packet.ReadPacket(t0, t1, t2, t3, t4, t5);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5);
		}

		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5, T6)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;

			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5, t6);
		}


		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5, T6, T7)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;
			T7 t7;

			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6, t7);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5, t6, t7);
		}


		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5, T6, T7, T8)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;
			T7 t7;
			T8 t8;

			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6, t7, t8);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5, t6, t7, t8);
		}

		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;
			T7 t7;
			T8 t8;
			T9 t9;

			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
		}

		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;
			T7 t7;
			T8 t8;
			T9 t9;
			T10 t10;

			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
		}

		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)> func)
		{

			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;
			T7 t7;
			T8 t8;
			T9 t9;
			T10 t10;
			T11 t11;



			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11);
		}

		
		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)> func)
		{

			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;
			T7 t7;
			T8 t8;
			T9 t9;
			T10 t10;
			T11 t11;
			T12 t12;
			

			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12);
		}

		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)> func)
		{

			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;
			T7 t7;
			T8 t8;
			T9 t9;
			T10 t10;
			T11 t11;
			T12 t12;
			T13 t13;

			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13);
		}

		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
			auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)> func)
		{

			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;
			T7 t7;
			T8 t8;
			T9 t9;
			T10 t10;
			T11 t11;
			T12 t12;
			T13 t13;
			T14 t14;

			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
			return returnanywithlog(func, args..., t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14);
		}
		template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
		auto ExecuteFromPacket(Types... args,  Packet& packet, std::function<R(Types..., T0,T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)> func)
		{
			T0 t0;
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			T5 t5;
			T6 t6;
			T7 t7;
			T8 t8;
			T9 t9;
			T10 t10;
			T11 t11;
			T12 t12;
			T13 t13;
			T14 t14;
			T15 t15;
			
			packet.ReadPacket(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
			return returnanywithlog(func, args..., t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15);
		}

	};

	template<class ...Types>
	inline PacketExtractor<Types...>::PacketExtractor()
	{
	}

	template<class ...Types>
	inline void PacketExtractor<Types...>::Initialize()
	{
	}

}
