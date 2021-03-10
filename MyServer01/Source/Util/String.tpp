
template <class Type>
size_t My::MyString::Size(Type data){ return sizeof(data); }

template <class Type, class ... Types>
size_t My::MyString::Size(Type first, Types ... others)
{
	return Size(first) + Size(others...);
}
template <class Type, class... Types>
size_t My::MyString::SizeWith(char* ch, Type first, Types... others)
{
	//strlen(ch)은 마지막 띄어쓰기에 추가적으로 들어가는 길이
	return strlen(ch) + Size(ch, first) + Size(ch, others...);
}


template <class Type, class... Types>
void My::MyString::Append(std::string& dest, Type source)
{
	dest.append(MakeString(source));
	return;
}
template <class Type, class... Types>
void My::MyString::Append(std::string& dest, Type source, Types... next)
{
	dest.append(MakeString(source));
	Append(dest, next...);
	return;
}
template <class Type>
void  My::MyString::AppendWith(std::string& dest, char* ch, Type source)
{
	dest.append(MakeString(source));
	dest.append(ch);
	//마지막 띄어쓰기 넣기
	Append(dest, ch, source, ch);
	return;
}
template <class Type, class... Types>
void  My::MyString::AppendWith(std::string& dest, char* ch, Type source, Types... next)
{
	dest.append(MakeString(source));
	dest.append(ch);
	AppendWith(dest, ch, next...);
	return;
}
template <class Type>
std::string My::MyString::String(Type first)
{
	return MakeString(first);
	//return [&]()->std::string {return MakeString(first); };
}

template <class Type, class... Types>
std::string My::MyString::String(Type first, Types... others)
{
	int size = Size(first, others...);
	std::string str = "";
	str.reserve(size);
	Append(str, first, others...);
	return str;
}
template <class Type, class... Types>
std::string  My::MyString::StringWith(char* ch, Type first, Types... others)
{
	std::string str = "";
	//str.reserve(64);
	int size = SizeWith(ch, first, others...);
	str.reserve(size);
	AppendWith(str, ch, first, others...);
	return str;
}


template<class Type, class ...Types>
std::string My::MyMakeString(Type first, Types ...others)
{
	static My::MyString* mystring = new My::MyString;
	return mystring->String(first, others...);
}


template <class Type, class... Types>
static std::string  My::MyMakeStringWith(char* ch, Type first, Types... others)
{
	static MyString* mystring = new MyString;
	return mystring->StringWith(ch, first, others...);
}

