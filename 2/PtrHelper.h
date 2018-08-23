#pragma once
#include <stdio.h>
template <class T>
class CPtrHelper;

template <class T1>
class  U_Ptr
{
	friend class CPtrHelper<T1>;
	T1* m_Ptr;
	int m_count;
	U_Ptr(T1* lp) :m_Ptr(lp), m_count(1)
	{
	}
	~U_Ptr()
	{
		delete m_Ptr;
		m_Ptr = nullptr;
	}
};

template <class T>
class  CPtrHelper
{
private:
	// Pointer variable
	T* m_Ptr;
public:
	// Constructors
	CPtrHelper()
		:m_Ptr(0)
	{
	}

	CPtrHelper(T* lp)
	{
		m_Ptr = lp;
		if (m_Ptr != NULL)
		{
			m_Ptr->AddRef();
		}
	}

	CPtrHelper(const CPtrHelper<T>& lp)
	{
		m_Ptr = lp.m_Ptr;
		if (m_Ptr)
		{
			addRef();
		}
	}
	// Destructor
	virtual ~CPtrHelper()
	{
		if (m_Ptr != NULL)
		{
			release();
		}
	}
	void addRef()
	{
		m_Ptr->AddRef();
		//m_Ptr->m_count++;
	}
	void release()
	{
		T* old_ptr = m_Ptr;
		m_Ptr = NULL;
		old_ptr->Release();
		/*m_Ptr->m_count--;
		if (m_Ptr->m_count == 0)
		{
			delete m_Ptr;
		}
		m_Ptr = NULL;*/
	}
	// Conversion
public:
	operator T*()
	{
		return m_Ptr;
	}
	//T* operator *() { return m_Ptr; }
public:
	// Pointer operations
	//T& operator*()  { return *m_Ptr ;}
	//T** operator&() { return &m_Ptr ;}
	T* operator->() const
	{
		return m_Ptr;
	}

	// Assignment from the same interface
	T* operator=(const CPtrHelper& pI)
	{
		if (m_Ptr != pI.m_Ptr)
		{
			if (m_Ptr != NULL)
			{
				release();			// Release the old interface.
			}
			m_Ptr = pI.m_Ptr;
			if (m_Ptr != NULL)
			{
				addRef();
			}

		}
		return m_Ptr;
	}

	T* operator=(T* pI)
	{
		if (m_Ptr != pI)
		{
			T* pOld = m_Ptr;
			if (pOld)
			{
				release();
			}
			m_Ptr = pI;
			if (m_Ptr)
			{
				addRef();
			}
		}
		return m_Ptr;
	}

	// Boolean functions
	bool operator!() { return (m_Ptr == NULL) ? true : false ;}

	// Requires a compiler that supports bool
	 	operator bool() const
	 	{ 
			return (m_Ptr != NULL) ? true : false;
	 	}

	 	bool operator==(const CPtrHelper& pI)
	  	{
	  		return (m_Ptr == pI.m_Ptr) ? true : false;
	  	}
	 	/*bool operator==(const T* pI)
	 	{
	 		return (m_Ptr == pI) ? true : false;
	 	}*/
	// 
	 	bool operator!=(const CPtrHelper& pI)
	 	{
			return (m_Ptr != pI.m_Ptr) ? true : false;
	 	}
	// 
	  	/*bool operator!=(const T* pI) 
	 	{
			return (m_Ptr != pI) ? true : false;
	 	}*/
private:
	//T* operator==(T* pI)
	//{
	//	return (m_Ptr == pI) ? true : false;
	//}

public:
	template <class T1>
	CPtrHelper<T1> cast()
	{
		CPtrHelper<T1> ptr;
		if (m_Ptr)
		{
			ptr = dynamic_cast<T1*>(m_Ptr);
		}
		return ptr;
	}
};