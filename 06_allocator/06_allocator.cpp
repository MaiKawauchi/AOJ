#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <memory>
#include <random>
#include "myAllocator.h"

#define MAX_AVAILABLE_MEMORY 1000	// �g�p�\�������e��
#define THRESHOLD 0.7				// �������l(70%)
#define MAX_RANDOM_RANGE 100		// �����̍ő�l
#define TEST_LOOPCOUNT 50			// 70%�ɒB������ɂ܂킷��
#define ODDNUM 2					// �


//�����Z���k�c�C�X�^
int Random_MT()
{
	std::random_device seed_gen;		// �񌈒�I�ȗ���������
	std::mt19937 engine(seed_gen());	// �V�[�h�w��
	return engine();
}

// 1B - 1000000B(1MB) �͈̔͂Ń����_���Ȓl�𐶐�����
uint32_t Random_1Bto1MB()
{
	uint32_t mt = Random_MT();
	uint32_t val = (uint32_t)(mt % MAX_RANDOM_RANGE) + 1;
	std::cout << val << std::endl;
	return val;
}

// �������m��
void MyAlloc(uint8_t* pointer, MyAllocator<uint8_t> alc)
{

	
}

int main()
{
	auto alc = MyAllocator<uint8_t>();

	// �g�p�\�������e�ʂ��A���P�[�^�[�ɋ�����
	alc.getMaxAvailableMemory(MAX_AVAILABLE_MEMORY);
	alc.MyMalloc();
	// �m�ۂ����|�C���^���i�[����z��
	uint8_t* mem_ptr[MAX_AVAILABLE_MEMORY];

	// =================================
	// ���e�ʂ�70%�܂Ŋm�ۂ�������
	// =================================
	uint8_t upto70 = 0;
	for (upto70 = 0; alc.getUtilMemory() <= THRESHOLD; upto70++) 
	{
		// 1B-1MB�͈̔͂Ń����_���Ȓl���擾
		uint32_t rand_size_memory = Random_1Bto1MB();

		// ���������m�ۂ��A�|�C���^�[�ƃT�C�Y��ێ�
		mem_ptr[upto70] = alc.allocate(rand_size_memory);

		// test output :�g�p�����擾
		alc.CalculationUtilMemory();
	}

	// =================================
	// ��������m�ۂƊJ�����J��Ԃ�
	// =================================
	for (int j = 0; j < TEST_LOOPCOUNT; j++)
	{
		// �m�ہitrue�j���邩�A����ifalse�j���邩
		bool do_alloc = Random_MT() % ODDNUM;
		if (do_alloc)
		{
			std::cout << "�m�ۂ��܂�" << std::endl;

			// 1B-1MB�͈̔͂Ń����_���Ȓl���擾
			uint32_t rand_size_memory = Random_1Bto1MB();

			// �����_���T�C�Y�Ń������m��
			mem_ptr[upto70 + j] = alc.allocate(rand_size_memory);

			// test output : �g�p�����擾
			alc.CalculationUtilMemory();
		}
		else
		{
			std::cout << "*** ������܂�" << std::endl;
			// �̈���������
			alc.free(mem_ptr[Random_MT() % alc.getCount()]);

			// test output :�g�p�����擾
			alc.CalculationUtilMemory();
		}
	}
	alc.MyFree();
  	return 0;
}