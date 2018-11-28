#include "Menu.h"
#include <fstream>
#include <sstream>
MenuState menuState = MenuState::START;
string last_message;
User * loggedInUser = nullptr;

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}
struct search1{
    string us;
    string n;
};

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
    catch (UsernameAlreadyExistsException &e) {
        last_message = e.what();
    }
}

void Menu::ShowAllUsers()
{
    int flag = 0;
    string us;
    fstream input_file;
    input_file.open("./Users/AllUsers.txt", ios::in | ios::binary);
    while(!input_file.eof())
    {
        if(!input_file){
            cout << "Error in opening file.";
            //return 0;
        }
        if(flag == 0){
            getline(input_file, us);
            getline(input_file, us);
            flag = 1;
        }
        else if(flag == 1){
            getline(input_file, us);
            getline(input_file, us);
            getline(input_file, us);
        }
        cout << us << endl;
    }
    input_file.close();
}

void Menu::SearchForSpecialTag(){
    system("clear");
    vector<search1> find;
    cout<<"Please enter tag:";
    string tagname;
    cin>>tagname;
    string s="./Questions/AllQuestions.txt";
    fstream file;
    file.open(s,ios::binary | ios::in);
    string question1;

    while (!file.eof()){
        string question,username,tags,n,type;
        getline(file,question);
        getline(file,username);
        getline(file,tags);
        getline(file,n);
        getline(file,type);
        vector<string>v;
        v=split(tags,"\t") ;
        for (auto i = v.begin(); i <v.end() ; i++) {

            if (tagname.compare(*i)==0)   {
                search1 a;
                a.us=username;
                a.n=n;
                find.push_back(a);
                break;
            }
        }}
    file.close();
    for (auto j = find.begin(); j <find.end() ; j++) {
        string s1="./Users/"+(*j).us+"/contents/Q/"+(*j).n+".txt";
        fstream file1;
        file1.open(s1,ios::binary | ios::in);
        string s2;
        while (getline(file1,s2)){

            cout<<s2<<endl;

        }
        file1.close();
        cout<<"1:next\n2:previous\n3.Answer this question\n4:stop\n";
        char input;
        cin>>input;
        switch (input){
            case '1':
                continue;
            case '2':
                j--;
                j--;
                continue;
            case '3':
                //(*loggedInUser).add_answer();
                last_message="Answer added.\n";
            case '4':
                return;
        }
        // string question1,tags,n,type;

        //  getline(file,question);

    }
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
    (*loggedInUser).add_question();
    last_message="Question added.\n";
}

void Menu::EditQuestion() {
    try {
        (*loggedInUser).edit_question();
        last_message="Question changed.\n";
    }catch (QuestionNotFound &e){
        last_message = e.what();
    }

}
void Menu::ShowAllQuestions()
{int ten=1;
    string s="./Questions/AllQuestions.txt";
    fstream file;
    file.open(s,ios::binary|ios::in);
    int counterque=1;
    while(!file.eof()) {
        char input;
        do {
            while (ten != 10 && !file.eof()) {
                if (!file) {
                    cout << "Error in opening file..";
                    //return 0;
                }
                string tmp;
                getline(file, tmp);
                cout<<counterque<<" : ";
                counterque++;
                cout << tmp;
                cout << "\n";
                for (int i = 0; i < 4; ++i) {
                    getline(file, tmp);
                }
                ten++;
            }
            char qnum;
            cout<<"Do you want to see one of the above?(y/n)"<<endl;
            cin>>qnum;
            if(qnum=='y'){
                cout<<"Enter number of question: ";
                int number;
                cin>>number;
                cout<<"call answer function later.\n";
                return;
            }
            if(qnum=='n'){
            cout << "Do you want to continue?(y/n)" << endl;
            cin >> input;
            ten=0;
            }
        }while(input=='y' && !file.eof());
        return;
    }
    file.close();
    return;
}

void Menu::Logout()
{
    menuState = MenuState::START;
}

void Menu::DeleteAccount()
{
    (*loggedInUser).deletAccount();
    last_message = "Account deleted.\n";
}


void Menu::RunMenu()
{create();
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
            system("read");
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
                    case '3':
                        ShowRecentQuestions();
                        break;
                    case '4':
                        ShowAllQuestions();
                        break;
                    case '5':
                        ShowAllUsers();
                        break;
                    case '6':

                        return ;
                        break;
                    default: // unknown input
                        last_message = "unknown input\n";
                        break;
                }
            }
                continue;
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
                    case '3':
                        ShowRecentQuestions();
                        break;
                    case '4':
                        ShowAllQuestions();
                        break;
                    case '5':
                        AskANewQuestion();
                        break;
                    case '6':
                        ShowAllUsers();
                        break;
                    case '7':
                        SearchForSpecialTag();
                        break;
                    case '8':
                        EditQuestion();
                        break;
                    case '0':
                        return ;
                        break;
                    default: // unknown input
                        last_message = "unknown input\n";
                        break;
                }
                //continue;
            }
                continue;
        }
        system(CLEAR);
        cout << "GOODBYE" << endl;
    }
}

