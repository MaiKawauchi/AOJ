#ifndef MYALLOCATOR_H
#define MYALLOCATOR_H

#include <iostream>

class MyAllocator
{
private:
	// �A���P�[�^�[�Ǘ����
	// atention : sizeof(AllocInfo)�ł��̍\���̂̃T�C�Y���v�Z�ł���
	struct AllocInfo
	{
		uint32_t full_size;		// �������u���b�N�̑��T�C�Y 
		void* free_mem_ptr;		// �t���[�������u���b�N�ւ̃|�C���^
	};

	// �݂��o���Ǘ��̈�
	struct MemInfo
	{
		// atention : �݂��o���������̃|�C���^��MemInfo::getMem()�ƂȂ�
		std::size_t mem_size;	// �݂��o���������T�C�Y
		uint8_t* getMem()		// �������u���b�N 
		{
			return reinterpret_cast<uint8_t*>(this) + sizeof(MemInfo);
		}
	};

	// �ݏo���e��
	std::size_t m_using_memory = 0;

public:
	// �R���X�g���N�^
	MyAllocator() {}

	void* allocate(std::size_t size)
	{
		if(checkFreeSize(size))
		{
			// �t���[�������u���b�N�̐擪�|�C���^
			void* p = allocinfo.free_mem_ptr;
			// �t���[�������u���b�N�̐擪�|�C���^���X�V
			allocinfo.free_mem_ptr = reinterpret_cast<uint8_t*>(p) + size;

			// �݂��o�����|�C���^�ƃT�C�Y���m��
			meminfo.mem_size = size;
			m_using_memory += size;

			return p;
		}
		return nullptr;
	}

	void free(uint8_t* p)
	{


	}

	void initialize(void* capacity, std::size_t max_available_memeory)
	{
		allocinfo.free_mem_ptr = capacity;
		allocinfo.full_size = max_available_memeory;
	}

	// ���`���X�g���Ǘ�
	void linkListManager()
	{

	}
	// �ݏo���e�ʂ��擾
	std::size_t getUsingMemory() const
	{
		return m_using_memory;
	}
	// �ݏo�����v�Z
	float CalculationUtilMemory()
	{
		float m_util_memory = (float)(getUsingMemory()) / allocinfo.full_size;
		// test output
		std::cout << "Utilization    : " << m_util_memory * 100.0 << " %" << std::endl;
		return m_util_memory;
	}
	// �̈悪�m�ۂł��Ȃ������ꍇ�̃G���[���O
	void OutputLog(int rand_size_memory)
	{
		// �v���T�C�Y�E���T�C�Y�E�g�p����\��
		std::cout << "Error : cannot allocate the memory." << std::endl;
		std::cout << "Request Size   : " << rand_size_memory << std::endl;
		std::cout << "Available Size : " << allocinfo.full_size << std::endl;
		std::cout << "Utilization    : " << CalculationUtilMemory() * 100.0 << " %" << std::endl;
	}
	// �󂫗e�ʂ̃`�F�b�N
	bool checkFreeSize(std::size_t size)
	{
		int check_free_size = allocinfo.full_size - getUsingMemory() - sizeof(AllocInfo);
		if (check_free_size < 0 || check_free_size < size)
		{
			OutputLog(size);
			return false;
		}
		return true;
	}

	// �\����
	AllocInfo allocinfo;
	MemInfo meminfo;
};

#endif // !MYALLOCATOR_H


/*---------------------------------------------------------------------
1. �\�񂳂ꂽ�������u���b�N�̐擪�|�C���^�̏����擾
	1-1. �\�񂳂ꂽ�������u���b�N���ŏ�����t���[�����������N���X�g�ɓo�^
2. ���ɑݏo�˗����������ɁA(1)�̐擪�|�C���^��Ԃ�
	2-1. �t���[�������u���b�N�̐擪�|�C���^��ۑ� (���ݏo�����тɍX�V
	2-2. �������u���b�N���ŏ��ɖ�������A���ۂɎg����^�̃t���[�̈��
		 �������u���b�N�̃T�C�Y���炱�̊Ǘ��̈����������
3. �ԋp���ꂽ�Ƃ��A�݂��o���Ǘ��̈�͎c���āA�݂��o���Ǘ��̈�
   �ւ̃|�C���^���A���P�[�^�Ǘ��̈�ɕۑ�
	3-1. �������A���P�[�^���̂��ė��p�\�ȃ���������L�[�v�������
4. ���ɑݏo�˗����������ɁA���g�p�̃t���[�������u���b�N�ł͂Ȃ�
   �A���P�[�^�Ǘ��̈�ɃL�[�v���Ă���ė��p�\��������݂��o��
	4-1. �A���P�[�^�̊Ǘ��̈�ɂ̓����N�̍Ō���̃t���[�������ւ�
		�|�C���^���o���Ă���
	4-2. �ԋp����t���[��������������x�ɁA���̍Ō���t���[��������
		�A�����ăA���P�[�^�̍Ō���t���[�������ւ̃|�C���^���X�V
5. �s���葽���L�[�v����ɂ́u�t���[�����������N���X�g�v�����
   (�t���[���������A�����ĘA�Ȃ��Ă��郊���N���X�g)
   5-1. �݂��o�����������̊Ǘ��̈�ɗ\�ߒǉ�
6.


			******************************

�t���[���������X�g����ŏI�I�Ƀ�������݂��o���ɂ́A

�E ���X�g����t���[������������o��
�E ���̃t���[����������v���T�C�Y��؂肾���邩�`�F�b�N
�E �؂�o�����
�E �v���T�C�Y���̐؂�o�����o���Ȃ��ꍇ�A���̂܂ܓn���邩�`�F�b�N
�E ���̂܂ܓn���Ȃ��ꍇ�͎��̃t���[�����������X�g������o��
---------------------------------------------------------------------*/