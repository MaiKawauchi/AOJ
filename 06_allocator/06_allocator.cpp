#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <memory>
#include <random>
#include "myAllocator.h"

#define MAX_AVAILABLE_MEMORY 1000	// 使用可能メモリ容量
#define THRESHOLD 0.7				// しきい値(70%)
#define MAX_RANDOM_RANGE 100		// 乱数の最大値
#define TEST_LOOPCOUNT 50			// 70%に達した後にまわす回数
#define ODDNUM 2					// 奇数


//メルセンヌツイスタ
int Random_MT()
{
	std::random_device seed_gen;		// 非決定的な乱数生成器
	std::mt19937 engine(seed_gen());	// シード指定
	return engine();
}

// 1B - 1000000B(1MB) の範囲でランダムな値を生成する
uint32_t Random_1Bto1MB()
{
	uint32_t mt = Random_MT();
	uint32_t val = (uint32_t)(mt % MAX_RANDOM_RANGE) + 1;
	std::cout << val << std::endl;
	return val;
}

// メモリ確保
void MyAlloc(uint8_t* pointer, MyAllocator<uint8_t> alc)
{

	
}

int main()
{
	auto alc = MyAllocator<uint8_t>();

	// 使用可能メモリ容量をアロケーターに教える
	alc.getMaxAvailableMemory(MAX_AVAILABLE_MEMORY);
	alc.MyMalloc();
	// 確保したポインタを格納する配列
	uint8_t* mem_ptr[MAX_AVAILABLE_MEMORY];

	// =================================
	// 総容量の70%まで確保し続ける
	// =================================
	uint8_t upto70 = 0;
	for (upto70 = 0; alc.getUtilMemory() <= THRESHOLD; upto70++) 
	{
		// 1B-1MBの範囲でランダムな値を取得
		uint32_t rand_size_memory = Random_1Bto1MB();

		// メモリを確保し、ポインターとサイズを保持
		mem_ptr[upto70] = alc.allocate(rand_size_memory);

		// test output :使用率を取得
		alc.CalculationUtilMemory();
	}

	// =================================
	// ここから確保と開放を繰り返す
	// =================================
	for (int j = 0; j < TEST_LOOPCOUNT; j++)
	{
		// 確保（true）するか、解放（false）するか
		bool do_alloc = Random_MT() % ODDNUM;
		if (do_alloc)
		{
			std::cout << "確保します" << std::endl;

			// 1B-1MBの範囲でランダムな値を取得
			uint32_t rand_size_memory = Random_1Bto1MB();

			// ランダムサイズでメモリ確保
			mem_ptr[upto70 + j] = alc.allocate(rand_size_memory);

			// test output : 使用率を取得
			alc.CalculationUtilMemory();
		}
		else
		{
			std::cout << "*** 解放します" << std::endl;
			// 領域を解放する
			alc.free(mem_ptr[Random_MT() % alc.getCount()]);

			// test output :使用率を取得
			alc.CalculationUtilMemory();
		}
	}
	alc.MyFree();
  	return 0;
}