//Final Project Milestone 5
//Module: Book Module
//Filename: Book.h
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

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include "Publication.h"

namespace sdds{


class Book: public Publication{

    char* b_author;
    
public:
    Book();
    virtual ~Book();
    
    Book(const Book& src);
    Book& operator=(const Book& src);
    
    virtual char type()const; //return 'B'
    virtual std::ostream& write(std::ostream& os) const;
    virtual std::istream& read(std::istream& istr);
    virtual void set(int member_id);
    virtual operator bool() const;
    
    
    
};



}



#endif
