#pragma once
namespace My
{


	class Packet
	{
	public:
		Packet(char* ptr) :m_buffer(ptr) {}

		/*constexpr int m_size() { return 1; }
		constexpr int m_type() { return 1; }*/
		char* m_buffer = nullptr;

		//하드코딩
		int GetSize() { return m_buffer[0]; }
		int GetType() { return m_buffer[1]; }
		int GetData(char* ptr)
		{
			ptr = m_buffer;
			return GetSize() - 2;//사이즈 타입
		}
	private:
		int ReadData(char* c);
		int ReadData(char* c, std::string&);
		//int ReadData(char* c, Packet&);
		template <class Type>
		int ReadData(char* c,Type& value)
		{
			value = *(reinterpret_cast<Type*>(c));
			return sizeof(value);
		}
		/*template <class Type>
		int ReadData(size_t size,char* c, Type& value)
		{
			value = *(reinterpret_cast<Type*>(c));
			return sizeof(value);
		}*/
	public:
		template <class First,class... Others>
		int ReadPacket(First& first, Others&... others) 
		{
			size_t size = 0;
			char* ch = m_buffer + 2;
			/*ch += ReadData(ch, first);
			ch += ReadData(ch, others...);*/
			size += ReadData(ch, first);
			size += ReadData(ch + size, others...);
			return size;
		}
	private:
		int WriteData(char* c) { return 0; }
		template <class Type>
		int WriteData(char* c, Type& value)
		{
			*(reinterpret_cast<Type*>(c))=value;
			return sizeof(value);
		}
	public:
		template <class First, class... Others>
		void WritePacket(First& first, Others&... others)
		{
			char* ch = m_buffer + 2;
			ch += WriteData(ch, first);
			ch += WriteData(ch, others...);
			return;
		}
		
	};

	


	
}