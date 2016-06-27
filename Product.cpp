// OOP244 Aid Management Application : MS4
// File: Product.cpp
// Version 1.0
// Date	2016-03-19
// Author         Heetai Park
// email          hpark77@myseneca.ca
// studentNumber  041258153
// Description:
// FinalProject
////////////////////////////////////////////

#include <cstring>
#include "Product.h"

namespace sict {
	void Product::setEmpty(){
		sku_[0] = 0;
		name_ = nullptr;
		price_ = 0;
		taxed_ = false;
		quantity_ = 0;
		qtyNeeded_ = 0;
	}
	void Product::copySet(const char* sku, const char* name, bool taxed, double price, int qtyNeeded, int quantity){
		if (sku && name){
			this->sku(sku);
			if (name_){
				name_ = nullptr;
			}
			this->name(name);
			
			taxed_ = taxed;
			price_ = price;
			qtyNeeded_ = qtyNeeded;
			quantity_ = quantity;
		}
		else {
			setEmpty();
		}
	}
	Product::Product(){
		setEmpty();
	}

	Product::Product(const char* sku, const char* name, bool taxed, double price, int qtyNeeded){
		int quantity = 0;
		copySet(sku, name, taxed, price, qtyNeeded, quantity);
	}
	Product::Product(const Product& P){
		if (this != &P){
			copySet(P.sku_, P.name_, P.taxed_, P.price_, P.qtyNeeded_, P.quantity_);
		}
	}
	Product::~Product(){
		delete[] name_;
		name_ = nullptr;
	}
	//setters
	void Product::sku(const char* sku){
		strncpy(sku_, sku, 7);
		sku_[7] = 0;
	}
	void Product::price(const double price){
		price_ = price;
	}
	void Product::name(const char* name){
		int len = strlen(name);
		delete[] name_;
		name_ = new char[len + 1];
		strncpy(name_, name, len);
		name_[len] = 0;
	}
	void Product::taxed(const bool taxed){
		taxed_ = taxed;
	}
	void Product::quantity(const int quantity){
		quantity_ = quantity;
	}
	void Product::qtyNeeded(const int qtyNeeded){
		qtyNeeded_ = qtyNeeded;
	}
	//getters
	const char* Product::sku()const{
		return sku_;
	}
	double Product::price()const{
		return price_;
	}
	const char* Product::name()const{
		return name_;
	}
	bool Product::taxed()const{
		return taxed_;
	}
	int Product::quantity()const{
		return quantity_;
	}
	int Product::qtyNeeded()const{
		return qtyNeeded_;
	}
	double Product::cost()const{
		double rtn = 0;
		if (!taxed_){
			rtn = price();
		}
		else{
			rtn = price() * (1+TAX);
		}
		return rtn;
	}

	bool Product::isEmpty()const{
		return 	sku_[0] == 0 && name_ == nullptr && price_ == 0 && !taxed_ && quantity_ == 0 && qtyNeeded_ == 0;
	}
	//operator overload
	Product& Product::operator=(const Product& P){
		if (this != &P){
			delete[] name_;
			name_ = nullptr;
			copySet(P.sku_, P.name_, P.taxed_, P.price_, P.qtyNeeded_, P.quantity_);
		}
		return *this;
	}
	bool Product::operator==(const char* sku){
		return strcmp(sku_, sku) == 0;
	}
	int Product::operator+=(int quantity){
		return quantity_ += quantity;
	}
	int Product::operator-=(int quantity){
		return quantity_ -= quantity;
	}
	Product::operator const char*()const{
		return name_;
	}
	double operator+=(double& tPrice, const Product& P){
		return tPrice += P.cost() * P.quantity();
	}
	std::ostream& operator<<(std::ostream& ostr, const Product& P){
		return P.write(ostr, true);
	}
	std::istream& operator>>(std::istream& istr, Product& P){
		return P.read(istr);
	}
}