#pragma once
#ifndef STACKOVERFLOW_IN_CPP1_MENU_H
#define STACKOVERFLOW_IN_CPP1_MENU_H

#include <iostream>
#include <string>
#include "AbstractUser.h"
#include "Exceptions.h"
#include "User.h"

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

User * loggedInUser = nullptr;
MenuState menuState = MenuState::START;
string last_message;

class Menu {
public:
	string _guestMenuItems[10] = {
		"1. Sign up",
		"2. Login",
		"3. Show recent questions",
		"4. Show all questions",
		"5. Ask a new question",
		"6. show all users",
		"7. Exit"
	};
	int size1 = 7;

	string _userMenuItems[10] = {
		"1. logout",
		"2. delete account",
		"3. Show recent questions",
		"4. Show all questions",
		"5. Ask a new question",
		"6. answer a question",
		"7. See all users",
		"8. Search for a special user",
		"9. Exit"
	};
	int size2 = 9;

	void ShowGuestMenu();

	void Login();

	void SignUp();

	void ShowAllUsers();

	void SearchForSpecialUser();

	int Exit();					// function to go out of program.

	void ShowUserMenu();

	void ShowRecentQuestions();

	void AskANewQuestion();

	void AnswerAQuestion();

	void ShowAllQuestions();

	void Logout();

	void DeleteAccount();

	void RunMenu();
};

#endif //STACKOVERFLOW_IN_CPP1_MENU_H
