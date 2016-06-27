// OOP244 Aid Management Application : MS5
// File: AmaPerishable.cpp
// Version 1.0
// Date	2016-04-03
// Author         Heetai Park
// email          hpark77@myseneca.ca
// studentNumber  041258153
// Description:
// FinalProject
////////////////////////////////////////////
#include "AmaPerishable.h"
using namespace std;
namespace sict{
	AmaPerishable::AmaPerishable(char fileTag) : AmaProduct(fileTag){

	}
	const Date& AmaPerishable::expiry()const{
		return expiry_;
	}
	void AmaPerishable::expiry(const Date &value){
		expiry_ = value;
	}
	fstream& AmaPerishable::store(fstream& file, bool addNewLine)const{
		AmaProduct::store(file, false);
		file << "," << expiry();
		if (addNewLine){
		file << endl;
		}
		return file;
	}
	fstream& AmaPerishable::load(fstream& file){
		AmaProduct::load(file);
		expiry_.read(file);
		return file;
	}
	ostream& AmaPerishable::write(ostream& ostr, bool linear)const{
		AmaProduct::write(ostr, linear);
		if (err_.isClear() && !isEmpty()){
			linear ? ostr << expiry() : ostr << "Expiry date: " << expiry() << endl;
		}
		return ostr;
	}
	istream& AmaPerishable::read(istream& istr){
		AmaProduct::read(istr);
		if (err_.isClear()){
			cout << "Expiry date (YYYY/MM/DD): ";
			Date temp;
			temp.read(istr);
			if (temp.errCode() == CIN_FAILED){
				istr.setstate(ios::failbit);
				err_.message("Invalid Date Entry");
			}
			else if (temp.errCode() == YEAR_ERROR){
				istr.setstate(ios::failbit);
				err_.message("Invalid Year in Date Entry");
			}
			else if (temp.errCode() == MON_ERROR){
				istr.setstate(ios::failbit);
				err_.message("Invalid Month in Date Entry");
			}
			else if (temp.errCode() == DAY_ERROR){
				istr.setstate(ios::failbit);
				err_.message("Invalid Day in Date Entry");
			}
			else if (!cin.fail()){
				expiry_ = temp;
			}
		}
		return istr;
	}
}
