//Final Project Milestone 5
//Module: Publication Module
//Filename: Publication.cpp
//Version 1.0
//Author    SIU MAN CHENG 121104228
//Revision History
//-----------------------------------------------------------
//Date      Reason
//2023/07/18  Preliminary release
//
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
//-----------------------------------------------------------


#define _CRT_SECURE_NO_WARNINGS
#include "Publication.h"
#include <iostream>


using namespace std;
namespace sdds {

Publication::Publication(){
    m_title = nullptr;
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    
}

Publication::~Publication(){
    delete[] m_title;
}

//Copying constructors
Publication::Publication(const Publication& src){
    if(src){
        m_title = new char[strlen(src.m_title)+1];
        strcpy(m_title,src.m_title);
        strcpy(m_shelfId,src.m_shelfId);
        m_membership = src.m_membership;
        m_libRef = src.m_libRef;
    }
    
}


Publication& Publication::operator=(const Publication& src){
    if(this!=&src){
        if(src){
            if(m_title!=nullptr){
                delete[] m_title;
                m_title = nullptr;
            }
            m_title = new char[strlen(src.m_title)+1];
            strcpy(m_title,src.m_title);
            strcpy(m_shelfId,src.m_shelfId);
            m_membership = src.m_membership;
            m_libRef = src.m_libRef;
            m_date = src.m_date;
        }
    }
    return *this;
}



void Publication::set(int member_id){
    m_membership = member_id;
}

void Publication::setRef(int value){
    m_libRef = value;
}

void Publication::resetDate(){
    m_date = Date(); 
}

char Publication::type()const{
    return 'P';
}

bool Publication::onLoan()const{
    return (m_membership!=0);
}

Date Publication::checkoutDate()const{
    return m_date;
}

bool Publication::operator==(const char* title)const{
    bool isFound = false;
    
    if(strstr(m_title, title)){
        isFound = true;
    }
    
    return isFound;
}

Publication::operator const char* ()const{
    return m_title;
}

int Publication::getRef()const{
    return m_libRef;
}


bool Publication::conIO(std::ios& ios) const{
    
    return ((&ios == &cin) || (&ios == &cout));
}

std::ostream& Publication::write(std::ostream& os) const{
    if(conIO(os)){
    
        //print content
        os << "| "<< m_shelfId << " | ";
        os.width(SDDS_TITLE_WIDTH);
        os.fill('.');
        char title[SDDS_TITLE_WIDTH + 1] = { 0 };
        strncpy(title, m_title, SDDS_TITLE_WIDTH);
        os << left << title;
        
        os << " | ";
        
        if(m_membership!=0){
            os << m_membership;
        }
        else{
            os << " N/A ";
        }
        
        os << " | ";
        os << m_date;
        os << " |";
        
    }
    
    else{
        os << type() << "\t";
        os << m_libRef << "\t";
        os << m_shelfId << "\t";
        os << m_title << "\t";
        os << m_membership << "\t";
        os << m_date;
        
    }
    return os;
}

std::istream& Publication::read(std::istream& istr){
    
    char tempTitle[255 + 1] = {};
    char tempShelfId[SDDS_SHELF_ID_LEN + 1] = {};
    int tempMembership = 0 ;
    int tempLibRef = -1 ;
    Date tempDate;
    
    //freeing the memory and setting everything to their default values.
    if(m_title!=nullptr){
        delete[] m_title;
        m_title = nullptr;
    }
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    resetDate();
    
    if(conIO(istr)){
        cout << "Shelf No: ";
       istr.getline(tempShelfId,SDDS_SHELF_ID_LEN+1);
        
        if(strlen(tempShelfId)!=SDDS_SHELF_ID_LEN){
            istr.setstate(ios::failbit);
        }
        
        cout << "Title: ";
        istr.getline(tempTitle,256);
        cout << "Date: ";
        istr >> tempDate;
    }

    else{


        istr >> tempLibRef;
        istr.ignore();
        istr.getline(tempShelfId, SDDS_SHELF_ID_LEN + 1, '\t');
        istr.getline(tempTitle, 255 + 1, '\t');
        istr >> tempMembership;
        istr.ignore();
        istr >> tempDate;
       
    }

    if(!tempDate){
        istr.setstate(ios::failbit);
    }
    
    if(istr){
        m_title = new char[strlen(tempTitle)+1];
        strcpy(m_title,tempTitle);
        strcpy(m_shelfId,tempShelfId);
        m_libRef = tempLibRef;
        m_membership = tempMembership;
        m_date = tempDate;
    
    }
    
    return istr;
}


Publication::operator bool() const{
    return (m_title != nullptr && m_shelfId[0] != '\0');
}



    
}
