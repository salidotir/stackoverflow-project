#include <utility>

//
// Created by spsina on 11/8/18.
//

#include <sstream>
#include<fstream>
#include "User.h"
#include "Exceptions.h"
#include <iostream>
#include<string>
#include<string.h>
#include <stdlib.h>

using namespace std;
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}
struct info{
    string username;
    string password;
    string email;
};
struct len{
    int all;
    int q;
    int a;
};
struct dataQuestion{
    string body;
    string username;
    int n;
    vector<string> tag;
};

struct dataAnswer{
    string question;
    string body;
    string username;
    int n;
};

string encryptDecrypt(string toEncrypt) {
    char key = 'K'; //Any char will work
    string output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;

    return output;
}

void eraseFileLine(std::string path, std::string eraseLine) {
    std::string line;
    std::ifstream fin;

    fin.open(path);
    std::ofstream temp; // contents of path must be copied to a temp file then renamed back to the path file
    temp.open("./Users/temp.txt");

    int x=1;
    int y;
    getline(fin, line);
    while (getline(fin, line)) {
        if (line != eraseLine) // write all lines to temp other than the line marked fro erasing
        {
// temp << line << std::endl;
            ++x;
        }
        if(line== eraseLine)
        {
            y=x-1;
        }
        getline(fin, line);
        getline(fin, line);
        getline(fin, line);
        x+=3;


    }
    fin.close();
    ifstream fin1;
    fin1.open(path);
//cout<<y;
//int yy=y+3;
    for (y ; y>0 ; y--)
    {
        getline(fin1 , line);
        temp << line << std::endl;
    }
    getline(fin1 , line);
    cout<<line<<endl;
    getline(fin1 , line);
    cout<<line<<endl;
    getline(fin1 , line);
    cout<<line<<endl;
    getline(fin1 , line);
    cout<<line<<endl;

    while(getline(fin1, line)){

        temp << line << std::endl;
    }

    temp.close();
    fin1.close();

    const char * p = path.c_str(); // required conversion for remove and rename functions
    string rm="rm "+path;
    system(rm.c_str());
    rename("./Users/temp.txt", p);}




void make_user_database(string username, string password, string email, UserType type){
    // User user( username,  password,  email,type);
    char s[30],s2[30];
    strcpy(s,"./Users/AllUsers.txt");
    ofstream output_file;
    //type == UserType ::MEMBER;

    string encrypted = encryptDecrypt(password);

    //open file in write mode
    output_file.open(s,ios::binary|ios::app);
    output_file<<email;
    output_file<<"\n";
    output_file<<username;
    output_file<<"\n";

    output_file<<encrypted;
    output_file<<"\n";
    output_file<<type;
    output_file<<"\n";
    output_file.close();


    string s1;
    s1="mkdir ./Users/"+ username+"/";
    system(s1.c_str());
    string s3,s4,s5;
    s3=s1+"/contents/";
    system(s3.c_str());
    s4="touch ./Users/"+ username+"/info.txt";

    s3.clear();
    s3="./Users/"+username+"/info.txt";
    system(s4.c_str());
    ofstream info_file(s3,ios::app);
    info_file<<username;
    info_file<<"\n";
    info_file<<password;
    info_file<<"\n";
    info_file<<email;
    info_file<<"\n";
    info_file<<type;
    info_file<<"\n";
    //info_file.write((char*) &username, sizeof(username));
    //info_file.write((char*) &password, sizeof(password));
    //info_file.write((char*) &email, sizeof(email));
    //info_file.write((char*) &type, sizeof(type));
    //info_file.close();
    //cout<<"s2"<<endl;
    s5="touch ./Users/"+username+"/len.txt";
    system(s5.c_str());
    s3.clear();
    s3="./Users/"+username+"/len.txt";

    ofstream len_file(s3,ios::app);
    len_file<<"0";
    len_file<<"\n";
    len_file<<"0";
    len_file<<"\n";
    len_file<<"0";
    len_file<<"\n";

    len_file.close();
    system(s4.c_str());
    s3="mkdir ./Users/"+username+"/contents/Q";
    system(s3.c_str());
    s3.clear();
    s3="mkdir ./Users/"+username+"/contents/A";
    system(s3.c_str());

}


vector<User> User::users;
string User::salt;


User::User(string username, string password, string email, UserType type){
    lower(username);
    this->username = username;
    set_password(std::move(password));
    this->email = email;
    this->type = type;
}

void User::set_password(string password){
    size_t ps = pass_hash(password + salt);
    stringstream out;
    out << ps;
    this->password = out.str();
}

bool User::check_password(string password){
    size_t check = pass_hash(password + salt);
    stringstream out;
    out << check;
    return (this->password == out.str());
}

bool User::authenticate(string username, string password){
    lower(username);
    return this->username == username and check_password(password);
}
void User::deleteAccount(){
    eraseFileLine("./Users/AllUsers.txt",username);
    string s="rm -r ./Users/"+username;
    if (this->type == UserType::ADMIN) {
        throw DeleteAdminException();
    }

    for (auto user = users.begin(); user != users.end();user++){
        if ( user->username == this->username  ) {
            users.erase(user);
            break;
        }
    }

    system(s.c_str());


}

