#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;
public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    string getItem() { return Item; }
    int getRate() { return Rate; }
    int getQuant() { return Quantity; }
};

void addItem(Bill& b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1. Add Item\n";
        cout << "\t2. Close\n";
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("D:/Bill.txt", ios::app);
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            } else {
                out << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl;
                cout << "\tItem Added Successfully" << endl;
            }
            out.close();
            Sleep(2000);
        } else if (choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(2000);
        }
    }
}

void printBill() {
    system("cls");
    int count = 0;
    bool close = false;
    while (!close) {
        system("cls");
        int choice;
        cout << "\t1. Add Bill\n";
        cout << "\t2. Close Session\n";
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("D:/Bill.txt");
            ofstream out("D:/BillTemp.txt");
            string line;
            bool found = false;

            while (getline(in, line)) {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;

                getline(ss, itemName, ':');
                ss >> ws >> itemRate;
                ss.ignore(2, ':'); // skip ' :'
                ss >> ws >> itemQuant;

                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = itemRate * quant;
                        cout << "\n\tItem | Rate | Quantity | Amount\n";
                        cout << "\t" << itemName << "\t" << itemRate << "\t" << quant << "\t" << amount << endl;
                        int newQuant = itemQuant - quant;
                        count += amount;
                        out << itemName << " : " << itemRate << " : " << newQuant << endl;
                    } else {
                        cout << "\tSorry, Not Enough Stock!" << endl;
                        out << line << endl;
                    }
                } else {
                    out << line << endl;
                }
            }

            if (!found) {
                cout << "\tItem Not Available!" << endl;
            }

            in.close();
            out.close();
            remove("D:/Bill.txt");
            rename("D:/BillTemp.txt", "D:/Bill.txt");
            Sleep(3000);
        } else if (choice == 2) {
            close = true;
            cout << "\tCounting Total Bill..." << endl;
            Sleep(2000);
        }
    }

    system("cls");
    cout << "\n\n\tTotal Bill ----------------- : " << count << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(4000);
}

int main() {
    Bill b;
    bool exit = false;
    while (!exit) {
        system("cls");
        int val;

        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t1. Add Item\n";
        cout << "\t2. Print Bill\n";
        cout << "\t3. Exit\n";
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            addItem(b);
        } else if (val == 2) {
            printBill();
        } else if (val == 3) {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(2000);
        }
    }
}
