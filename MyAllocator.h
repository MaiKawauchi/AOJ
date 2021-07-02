#ifndef MYALLOCATOR_H
#define MYALLOCATOR_H

#include <iostream>

class MyAllocator
{
private:
	// アロケーター管理情報
	// atention : sizeof(AllocInfo)でその構造体のサイズを計算できる
	struct AllocInfo
	{
		uint32_t full_size;		// メモリブロックの総サイズ 
		void* free_mem_ptr;		// フリーメモリブロックへのポインタ
	};

	// 貸し出し管理領域
	struct MemInfo
	{
		// atention : 貸し出すメモリのポインタはMemInfo::getMem()となる
		std::size_t mem_size;	// 貸し出しメモリサイズ
		uint8_t* getMem()		// メモリブロック 
		{
			return reinterpret_cast<uint8_t*>(this) + sizeof(MemInfo);
		}
	};

	// 貸出中容量
	std::size_t m_using_memory = 0;

public:
	// コンストラクタ
	MyAllocator() {}

	void* allocate(std::size_t size)
	{
		if(checkFreeSize(size))
		{
			// フリーメモリブロックの先頭ポインタ
			void* p = allocinfo.free_mem_ptr;
			// フリーメモリブロックの先頭ポインタを更新
			allocinfo.free_mem_ptr = reinterpret_cast<uint8_t*>(p) + size;

			// 貸し出したポインタとサイズを確保
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

	// 線形リストを管理
	void linkListManager()
	{

	}
	// 貸出中容量を取得
	std::size_t getUsingMemory() const
	{
		return m_using_memory;
	}
	// 貸出率を計算
	float CalculationUtilMemory()
	{
		float m_util_memory = (float)(getUsingMemory()) / allocinfo.full_size;
		// test output
		std::cout << "Utilization    : " << m_util_memory * 100.0 << " %" << std::endl;
		return m_util_memory;
	}
	// 領域が確保できなかった場合のエラーログ
	void OutputLog(int rand_size_memory)
	{
		// 要求サイズ・総サイズ・使用率を表示
		std::cout << "Error : cannot allocate the memory." << std::endl;
		std::cout << "Request Size   : " << rand_size_memory << std::endl;
		std::cout << "Available Size : " << allocinfo.full_size << std::endl;
		std::cout << "Utilization    : " << CalculationUtilMemory() * 100.0 << " %" << std::endl;
	}
	// 空き容量のチェック
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

	// 構造体
	AllocInfo allocinfo;
	MemInfo meminfo;
};

#endif // !MYALLOCATOR_H


/*---------------------------------------------------------------------
1. 予約されたメモリブロックの先頭ポインタの情報を取得
	1-1. 予約されたメモリブロックを最初からフリーメモリリンクリストに登録
2. 次に貸出依頼が来た時に、(1)の先頭ポインタを返す
	2-1. フリーメモリブロックの先頭ポインタを保存 (※貸出すたびに更新
	2-2. メモリブロックを最初に貰った時、実際に使える真のフリー領域は
		 メモリブロックのサイズからこの管理領域を引いた分
3. 返却されたとき、貸し出し管理領域は残して、貸し出し管理領域
   へのポインタをアロケータ管理領域に保存
	3-1. メモリアロケータ自体が再利用可能なメモリを一つキープした状態
4. 次に貸出依頼が来た時に、未使用のフリーメモリブロックではなく
   アロケータ管理領域にキープしてある再利用可能メモリを貸し出す
	4-1. アロケータの管理領域にはリンクの最後尾のフリーメモリへの
		ポインタを覚えておく
	4-2. 返却されフリーメモリが増える度に、その最後尾フリーメモリに
		連結してアロケータの最後尾フリーメモリへのポインタを更新
5. 不特定多数キープするには「フリーメモリリンクリスト」を作る
   (フリーメモリが連結して連なっているリンクリスト)
   5-1. 貸し出したメモリの管理領域に予め追加
6.


			******************************

フリーメモリリストから最終的にメモリを貸し出すには、

・ リストからフリーメモリを一つ取り出す
・ そのフリーメモリから要求サイズを切りだせるかチェック
・ 切り出し作業
・ 要求サイズ分の切り出しが出来ない場合、そのまま渡せるかチェック
・ そのまま渡せない場合は次のフリーメモリをリストから取り出す
---------------------------------------------------------------------*/