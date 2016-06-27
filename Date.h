#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>
#include "general.h"
namespace sict{

	class Date{
	private:
		int year_;
		int mon_;
		int day_;
		int readErrorCode_;
		int value()const;
		void errCode(int errorCode);
		void setEmpty();
		void setCopy(int year, int mon, int day);
		void validation();
	public:
		Date();
		Date(int year, int mon, int day);
		bool operator==(const Date& D)const;
		bool operator!=(const Date& D)const;
		bool operator<(const Date& D)const;
		bool operator>(const Date& D)const;
		bool operator<=(const Date& D)const;
		bool operator>=(const Date& D)const;
		int mdays()const;
		int errCode()const;
		bool bad()const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
	};
	std::istream& operator>>(std::istream& istr, Date& D);
	std::ostream& operator<<(std::ostream& ostr, const Date& D);
}
#endif