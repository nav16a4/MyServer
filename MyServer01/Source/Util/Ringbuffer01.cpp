#include "Precompiled.h"
#include "Ringbuffer01.h"

bool  My::Util::RingBuffer::IsPacketMaked() const

{
	bool returnvalue = false;
	if (saved < 1)
	{
		return returnvalue;
	}
	else
	{
		const unsigned int size = static_cast<unsigned int>(buffer[readPosition]);

		if (saved <= size)
		{
			returnvalue = true;
		}

	}
	return returnvalue;
}

unsigned int  My::Util::RingBuffer::Push(const char* source, unsigned int size)
{
	bool is_split = false;
	int first = size;
	int second = 0;
	int task = 0;
	int temp = writePosition;
	int returnvalue = 0;
	std::lock_guard<std::mutex> lockguard(mutex);
	//실제로 넣기 전에 다른 스레드에서 접근해서 데이터를 빼거나 넣으면 문제 생길 수 있으므로 일단은 작업 도중에는 통째로 락을 건다.
	//넣을 공간만 확보하고 다른 스레드에서 쓸 수 있게 락을 푸는 것은 넣고 바로 빼려고 시도할 때 문제가 생길 것이다.
	//리턴 값은 패킷 완성되었는지 여부

	//if (max < size)
	//{
	//	//버퍼보다 크면 어떻게 해도 넣을 수 없으므로 리턴
	//	return false;
	//}

	if (max < saved + size)
	{
		std::cout << "가득찼엉\n";
		//가득 차 있으면 넣을 수 없다.
		return returnvalue;
	}



	if (max < (writePosition + size))
	{
		//
		is_split = true;
		second = (size + writePosition) % max;
		first = size - second;
	}


	int destsize = max - writePosition;
	memcpy_s(buffer + writePosition, destsize, source, first);

	writePosition += first;
	writePosition %= max;

	saved += first;
	returnvalue += first;

	if (true == is_split)
	{
		memcpy_s(buffer, max, source + first, second);

		writePosition = second;
		saved += second;
		returnvalue += second;
	}
	int packetsize = static_cast<int>(buffer[temp]);

	//if (writePosition == max) { writePosition = 0; }

	return returnvalue;

}

unsigned int My::Util::RingBuffer::Pull(char* dest, const int destbuffersize)
{
	std::lock_guard<std::mutex> lockguard(mutex);
	bool is_split = false;
	int returnvalue = 0;
	int first = 0;
	int second = 0;
	if (saved == 0)
	{
		std::cout << "저장된게 없는데?\n";
		//저장된게 없는데?
		return returnvalue;
	}

	int packetsize = static_cast<int>(buffer[readPosition]);
	first = packetsize;

	if (destbuffersize < packetsize)
	{
		std::cout << "데이터 옮길 공간을 작게 만들면 어떻하니...?\n";
		//데이터 옮길 공간을 작게 만들면 어떻하니...
		return returnvalue;
	}
	//if ((readPosition + packetsize) % max < writePosition)
	//{
	//	//패킷이 완성 안됨
	//	return returnvalue;
	//}
	if (saved < packetsize)
	{
		std::cout << "패킷 미완성!\n";
		return returnvalue;
	}
	if (max < readPosition + packetsize)
	{
		is_split = true;
		first = max - readPosition;
		second = packetsize - first;

	}

	memcpy_s(dest, destbuffersize, buffer + readPosition, first);
	returnvalue += first;
	saved -= first;
	readPosition += first;
	readPosition %= max;
	if (true == is_split)
	{
		memcpy_s(dest + first, destbuffersize - first, buffer, second);
		returnvalue += second;
		saved -= second;
		readPosition = second;
	}
	//if (readPosition == max) { readPosition = 0; }
	return returnvalue;
}

