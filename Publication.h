//Final Project Milestone 5
//Module: Publication Module
//Filename: Publication.h
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

#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H

#include "Date.h"
#include "Streamable.h"
#include "Lib.h"
#include "string.h"

#define MAXTITLESIZE 255

namespace sdds {


class Publication: public Streamable{
    char* m_title;
    char m_shelfId[SDDS_SHELF_ID_LEN + 1];
    int m_membership;
    int m_libRef;
    Date m_date; 
    
public:
    Publication();
    virtual ~Publication();
    
    //Copying constructors
    Publication(const Publication& src);
    Publication& operator=(const Publication& src);
    
    //Modifiers
    virtual void set(int member_id);
       // Sets the membership attribute to either zero or a five-digit integer.
    void setRef(int value);
       // Sets the **libRef** attribute value
    void resetDate();
       // Sets the date to the current date of the system.
    
    
    //Queries
    virtual char type()const;
       //Returns the character 'P' to identify this object as a "Publication object"
    bool onLoan()const;
       //Returns true is the publication is checkout (membership is non-zero)
    Date checkoutDate()const;
       //Returns the date attribute
    bool operator==(const char* title)const;
       //Returns true if the argument title appears anywhere in the title of the
       //publication. Otherwise, it returns false; (use strstr() function in <cstring>)
    operator const char* ()const;
       //Returns the title attribute
    virtual int getRef()const;
       //Returns the libRef attirbute.
    
    bool conIO(std::ios& ios) const;
    virtual std::ostream& write(std::ostream& os) const;
    virtual std::istream& read(std::istream& istr);
    
   operator bool() const;
    
};

    

}
#endif // !SDDS_STREAMABLE_H



