#include"transaction.h"
#include"product.h"

Transaction* readFile(const char* fileName);
void writeFile(const char* fileName, char* itemSet[], int priceSet[]);
Product* readProducts(const char* fileName);
