#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <memory>
#include <random>
#include "MyAllocator.h"

#define MAX_AVAILABLE_MEMORY 1000	// 使用可能メモリ容量
#define MAX_RANDOM_RANGE 100		// 乱数の最大値
#define TEST_LOOPCOUNT 50			// 70%に達した後にまわす回数
#define THRESHOLD 0.7				// しきい値(70%)
#define ODDNUM 2					// 奇数



// メルセンヌツイスタ
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



/*---------------------------------------------------------------------
1. 100MBのメモリブロックを予約
2. メモリを確保してもらう(サイズを渡してポインタが返る)
3. メモリを開放してもらう(ポインタを渡す)
---------------------------------------------------------------------*/

int main()
{
	MyAllocator alc = MyAllocator();
	
	// アロケーター用メモリブロックの予約
	void* capacity = malloc(sizeof(uint8_t) * MAX_AVAILABLE_MEMORY);
	if(capacity == NULL)
	{
		std::cout << "Error : cannot malloc the memory." << std::endl;
		exit(1);
	}
	// 初期化
	alc.initialize(capacity, MAX_AVAILABLE_MEMORY);

	// 確保した先頭ポインタを格納する配列
	uint8_t* mem_ptr[MAX_AVAILABLE_MEMORY];
	

	// =================================
	// 総容量の70%まで確保し続ける
	// =================================
	uint8_t total_num = 0;
	for (int i = 0; alc.CalculationUtilMemory() <= THRESHOLD; i++)
	{
		std::cout << "[alloc]　";

		// 1B-1MBの範囲でランダムな値を取得
		uint32_t rand_size_memory = Random_1Bto1MB();

		// メモリ貸出依頼をし、帰ってきたポインターを保持
		mem_ptr[i] = reinterpret_cast<uint8_t*>(alc.allocate(rand_size_memory));
		total_num++;
	}
	
	// =================================
	// ここから確保と開放を繰り返す
	// =================================
	for (int j = 0; j < TEST_LOOPCOUNT; j++)
	{
		// 確保（true）するか、解放（false）するか
		bool do_alloc = true;// Random_MT() % ODDNUM;
		if (do_alloc)
		{
			std::cout << "[alloc]　";

			// 1B-1MBの範囲でランダムな値を取得
			uint32_t rand_size_memory = Random_1Bto1MB();

			// ランダムサイズでメモリ確保
			mem_ptr[total_num + j + 1] = reinterpret_cast<uint8_t*>(alc.allocate(rand_size_memory));
			total_num++;
		}
		else
		{
			std::cout << "[free]　";

			// 領域を解放する
			alc.free(mem_ptr[Random_MT() % total_num]);

			// test output :使用率を取得
			alc.CalculationUtilMemory();
			total_num--;
		}
	}
	free(capacity);
	return 0;
}