#ifndef STRING_H
#define STRING_H
#include <functional>
#include <string>

namespace My
{
	std::string GetCurrTimeString();

	class MyStringFunc
	{
	private:
		const std::function<std::string(void)> func;
		const std::string str;
	public:
		MyStringFunc(std::function<std::string(void)> str_func) : func(str_func), str(std::string("")) {}
		MyStringFunc(std::string const_str) : func(nullptr), str(const_str) {}
		MyStringFunc(const char* ch) : func(nullptr), str(std::string(ch)) {}

		std::string operator()(void)
		{
			return func != nullptr ? func() : str;
		}
	};
	
	class MyString
	{
	private:
		MyString() = default;
		MyString(MyString&&) = delete;
		MyString(const MyString&) = delete;
		MyString& operator=(const MyString&) = delete;
		MyString& operator=(MyString&&) = delete;

		size_t Size(void);
		size_t Size(const char* c);
		size_t Size(std::string& str);
		size_t Size(bool);
		template <class Type>
		size_t Size(Type data);
		template <class Type, class... Types>
		size_t Size(Type first, Types... others);

		//Logger클래스에서 필요하여 추가
		template <class Type, class... Types>
		size_t SizeWith(char* ch, Type first, Types... others);

		std::string MakeString(void);
		std::string MakeString(int integer);
		std::string MakeString(long integer);
		std::string MakeString(unsigned long integer);
		std::string MakeString(long long integer);
		std::string MakeString(unsigned long long integer);

		std::string MakeString(float decimal);
		std::string MakeString(double decimal);
		std::string MakeString(long double decimal);


		std::string MakeString(const char* ch);
		std::string MakeString(char* ch);
		std::string MakeString(std::string str);
		std::string MakeString(std::string& str);
		std::string MakeString(bool trueorfalse);

		void Append(std::string& dest);
		
		template <class Type, class... Types>
		void Append(std::string& dest, Type source);

		template <class Type, class... Types>
		void Append(std::string& dest, Type source, Types... next);
		template <class Type>
		void AppendWith(std::string& dest, char* ch, Type source);
		template <class Type, class... Types>
		void AppendWith(std::string& dest, char* ch, Type source, Types... next);
		template <class Type>
		std::string String(Type first);

		template <class Type, class... Types>
		std::string String(Type first, Types... others);
		template <class Type, class... Types>
		std::string StringWith(char* ch, Type first, Types... others);
	public:
		template <class Type, class... Types>
		static friend std::string MyMakeString(Type first, Types... others);
		template <class Type, class... Types>
		static friend std::string MyMakeStringWith(char* ch, Type first, Types... others);

	};
	template <class Type, class... Types>
	static std::string MyMakeString(Type first, Types... others);
	template <class Type, class... Types>
	static std::string MyMakeStringWith(char* ch, Type first, Types... others);

}
#include  "String.tpp"
#endif
