
#pragma once
#include <vector>
#include "PtrHelper.h"
class FileUtils
{
public:
	static bool splitFileName(const char* fileName, char* name, char* ext);

	static void getTimeArray(std::vector<int>& vector);

	static void GetCurrentDir(char* curDir);

	static void generateFullPath(const char* fileName,char* pathName);

	static FILE* openFile(const char* fileName, const char* mode);

	static int getFileLen(const char* fileName);

	static CPtrHelper<char*> getFile();

	//todo
	//md5
	//crc
	//һЩ���õļ����㷨
	//http ���� ����
	//����bat�ļ�
	//����Ŀ¼
	//����
	//���ݿ�
	//��־ϵͳ
	//����ָ��
	//�ڴ�� �����
	//�ڴ�й¶
};