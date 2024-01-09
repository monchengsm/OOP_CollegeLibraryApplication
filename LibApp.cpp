//Final Project Milestone 5
//Module: LibApp Module
//Filename: LibApp.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include "LibApp.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
namespace sdds {
   
    LibApp::LibApp():m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_pubMenu("Choose the type of publication:"){
        
        setEmpty();
        p_fileName[0] = '\0';
        load();
    }


    LibApp::LibApp(const char* filename):m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_pubMenu("Choose the type of publication:"){
        
        setEmpty();
        if(filename!=nullptr && filename[0]!='\0'){
            strcpy(p_fileName, filename);
        }
        load();
    }

    void LibApp::setEmpty(){
        m_changed = false;
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_pubMenu << "Book" << "Publication";
        numLoadedPub = 0;
        lastLibRefNum = 0;
    }

    LibApp::~LibApp(){
        int i = 0;
        for (i=0; i<numLoadedPub; i++){
        delete p_Array[i];
        }
    }


    bool LibApp::confirm(const char* message){
        
        bool isTrue = false;
        
        Menu confirmMenu(message);
        confirmMenu << "Yes";
        
        if (confirmMenu.run()==1){
            isTrue = true;
        }
        
        return isTrue;
    }


    void LibApp::load(){
        cout << "Loading Data" << endl;
        ifstream fin(p_fileName);
        char type{};
        int i;
        for (i = 0; fin && i < SDDS_LIBRARY_CAPACITY; i++) {
            fin >> type;
            fin.ignore();

            if(fin){
                if (type == 'P'){
                    p_Array[i] = new Publication;
                }
            
                else if (type == 'B'){
                    p_Array[i] = new Book;
                }
           
                if(p_Array[i]){
                    fin >> *p_Array[i];
                    numLoadedPub++;
                    lastLibRefNum = p_Array[i]->getRef();
                }
            
        }
    }
    }
    void LibApp::save(){
        cout << "Saving Data" << endl;
        ofstream outf(p_fileName);
        int i=0;
        for(i=0; i<numLoadedPub; i++){
            if(p_Array[i]->getRef()!=0){
                outf << *p_Array[i] << endl;
            }
        }
        
    }
    int LibApp::search(int searchType){
        //cout << "Searching for publication" << endl;
        int selectPubType = -1;
        int i = 0;
        char PubType = '0';
        char searchTitle[256];
        int selectedLibRef = 0;
        
        selectPubType = m_pubMenu.run();
        cin.ignore();
        
        if (selectPubType!=0){
            switch(selectPubType){
                case 1:
                    PubType = 'B';
                    break;
                case 2:
                    PubType = 'P';
                    break;
            }
            
            cout << "Publication Title: ";
            cin.getline(searchTitle, 256);
            
            
            PublicationSelector ps("Select one of the following found matches:");
            
            //Search All
            if (searchType == 1){
                for (i=0; i<numLoadedPub; i++){
                    if(p_Array[i]->getRef()!=0 && *p_Array[i]==searchTitle && p_Array[i]->type()==PubType){
                        ps << p_Array[i];
                    }
                }
            }
            
            //Search Checkout Items which are on loan by library members
            if (searchType == 2){
                for (i=0; i<numLoadedPub; i++){
                    if(p_Array[i]->getRef()!=0 && *p_Array[i]==searchTitle && p_Array[i]->type()==PubType &&p_Array[i]->onLoan()){
                        ps << p_Array[i];
                    }
                }
            }
            
            //Search Available Items not on loan by library members
            if (searchType == 3){
                for (i=0; i<numLoadedPub; i++){
                    if(p_Array[i]->getRef()!=0 && *p_Array[i]==searchTitle && p_Array[i]->type()==PubType &&!(p_Array[i]->onLoan())){
                        ps << p_Array[i];
                    }
                }
            }
            
            //if matches found, sort and get user selector
            if(ps){
                ps.sort();
                selectedLibRef = ps.run();
                
                if(selectedLibRef==0){
                    cout << "Aborted!" << endl;
                }

                else {
                    cout << *getPub(selectedLibRef) << endl;
                }
                
            }
            else {
                cout << "No matches found!" << endl;
            }
        }
        else {
            cout << "Aborted!" << endl;
            }
        
    return selectedLibRef;
    }


Publication* LibApp::getPub(int libRef){
    int i=0;
    int getIndex = -1;
    for(i=0; i<numLoadedPub && getIndex== -1; i++){
        if(p_Array[i]->getRef() == libRef){
            getIndex = i;
        }
    }

        return getIndex!=-1? p_Array[getIndex]: nullptr;
}

        
    void LibApp::returnPub(){
        int userSelectLibRef = 0;
        double totalPenalty = 0;
        
        cout << "Return publication to the library" << endl;
        userSelectLibRef = search(2);
        
        if(userSelectLibRef!=0){
            if(confirm("Return Publication?")){
                
                int numDaysLoan = Date() - getPub(userSelectLibRef)->checkoutDate();
                
                if (numDaysLoan > MAXLOANDAYS) {
                    totalPenalty = PENALTY * (numDaysLoan - MAXLOANDAYS) / 100.0;

                    cout << "Please pay $";
                    cout << fixed << setprecision(2) << totalPenalty;
                    cout << " penalty for being " << (numDaysLoan - MAXLOANDAYS) << " days late!" << endl;
                }
                //Set membership number
                getPub(userSelectLibRef)->set(0);
                m_changed = true;
                cout << "Publication returned" << endl;
                
            }
        }
    }

