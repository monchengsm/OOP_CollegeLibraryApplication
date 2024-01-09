//Final Project Milestone 5
//Module: Book Module
//Filename: Book.cpp
//Version 1.0
//Author    SIU MAN CHENG 121104228
//Revision History
//-----------------------------------------------------------
//Date      Reason
//2023/07/25  Preliminary release
//
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
//-----------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Book.h"

using namespace std;

namespace sdds{

Book::Book():Publication(){
    b_author = nullptr;
}

Book::~Book(){
    delete[] b_author;
}


Book::Book(const Book& src):Publication(src){
    b_author = new char[strlen(src.b_author)+1];
    strcpy(b_author, src.b_author);
}


Book& Book::operator=(const Book& src){
    if(this!=&src){
        if(src){
            Publication::operator=(src);
            if(b_author!=nullptr){
                delete[] b_author;
                b_author = nullptr;
            }
            b_author = new char[strlen(src.b_author)+1];
            strcpy(b_author, src.b_author);
        }
    }
    return *this;
}


char Book::type()const{
    return 'B';
}


std::ostream& Book::write(std::ostream& os) const{

    
    Publication::write(os);
    if(conIO(os)){
        os << " ";
        os.width(SDDS_AUTHOR_WIDTH);
        char author[SDDS_AUTHOR_WIDTH + 1] = { 0 };
        strncpy(author, b_author, SDDS_AUTHOR_WIDTH);
        os << left << author;
        os << " |";
        
    }
    
    else{
        os << "\t";
        os << b_author;
    }
    
    return os;
}

std::istream& Book::read(std::istream& istr){
    
    char tempName[256] = {};
    Publication::read(istr);
    istr.ignore();
    
    if (b_author!=nullptr){
        delete[] b_author;
        b_author = nullptr;
    }
    
    
    if(conIO(istr)){
        cout << "Author: ";
        istr.getline(tempName,256);
    }
    
    else{
        istr.get(tempName,256);
    }
        
    if(!istr.fail()){
        b_author = new char[strlen(tempName)+1];
        strcpy(b_author, tempName);
    }
    
    return istr;
}

void Book::set(int member_id){
    Publication::set(member_id);
    Publication::resetDate();
}


Book::operator bool() const{
    return (b_author != nullptr && b_author[0] != '\0' && Publication::operator bool());
}

}
