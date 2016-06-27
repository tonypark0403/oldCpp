#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__
#include "AmaProduct.h"
#include "Date.h"

namespace sict{
  class AmaPerishable:public AmaProduct{
  private:
	  Date expiry_;
  public:
	  AmaPerishable(char fileTag = 'P');
	  const Date& expiry()const;
	  void expiry(const Date &value);
	  virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const;
	  virtual std::fstream& load(std::fstream& file);
	  virtual std::ostream& write(std::ostream& ostr, bool linear)const;
	  virtual std::istream& read(std::istream& istr);
  };
}
#endif
