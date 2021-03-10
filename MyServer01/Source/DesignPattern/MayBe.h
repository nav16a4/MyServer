#ifndef MAYBE_H
#define MAYBE_H
#include <optional>

template <class Type>
//std::optional ����ϹǷ� C++17 ��� �ʿ���
struct MayBe 
{
	std::optional<Type>& context;
	MayBe(std::optional<Type>& _context) : context(_context) {}

	template<class Func>
	//������ ���̸� ���� �Լ� ������ ����, �����̸� �ƹ� ���� ���ϰ� �ڱ� ��ü����
	auto Do(const bool do_action_if, Func action);

	


	
	template<class TrueFunc, class FalseFunc>
	//������ ���̸� �տ� ���� �Լ������� ����, �����̸� �ڿ� ���� �Լ������� ����
	auto Do(TrueFunc trueaction, FalseFunc falseaction);


};
template <class Type>
auto maybe(std::optional<Type>& context);

#include "MayBe.tpp"
#endif

