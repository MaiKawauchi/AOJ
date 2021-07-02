#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <memory>
#include <random>
#include "MyAllocator.h"

#define MAX_AVAILABLE_MEMORY 1000	// �g�p�\�������e��
#define MAX_RANDOM_RANGE 100		// �����̍ő�l
#define TEST_LOOPCOUNT 50			// 70%�ɒB������ɂ܂킷��
#define THRESHOLD 0.7				// �������l(70%)
#define ODDNUM 2					// �



// �����Z���k�c�C�X�^
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



/*---------------------------------------------------------------------
1. 100MB�̃������u���b�N��\��
2. ���������m�ۂ��Ă��炤(�T�C�Y��n���ă|�C���^���Ԃ�)
3. ���������J�����Ă��炤(�|�C���^��n��)
---------------------------------------------------------------------*/

int main()
{
	MyAllocator alc = MyAllocator();
	
	// �A���P�[�^�[�p�������u���b�N�̗\��
	void* capacity = malloc(sizeof(uint8_t) * MAX_AVAILABLE_MEMORY);
	if(capacity == NULL)
	{
		std::cout << "Error : cannot malloc the memory." << std::endl;
		exit(1);
	}
	// ������
	alc.initialize(capacity, MAX_AVAILABLE_MEMORY);

	// �m�ۂ����擪�|�C���^���i�[����z��
	uint8_t* mem_ptr[MAX_AVAILABLE_MEMORY];
	

	// =================================
	// ���e�ʂ�70%�܂Ŋm�ۂ�������
	// =================================
	uint8_t total_num = 0;
	for (int i = 0; alc.CalculationUtilMemory() <= THRESHOLD; i++)
	{
		std::cout << "[alloc]�@";

		// 1B-1MB�͈̔͂Ń����_���Ȓl���擾
		uint32_t rand_size_memory = Random_1Bto1MB();

		// �������ݏo�˗������A�A���Ă����|�C���^�[��ێ�
		mem_ptr[i] = reinterpret_cast<uint8_t*>(alc.allocate(rand_size_memory));
		total_num++;
	}
	
	// =================================
	// ��������m�ۂƊJ�����J��Ԃ�
	// =================================
	for (int j = 0; j < TEST_LOOPCOUNT; j++)
	{
		// �m�ہitrue�j���邩�A����ifalse�j���邩
		bool do_alloc = true;// Random_MT() % ODDNUM;
		if (do_alloc)
		{
			std::cout << "[alloc]�@";

			// 1B-1MB�͈̔͂Ń����_���Ȓl���擾
			uint32_t rand_size_memory = Random_1Bto1MB();

			// �����_���T�C�Y�Ń������m��
			mem_ptr[total_num + j + 1] = reinterpret_cast<uint8_t*>(alc.allocate(rand_size_memory));
			total_num++;
		}
		else
		{
			std::cout << "[free]�@";

			// �̈���������
			alc.free(mem_ptr[Random_MT() % total_num]);

			// test output :�g�p�����擾
			alc.CalculationUtilMemory();
			total_num--;
		}
	}
	free(capacity);
	return 0;
}