//Final Project Milestone 5
//Module: Streamable Module
//Filename: Streamable.h
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

#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H

#include "iostream"

namespace sdds {

class Streamable{

public:
    virtual std::ostream& write(std::ostream& os) const= 0;
    virtual std::istream& read(std::istream& istr)= 0;
    
    virtual bool conIO(std::ios& ios) const = 0;
    virtual operator bool() const = 0;
    
    virtual ~Streamable(){};
};

    std::ostream& operator<<(std::ostream& os, const Streamable& src);
    std::istream& operator>>(std::istream& istr, Streamable& src);

}
#endif // !SDDS_STREAMABLE_H



