// OOP244 Aid Management Application : MS5
// File: AmaProduct.cpp
// Version 1.0
// Date	2016-04-03
// Author         Heetai Park
// email          hpark77@myseneca.ca
// studentNumber  041258153
// Description:
// FinalProject
////////////////////////////////////////////
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "AmaProduct.h"
using namespace std;
namespace sict{
	AmaProduct::AmaProduct(char fileTag)
		/*:Product(sku, name)*/
	{
		fileTag_ = fileTag;
	}
	const char* AmaProduct::unit()const{
		return unit_;
	}
	void AmaProduct::unit(const char* value){
		strncpy(unit_, value, 10);
		unit_[10] = '\0';
	}
	fstream& AmaProduct::store(fstream& file, bool addNewLine)const{
		if (!isEmpty()){
			//file.open("amaPrd.txt", ios::out | ios::app);
			file << fileTag_ << "," << sku() << "," << name() << "," << price() << ","
				<< taxed() << "," << quantity() << "," << unit() << "," << qtyNeeded();
			if (addNewLine){
				file << endl;
			}
			//file.clear();
			//file.close();
		}
		return file;
	}
	fstream& AmaProduct::load(fstream& file){
		//file.open("amaPrd.txt", ios::in);
		char buf[2000];
		double dbuf;
		int ibuf;
		file.getline(buf, MAX_SKU_LEN + 1, ',');
		sku(buf);
		file.getline(buf, 2000, ',');
		name(buf);
		file >> dbuf;
		price(dbuf);
		file.ignore();
		file >> ibuf;
		taxed(bool(ibuf));
		file.ignore();
		file >> ibuf;
		quantity(ibuf);
		file.ignore();
		file.getline(buf, 10, ',');
		unit(buf);
		file >> ibuf;
		qtyNeeded(ibuf);
		file.ignore();
		//file.clear();
		//file.close();
		return file;
	}
	ostream& AmaProduct::write(ostream& os, bool linear)const{
		if (err_.isClear()){
			linear ? os << setfill(' ') << setw(MAX_SKU_LEN) << left << sku() << "|" << setw(20) << name() << "|"
				<< setw(7) << setprecision(2) << right << fixed << cost() << "|" << setw(4)
				<< quantity() << "|" << setw(10) << left << unit() << "|" << setw(4)
				<< right << qtyNeeded() << "|"
				:
				os << "Sku: " << sku() << endl
				<< "Name: " << name() << endl
				<< "Price: " << price() << endl
				<< "Price after tax: ";
			if (!linear){
				if (!taxed()){
				os << "N/A";
				}
				else {
					os << cost();
				}
				os << endl << "Quantity On Hand: " << quantity() << " " << unit() << endl
					<< "Quantity Needed: " << qtyNeeded() << endl;
			}
		}
		else {
			os << err_;
		}
		
		return os;
	}
	istream& AmaProduct::read(istream& istr){
		char buf[2000];
		double dbuf;
		int ibuf = 0;
		bool check = false;
		cout << "Sku: ";
		istr >> buf;
		sku(buf);
		cout << "Name: ";
		istr >> buf;
		name(buf);
		cout << "Unit: ";
		istr >> buf;
		unit(buf);
		cout << "Taxed? (y/n): ";
		istr >> buf;
		if (!cin.fail() && (buf[0] == 'y' || buf[0] == 'Y')){
			taxed(true);
			check = true;
		}
		else if (!cin.fail() && (buf[0] == 'n' || buf[0] == 'N')){
			taxed(false);
			check = true;
		}
		else{
			istr.setstate(ios::failbit);
			err_.message("Only (Y)es or (N)o are acceptable");
		}
		if (check){
			cout << "Price: ";
			istr >> dbuf;
			if (cin.fail()){
				err_.message("Invalid Price Entry");
				check = false;
			}
			else {
				err_.clear();
				price(dbuf);
			}
		}
		if (check){
			cout << "Quantity On hand: ";
			istr >> ibuf;
			if (cin.fail()){
				err_.message("Invalid Quantity Entry");
				check = false;
			}
			else {
				err_.clear();
				quantity(ibuf);
			}
		}
		if (check){
			cout << "Quantity Needed: ";
			istr >> ibuf;
			if (cin.fail()){
				err_.message("Invalid Quantity Needed Entry");
				check = false;
			}
			else {
				err_.clear();
				qtyNeeded(ibuf);
			}
		}
		return istr;
	}
}