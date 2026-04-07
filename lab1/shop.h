#ifndef SHOP_H
#define SHOP_H
#include <string>

struct Money {
    int hrn;
    short int kop;
};
void normalize(Money& money);
void addValues(Money& money,int addHrn, int addKop);
void multiplyBy(Money& money, int count);
short int roundTo10(Money& money);
void display(const Money& money);

void displayMenu();


#endif