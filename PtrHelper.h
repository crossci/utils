#pragma once
template <class T> class U_Ptr
{
	friend class CPtrHelper;
	T* m_Ptr;
	int m_count;
	U_Ptr(T* lp) :m_Ptr(lp), m_count(1)
	{
	}
	~U_Ptr()
	{
		delete m_Ptr;
		m_Ptr = nullptr;
	}
};

template <class T> class CPtrHelper
{
private:
	// Pointer variable
	U_Ptr<T>* m_Ptr;
public:
	// Constructors
	CPtrHelper()
		:m_Ptr(0)
	{	
	}

	CPtrHelper(T* lp)
	{
		if (lp != nullptr)
 		{
			m_Ptr = new U_Ptr<T>(lp);
 		}
	}

	CPtrHelper(const CPtrHelper& lp)
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
		if (m_Ptr != nullptr)
		{
			release();
		}
	}
	void addRef()
	{
		m_count++;
	}
	void release()
	{
		m_count--;
		if (m_count == 0)
		{
			delete m_Ptr;
			m_Ptr = nullptr;
		}
	}
	// Conversion
public:
	operator T*() { return m_Ptr ;}
	//T* operator *() { return m_Ptr; }
public:
	// Pointer operations
	//T& operator*()  { return *m_Ptr ;}
	//T** operator&() { return &m_Ptr ;}
	T* operator->() const
	{ return m_Ptr; }

	// Assignment from the same interface
	T* operator=(const CPtrHelper& pI)
	{
		if (m_Ptr != pI.m_Ptr)
		{
			T* pOld = m_Ptr ;		// Save current value.
			m_Ptr = pI.m_Ptr ;      // Assign new value.
			if (pOld != nullptr)
			{
				release()			// Release the old interface.
			}
			if (m_Ptr != nullptr)
			{
				m_Ptr->AddRef();
			}
			
		}
		return m_Ptr ;
	}

	T* operator=(T* pI)
	{
		if (m_Ptr != pI)
		{
			T* pOld = m_Ptr;    // Save current value.
			m_Ptr = pI;                // Assign new value.
			if (m_Ptr != nullptr)
			{
				m_Ptr->AddRef();
			}
			if (pOld != nullptr)
			{
				pOld->Release();       // Release the old interface.
			}
		}
		return m_Ptr;
	}

	// Boolean functions
	//bool operator!() { return (m_Ptr == nullptr) ? true : false ;}

	// Requires a compiler that supports bool
// 	operator bool() const
// 	{ 
// 		return (m_Ptr != nullptr) ? true : false ; 
// 	}

// 	bool operator==(const CPtrHelper& pI)
//  	{
//  		return (m_Ptr == pI.m_Ptr) ? true : false;
//  	}
// 
// 	bool operator==(const T* pI)
// 	{
// 		return (m_Ptr == pI) ? true : false;
// 	}
// 
// 	bool operator!=(const CPtrHelper& pI)
// 	{
// 		return (m_Ptr == pI.m_Ptr) ? true : false;
// 	}
// 
//  	bool operator!=(const T* pI) 
// 	{
// 		return (m_Ptr != nullptr) ? true : false; 
// 	}
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