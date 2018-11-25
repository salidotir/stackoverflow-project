#include "Menu.h"

void Menu::ShowGuestMenu()
	{
		cout << "*****************Menu*****************" << endl << endl;
		for (int i = 0; i < size1; i++)
		{
			cout << _guestMenuItems[i] << endl;
		}
	}

	void Menu::Login()
	{
		try {
			string username, password;
			cout << "Enter Username: ";
			cin >> username;
			cout << "Enter Password: ";
			cin >> password;
			loggedInUser = &User::login(username, password);
			menuState = MenuState::LOGGED_IN;
		}
		catch (WrongUsernameOrPasswordException &e) {
			last_message = e.what();
		}
	}

	void Menu::SignUp()
	{
		try {
			string username, password, email;
			cout << "Enter Username: ";
			cin >> username;
			cout << "Enter Password: ";
			cin >> password;
			cout << "Enter email: ";
			cin >> email;
			loggedInUser = &User::signup(username, password, email);
			menuState = MenuState::LOGGED_IN;
			last_message = "User signed up!\n";
		}
		catch (UserAlreadyExistsException &e) {
			last_message = e.what();
		}
	}

	void Menu::ShowAllUsers()
	{
		DBAccess dbAccess;
		string readUserName;
		string readPassWord;
		string readEmail;
		Logger lg;
		int num = dbAccess.GetNumberOfUsers();

		ifstream file;
		file.open("Users\\users.bin", ios::in | ios::binary);
		file.seekg(0, file.beg);
		for (int i = 0; i < num; i++)
		{
			if (!file.eof()) {
				file.read((char*)&readUserName, sizeof(string));
				file.read((char*)&readPassWord, sizeof(string));
				file.read((char*)&readEmail, sizeof(string));

				cout << "******************************" << endl;
				cout << "username : " << readUserName << endl;
				cout << "email : " << readEmail << endl;
				cout << "******************************" << endl;
			}
		}
		file.close();
	}

	void Menu::SearchForSpecialUser()
	{
		cout << "Which search would you like to choose?" << endl;
		cout << "1. Based on username" << endl;
		cout << "2. Based on email" << endl;

		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			break;
		case 2:
			break;
		default:
			cout << "Wrong choice!" << endl;
			break;
		}
	}

	int Menu::Exit()					// function to go out of program.
	{
		return 0;
	}

	void Menu::ShowUserMenu()
	{
		cout << "*****************Menu*****************" << endl << endl;
		for (int i = 0; i < size2; i++)
		{
			cout << _userMenuItems[i] << endl;
		}
	}

	void Menu::ShowRecentQuestions()
	{

	}

	void Menu::AskANewQuestion()
	{

	}

	void Menu::AnswerAQuestion()
	{

	}

	void Menu::ShowAllQuestions()
	{

	}

	void Menu::Logout()
	{
		menuState = MenuState::START;
	}

	void Menu::DeleteAccount()
	{

	}

	void Menu::RunMenu()
	{
		static int temp = 0;
		User::init("SECRET_KEY");

		char choice;
		while (menuState != MenuState::END) {
			system(CLEAR);
			if (!last_message.empty())
				cout << last_message << endl;
			last_message = "";
			if (temp++ != 0)
			{
				system("pause");
				system(CLEAR);
			}
			switch (menuState) {
			case MenuState::START: {

				ShowGuestMenu();
				cout << "Please choose what to do : ";
				cin >> choice;

				switch (choice) {
				case '1': // sign up
					SignUp();
					break;
				case '2': // login
					Login();
					break;
				case 3:
					ShowRecentQuestions();
					break;
				case 4:
					ShowAllQuestions();
					break;
				case 5:
					AskANewQuestion();
					break;
				case 6:
					ShowAllUsers();
					break;
				case 7:
					Exit();
					break;
				default: // unknown input
					last_message = "unknown input\n";
					break;
				}
				break;
			}
			case MenuState::LOGGED_IN: {
				ShowUserMenu();
				cout << "Please choose what to do : ";
				cin >> choice;

				switch (choice) {
				case '1': // logout
					Logout();
					break;

				case '2': // delete account
					DeleteAccount();
					break;
				case 3:
					ShowRecentQuestions();
					break;
				case 4:
					ShowAllQuestions();
					break;
				case 5:
					AskANewQuestion();
					break;
				case 6:
					AnswerAQuestion();
					break;
				case 7:
					ShowAllUsers();
					break;
				case 8:
					SearchForSpecialUser();
					break;
				case 9:
					Exit();
					break;
				default: // unknown input
					last_message = "unknown input\n";
					break;
				}
				break;
			}
			}
			system(CLEAR);
			cout << "GOODBYE" << endl;
		}
	}
