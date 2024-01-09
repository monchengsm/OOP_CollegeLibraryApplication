//Final Project Milestone 5
//Module: Streamable Module
//Filename: Streamable.cpp
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
#include "Streamable.h"
#include <iostream>

using namespace std;
namespace sdds {

std::ostream& operator<<(std::ostream& os, const Streamable& src){
    if (src){
        src.write(os);
    }
    
    return os;
}

std::istream& operator>>(std::istream& istr, Streamable& src){
    src.read(istr);
    
    return istr;
}
    
}
