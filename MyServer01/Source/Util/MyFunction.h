#pragma once
#include <any>
#include <functional>

namespace My
{
	using MyFunction = std::function<std::any(std::vector<std::any>)>;
	void makeanyvector(std::vector<std::any>& v);
	template <class Type>
	void makeanyvector(std::vector<std::any>& v, Type& t)
	{
		v.push_back(t);
	}
	template <class Type, class... Types>
	void makeanyvector(std::vector<std::any>& v, Type& t, Types&... ts)
	{
		makeanyvector(v, t);
		makeanyvector(v, ts...);
	}


	template <class... Type>
	std::vector<std::any> anyvector(Type&&... t)
	{
		std::vector<std::any> v;
		makeanyvector(v, t...);
		return v;
	}


	template <class R, class... Args>
	std::function<R(Args...)> stdfunction(R(*func)(Args...))
	{
		std::function<R(Args...)> temp = func;
		return temp;
	}
	template<class ReturnT, class C, class... Args>
	std::function<ReturnT(Args...)> stdfunction(
		ReturnT(C::*&& func)(Args...), C*&& c)
	{
		std::function<ReturnT(Args...)> t = [&c, &func](Args&&... args)
		{
			return (*c.*func)(args...);
		};
		return t;
	}
	template< class C, class... Args>
	std::function<void(Args...)> stdfunction(
		void (C::*&& func)(Args...), C*&& c)
	{
		std::function<void(Args...)> t = [c, func](Args&&... args)
		{
			(*c.*func)(args...);
			return;
		};
		return t;
	}



	template <class T, class... Args>
	inline std::any returnany(std::function<T(Args...)>func, Args... args)
	{
		std::any retval = func(args...);
		return retval;

	}
	template < class... Args>
	inline std::any returnany(std::function<void(Args...)>func, Args... args)
	{
		func(args...);
		void* t = nullptr;
		std::any dummy = t;
		return dummy;
	}





	template <class R>
	auto myfunction(std::function<R()> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			return returnany(func);
		};
	}

	template <class R, class T0>
	auto myfunction(std::function<R(T0)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			return returnany(func, v0);
		};
	}
	template <class R, class T0, class T1>
	auto myfunction(std::function<R(T0, T1)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			return returnany(func, v0, v1);
		};
	}
	template <class R, class T0, class T1, class T2>
	auto myfunction(std::function<R(T0, T1, T2)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			return returnany(func, v0, v1, v2);
		};
	}
	template <class R, class T0, class T1, class T2, class T3>
	auto myfunction(std::function<R(T0, T1, T2, T3)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			return returnany(func, v0, v1, v2, v3);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			return returnany(func, v0, v1, v2, v3, v4);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			return returnany(func, v0, v1, v2, v3, v4, v5);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			return returnany(func, v0, v1, v2, v3, v4, v5, v6);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			return returnany(func, v0, v1, v2, v3, v4, v5, v6, v7);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			T8 v8 = std::any_cast<T8>(args[8]);
			return returnany(func, v0, v1, v2, v3, v4, v5, v6, v7, v8);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			T8 v8 = std::any_cast<T8>(args[8]);
			T9 v9 = std::any_cast<T9>(args[9]);
			return returnany(func, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			T8 v8 = std::any_cast<T8>(args[8]);
			T9 v9 = std::any_cast<T9>(args[9]);
			T10 v10 = std::any_cast<T10>(args[10]);
			return returnany(func, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			T8 v8 = std::any_cast<T8>(args[8]);
			T9 v9 = std::any_cast<T9>(args[9]);
			T10 v10 = std::any_cast<T10>(args[10]);
			T11 v11 = std::any_cast<T11>(args[11]);
			return returnany(func, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			T8 v8 = std::any_cast<T8>(args[8]);
			T9 v9 = std::any_cast<T9>(args[9]);
			T10 v10 = std::any_cast<T10>(args[10]);
			T11 v11 = std::any_cast<T11>(args[11]);
			T12 v12 = std::any_cast<T12>(args[12]);
			return returnany(func, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			T8 v8 = std::any_cast<T8>(args[8]);
			T9 v9 = std::any_cast<T9>(args[9]);
			T10 v10 = std::any_cast<T10>(args[10]);
			T11 v11 = std::any_cast<T11>(args[11]);
			T12 v12 = std::any_cast<T12>(args[12]);
			T13 v13 = std::any_cast<T13>(args[13]);

			return returnany(func, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			T8 v8 = std::any_cast<T8>(args[8]);
			T9 v9 = std::any_cast<T9>(args[9]);
			T10 v10 = std::any_cast<T10>(args[10]);
			T11 v11 = std::any_cast<T11>(args[11]);
			T12 v12 = std::any_cast<T12>(args[12]);
			T13 v13 = std::any_cast<T13>(args[13]);
			T14 v14 = std::any_cast<T14>(args[14]);

			return returnany(func, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
		};
	}
	template <class R, class T0, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class T11, class T12, class T13, class T14, class T15>
	auto myfunction(std::function<R(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15)> func)
	{
		return [func]
		(std::vector<std::any>& args)
		{
			T0 v0 = std::any_cast<T0>(args[0]);
			T1 v1 = std::any_cast<T1>(args[1]);
			T2 v2 = std::any_cast<T2>(args[2]);
			T3 v3 = std::any_cast<T3>(args[3]);
			T4 v4 = std::any_cast<T4>(args[4]);
			T5 v5 = std::any_cast<T5>(args[5]);
			T6 v6 = std::any_cast<T6>(args[6]);
			T7 v7 = std::any_cast<T7>(args[7]);
			T8 v8 = std::any_cast<T8>(args[8]);
			T9 v9 = std::any_cast<T9>(args[9]);
			T10 v10 = std::any_cast<T10>(args[10]);
			T11 v11 = std::any_cast<T11>(args[11]);
			T12 v12 = std::any_cast<T12>(args[12]);
			T13 v13 = std::any_cast<T13>(args[13]);
			T14 v14 = std::any_cast<T14>(args[14]);
			T15 v15 = std::any_cast<T15>(args[15]);

			return returnany(func, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15);
		};


	};


	

}
