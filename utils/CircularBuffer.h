#pragma once
#include "..\base\define.h"
#include <string>
class DLL_SAMPLE_API CCircularBuffer
{
protected:
	// ����
	char* m_pBuffer;
	// �����С
	int m_iBuferSize;
	// ͷλ��
	int m_iHeadPos;
	// βλ��
	int m_iTailPos;
protected:
	// �������ӻ�������
	virtual void BufferResize(void);
	// ����洦
	virtual bool IsOverflow(int Length);
	// �ж��Ƿ񳬹�����
	virtual bool IsIndexOverflow(int Length);
	// �����ڴ�
	virtual void Sort(void);
public:
	CCircularBuffer(void)
	{
		m_iBuferSize = 1024;
		m_pBuffer = new char[m_iBuferSize];
		m_iHeadPos = 0;
		m_iTailPos = 0;
	}

	virtual ~CCircularBuffer(void)
	{
		m_iBuferSize = 0;
		if(m_pBuffer)
		{
			delete m_pBuffer;
			m_pBuffer = 0;
		}
	}
	// ��ʼͷβ��λ��
	virtual void SetEmpty(void);
	// ���÷����ֽ�
	virtual bool HeadIncrease(int increasement=1); 
	//
	virtual void SetSize(int Length);
	//
	virtual int GetSize(void);
	// �õ����ݴ�С
	virtual int GetCount(void);
	//��û���
	virtual const char* GetBuffer(void);
	//�����ַ�
	virtual int Find(char c,int start=0);
	//
	virtual bool Copy(CCircularBuffer* pCircularBuffer,int Length);
	virtual bool Append(CCircularBuffer* pCircularBuffer,int Length);
public:
	// д����
	virtual bool Write(const char* lpBuffer, int Length);
	// ������
	virtual bool Read(char* lpBuffer, int Length);
	virtual bool Read(char* lpBuffer, int Length, int& RetLength);
	virtual bool Read(int pos, char* lpBuffer, int Length);
	//unsigned char
	virtual bool WriteChar(unsigned char n);
	virtual bool ReadChar(unsigned char& n);
	//Short
	virtual bool WriteShort(unsigned short n);
	virtual bool ReadShort(unsigned short& n);
	//unsigned int
	virtual bool WriteInt(unsigned int n);
	virtual bool ReadInt(unsigned int& n);
	//int64
	virtual bool WriteLonglong(long long n);
	virtual bool ReadLonglong(long long& n);
	//float
	virtual bool WriteFloat(float n);
	virtual bool ReadFloat(float& n);
	//double
	virtual bool WriteDouble(double n);
	virtual bool ReadDouble(double& n);
	//string
	virtual bool ReadString(char* p,int len);
};

//�������ӻ�������
inline void CCircularBuffer::BufferResize(void)
{
	//��ǰ�����С
	int prevBuferSize = m_iBuferSize;
	//����һ��
	m_iBuferSize <<= 1;
	//���뻺��
	char *pNewData = new char[m_iBuferSize];
	//�������»���
	memcpy(pNewData, m_pBuffer, prevBuferSize);
	//���ѭ��ʹ��
	if (m_iTailPos<m_iHeadPos) 
	{
		//����ѭ������
		memcpy(pNewData+prevBuferSize, m_pBuffer, m_iTailPos);
		m_iTailPos += prevBuferSize;
	}
	delete [] m_pBuffer;
	m_pBuffer = pNewData;
}

// ����洦
inline bool CCircularBuffer::IsOverflow(int Length)
{
	return (Length>=(m_iBuferSize-GetCount()));
}

// �ж��Ƿ񳬹�����
inline bool CCircularBuffer::IsIndexOverflow(int Length)
{
	return ((Length+m_iTailPos)>=m_iBuferSize);
}

// �����ڴ�
inline void CCircularBuffer::Sort(void)
{
    if (m_iTailPos<m_iHeadPos) 
    {
		//��Ҫ����
		//���뻺��
		char *pNewData = new char[m_iBuferSize];
		int count = m_iBuferSize-m_iHeadPos;
		//�������»���
		memcpy(pNewData, m_pBuffer+m_iHeadPos, count);

		//����ѭ������
		memcpy(pNewData+count, m_pBuffer, m_iTailPos);
		m_iTailPos += count;
		m_iHeadPos = 0;

		delete [] m_pBuffer;
		m_pBuffer = pNewData;
    }
}

//�õ����ݴ�С
inline int CCircularBuffer::GetCount(void)
{
	//β��ȥͷ
	int count = m_iTailPos-m_iHeadPos;
	//��������򻺴�ѭ��ʹ�ã�����ѭ������
	if (count<0) count = m_iBuferSize+count;
	return count;
}

