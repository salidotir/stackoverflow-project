#ifndef USER_H
#define USER_H
#pragma once
#include <iostream>
#include "AbstractUser.h"
#include "Content.h"

//void make_user_database(User);

class User : public AbstractUser {
    friend void make_user_database(string username, string password, string email, UserType type);
public:
    User(string username, string password, string email, UserType type);

    static void init(const string &salt);

public:
    void set_password(string password);
    bool check_password(string password);

public:
    bool authenticate(string username, string password);
    void deleteAccount();

public:
    static User& login(string username, string password);
    static User& signup(string username, string password, string email);

    void add_question();
    void edit_question();
    void add_answer(Content c);
    //void add_comment(Content c);

private:
    static string salt;
    static vector<User> users;

};

#endif