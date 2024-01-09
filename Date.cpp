// Final Project Milestone 5
// Date Module
// File	Date.cpp
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// SIU MAN CHENG      18 JUL 2023          MS3 UPDATE
//
/////////////////////////////////////////////////////////////////
///


#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <limits>
#include <ctime>
using namespace std;
#include "Date.h"
namespace sdds {



    //for MS3 testing
   bool sdds_test = false;
   int sdds_year = 2023;
   int sdds_mon = 12;
   int sdds_day = 25;


    //Copying constructors
    Date::Date(const Date& src){
        m_year = src.m_year;
        m_mon = src.m_mon;
        m_day = src.m_day;
        m_ErrorCode = src.m_ErrorCode;
        m_CUR_YEAR = src.m_CUR_YEAR;
    }

    Date& Date::operator=(const Date& src){
        if(this!=&src){
            m_year = src.m_year;
            m_mon = src.m_mon;
            m_day = src.m_day;
            m_ErrorCode = src.m_ErrorCode;
            m_CUR_YEAR = src.m_CUR_YEAR;
        }
        
        return *this;
    }


   bool Date::validate() {
      errCode(NO_ERROR);
      if (m_year < MIN_YEAR || m_year > m_CUR_YEAR) {
         errCode(YEAR_ERROR);
      }
      else if (m_mon < 1 || m_mon > 12) {
         errCode(MON_ERROR);
      }
      else if (m_day < 1 || m_day > mdays()) {
         errCode(DAY_ERROR);
      }
      return !bad();
   }
   int Date::mdays()const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
      mon--;
      return days[mon] + int((mon == 1) * ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
   }
    int Date::systemYear()const {
      int theYear = sdds_year;
      if (!sdds_test) {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         theYear = lt.tm_year + 1900;
      }
      return theYear;
   }

    void Date::setToToday() {
      if (sdds_test) {
         m_day = sdds_day;
         m_mon = sdds_mon;
         m_year = sdds_year;
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         m_day = lt.tm_mday;
         m_mon = lt.tm_mon + 1;
         m_year = lt.tm_year + 1900;
      }
      errCode(NO_ERROR);
   }

   int Date::daysSince0001_1_1()const { // Rata Die day since 0001/01/01 
      int ty = m_year;
      int tm = m_mon;
      if (tm < 3) {
         ty--;
         tm += 12;
      }
      return 365 * ty + ty / 4 - ty / 100 + ty / 400 + (153 * tm - 457) / 5 + m_day - 306;
   }
   Date::Date() :m_CUR_YEAR(systemYear()) {
      setToToday();
   }
   Date::Date(int year, int mon, int day) : m_CUR_YEAR(systemYear()) {
      m_year = year;
      m_mon = mon;
      m_day = day;
      validate();
   }
   const char* Date::dateStatus()const {
      return DATE_ERROR[errCode()];
   }
   int Date::currentYear()const {
      return m_CUR_YEAR;
   }
   void Date::errCode(int readErrorCode) {
      m_ErrorCode = readErrorCode;
   }
   int Date::errCode()const {
      return m_ErrorCode;
   }
   bool Date::bad()const {
      return m_ErrorCode != 0;
   }
  
   ostream& operator<<(ostream& os, const Date& RO) {
      return RO.write(os);
   }
   istream& operator>>(istream& is, Date& RO) {
      return RO.read(is);
   }

    std::istream& Date::read(std::istream& is){
        
        char delim;
        
        
        m_ErrorCode = NO_ERROR; //Clear error code
        is >> m_year >> delim >> m_mon >> delim >> m_day;
    
        
        //std::cout << "This is myear:" << m_year << endl;
        //std::cout << "This is mon:" << m_mon << endl;
        //std::cout << "This is day:" << m_day << endl;
        
        if(is.fail()){
            m_ErrorCode = CIN_FAILED;
        }
        
        else{
            validate();
        }
        
        is.clear();
        //is.ignore(1000, '\n');  MS3 requirement

        return is;
    }

    std::ostream& Date::write(std::ostream& os)const{
        
        
        if(*this){
            
            os << m_year << "/";
            os.fill('0');
            os.width(2);
            os << right << m_mon;
            os << "/";
            os.fill('0');
            os.width(2);
            os << m_day;
            
            os.fill(' ');
        
        }
        
        else{
            os << dateStatus();
        }
        
        return os;
    }
    
    Date::operator bool() const {

        return !bad();
    }


    bool operator==(const Date& src1, const Date& src2){        
        return src1.daysSince0001_1_1() == src2.daysSince0001_1_1();
    }


    bool operator!=(const Date& src1, const Date& src2){
        return src1.daysSince0001_1_1() != src2.daysSince0001_1_1();
    }

    bool operator>=(const Date& src1, const Date& src2){
        return src1.daysSince0001_1_1() >= src2.daysSince0001_1_1();
    }

    bool operator<=(const Date& src1, const Date& src2){
        return src1.daysSince0001_1_1() <= src2.daysSince0001_1_1();
    }

    bool operator>(const Date& src1, const Date& src2){
        return src1.daysSince0001_1_1() > src2.daysSince0001_1_1();
    }

    bool operator<(const Date& src1, const Date& src2){
        return src1.daysSince0001_1_1() < src2.daysSince0001_1_1();
    }

    int operator-(const Date& src1, const Date& src2){
        return src1.daysSince0001_1_1() - src2.daysSince0001_1_1();
    }


    

}