User& User::login(string username, string password){
    int flag2=0;
    int flag=0;
    string email;
    UserType type;
    fstream input_file2;
    input_file2.open("./Users/AllUsers.txt",ios::in|ios::binary);
    string us;
    //read data from file
    while(!input_file2.eof()){
        if(!input_file2){
            cout<<"Error in opening file..";
            //return 0;
        }
        if(flag==0)
        {
            getline(input_file2 , us);
            getline(input_file2 , us);
            flag=1;
        }

        else if(flag==1)
        {
            getline(input_file2 , us);
            getline(input_file2 , us);
            //cout << l<<endl;
            getline(input_file2 , us);
            //cout << l<<endl;
            getline(input_file2 , us);
        }

        if (us == username) {


            fstream input_file3;
            input_file3.open("./Users/AllUsers.txt",ios::in|ios::binary);
            string ps;
            //read data from file
            while(!input_file3.eof()){
                if(!input_file3){
                    cout<<"Error in opening file..";
                    //return 0;
                }
                else {
                    getline(input_file3, ps);
                    email=ps;
                    //cout << l<<endl;
                    getline(input_file3, ps);
                    //cout << l<<endl;
                    getline(input_file3, ps);


                }

                string decrypted = encryptDecrypt(ps);
                getline(input_file3, ps);
                if(ps=="1")
                    type=MEMBER;
                else if(ps=="0")
                    type=ADMIN;
//        input_file.read((char*) u.type, sizeof(u.type));

                //input_file.close();
                //cout << us<<endl;
                if (decrypted == password) {
                    flag2=1;
                    break;
                }



            }
            if(flag2==1){
                break;
            }
            input_file3.close();


        }

    }
    input_file2.close();

    if(flag2==0)
        throw WrongUsernameOrPasswordException();
    else if(flag2==1)
    {

        cout<<"you are logged in now\n";
        users.emplace_back(username, password, email, type);
        return users[users.size() -1];
    }
}

User& User::signup(string username, string password, string email){
    User u("","","",MEMBER);
    int flag=0;
    //info person;
    fstream input_file;
    input_file.open("./Users/AllUsers.txt",ios::in|ios::binary);
    string us;
    //read data from file
    while(!input_file.eof()){
        if(!input_file){
            cout<<"Error in opening file..";
            //return 0;
        }
        if(flag==0)
        {
            getline(input_file , us);
            getline(input_file , us);
            flag=1;
        }

        else if(flag==1)
        {
            getline(input_file , us);

            getline(input_file, us);
            //cout << l<<endl;
            getline(input_file , us);
            //cout << l<<endl;
            getline(input_file , us);
        }

//        input_file.read((char*) u.type, sizeof(u.type));

        //input_file.close();
        //cout << us<<endl;
        if (us == username) {
            throw UsernameAlreadyExistsException();
        }
//        else if (u.email == email) {
//            throw EmailAlreadyExistsException();
//        }


    }
    input_file.close();
    int flag1=0;
    fstream input_file1;
    input_file1.open("./Users/AllUsers.txt",ios::in|ios::binary);
    string em;
    //read data from file
    while(!input_file1.eof()){
        if(!input_file1){
            cout<<"Error in opening file..";
            //return 0;
        }
        if(flag1==0)
        {
            getline(input_file1 , em);
            flag1=1;
        }

        else if(flag1==1)
        {
            getline(input_file1 , em);
            //cout << l<<endl;
            getline(input_file1 , em);
            //cout << l<<endl;
            getline(input_file1 , em);

            getline(input_file1 , em);
        }

//        input_file.read((char*) u.type, sizeof(u.type));

        //input_file.close();
        // cout << "em = "<<em<<endl;
//        if (em== email) {
//            throw UsernameAlreadyExistsException();
//        }
        if (em == email) {
            throw EmailAlreadyExistsException();
        }


    }
    //Create user
    input_file1.close();
    // cout <<"end"<<endl;
    users.emplace_back(username, password, email, UserType::MEMBER);
    make_user_database(username, password, email, UserType::MEMBER);
    return users[users.size() -1];
}

void User::init(const string &salt) {
    User::salt = salt;
    users.reserve(20);
    users.emplace_back("admin", "admin", "admin@stackoverflow.com", UserType::ADMIN);
}

