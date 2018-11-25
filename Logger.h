#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include "User.h"

struct info {
	string username;
	string password;
	string email;
};

class Logger
{
public:
	Logger();
	~Logger();
};

int GetNum();

void operator<<(const Logger& lg, info _userInfo);


#endif