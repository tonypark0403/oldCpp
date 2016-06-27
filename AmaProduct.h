#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__
#include "ErrorMessage.h"
#include "Product.h"

namespace sict{
  class AmaProduct : public Product{
  private:
	  char fileTag_;
	  char unit_[11];
  protected:
	  ErrorMessage err_;
  public:
	  AmaProduct(const char fileTag = 'N');
	  const char* unit()const;
	  void unit(const char* value);
	  virtual std::fstream& store(std::fstream& file, bool addNewLine=true)const;
	  virtual std::fstream& load(std::fstream& file);
	  virtual std::ostream& write(std::ostream& os, bool linear)const;
	  virtual std::istream& read(std::istream& istr);
  };
}
#endif


