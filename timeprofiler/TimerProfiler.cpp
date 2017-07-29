#include "TimeProfiler.h"
#include "..\fileutils\FileUtils.h"
#include <Windows.h>
#include <time.h>

TimeProfiler::TimeProfiler() :m_logFile(0)
{
}

TimeProfiler::~TimeProfiler()
{
	clear();
}

void TimeProfiler::addStop(const char* stopName)
{
#ifdef _DEBUG
	m_stopNames.push_back(stopName);
	m_stopTimes.push_back(timeGetTime());
#endif
}

void TimeProfiler::reset()
{
#ifdef _DEBUG
	m_stopNames.clear();
	m_stopTimes.clear();
#endif
}
void TimeProfiler::setLogFileName(const char* fileName)
{
#ifdef _DEBUG
	clear();
	char fullPath[MAX_PATH];
	FileUtils::generateFullPath(fileName, fullPath);
	m_logFile = FileUtils::openFile(fullPath, "w");;
#endif
}

void TimeProfiler::clear()
{
#ifdef _DEBUG
	if (m_logFile)
	{
		fclose(m_logFile);
		m_logFile = NULL;
	}
	reset();
#endif
}
void TimeProfiler::showResult()
{
#ifdef _DEBUG
	int size = m_stopNames.size();
	char data[100];
	for (int i = 0; i < size; i++)
	{
		memset(data, 0, sizeof(data));
		int lastTime = (i>0) ? m_stopTimes[i - 1] : m_stopTimes[i];
		//sprintf(data, "[%s]-%dms-lastTime=[%d]ms \r\n", "test", 16715916, 16715916);
		sprintf(data, "[%s]-[%d]ms-lastTime=[%d]ms \n", m_stopNames[i].c_str(), m_stopTimes[i], (m_stopTimes[i] - lastTime));
		fwrite(data, 1, strlen(data), m_logFile);
	}
	fflush(m_logFile);
#endif
}
