#pragma once
#include <stdarg.h>
#include <stdlib.h>   
#include <malloc.h>
#include<iostream>
namespace MY_MEMORY_ALLOC
{

	typedef void(*FUNC_HANDLER)();

	// һ���ռ�������
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

	// �����ռ�������

	class SmallAllocStrategy {

		enum {__ALIGN = 8};			// ��׼ֵ
		enum {__MAX_BYTES = 128};	// ���ֵ
		enum {__NFREELISTS = __MAX_BYTES/__ALIGN};	// ��������Ĵ�С

		union Obj
		{
			union Obj* _freeListLink;	// ָ����һ���ڴ������ָ��
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
			// 1.�ڴ�����㹻20�������С�ռ䣬��ֱ�ӷ���
			// 2.����20��������1һ����ֻ�ܷ�����ٷ������
			// 3.����1��������ʣ��ռ䣬��ϵͳ���䡣
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

				// ��ʣ��ռ�ҵ���������
				if (bytesLeft > 0)
				{
					size_t index = FREELIST_INDEX(bytesLeft);
					((Obj*)_startFree)->_freeListLink = _freeList[index];
					_freeList[index] = (Obj*)_startFree;
				}

				_startFree = (char*)malloc(bytesToGet);
				if (_startFree == 0)
				{
					// ���������������λ��ȥȡ
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

					// ���һ����������
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

			// ��ʣ��Ŀ�ҵ���������
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

			// ������Ҫ���ڴ�������������е�λ��
			void* ret = 0;
			size_t index = FREELIST_INDEX(n);
			if (_freeList[index] == 0)
			{
				// ���ڴ�ؽ��з������
				ret = Refill(ROUND_UP(n));
			}
			else
			{
				// ͷɾ������ͷ�ڴ��
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
		// �������� 
		static Obj* _freeList[__NFREELISTS];

		// �ڴ��
		static char* _startFree; // �ڴ�ص���ʼλ��
		static char* _endFree;	 // �ڴ�ص�ˮλ��

		static size_t _heapSize; // �ѷ���ռ��С���������ڣ�
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