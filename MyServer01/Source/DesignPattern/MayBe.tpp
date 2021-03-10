

template<class Type>
template<class Func>
 auto MayBe<Type>::Do(const bool do_action_if, Func action)
{
	if (do_action_if == context.has_value()) { action(context); } return *this;
}

template<class Type>
template<class TrueFunc, class FalseFunc>
 auto MayBe<Type>::Do(TrueFunc trueaction, FalseFunc falseaction)
{
	return (true == context.has_value()) ? trueaction(context.value()) : falseaction(context.value());
}
template<class Type>
inline auto maybe(std::optional<Type>& context)
{
	return MayBe<Type>(context);
}
