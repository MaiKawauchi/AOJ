#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>

template <typename T> // テンプレートであることを示す記述
class MyAllocator
{
public:
	// 要素の型
	using value_type = T;

	// 特殊関数(コンストラクタ)
	MyAllocator() {}
	MyAllocator(const MyAllocator&) {}
	MyAllocator(MyAllocator&&) {}

	// 別な要素型のアロケータを受け取るコンストラクタ
	template <typename U> MyAllocator(const MyAllocator<U>&);

	// =================================
	// 使用可能メモリ容量(10MB)の予約
	T* MyMalloc()
	{
		T* custom_capacity = (T*)malloc(sizeof(T) * m_max_available_memory);
		if (!custom_capacity) { return 0; }
		meminfo[0].m_next_ptr = custom_capacity;
		return custom_capacity;
	}

	// 使用可能メモリ容量(10MB)の解放
	void MyFree()
	{
		free(custom_capacity);
	}
	// =================================

	// メモリ領域の確保
	T* allocate(std::size_t num)
	{
		// 残りの空き容量よりも確保しようとしているサイズが大きい場合
		if (num > m_max_available_memory - getTotalCapacity())
		{
			CannotAlloc(num);
			m_util_flag = true;

			return nullptr;
		}

		const std::size_t size = num * sizeof(T);
		// フリーメモリブロックの先頭ポインタ
		T* const p = static_cast<T*>(meminfo[m_count].m_next_ptr);
		// フリーメモリブロックの先頭ポインタを更新
		meminfo[m_count+1].m_next_ptr = p + size;

		// 割り当てたポインタとサイズを確保
		meminfo[m_count].m_size = size;
		meminfo[m_count].m_ptr = p;

		m_total_capacity += size;
		m_count++;

		// 割り当てられたメモリ領域のメモリアドレスを返す
		return p;
	}

	// メモリ領域の解放
	void free(T* p)
	{
		m_has_alloc = false;

		// 解放してほしいポインタの場所を探す
		for (uint8_t i = 0; i < m_count; i++) {
			if (meminfo[i].m_ptr == p)
			{
				const std::size_t size = meminfo[i].m_size;
				m_total_capacity -= size;
				m_count--;

				// test output
				std::cout << size << std::endl;
				
				// TODO : メモリを解放
				// ポインタをひとつづつずらしてヌルを入れるか？

				m_has_alloc = true;
				meminfo[i].m_ptr = nullptr;

				break;
			}
		}
		// TODO : 未確保のポインタを指した場合エラー
		if(!m_has_alloc)
		{
			std::cout << "未確保のメモリを解放しようとしています" << std::endl;
		}
	}

	// 使用率を計算
	float CalculationUtilMemory()
	{
		m_util_memory = (float)(getTotalCapacity()) / m_max_available_memory;
		// test output
		std::cout << "Utilization    : " << m_util_memory * 100.0 << " %" << std::endl;
		return m_util_memory;
	}

	// 領域が確保できなかった場合のエラーログ
	void CannotAlloc(int rand_size_memory)
	{
		// 要求サイズ・総サイズ・使用率を表示
		std::cout << "Error : cannot allocate the memory." << std::endl;
		std::cout << "Request Size   : " << rand_size_memory << std::endl;
		std::cout << "Available Size : " << m_max_available_memory << std::endl;
		std::cout << "Utilization    : " << CalculationUtilMemory() * 100.0 << " %" << std::endl;
	}

	// 使用中容量を取得
	std::size_t getTotalCapacity() const
	{
		return m_total_capacity;
	}
	// メモリを割り付けた数
	std::size_t getCount() const
	{
		return m_count;
	}
	// メモリ使用率を取得
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
	
	// 使用率が100%を超えたかどうか
	bool m_util_flag = false;
	// 確保中であるかどうか
	bool m_has_alloc = false;
		
};

// static 初期化
template <typename T> uint32_t		MyAllocator<T>::m_max_available_memory = 0;
template <typename T> T*			MyAllocator<T>::custom_capacity = 0;
template <typename T> std::size_t	MyAllocator<T>::m_total_capacity = 0;
template <typename T> std::size_t	MyAllocator<T>::m_count = 0;
template <typename T> float			MyAllocator<T>::m_util_memory = 0.0;


// 比較演算子
template <typename T1, typename T2>
bool operator==(const MyAllocator<T1>&, const MyAllocator<T2>&) { return true; }
template <typename T1, typename T2>
bool operator!=(const MyAllocator<T1>&, const MyAllocator<T2>&) { return false; }

#endif // !ALLOCATOR_H