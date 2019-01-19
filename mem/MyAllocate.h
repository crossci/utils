#pragma once
#include <stdarg.h>
#include <stdlib.h>   
#include <malloc.h>
#include<iostream>
namespace MY_MEMORY_ALLOC
{

	typedef void(*FUNC_HANDLER)();

	// 一级空间配置器
	class BigAllocStrategy
	{
	private:
		static void* OomMalloc(size_t n)
		{
			void* result;

			for (;;) {
				if (0 == __MallocAllocOomHandler)
				{
					throw std::bad_alloc();
				}

				(*__MallocAllocOomHandler)();

				result = malloc(n);
				if (result)
					return(result);
			}
		}

		//static void (* __MallocAllocOomHandler)();
		static FUNC_HANDLER __MallocAllocOomHandler;

	public:
		static void* allocate(size_t n)
		{
			void *result = malloc(n);
			if (0 == result)
				result = OomMalloc(n);

			return result;
		}

		static void deallocate(void *p, size_t /* n */)
		{
			free(p);
		}

		//static void (* SetMallocHandler(void (*f)()))()
		static FUNC_HANDLER SetMallocHandler(FUNC_HANDLER f)
		{
			FUNC_HANDLER old = __MallocAllocOomHandler;
			__MallocAllocOomHandler = f;
			return(old);
		}
	};

	FUNC_HANDLER BigAllocStrategy::__MallocAllocOomHandler = 0;

	// 二级空间配置器

	class SmallAllocStrategy {

		enum {__ALIGN = 8};			// 基准值
		enum {__MAX_BYTES = 128};	// 最大值
		enum {__NFREELISTS = __MAX_BYTES/__ALIGN};	// 自由链表的大小

		union Obj
		{
			union Obj* _freeListLink;	// 指向下一个内存块对象的指针
			char _clientData[1];		/* The client sees this.*/
		};

	public:
		// 7 8 9
		static size_t FREELIST_INDEX(size_t bytes)
		{
			return (((bytes) + __ALIGN-1)/__ALIGN - 1);
		}

		// 7 8 9
		static size_t ROUND_UP(size_t bytes)
		{
			return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
		}

		static char* ChunkAlloc(size_t n, size_t& nobjs)
		{
			char * result;
			size_t totalBytes = n * nobjs;
			size_t bytesLeft = _endFree - _startFree;

			// 
			// 1.内存池有足够20个对象大小空间，则直接分配
			// 2.不够20个，大于1一个，只能分配多少分配多少
			// 3.不够1个，则处理剩余空间，到系统分配。
			//
			if (bytesLeft >= totalBytes)
			{
				result = _startFree;
				_startFree += totalBytes;
				return result;
			}
			else if (bytesLeft >= n)
			{
				nobjs = bytesLeft/n;
				totalBytes = nobjs*n;
				result = _startFree;
				_startFree += totalBytes;

				return result;
			}
			else
			{
				size_t bytesToGet = 2 * totalBytes + ROUND_UP(_heapSize >> 4);

				// 将剩余空间挂到自由链表
				if (bytesLeft > 0)
				{
					size_t index = FREELIST_INDEX(bytesLeft);
					((Obj*)_startFree)->_freeListLink = _freeList[index];
					_freeList[index] = (Obj*)_startFree;
				}

				_startFree = (char*)malloc(bytesToGet);
				if (_startFree == 0)
				{
					// 到更大的自由链表位置去取
					for (size_t i = n; i <= __MAX_BYTES; i+=__ALIGN)
					{
						size_t index = FREELIST_INDEX(i);
						if (_freeList[index])
						{
							Obj* first = _freeList[index];
							_startFree = (char*)first;
							_freeList[index] = first->_freeListLink;
							_endFree = _startFree+i;
							return ChunkAlloc(n, nobjs);
						}
					}

					// 最后一根救命稻草
					_startFree = (char*)BigAllocStrategy::allocate(bytesToGet);

				}

				_endFree = _startFree+bytesToGet;
				_heapSize += bytesToGet;
				return ChunkAlloc(n, nobjs);
			}
		}

		static void* Refill(size_t n)
		{
			size_t nobjs = 20;
			char* chunk = ChunkAlloc(n, nobjs);

			if (1 == nobjs)
				return chunk;

			size_t index = FREELIST_INDEX(n);

			// 将剩余的块挂到自由链表
			Obj* cur = (Obj*)(chunk+n);
			_freeList[index] = cur;

			for (size_t i = 2; i < nobjs; ++i)
			{
				Obj* next = (Obj*)(chunk+n*i);
				cur->_freeListLink = next;
				cur = next;
			}

			cur->_freeListLink = NULL;
			return chunk;
		}

		static void* allocate(size_t n)
		{

			if (n > 128)
			{
				return BigAllocStrategy::allocate(n);
			}

			// 计算需要的内存块在自由链表中的位置
			void* ret = 0;
			size_t index = FREELIST_INDEX(n);
			if (_freeList[index] == 0)
			{
				// 找内存池进行分配填充
				ret = Refill(ROUND_UP(n));
			}
			else
			{
				// 头删，返回头内存块
				ret = _freeList[index];
				_freeList[index] = ((Obj*)ret)->_freeListLink;
			}

			return ret;
		}
	
		static void deallocate(void* p, size_t n)
		{

			if (n > 128)
			{
				BigAllocStrategy::deallocate(p, n);
				return;
			}

			size_t index = FREELIST_INDEX(n);
			((Obj*)p)->_freeListLink = _freeList[index];
			_freeList[index] = (Obj*)p;
		}

	private:
		// 自由链表 
		static Obj* _freeList[__NFREELISTS];

		// 内存池
		static char* _startFree; // 内存池的起始位置
		static char* _endFree;	 // 内存池的水位线

		static size_t _heapSize; // 已分配空间大小（反馈调节）
	};

	char* SmallAllocStrategy::_startFree = 0;
	char* SmallAllocStrategy::_endFree = 0;
	size_t SmallAllocStrategy::_heapSize = 0;
	SmallAllocStrategy::Obj* SmallAllocStrategy::_freeList[__NFREELISTS] = { 0 };


	template<class T, class AllocStrategy>
	class MyAlloc
	{

	public:
		static T* alloc(size_t n)
		{ 
			return 0 == n ? 0 : (T*)AllocStrategy::allocate(n * sizeof(T));
		}

		static T* allocate(void)
		{ 
			return (T*)AllocStrategy::allocate(sizeof(T));
		}

		static void deallocate(T *p, size_t n)
		{ 
			if (0 != n)
				AllocStrategy::deallocate(p, n * sizeof(T));
		}

		static void deallocate(T *p)
		{ 
			AllocStrategy::deallocate(p, sizeof(T));
		}
	};

}