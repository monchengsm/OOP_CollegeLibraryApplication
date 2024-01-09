//Final Project Milestone 5
//Module: LibApp Module
//Filename: LibApp.h
//Version 1.0
//Author    SIU MAN CHENG 121104228
//Revision History
//-----------------------------------------------------------
//Date      Reason
//2023/07/11  Preliminary release
//2023/07/27 MS5 Update
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my workshops and assignments.
//-----------------------------------------------------------

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H

#include "Menu.h"
#include "Book.h"
#include "Publication.h"
#include "PublicationSelector.h"

#define MAXLOANDAYS 15
#define PENALTY 50

namespace sdds {
   class LibApp {
       bool m_changed = false;
       Menu m_mainMenu;
       Menu m_exitMenu;
       Menu m_pubMenu; //Publication Type Menu
       char p_fileName[256];
       Publication* p_Array[SDDS_LIBRARY_CAPACITY]; //PPA
       int numLoadedPub;  //NOLP
       int lastLibRefNum; //LLRN
       
       
       bool confirm(const char* message);
       
       void load();  
       void save();
       int search(int searchType);
       Publication* getPub(int libRef); //return address of PPA which match libReg
       void returnPub();
       void newPublication();
       void removePublication();
       void checkOutPub();
       
       
       
   public:
       LibApp();
       LibApp(const char* filename);
       virtual ~LibApp();
       void setEmpty(); //added
       void run();
       
       
   };
}
#endif // !SDDS_LIBAPP_H



