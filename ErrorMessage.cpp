// OOP244 Aid Management Application : MS2
// File: ErrorMessage.cpp
// Version 1.0
// Date	2016-03-11
// Author         Heetai Park
// email          hpark77@myseneca.ca
// studentNumber  041258153
// Description:
// FinalProject
////////////////////////////////////////////
#include "ErrorMessage.h"
#include <cstring>
namespace sict{

	ErrorMessage::ErrorMessage(){
		message_ = nullptr;
	}
	ErrorMessage::ErrorMessage(const char* errorMessage){
		message_ = nullptr;
		message(errorMessage);
	}
	ErrorMessage& ErrorMessage::operator=(const char* errorMessage){
		message(errorMessage);
		return *this;
	}
	ErrorMessage::~ErrorMessage(){
		delete[] message_;
	}
	void ErrorMessage::clear(){
		delete[] message_;
		message_ = nullptr;
	}
	bool ErrorMessage::isClear()const{
		return message_ == nullptr;
	}
	void ErrorMessage::message(const char* value){
		delete[] message_;
		message_ = new char[strlen(value) +1];
		strcpy(message_, value);
	}
	const char* ErrorMessage::message()const{
		return message_;
	}
	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& E){
		if (!E.isClear()){
			ostr << E.message();
		}
		return ostr;
	}


}