//
// Created by spsina on 11/8/18.
//

#ifndef STACKOVERFLOW_IN_CPP1_CONTENT_H
#define STACKOVERFLOW_IN_CPP1_CONTENT_H
#include <vector>
#include <iostream>
#include "AbstractUser.h"
#include <sys/time.h>
#include <time.h>
#include "User.h"
enum ContentType{
    QUESTION,
    ANSWER,
    COMMENT
};

enum ContentRelationType{
    DUPLECATE_OF,
    ANSWER_TO,
    COMMENT_TO
};
class ContentRelation ;
class Content {
   string body;
   ContentType type;
   vector<string> tag; 
   int visit;
   vector<ContentRelation> relations;
    char* time_create=new char(100);
public:

    Content(){}
    Content(string bd){ //question
        time_t ticks[100];
        time(ticks);
        time_create=ctime(ticks);
        body=bd;
        type = QUESTION;
        cout<<"Please enter your tags of question.If you want to exit please enter 'q'. "<<endl;
        string input_tag;
        cin>>input_tag;
        while (input_tag!="q"){
            tag.push_back(input_tag);
            input_tag.clear();
            cin>>input_tag;
        }


    }
    Content(string bd,ContentRelation* ty,int tp) {//tp=1-->answer  tp=2-->comment
        if (tp == 1) {
            time_t ticks[100];
            time(ticks);
            time_create = ctime(ticks);
            body = bd;
            type = ANSWER;

            relations.emplace_back(*ty);
            //  relatio
        }
        else if(tp==2){
            time_t ticks[100];
            time(ticks);
            time_create = ctime(ticks);
            body = bd;
            type = COMMENT;
            relations.emplace_back(*ty);

        }
    }

    void set_body(string str);
    string get_body();
    ContentType get_ContentType();
    void set_tag(string str);
    void remove_tag(string str);
    bool search_tag(string str);
    vector<string>& get_tag();
    int get_visit();
    void visit_content();
    void operator =(Content c);
};

class ContentRelation {
    //friend void User.add_answer(),User::add_question();
    Content destination;
    ContentRelationType type;
public:
    void set_destination(Content);
    void set_type(ContentRelationType);
   // ContentRelation(){};

};

#endif //STACKOVERFLOW_IN_CPP1_CONTENT
