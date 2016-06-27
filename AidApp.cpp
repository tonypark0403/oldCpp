// OOP244 Aid Management Application : MS6
// File: AidApp.h
// Version 1.0
// Date   2016-04-11
// Author         Heetai Park
// email          hpark77@myseneca.ca
// studentNumber  041258153
// Description:
// FinalProject
////////////////////////////////////////////
#include <iostream>
#include <cstring>
#include <iomanip>
#include "AidApp.h"
#include "AmaPerishable.h"
using namespace std;
namespace sict{
	AidApp::AidApp(const char* filename){
		int i;
		if (filename){
			strncpy(filename_, filename, 255);
			filename_[255] = 0;
			for (i = 0; i < MAX_NO_RECS; i++){
				product_[i] = nullptr;
			}
			noOfProducts_ = 0;
			loadRecs();
		}
	}
	AidApp::~AidApp(){
		//delete[] product_;
		int i = 0;
		for (i = 0; i < noOfProducts_; i++){
			delete product_[i];
		}
	}
	void AidApp::pause()const{
		cout << "Press Enter to continue..." << endl;
		cin.ignore(2000, '\n');
	}
	int AidApp::menu(){
		int rtn = -1;
		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "1- List products" << endl;
		cout << "2- Display product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to quantity of purchased products" << endl;
		cout << "6- Update product quantity" << endl;
		cout << "7- Delete product" << endl;
		cout << "8- Sort Products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> rtn;
		return (cin.fail() || rtn < 0 || rtn > 8) ? -1 : rtn;
	}
	void AidApp::loadRecs(){
		int readIndex = 0;
		char ch;
		datafile_.open(filename_, ios::in);
		if (datafile_.is_open()){
			while (!datafile_.get(ch).fail()){
				datafile_.ignore(1);
				delete product_[readIndex];
				if (ch == 'P'){
					AmaPerishable* item = new AmaPerishable;
					item->load(datafile_);
					product_[readIndex] = item;
					readIndex++;
					datafile_.ignore();
				}
				else if (ch == 'N'){
					AmaProduct* item = new AmaProduct;
					item->load(datafile_);
					product_[readIndex] = item;
					readIndex++;
				}
				noOfProducts_ = readIndex;
			}
		}
		else {
			datafile_.clear();
			datafile_.close();
			datafile_.open(filename_, ios::out);
			datafile_.close();
		}
	}
	void AidApp::saveRecs(){
		datafile_.open(filename_, ios::out);
		int i = 0;
		for (i = 0; i < noOfProducts_; i++){
			product_[i]->store(datafile_);
		}
		datafile_.close();
	}
	void AidApp::listProducts()const{
		int i;
		cout << endl << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
		cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;
		double totalCost = 0;
		int count = 0;
		for (i = 0; i < noOfProducts_; i++){
			cout << setw(4) << setfill(' ') << i + 1 << " | ";
			product_[i]->write(cout, true) << endl;
			count++;
			totalCost += (product_[i]->cost() * product_[i]->quantity());
			if (count == 10){
				pause();
				count = 0;
			}
		}
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "Total cost of support: $" << totalCost << endl;
	}
	int AidApp::SearchProducts(const char* sku)const{
		int rtn = -1;
		int i = 0;
		for (i = 0; i < noOfProducts_; i++){
			if (*product_[i] == sku){
				rtn = i;
			}
		}
		return rtn;
	}
	void AidApp::addQty(const char* sku){
		int searchSku = SearchProducts(sku);
		if (searchSku == -1){
			cout << "Not found!" << endl;
		}
		else{
			int numOfQty = 0;
			cout << endl;
			product_[searchSku]->write(cout, false);
			cout << endl << "Please enter the number of purchased items: ";
			cin >> numOfQty;
			while (cin.fail()){
				cout << "Invalid quantity value!" << endl;
				cout << "Please enter the number of purchased items: ";
				cin >> numOfQty;
			}
			if (numOfQty <= (product_[searchSku]->qtyNeeded() - product_[searchSku]->quantity())){
				*product_[searchSku] += numOfQty;
			}
			else{
				int needCnt = product_[searchSku]->qtyNeeded() - product_[searchSku]->quantity();
				*product_[searchSku] += needCnt;
				cout << "Too many items; only " << needCnt
					<< " is needed, please return the extra " << numOfQty - needCnt << " items." << endl;
			}
			saveRecs();
			cout << endl << "Updated!" << endl;
		}
	}
	void AidApp::addProduct(bool isPerishable){
		Product* P;
		if (isPerishable){
			P = new AmaPerishable;
		}
		else{
			P = new AmaProduct;
		}
		P->read(cin);
		if (cin.fail()){
			P->write(cout, false);
			cin.clear();
			cin.ignore();
		}
		else {
			product_[noOfProducts_] = P;
			noOfProducts_++;
			saveRecs();
			cout << endl << "Product added" << endl;
		}
	}
	void AidApp::updateProduct(const char* sku){
		int searchSku = SearchProducts(sku);
		if (searchSku == -1){
			cout << "Not found!" << endl;
		}
		else{
			cout << endl;
			product_[searchSku]->write(cout, false);
			cout << endl;
			product_[searchSku]->read(cin);
			while (cin.fail()){
				cout << "Invalid value!" << endl;
				cout << "Please update correct data" << endl;
				product_[searchSku]->read(cin);
			}
			saveRecs();
			cout << endl << "Updated!" << endl;
		}
	}
	void AidApp::deleteProduct(const char* sku){
		int searchSku = SearchProducts(sku);
		if (searchSku == -1){
			cout << "Not found!" << endl;
		}
		else{
			cout << endl;
			int i = 0;
			int check;
			for (i = 0; i < noOfProducts_; i++){
				if (*product_[i] == sku){
					check = i;
					break;
				}
			}
			for (i = check; i < (noOfProducts_ - 1); i++){
				*product_[i] = *product_[i + 1];
			}
			noOfProducts_--;
			saveRecs();
			cout << endl << "Deleted!" << endl;
		}
	}
	void AidApp::sortProduct(){
		sort(product_, noOfProducts_, true);
		saveRecs();
		cout << endl << "Sorted!" << endl;
	}
	int AidApp::run(){
		int check;
		int searchSku = -1;
		char buf[256];
		do{
			check = menu();
			cin.ignore(2000, '\n');
			switch (check){
			case -1:
				cout << "===Invalid Selection, try again.===" << endl;
				cout << endl;
				pause();
				break;
			case 0:
				cout << endl << "Goodbye!!" << endl;
				break;
			case 1:
				listProducts();
				cout << endl;
				pause();
				break;
			case 2:
				cout << endl << "Please enter the SKU: ";
				cin >> buf;
				cin.ignore(2000, '\n');
				searchSku = SearchProducts(buf);
				if (searchSku == -1){
					cout << "Not found!" << endl;
				}
				else{
					cout << endl;
					product_[searchSku]->write(cout, false);
				}
				cout << endl;
				pause();
				break;
			case 3:
				cout << endl;
				addProduct(false);
				cout << endl;
				break;
			case 4:
				cout << endl;
				addProduct(true);
				cout << endl;
				break;
			case 5:
				cout << endl;
				cout << "Please enter the SKU: ";
				cin >> buf;
				addQty(buf);
				cout << endl;
				break;
			case 6:
				cout << endl;
				cout << "Please enter the SKU: ";
				cin >> buf;
				updateProduct(buf);
				cout << endl;
				break;
			case 7:
				cout << endl;
				cout << "Please enter the SKU: ";
				cin >> buf;
				deleteProduct(buf);
				cout << endl;
				break;
			case 8:
				cout << endl;
				sortProduct();
				cout << endl;
				break;
			default:
				cout << "===Invalid Selection, try again.===";
				break;
			}
		} while (check != 0);
		return 0;
	}
}