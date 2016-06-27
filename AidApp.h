#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__
#include "Product.h"
#include <cstring>

namespace sict{
	class AidApp{
	private:
		char filename_[256];
		Product* product_[MAX_NO_RECS];
		std::fstream datafile_;
		int noOfProducts_;

		AidApp(const AidApp& A) = delete;
		AidApp& operator=(const AidApp& A) = delete;
	public:
		AidApp(const char* filename);
		~AidApp();
		void pause()const;
		int menu();
		void loadRecs();
		void saveRecs();
		void listProducts()const;
		int SearchProducts(const char* sku)const;
		void addQty(const char* sku);
		void addProduct(bool isPerishable);
		void updateProduct(const char* sku);
		void deleteProduct(const char* sku);
		void sortProduct();
		int run();
	};
	template <typename Type>
	void swap(Type** a, Type** b){
		Type* temp = *a;
		*a = *b;
		*b = temp;
	}

	template <typename Type>
	void sort(Type a[], int size, bool ascending = true){
		int i;
		int j;
		for (i = 0; i < (size - 1); i++){
			for (j = 0; j < size - i - 1; j++){
				if (ascending){
					if (strcmp(*a[j], *a[j + 1]) > 0){
						swap(&a[j], &a[j + 1]);
					}
				}
				else{
					if (strcmp(*a[j], *a[j + 1]) < 0){
						swap(&a[j], &a[j + 1]);
					}
				}
			}
		}
	}
}
#endif