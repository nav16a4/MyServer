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
	//������ �ֱ� ���� �ٸ� �����忡�� �����ؼ� �����͸� ���ų� ������ ���� ���� �� �����Ƿ� �ϴ��� �۾� ���߿��� ��°�� ���� �Ǵ�.
	//���� ������ Ȯ���ϰ� �ٸ� �����忡�� �� �� �ְ� ���� Ǫ�� ���� �ְ� �ٷ� ������ �õ��� �� ������ ���� ���̴�.
	//���� ���� ��Ŷ �ϼ��Ǿ����� ����

	//if (max < size)
	//{
	//	//���ۺ��� ũ�� ��� �ص� ���� �� �����Ƿ� ����
	//	return false;
	//}

	if (max < saved + size)
	{
		std::cout << "����á��\n";
		//���� �� ������ ���� �� ����.
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
		std::cout << "����Ȱ� ���µ�?\n";
		//����Ȱ� ���µ�?
		return returnvalue;
	}

	int packetsize = static_cast<int>(buffer[readPosition]);
	first = packetsize;

	if (destbuffersize < packetsize)
	{
		std::cout << "������ �ű� ������ �۰� ����� ��ϴ�...?\n";
		//������ �ű� ������ �۰� ����� ��ϴ�...
		return returnvalue;
	}
	//if ((readPosition + packetsize) % max < writePosition)
	//{
	//	//��Ŷ�� �ϼ� �ȵ�
	//	return returnvalue;
	//}
	if (saved < packetsize)
	{
		std::cout << "��Ŷ �̿ϼ�!\n";
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

