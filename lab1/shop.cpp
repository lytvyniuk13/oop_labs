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
    int total_kopecks = (int)money.hrn * 100 + money.kop;
    total_kopecks *= count;

    money.hrn = (int)(total_kopecks / 100);
    money.kop = (short int)(total_kopecks % 100);
    
}

Money roundTo25(const Money& money)  {
    int total_kopecks = (int)money.hrn * 100 + money.kop;
    
    int remainder = total_kopecks % 25;
    int base = total_kopecks - remainder;

    if (remainder >= 13) {
        base += 25;
    }

    Money rounded = { base / 100, (short int)(base % 100) };
    return rounded;
}

void display(const Money& money) {
    cout << money.hrn << ".";
    if (money.kop < 10) {
        cout << "0";
    }
    cout << money.kop << " UAH";
}

void displayMenu() {
    const int MAX_ITEMS = 3;
    
    string names[MAX_ITEMS] = {"Milk", "Bread", "Eggs"};
    Money prices[MAX_ITEMS];
    
    //file
    ifstream file("items.txt");
    int h, k_input;
    int itemCount = 0;
    
    while (file >> h >> k_input) {
        if (itemCount >= MAX_ITEMS) break; 

        prices[itemCount].hrn = h;
        prices[itemCount].kop = (short int)k_input;
        itemCount++;

    }
    file.close();

    Money totalSum = {0, 0};
    int choice;
//menu
    do {
        cout << "\nAvailable Items:" << endl;
        for (int j = 0; j < itemCount; ++j) {
            normalize(prices[j]);
            cout << j + 1 << ". " << names[j] << " - ";
            display(prices[j]);
            cout << endl;
        }
        cout << "0. Generate Receipt" << endl;
        cout << "Your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= itemCount) {
            int quantity;
            cout << "Enter quantity:";
            cin >> quantity;

            if (quantity > 0) {
                Money itemTotal = prices[choice - 1];
                multiplyBy(itemTotal, quantity);
                addValues(totalSum, itemTotal.hrn, itemTotal.kop);
            }
        } else if (choice != 0) {
            cout << "Invalid choice, please try again" << endl;
        }

    } while (choice != 0);
//receipt
    normalize(totalSum);
    Money roundedSum = roundTo25(totalSum);

    cout << "====================================" << endl;
    cout << "Total Sum:           "; display(totalSum); cout << endl;
    cout << "Amount to Pay:       "; display(roundedSum); cout << endl;
    cout << "====================================" << endl;

}
