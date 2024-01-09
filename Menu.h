//Final Project Milestone 5
//Module: Menu Module
//Filename: Menu.h
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


#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
#include <limits>

#define MAX_MENU_ITEMS 20

namespace sdds {

class Menu;

class MenuItem{
    private: //allprivate
    char* m_item;
    
    //Constructor
    MenuItem();
    MenuItem(const char* itemName);
    
    //Rule of three
    MenuItem(const MenuItem& src)=delete;
    MenuItem& operator=(const MenuItem& src)=delete;
    
    ~MenuItem();
    
    //Type conversion
    operator bool() const;
    operator const char*() const;
    
    //setEmpty
    void setEmpty();
    
    //display
    std::ostream& displayMenuItem(std::ostream& os) const;
    
    friend class Menu;

};

class Menu{
    
    private:
    MenuItem title;
    MenuItem* menuName[MAX_MENU_ITEMS];
    int nItems;

    public:
    //Rule of three
    Menu(const Menu& src)=delete;
    Menu& operator=(const Menu& src)=delete;
    
    ~Menu();
    
    //Constructor
    Menu();
    Menu(const char* titles);
    
    //setEmpty
    void setEmpty();
    
    std::ostream& displayTitle(std::ostream& os) const;
    std::ostream& displayMenuItem(std::ostream& os) const;
    
    
    unsigned run();
    unsigned operator~(); //same as run
    
    Menu& operator<<(const char* menuitemConent);
    
    //type conversion
    operator int() const;
    operator unsigned() const;
    operator bool() const;
    
    const char* operator[](unsigned index)const;
    
};
    //helper
    std::ostream& operator<<(std::ostream& os, const Menu& src);

} //sdds end


#endif
