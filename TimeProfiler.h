#pragma once
#pragma comment( lib,"winmm.lib" )
#include <vector>
using namespace std;
class TimeProfiler
{
private:
	vector<string> m_stopNames;
	vector<int> m_stopTimes;
	FILE* m_logFile;
public:
	TimeProfiler();
	virtual ~TimeProfiler();
	void addStop(const char* stopName);
	void reset();
	void setLogFileName(const char* fileName);
	void clear();
	void showResult();
};