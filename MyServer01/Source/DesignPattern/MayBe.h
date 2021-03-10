#ifndef MAYBE_H
#define MAYBE_H
#include <optional>

template <class Type>
//std::optional 사용하므로 C++17 사용 필요함
struct MayBe 
{
	std::optional<Type>& context;
	MayBe(std::optional<Type>& _context) : context(_context) {}

	template<class Func>
	//조건이 참이면 넣은 함수 포인터 실행, 거짓이면 아무 실행 안하고 자기 객체리턴
	auto Do(const bool do_action_if, Func action);

	


	
	template<class TrueFunc, class FalseFunc>
	//조건이 참이면 앞에 넣은 함수포인터 실행, 거짓이면 뒤에 넣은 함수포인터 실행
	auto Do(TrueFunc trueaction, FalseFunc falseaction);


};
template <class Type>
auto maybe(std::optional<Type>& context);

#include "MayBe.tpp"
#endif

