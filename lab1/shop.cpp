#include <iostream>
#include <fstream>
#include "shop.h"
using namespace std;

void normalize(Money& money) {
    if (money.kop >= 100) {
        money.hrn += money.kop / 100;
        money.kop %= 100;
    }
    while (money.kop < 0) {
        money.hrn -= 1;
        money.kop += 100;
    }
}

void addValues(Money& money, int addHrn, int addKop) {
    money.hrn += addHrn;
    money.kop += addKop;
}

void multiplyBy(Money& money, int count) {
    money.hrn *= count;
    money.kop *= count; 
}

short int roundTo10(Money& money)  {
    short int remainder = money.kop % 10;
    if (remainder >= 7) {
        money.kop += (10 - remainder);
    } else {
        money.kop -= remainder;
    }
    return money.kop;
}
void display(const Money& money) {
    cout << money.hrn << ".";
    if (money.kop < 10) {
        cout << "0";
    }
    cout << money.kop << " UAH";
}

void displayMenu() {
   
    //file
    ifstream file("items.txt");
    string name;
    int h, k, q;
    Money totalSum = {0, 0};
    while (file >> name >> h >> k >> q) {
       Money itemPrice = {h, (short int)k};
        normalize(itemPrice);
        
        Money itemTotal = itemPrice;
        multiplyBy(itemTotal, q);
        addValues(totalSum, itemTotal.hrn, itemTotal.kop);
    }
    file.close();

    normalize(totalSum);
    Money roundedSum = totalSum;
    roundTo10(roundedSum);
    cout << "====================================" << endl;
    cout << "Total Sum:           "; display(totalSum); cout << endl;
    cout << "Amount to Pay:       "; display(roundedSum); cout << endl;
    cout << "====================================" << endl;

}
