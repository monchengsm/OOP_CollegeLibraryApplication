//Final Project Milestone 5
//Module: Utils Module
//Filename: Utils.cpp
//Version 1.0
//Author    SIU MAN CHENG 121104228
//Revision History
//-----------------------------------------------------------
//Date      Reason
//2023/07/08  Preliminary release
//2023/07/11  MS2 update
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
//-----------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
#include <iostream>
using namespace std;

namespace sdds {

unsigned userSelection(int nItem){
    
    unsigned result = 0;
    int select = 0;
    bool isValid = false;
    
    cout << "> ";
    
    do{
        cin >> select;
        
        if(cin.fail()){
            cout << "Invalid Selection, try again: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        
        else if (select>=0 && select<= nItem){
            isValid = true;
            result = unsigned(select);
        }
        else{
            cout << "Invalid Selection, try again: ";
        }
        
    }while(isValid == false);
    
    return result;
}

}