inline void CCircularBuffer::SetSize(int Length)
{
	// �ж��Ƿ���Ҫ���뻺��
	while (IsOverflow(Length))
	{
		//�������뻺��
		BufferResize();
	}
}

inline int CCircularBuffer::GetSize(void)
{
	return m_iBuferSize-GetCount();
}

// ���÷����ֽ�
inline bool CCircularBuffer::HeadIncrease(int increasement)
{
	m_iHeadPos += increasement;
	m_iHeadPos %= m_iBuferSize;
	return m_iHeadPos!=m_iTailPos;
}

// ��ʼͷβ��λ��
inline void CCircularBuffer::SetEmpty(void)
{
	m_iHeadPos=0;
	m_iTailPos=0;
}

//��û���
inline const char* CCircularBuffer::GetBuffer(void)
{
	Sort();
	return m_pBuffer+m_iHeadPos;
}

//�����ַ�
inline int CCircularBuffer::Find(char c,int start)
{
	//�ж��Ƿ񳬹��������
	int Count = GetCount();
	int len = -1;
	int i = 0;
	char* pData = 0;
	//���ѭ��ʹ��
	if (m_iTailPos<m_iHeadPos)
	{
		//һ��
		int fc, sc;
		fc = m_iBuferSize-m_iHeadPos;
		sc = Count - fc;

		pData = m_pBuffer+m_iHeadPos;
		for(i=start;i<fc;i++)
		{
			if(pData[i]==c)
			{
				len = i+1;
				break;
			}
		}
		if(sc&&(len==-1))
		{
			if(start<fc)
			{
				start = 0;
			}
			else
			{
				start = start-fc;
			}
			pData = m_pBuffer;
			for(i=start;i<sc;i++)
			{
				if(pData[i]==c)
				{
					len = fc+i+1;
					break;
				}
			}
		}
	}
	else
	{
		//һ��
		pData = m_pBuffer+m_iHeadPos;
		for(i=start;i<Count;i++)
		{
			if(pData[i]==c)
			{
				len = i+1;
				break;
			}
		}
	}
	return len;
}

//
inline bool CCircularBuffer::Copy(CCircularBuffer* pCircularBuffer,int Length)
{
	SetEmpty();
	// �ж��Ƿ���Ҫ���뻺��
	while (IsOverflow(Length))
	{
		//�������뻺��
		BufferResize();
	}
	if(pCircularBuffer->Read(m_pBuffer,Length))
	{
		m_iTailPos = Length;
		return true;
	}
	return false;
}

//
inline bool CCircularBuffer::Append(CCircularBuffer* pCircularBuffer,int Length)
{
	// �ж��Ƿ���Ҫ���뻺��
	while (IsOverflow(Length))
	{
		//�������뻺��
		BufferResize();
	}
	//�ж��Ƿ���Ҫѭ��ʹ��
	if (IsIndexOverflow(Length))
	{
		//����
		int FirstCopyLen = m_iBuferSize-m_iTailPos;
		//ѭ������
		int SecondCopyLen = Length-FirstCopyLen;
		//��������
		if(pCircularBuffer->Read(m_pBuffer+m_iTailPos,FirstCopyLen))
		{
			//ѭ������
			if (SecondCopyLen)
			{
				//������ѭ������
				if(pCircularBuffer->Read(FirstCopyLen,m_pBuffer,SecondCopyLen))
				{
					//���Ӵ�С
					m_iTailPos = SecondCopyLen;
					return true;
				}
			}
			else
			{
				//����
				m_iTailPos = 0;
				return true;
			}
		}
	}
	else
	{
		if(pCircularBuffer->Read(m_pBuffer+m_iTailPos,Length))
		{
			m_iTailPos += Length;
			return true;
		}
	}


	return false;
}

//д����
inline bool CCircularBuffer::Write(const char* lpBuffer, int Length)
{
	// �������0����
	if (Length==0)
	{
		return false;
	}
	// �ж��Ƿ���Ҫ���뻺��
	while (IsOverflow(Length))
	{
		//�������뻺��
		BufferResize();
	}
	//�ж��Ƿ���Ҫѭ��ʹ��
	if (IsIndexOverflow(Length))
	{
		//����
		int FirstCopyLen = m_iBuferSize-m_iTailPos;
		//ѭ������
		int SecondCopyLen = Length-FirstCopyLen;
		//��������
		memcpy(m_pBuffer+m_iTailPos, lpBuffer, FirstCopyLen);
		//ѭ������
		if (SecondCopyLen)
		{
			//������ѭ������
			memcpy(m_pBuffer, lpBuffer+FirstCopyLen, SecondCopyLen);
			//���Ӵ�С
			m_iTailPos = SecondCopyLen;
		}
		else
		{
			//����
			m_iTailPos = 0;
		}
	}
	else
	{
		//��������
		memcpy(m_pBuffer+m_iTailPos, lpBuffer, Length);
		//���Ӵ�С
		m_iTailPos += Length;
	}

	return true;
}