    void LibApp::newPublication(){
        int selectPubType = -1;
        Publication* p = nullptr; // for user selected object
        
        if(numLoadedPub==SDDS_LIBRARY_CAPACITY){
            cout<<"Library is at its maximum capacity!" << endl;
        }
        else{
            cout << "Adding new publication to the library" << endl;

            selectPubType = m_pubMenu.run();
            cin.ignore();

            if (selectPubType != 0) {

                if (selectPubType == 1) {
                    p = new Book;
                    cin >> *p;
                }

                else if (selectPubType == 2) {
                    p = new Publication;
                    cin >> *p;
                }

                if (cin.fail()) {
                    cin.ignore(1000, '\n');
                    cout << "Aborted!" << endl;

                }
                else {
                    if (confirm("Add this publication to the library?")) {

                        //if the object is valid
                        if (*p) {
                            //add the publication LibRefNum
                            lastLibRefNum++;
                            p->setRef(lastLibRefNum);

                            //add the address to the end of the PPA and add one to the NOLP.
                            p_Array[numLoadedPub] = p;
                            numLoadedPub++;

                            //set the "changed" flag to true
                            m_changed = true;

                            cout << "Publication added" << endl;
                        }
                        else {
                            cout << "Failed to add publication!";
                            delete p;
                        }

                    }

                }

            }

            else {
                cout << "Aborted!" << endl;
            }
        }
    }

    void LibApp::removePublication(){
        
        int userSelectLibRef;
        
        cout << "Removing publication from the library" << endl;
        userSelectLibRef = search(1);
        
        if(userSelectLibRef!=0){
            if(confirm("Remove this publication from the library?")){
                
                //get the PPA address of the publication
                //set library reference of the selected publication to 0 (zero)
                getPub(userSelectLibRef)->setRef(0);
                m_changed = true;
                cout << "Publication removed" << endl;
            }
        }
    }
        
    void LibApp::checkOutPub(){
        int userSelectLibRef = 0;
        int inputMemNum = 0;
        bool validInput = 0;
        
        cout << "Checkout publication from the library" <<endl;
        userSelectLibRef = search(3);
        
        
        if (userSelectLibRef!=0){
            if(confirm("Check out publication?")){
                cout << "Enter Membership number: ";
                
                while(validInput==0){
                    cin >> inputMemNum;
                    if(inputMemNum>=10000 && inputMemNum<=99999){
                        validInput = 1;
                        //Set membership number
                        getPub(userSelectLibRef)->set(inputMemNum);
                        m_changed = true;
                        cout << "Publication checked out" << endl;
                    }
                    else{
                        cout << "Invalid membership number, try again:";
                    }
                }
            }
        }
    }

    void LibApp::run(){
        
        bool isTerminate = false;
        unsigned userSelection;
        unsigned exitSelection;
        bool confirmSelection;
        
        do{
            userSelection = m_mainMenu.run(); //display menu
            if(userSelection == 1){
                newPublication();
            }
            else if(userSelection == 2){
                removePublication();
            }
            else if(userSelection == 3){
                checkOutPub();
            }
            else if(userSelection == 4){
                returnPub();
            }
            else if(userSelection == 0){
                if(m_changed==true){
                    exitSelection = m_exitMenu.run();
                    
                    if(exitSelection==1){
                        save();
                        isTerminate = true;
                    }
                    else if(exitSelection==0){
                        confirmSelection = confirm("This will discard all the changes are you sure?");
                        if(confirmSelection){
                            isTerminate = true;
                        }
                    }
                    
                }
            
                else{
                    isTerminate = true;
                    //cout << endl;
                }
                
            }

        cout << endl;
        }while(isTerminate!=true); //m_mainmenu
        cout << "-------------------------------------------" << endl;
        cout <<"Thanks for using Seneca Library Application" << endl;
    }

}