void User::add_question(){
    cout<<"Please enter your question:"<<endl;
    string bd;
    getchar();
    std::getline(std::cin,bd);
    fstream file;
    dataQuestion dq;
    // file.open("./Questions/AllQuestions.txt",ios::binary | ios::in);
    /*   while(!file.eof()){
           if (!file)
               break;
           getline(file,dq.body);

           if (dq.body.compare(bd)==0) {
               file.close();
               throw dq;
           }

       }*/
    //  file.close();
    Content c(bd);
    file.open("./Users/" + username + "/len.txt", ios::binary | ios::in|ios::out);
    char s3[100];
    len obj;
    string a,q,answer;
    getline(file,a);
    getline(file,q);
    getline(file,answer);
    file.close();
    file.open("./Users/" + username + "/len.txt", ios::binary | ios::out);
    obj.all=atoi(a.c_str());
    obj.q =atof(q.c_str());

    obj.q++;
    string s = "./Users/" + username + "/contents/Q/" + itoa(obj.q, s3, 100) + ".txt";
    string s2 = "touch " + s;
    obj.all++;

    char s4[100],s6[100];
    file<<itoa(obj.all,s4,100);
    file<<"\n";
    char s5[100];
    file<<itoa(obj.q,s5,100);
    file<<"\n";
    file<<itoa(obj.a,s6,100);
    file<<"\n";
    file.close();
    dq.body=c.get_body();
    dq.tag=c.get_tag();
    dq.username=username;
    dq.n=obj.q;

    system(s2.c_str());
    file.open(s,ios::binary | ios::app);
    file<<dq.body;
    file<<"\n";
    for (const auto &e : dq.tag) file << e << "\t";
    file<<"\n";
    file.close();
    file.open("./Questions/AllQuestions.txt",ios::binary | ios::app);
    file<<dq.body;
    file<<"\n";
    file<<dq.username;
    file<<"\n";
    for (const auto &e : dq.tag) file << e << "\t";
    file<<"\n";
    file<<dq.n;
    file<<"\n";
    file<<"unanswerd";
    file<<"\n";
    file.close();

}
void User::edit_question(){
    string s="./Users/"+username+"/len.txt";
    fstream file;
    file.open(s,ios::binary|ios::in);
    string q,all;
    getline(file,all);
    getline(file,q);
    file.close();
    if(atoi(q.c_str())) {
        char s2[20];
        for (int i = 1; i < atoi(q.c_str()) + 1; i++) {
            string question;
            string s1 = "./Users/" + username + "/contents/Q/" + itoa(i, s2, 20) + ".txt";
            file.open(s1, ios::binary | ios::in);
            getline(file, question);
            cout << question << endl;
            cout << "1.next\n2.previous\n3.change\n";
            char input;
            cin>>input;
            switch (input) {

                case '1':
                    continue;
                case '2':
                    i--;
                    i--;
                    continue;
                case '3':
                    string bd;
                    cout << "Please enter your question:";
                    getchar();
                    std::getline(std::cin, bd);
                    file << bd;
                    file.close();
                    string s3 = "./Questions/AllQuestions.txt";
                    file.open(s3, ios::binary | ios::in);
                    string strTemp;
                    ofstream file2("./Questions/AllQuestion.txt");
                    while (getline(file, strTemp)) {
                        if (strTemp.compare(question)==0) {
                            strTemp = bd;
                            //found = true;
                        }
                        file2 << strTemp;
                        file2 << "\n";

                    }
                    file.close();
                    file2.close();
                    system("rm -rf ./Questions/AllQuestions.txt");
                    system("mv ./Questions/AllQuestion.txt ./Questions/AllQuestions.txt");
            }
        }
    }
    else{
        QuestionNotFound e;
        throw e;
    }
}

void User::add_answer(Content con){
    cout<<"Please enter your answer."<<endl;
    string bd;
    cin>>bd;
    ContentRelation CR;
    dataAnswer da;
    CR.set_type(ANSWER_TO);
    CR.set_destination(con);
    Content c(bd,&CR,1);
    fstream file;
    file.open("./Users/"+this->username+"/len.txt");
    len obj;
    char s3[100];
    string all,q,a;
    getline(file,all);
    getline(file,q);
    getline(file,a);
    obj.all=atoi(all.c_str());
    obj.q =atof(q.c_str());
    obj.a=atoi(a.c_str());
    string s="./Users/"+this->username+"/contents/A/"+itoa(obj.q,s3,100)+".txt";
    string s2="touch "+s;
    ++obj.all;
    ++obj.a;
    file<<obj.all;
    file<<"\n";
    file<<obj.q;
    file<<"\n";
    file<<obj.a;
    file<<"\n";



    da.body=c.get_body();
    da.username=username;
    da.n=obj.a;

    file.close();
    system(s2.c_str());
    file.open(s,ios::binary | ios::app);
    file<<da.body; //answer
    file<<"\n";
    file<<con.get_body(); //question

    file.close();

    fstream file1;
    dataQuestion dq;
    file.open("./Questions/AllQuestions.txt",ios::binary | ios::in);
    while(!file.eof()){
        if (!file)
            break;
        getline(file,dq.body);
        getline(file,dq.username);

        if (dq.body == con.get_body()) {
            file.close();

            string s1="./Users/"+dq.username+"/contents/Q/"+itoa(dq.n,s3,100)+".txt";
            file1.open(s1,ios::binary | ios::app);
            file1<<da.body;
            file<<"\n";
            file1.close();
        }

    }
}

/*
void User::add_comment(Content con){
    cout<<"Please enter your Comment."<<endl;
    string bd;
    cin>>bd;
    ContentRelation CR;
    CR.set_type(COMMENT_TO);
    CR.set_destination(con);
    Content c(bd,&CR,2);
    fstream file;
    char s3[100];
    // da.body=c.get_body();
    //da.username=username;
    //da.n=obj.a;


}*/