// ������
inline bool CCircularBuffer::Read(char* lpBuffer, int Length)
{
	//�ж��Ƿ񳬹��������
	int Count = GetCount();
	if(Length>Count)
	{
		return false;
	}
	//
	if (Length < m_iBuferSize-m_iHeadPos)
	{
		memcpy(lpBuffer, m_pBuffer+m_iHeadPos, Length);
	}
	else
	{
		int fc, sc;
		fc = m_iBuferSize-m_iHeadPos;
		sc = Length - fc;
		memcpy(lpBuffer, m_pBuffer+m_iHeadPos, fc);
		if (sc) memcpy(lpBuffer+fc, m_pBuffer, sc);
	}

	return true;
}

// ������
inline bool CCircularBuffer::Read(char* lpBuffer, int Length, int& RetLength)
{
	//�ж��Ƿ񳬹��������
	int Count = GetCount();
	if(Length>Count)
	{
		Length = Count;
	}
	//
	if (Length < m_iBuferSize-m_iHeadPos)
	{
		memcpy(lpBuffer, m_pBuffer+m_iHeadPos, Length);
	}
	else
	{
		int fc, sc;
		fc = m_iBuferSize-m_iHeadPos;
		sc = Length - fc;
		memcpy(lpBuffer, m_pBuffer+m_iHeadPos, fc);
		if (sc) memcpy(lpBuffer+fc, m_pBuffer, sc);
	}
	RetLength = Length;

	return true;
}

//���word
inline bool CCircularBuffer::Read(int pos, char* lpBuffer, int Length)
{
	//�ж��Ƿ񳬹��������
	int Count = GetCount();
	if(Length+pos>Count)
	{
		return false;
	}
	//
	if( (pos+Length) <= (m_iBuferSize-m_iHeadPos) )
	{
		memcpy(lpBuffer, m_pBuffer+m_iHeadPos+pos, Length);
	}
	else
	{
		int fc;
		fc = m_iBuferSize-m_iHeadPos;
		if(fc>pos)
		{
			int l = Length-(fc-pos);
			memcpy(lpBuffer, m_pBuffer+m_iHeadPos+pos, l);
			memcpy(lpBuffer+l, m_pBuffer, Length-l);
		}
		else
		{
			pos -= fc;
			memcpy(lpBuffer, m_pBuffer+pos, Length);
		}
	}

	return true;
}

inline bool CCircularBuffer::WriteChar(unsigned char n)
{
	return Write((const char*)&n,sizeof(unsigned char));
}

inline bool CCircularBuffer::ReadChar(unsigned char& n)
{
	if(Read((char*)&n,sizeof(unsigned char)))
	{
		HeadIncrease(sizeof(unsigned char));
		return true;
	}
	return false;
}

inline bool CCircularBuffer::WriteShort(unsigned short n)
{
	return Write((const char*)&n,sizeof(unsigned short));
}

inline bool CCircularBuffer::ReadShort(unsigned short& n)
{
	if(Read((char*)&n,sizeof(unsigned short)))
	{
		HeadIncrease(sizeof(unsigned short));
		return true;
	}
	return false;
}

inline bool CCircularBuffer::WriteInt(unsigned int n)
{
	return Write((const char*)&n,sizeof(unsigned int));
}

inline bool CCircularBuffer::ReadInt(unsigned int& n)
{
	if(Read((char*)&n,sizeof(unsigned int)))
	{
		HeadIncrease(sizeof(unsigned int));
		return true;
	}
	return false;
}

inline bool CCircularBuffer::WriteLonglong(long long n)
{
	return Write((const char*)&n,sizeof(long long));
}

inline bool CCircularBuffer::ReadLonglong(long long& n)
{
	if(Read((char*)&n,sizeof(long long)))
	{
		HeadIncrease(sizeof(long long));
		return true;
	}
	return false;
}

inline bool CCircularBuffer::WriteFloat(float n)
{
	return Write((const char*)&n,sizeof(float));
}

inline bool CCircularBuffer::ReadFloat(float& n)
{
	if(Read((char*)&n,sizeof(float)))
	{
		HeadIncrease(sizeof(float));
		return true;
	}
	return false;
}

inline bool CCircularBuffer::WriteDouble(double n)
{
	return Write((const char*)&n,sizeof(double));
}

inline bool CCircularBuffer::ReadDouble(double& n)
{
	if(Read((char*)&n,sizeof(double)))
	{
		HeadIncrease(sizeof(double));
		return true;
	}
	return false;
}

inline bool CCircularBuffer::ReadString(char* p,int len)
{
	if(Read(p,len))
	{
		HeadIncrease(len);
		return true;
	}
	return false;
}