//
// Created by negin on 11/26/18.
//

#ifndef STACK_MENU_H
#define STACK_MENU_H
#pragma once

#include <iostream>
#include <string>
#include "AbstractUser.h"
#include "Exceptions.h"
#include "User.h"
#include "database.h"
#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;

enum MenuState {
    START,
    LOGGED_IN,
    END
};



class Menu {
public:
    friend User;
    string _guestMenuItems[10] = {
            "1. Sign up",
            "2. Login",
            "3. Show recent questions",
            "4. Show all questions",
            "5. Show all users",
            "6. Exit"
    };
    int size1 = 6;

    string _userMenuItems[10] = {
            "1. logout",
            "2. delete account",
            "3. Show recent questions",
            "4. Show all questions",
            "5. Ask a new question",
            "6. See all users",
            "7. Search for a special tag",
            "8. Edit question",
            "0. Exit"
    };
    int size2 = 10;

    void ShowGuestMenu();

    void Login();

    void SignUp();

    void ShowAllUsers();
    void EditQuestion();
    void SearchForSpecialTag();

    // function to go out of program.

    void ShowUserMenu();

    void ShowRecentQuestions();

    void AskANewQuestion();

    void ShowAllQuestions();

    void Logout();

    void DeleteAccount();

    void RunMenu();
};


#endif //STACK_MENU_H
