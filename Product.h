#ifndef SICT__Product_H_
#define SICT__Product_H_

#include "general.h"
#include "Streamable.h"
#include <iostream>

namespace sict {
	class Product:public Streamable {
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;
		void setEmpty();
		void copySet(const char* sku, const char* name, bool taxed, double price, int qtyNeeded, int quantity);
	public:
		Product();
		Product(const char* sku, const char* name, bool taxed = true, double price = 0, int qtyNeeded = 0);
		Product(const Product& P);
		
		virtual ~Product();
		//setters
		void sku(const char* sku);
		void price(const double price);
		void name(const char* name);
		void taxed(const bool taxed);
		void quantity(const int quantity);
		void qtyNeeded(const int qtyNeeded);
		//getters
		const char* sku()const;
		double price()const;
		const char* name()const;
		bool taxed()const;
		int quantity()const;
		int qtyNeeded()const;
		double cost()const;
		
		bool isEmpty()const;
		//operator overload
		Product& operator=(const Product& P);
		bool operator==(const char* name);
		int operator+=(int quantity);
		int operator-=(int quantity);
		operator const char*()const;
	};

	double operator+=(double& price, const Product& P);
	
	std::ostream& operator<<(std::ostream& ostr, const Product& P);
	std::istream& operator>>(std::istream& istr, Product& P);
}

#endif