#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>

template <typename T> // �e���v���[�g�ł��邱�Ƃ������L�q
class MyAllocator
{
public:
	// �v�f�̌^
	using value_type = T;

	// ����֐�(�R���X�g���N�^)
	MyAllocator() {}
	MyAllocator(const MyAllocator&) {}
	MyAllocator(MyAllocator&&) {}

	// �ʂȗv�f�^�̃A���P�[�^���󂯎��R���X�g���N�^
	template <typename U> MyAllocator(const MyAllocator<U>&);

	// =================================
	// �g�p�\�������e��(10MB)�̗\��
	T* MyMalloc()
	{
		T* custom_capacity = (T*)malloc(sizeof(T) * m_max_available_memory);
		if (!custom_capacity) { return 0; }
		meminfo[0].m_next_ptr = custom_capacity;
		return custom_capacity;
	}

	// �g�p�\�������e��(10MB)�̉��
	void MyFree()
	{
		free(custom_capacity);
	}
	// =================================

	// �������̈�̊m��
	T* allocate(std::size_t num)
	{
		// �c��̋󂫗e�ʂ����m�ۂ��悤�Ƃ��Ă���T�C�Y���傫���ꍇ
		if (num > m_max_available_memory - getTotalCapacity())
		{
			CannotAlloc(num);
			m_util_flag = true;

			return nullptr;
		}

		const std::size_t size = num * sizeof(T);
		// �t���[�������u���b�N�̐擪�|�C���^
		T* const p = static_cast<T*>(meminfo[m_count].m_next_ptr);
		// �t���[�������u���b�N�̐擪�|�C���^���X�V
		meminfo[m_count+1].m_next_ptr = p + size;

		// ���蓖�Ă��|�C���^�ƃT�C�Y���m��
		meminfo[m_count].m_size = size;
		meminfo[m_count].m_ptr = p;

		m_total_capacity += size;
		m_count++;

		// ���蓖�Ă�ꂽ�������̈�̃������A�h���X��Ԃ�
		return p;
	}

	// �������̈�̉��
	void free(T* p)
	{
		m_has_alloc = false;

		// ������Ăق����|�C���^�̏ꏊ��T��
		for (uint8_t i = 0; i < m_count; i++) {
			if (meminfo[i].m_ptr == p)
			{
				const std::size_t size = meminfo[i].m_size;
				m_total_capacity -= size;
				m_count--;

				// test output
				std::cout << size << std::endl;
				
				// TODO : �����������
				// �|�C���^���ЂƂÂ��炵�ăk�������邩�H

				m_has_alloc = true;
				meminfo[i].m_ptr = nullptr;

				break;
			}
		}
		// TODO : ���m�ۂ̃|�C���^���w�����ꍇ�G���[
		if(!m_has_alloc)
		{
			std::cout << "���m�ۂ̃�������������悤�Ƃ��Ă��܂�" << std::endl;
		}
	}

	// �g�p�����v�Z
	float CalculationUtilMemory()
	{
		m_util_memory = (float)(getTotalCapacity()) / m_max_available_memory;
		// test output
		std::cout << "Utilization    : " << m_util_memory * 100.0 << " %" << std::endl;
		return m_util_memory;
	}

	// �̈悪�m�ۂł��Ȃ������ꍇ�̃G���[���O
	void CannotAlloc(int rand_size_memory)
	{
		// �v���T�C�Y�E���T�C�Y�E�g�p����\��
		std::cout << "Error : cannot allocate the memory." << std::endl;
		std::cout << "Request Size   : " << rand_size_memory << std::endl;
		std::cout << "Available Size : " << m_max_available_memory << std::endl;
		std::cout << "Utilization    : " << CalculationUtilMemory() * 100.0 << " %" << std::endl;
	}

	// �g�p���e�ʂ��擾
	std::size_t getTotalCapacity() const
	{
		return m_total_capacity;
	}
	// ������������t������
	std::size_t getCount() const
	{
		return m_count;
	}
	// �������g�p�����擾
	float getUtilMemory() const
	{
		return m_util_memory;
	}
	uint32_t getMaxAvailableMemory(uint32_t val)
	{
		return m_max_available_memory = val;
	}


	// =================================
private:
	static uint32_t		m_max_available_memory;
	static T*			custom_capacity;
	static std::size_t	m_total_capacity;
	static std::size_t	m_count;
	static float		m_util_memory;
	// =================================
	struct MemInfo
	{
		std::size_t	m_size;
		uint8_t*	m_ptr;
		uint8_t*	m_next_ptr;
	};
	MemInfo meminfo[1000];
	
	// �g�p����100%�𒴂������ǂ���
	bool m_util_flag = false;
	// �m�ے��ł��邩�ǂ���
	bool m_has_alloc = false;
		
};

// static ������
template <typename T> uint32_t		MyAllocator<T>::m_max_available_memory = 0;
template <typename T> T*			MyAllocator<T>::custom_capacity = 0;
template <typename T> std::size_t	MyAllocator<T>::m_total_capacity = 0;
template <typename T> std::size_t	MyAllocator<T>::m_count = 0;
template <typename T> float			MyAllocator<T>::m_util_memory = 0.0;


// ��r���Z�q
template <typename T1, typename T2>
bool operator==(const MyAllocator<T1>&, const MyAllocator<T2>&) { return true; }
template <typename T1, typename T2>
bool operator!=(const MyAllocator<T1>&, const MyAllocator<T2>&) { return false; }

#endif // !ALLOCATOR_H