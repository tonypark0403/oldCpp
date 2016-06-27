// OOP244 Aid Management Application : MS1 
// File: Date.cpp
// Version 1.0
// Date	2016-03-10
// Author         Heetai Park
// email          hpark77@myseneca.ca
// studentNumber  041258153
// Description:
// FinalProject
////////////////////////////////////////////
#include <iomanip>
#include <iostream>
using namespace std;
#include "Date.h"
#include "general.h"
namespace sict{
	int Date::value()const{
		return year_ * 372 + mon_ * 31 + day_;
	}
	void Date::errCode(int errorCode){
		readErrorCode_ = errorCode;
	}
	void Date::setEmpty(){
		year_ = 0;
		mon_ = 0;
		day_ = 0;
		readErrorCode_ = NO_ERROR;
	}
	void Date::setCopy(int year, int mon, int day){
		year_ = year;
		mon_ = mon;
		day_ = day;
		readErrorCode_ = NO_ERROR;
	}
	void Date::validation(){
		if (year_ < MIN_YEAR || year_ > MAX_YEAR){
			readErrorCode_ = YEAR_ERROR;
		}
		else if (mon_ < 1 || mon_ > 12) {
			readErrorCode_ = MON_ERROR;
		}
		else if (day_ < 1 || day_ > mdays()) {
			readErrorCode_ = DAY_ERROR;
		}
	}
	Date::Date(){
		setEmpty();
	}
	Date::Date(int year, int mon, int day){
		setCopy(year, mon, day);
	}
	bool Date::operator==(const Date& D)const{
		return (value() == D.value());
	}
	bool Date::operator!=(const Date& D)const{
		return (value() != D.value());
	}
	bool Date::operator<(const Date& D)const{
		return (value() < D.value());
	}
	bool Date::operator>(const Date& D)const{
		return (value() > D.value());
	}
	bool Date::operator<=(const Date& D)const{
		return (value() <= D.value());
	}
	bool Date::operator>=(const Date& D)const{
		return (value() >= D.value());
	}
	int Date::mdays()const{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}
	int Date::errCode()const {
		return readErrorCode_;
	}
	bool Date::bad()const{
		return (!readErrorCode_);
	}
	std::istream& Date::read(std::istream& istr){
		readErrorCode_ = NO_ERROR;
		istr >> year_;
		istr.ignore();
		istr >> mon_;
		istr.ignore();
		istr >> day_;
		if (cin.fail()){
			readErrorCode_ = CIN_FAILED;
		} 
		else {
			validation();
		}
		//cin.ignore(1000, '\n');
		return istr;
	}
	std::ostream& Date::write(std::ostream& ostr)const{
		ostr << year_ << "/" << setfill('0') << setw(2) << mon_ << "/" << setw(2) << day_;
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, Date& D){
		return D.read(istr);
	}
	std::ostream& operator<<(std::ostream& ostr, const Date& D){
		return D.write(ostr);
	}
}