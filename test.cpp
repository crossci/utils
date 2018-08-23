#include <iostream>
#include "fileutils\FileUtils.h"
#include "stringutils\stringutils.h"
#include <io.h>
#include <winsock2.h>
#include <Windows.h>
#include "md5\MD5Utils.h"
#include "utils\utils.h"
#include <algorithm>
#include <unordered_map>
#include <time.h>
#include <map>
#include "minidump\minidump.h"
#include<fstream>
#include "mail\CSmtp.h"
using namespace std;
#ifdef _DEBUG

time_t StringToDatetime(char *str)
{
	tm tm_;
	int year, month, day, hour, minute, second;
	sscanf(str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = hour;
	tm_.tm_min = minute;
	tm_.tm_sec = second;
	tm_.tm_isdst = 0;

	time_t t_ = mktime(&tm_); //已经减了8个时区
	return t_; //秒时间
}
int get_money_by_level(int vip_level)
{
	int v = 5 * vip_level*vip_level*vip_level;
	std::string s = std::to_string(v);
	int len = s.length() - 2;
	int m = 1;
	for (int i = 0; i < len; i++)
	{
		m *= 10;
	}
	return v / m*m;

}
int get_vip_level(int money)
{
	int vip_level = 0;
	if (money < 100)
	{
		vip_level = 0;
	}
	else if (money < 200)
	{
		vip_level = 1;
	}
	else if (money < 400)
	{
		vip_level = 2;
	}
	else if (money < 500)
	{
		vip_level = 3;
	}
	else if (money < 625)
	{
		vip_level = 4;
	}
	else
	{
		vip_level = 5;
		int v = get_money_by_level(vip_level);
		while (money > v)
		{
			++vip_level;
			v = get_money_by_level(vip_level);
		}
	}
	return vip_level;
}
typedef union _CARD_TYPE
{
	struct
	{
		int type;
		int value;
	};
	struct
	{
		char duizi : 1;
		char shunzi : 1;
		char tonghua : 1;
		char sanzhang : 1;
	};
}*PCARD_TYPE;

int main(int argc, char* argv[])
{
	//CSmtp sMailer;
	////    freopen("F://mailfile//out.txt","w+",stdout);

	//sMailer.SetSMTPServer("smtp.163.com", 25);
	//sMailer.SetSecurityType(USE_TLS);//USE_TLS);  
	//sMailer.SetLogin("crash10888888@163.com");
	//sMailer.SetPassword("a123456");
	//sMailer.SetSenderName("sendName");
	//sMailer.SetSenderMail("crash10888888@163.com");
	//sMailer.SetReplyTo("baishikele10888@gmail.com");
	//sMailer.SetSubject("The message");
	//sMailer.AddRecipient("crash10888888@163.com");//添加邮件接收者
	////sMailer.addReceiver("sixbeauty","sanyue9394@126.com");

	////sMailer.AddFilePath("F:\\mailfile\\out.txt");            //添加附件
	////    sMailer.AddFilePath("F:/mailfile/libcurl.exp");                                                //添加附件

	//sMailer.SetXPriority(XPRIORITY_NORMAL);
	//sMailer.SetXMailer("The Bat! (v3.02) Professional");
	//sMailer.AddMsgLine("Hello,");
	//sMailer.AddMsgLine("");
	//sMailer.AddMsgLine("...");
	//sMailer.AddMsgLine("How are you today?");
	//sMailer.AddMsgLine("");
	//sMailer.AddMsgLine("Regards");
	//sMailer.ModMsgLine(5, "regards");
	//sMailer.DelMsgLine(2);
	//sMailer.AddMsgLine("User");
	//sMailer.Send();
	for (int vip_level = 0; vip_level < 100; vip_level++)
	{
		int v = 5 * vip_level*vip_level*vip_level;
		std::string s = std::to_string(v);
		int len = s.length() - 2;
		int m = 1;
		if (len > 4)
			len = 4;
		for (int i = 0; i < len; i++)
		{
			m *= 10;
		}
		cout << vip_level << "-" << v / m*m << endl;
	}
system("pause");
}
#else
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif