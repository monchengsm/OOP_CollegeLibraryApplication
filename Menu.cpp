//Final Project Milestone 5
//Module: Menu Module
//Filename: Menu.cpp
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
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;
#include "Menu.h"
#include "Utils.h"

namespace sdds {

    //MenuItem
    //Constructor
    MenuItem::MenuItem(){
        setEmpty();
    }

    MenuItem::MenuItem(const char* itemName){
        if(itemName!=nullptr &&itemName[0]!='\0'){
            m_item = new char[strlen(itemName)+1];
            strcpy(m_item, itemName);
        }
        else{
            setEmpty();
        }
    }

    MenuItem::~MenuItem(){
        delete[] m_item;
    }

    //Type conversion
    MenuItem::operator bool() const{
        return (m_item!=nullptr &&m_item[0]!='\0');
    }

    MenuItem::operator const char*() const{
        return m_item;
    }

    void MenuItem::setEmpty(){
        m_item = nullptr;
    }

    //display
    std::ostream& MenuItem::displayMenuItem(std::ostream& os) const{
        if(*this){
            os << m_item;
        }
        return os;
    }

    //Menu

    //Constructor
    Menu::Menu(){
        setEmpty();
        }


    Menu::Menu(const char* titles){
        if(titles!=nullptr &&titles[0]!='\0'){
            setEmpty();
            title.m_item = new char[strlen(titles)+1];
            strcpy(title.m_item, titles);
        }
        else{
            setEmpty();
        }
    }

    Menu::~Menu(){
        for (unsigned int i = 0; i < (unsigned)nItems; i++)
               delete menuName[i];
    }
    
    void Menu::setEmpty(){
        int i = 0;
        title.setEmpty();
        nItems = 0;
        for (i=0; i<MAX_MENU_ITEMS; i++){
            menuName[i] = nullptr;
        }
    }

    std::ostream& Menu::displayTitle(std::ostream& os) const{
        title.displayMenuItem(os);
        
        return os;
    }

    std::ostream& Menu::displayMenuItem(std::ostream& os) const{
        int i = 0;
        
        displayTitle(os) << endl;


        for (i=0; i<nItems; i++){
            os << right << setw(2) << i+1 << "- " << menuName[i]->m_item << endl;
        }
        
        os << right << setw(2) << "0" << "- Exit" << endl;
        
        return os;
    }

    unsigned Menu::run(){
        
        displayMenuItem(cout);
        return userSelection(nItems);
    }

    unsigned Menu::operator~(){
        return run();
    }

    
    Menu& Menu::operator<<(const char* menuitemConent){
        if (menuitemConent!=nullptr && menuitemConent[0]!='\0'){
            if(nItems < MAX_MENU_ITEMS){
                menuName[nItems++] = new MenuItem(menuitemConent);
            }
        }
        return *this;
    }
    
    Menu::operator int() const{
        return nItems;
    }

    Menu::operator unsigned() const{
        return unsigned(nItems);
    }

    Menu::operator bool() const{
        return nItems>0;
    }

    const char* Menu::operator[](unsigned index)const{
        const char* result = nullptr;
        if(*this){
            if(int(index) < nItems){
                result = menuName[index]->m_item;
            }
            else{
                index %= nItems;
                result = menuName[index]->m_item;
            }
        }
        return result;
    }


    //helper
    std::ostream& operator<<(std::ostream& os, const Menu& src){
        src.displayTitle(os);
        return os;
    }
        

}//sdds

