#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

class shopping
{
public:
    char pcode[20];
    char price[20];
    char dis[20];
    char pname[20];
} s[100], t;
char buffer[50], temp[50];
int i, count = 0, key;
fstream fp1, fp2;

void administrator();
void buyer();
void write();
void pack();
void unpack();



void init()
{
    fp1.open("database.txt", ios::app | ios::out);
    for (i = 0; i < 20; i++)
    {

        fp1 << "xx"
            << "|";
        fp1 << "xx"
            << "|";
        fp1 << "xx"
            << "|";
        fp1 << "xx"
            << "|";
        for (int j = 0; j < 35; j++)
            fp1 << "*";
        fp1 << endl;
    }
}

void menu()
{
m:
    int choice;
    string email, password;
    cout << "\n\t\t\t\t____________________________________";
    cout << "\n\t\t\t\t                                    ";
    cout << "\n\t\t\t\t        SuperMarket Main Menu       ";
    cout << "\n\t\t\t\t                                    ";
    cout << "\n\t\t\t\t____________________________________";
    cout << "\n\t\t\t\t                                    ";
    cout << "\n\t\t\t\t\t|  1. Administrator  |";
    cout << "\n\t\t\t\t\t|                    |";
    cout << "\n\t\t\t\t\t|  2. Buyer          |";
    cout << "\n\t\t\t\t\t|                    |";
    cout << "\n\t\t\t\t\t|  3. Exit           |";
    cout << "\n\t\t\t\t\t|                    |";
    cout << "\n\t\t\t\t Please select:";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\t\t\t Please Login \n";
        cout << "\t\t\t Enter Email  \n";
        cin >> email;
        cout << "\t\t\t Enter Password \n";
        cin >> password;
        if (email == "swastik1710@gmail.com" && password == "1009")
        {
            administrator();
        }
        else
        {
            cout << "\t\t\t Invalid Email or Password \n";
        }
        break;
    /*case 2:
        buyer();*/
    case 3:
        exit(0);
    default:
        cout << "Please select from the given options";
    }
    goto m;
}

void administrator()
{
m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator Menu";
    cout << "\n\t\t\t|_____1. Add Product________|";
    cout << "\n\t\t\t|_____2. Search Product_____|";
    cout << "\n\t\t\t|_____3. Edit Product_______|";
    cout << "\n\t\t\t|_____4. Remove Product_____|";
    cout << "\n\t\t\t|_____5. Back to Main Menu_______|";
    cout << "\n\n\t Please enter your choice ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        unpack();
        write();
        break;
    /*case 2:
        search();
    case 3:
        search();
        modify();
        break;
    case 4:
        search();
        delet();
        break;
    case 5:
        menu();
        break;*/
    default:
        cout << "Please select from the given options";
    }
    goto m;
}

/*void buyer()
{
    m:
    int choice;
    cout << "\n\t\t\t\t\t Menu";
    cout << "\n\t\t\t|____________________________________|";
    cout << "\n\t\t\t|_________1. Buy the Product_________|";
    cout << "\n\t\t\t|_________2. Back to Main Menu_______|";
    cout << "\n\n\t Please enter your choice ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        receipt();
        break;
    case 2:
        menu();
    default:
        cout << "Please select from the given options";
    }
    goto m;
}
*/
void pack(shopping p)
{

    fp1.open("database.txt", ios::out | ios::app);
    strcpy(buffer, p.pcode);
    strcat(buffer, "|");
    strcat(buffer, p.pname);
    strcat(buffer, "|");
    strcat(buffer, p.price);
    strcat(buffer, "|");
    strcat(buffer, p.dis);
    strcat(buffer, "|");
    int x = strlen(buffer);
    for (int j = 0; j < 47 - x; j++)
        strcat(buffer, "*");

    fp1 << buffer << endl;
    fp1.close();
}

void unpack()
{
    fp1.open("database.txt", ios::in);
    for (i = 0; i < 20; i++)
    {
        fp1.getline(buffer, 100);
        sscanf(buffer, "%[^|]|%[^|]|%[^|]|%[^|]|", s[i].pcode, s[i].pname, s[i].price, s[i].dis);

       
    }
    fp1.close();
}

void write()
{
    char tempcode[20];

    cout << "\n\n\t\t\t Add new Product";
    cout << "\n\t\t\t Enter the Product Code ";
    cin >> tempcode;
    int code = atoi(tempcode);
    key = code % 20;
    cout << s[key].pcode;
    /*while(s[key].pcode!="")
        key++;*/
    strcpy(s[key].pcode, tempcode);
    cout << "\n\t\t\t Enter the Product Name ";
    cin >> s[key].pname;
    cout << "\n\t\t\t Enter the Product Price ";
    cin >> s[key].price;
    cout << "\n\t\t\t Enter the Product Discount ";
    cin >> s[key].dis;
    fp1.close();
    remove("database.txt");
    fp1.open("database.txt", ios::out);
    fp1.close();
    for (int j = 0; j < 20; j++)
        pack(s[j]);
}

int main()
{
    init();
    menu();
    return 0;
}