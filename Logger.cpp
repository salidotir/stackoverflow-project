#include "Logger.h"



Logger::Logger() {}


Logger::~Logger() {}

int GetNum()
{
	int num = 0;
	fstream tmp;
	tmp.open("Logs\\int.txt", ios::in);
	if (tmp.is_open())
	{
		tmp >> num;
	}
	tmp.close();
	return num;
}

void operator<<(const Logger& lg, info _userInfo)
{
	int i = GetNum();
	string temp;
	sprintf((char*)temp.c_str(), "Logs\\log%i.txt", i);
	fstream file;
	file.open(temp, ios::out);
	if (file.is_open())
	{
		file << _userInfo.email << endl;
		file << _userInfo.username << endl;
		time_t myTime = time(NULL);
		file << ctime(&myTime) << endl;
	}
	file.close();
}
