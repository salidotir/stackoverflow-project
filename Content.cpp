//
// Created by fatima_msd on 11/20/18.
//
#include "Content.h"

void Content::set_body(string str){
    body = str;
}

string Content::get_body(){
    return body;
}

ContentType Content::get_ContentType(){
    return type;
}


void Content::set_tag(string str) {
    tag.push_back(str);
}

void Content::remove_tag(string str){
     for(auto iter = tag.begin();iter != tag.end();iter++){
         if(*iter ==  str)
            tag.erase(iter);
     }
 }


bool Content::search_tag(string str){
    for(auto iter = tag.begin();iter != tag.end();iter++){
        if(*iter ==  str)
            return true;
    }
    return false;
}

int Content::get_visit() {
    return visit;
}

void  Content::visit_content() {
    ++visit;
}

void Content::operator=(Content c) {
    body=c.body;
    type=c.type;
    tag=c.tag;
    visit=c.visit;
    relations=c.relations;
}

vector<string>& Content::get_tag() {
    return tag;
}

void ContentRelation::set_destination(Content a) {
    destination=a;

}
void ContentRelation::set_type(ContentRelationType a) {
    type=a;
}

