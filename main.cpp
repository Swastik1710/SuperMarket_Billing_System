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
} s[100], bill[100], t;
char buffer[50], temp[50];
int i, count = 0, key, c;
fstream fp1, fp2;
int jump[20];

void administrator();
void write();
void pack();
void unpack();
void search();
void modify();
void remove();
void receipt();
void buy();

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
    fp1.close();
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
    cout << "\n";
    cout << "\n\t\t\t\tPlease select: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\t\t\t\tPlease Login \n";
        cout << "\t\t\t\tEnter Email: ";
        cin >> email;
        cout << "\t\t\t\tEnter Password: ";
        cin >> password;
        if (email == "a" && password == "a")
        {
            administrator();
        }
        else
        {
            cout << "\t\t\t\tInvalid Email or Password \n";
        }
        break;
    case 2:
        buy();
    case 3:
        cout << "\n\t\t\t\tHave a nice day!!!";
        exit(0);
    default:
        cout << "\t\t\t\tPlease select from the given options";
    }
    goto m;
}

void administrator()
{
m:
    int choice;
    cout << "\n\t\t\t\t____________________________________";
    cout << "\n\t\t\t\t                                    ";
    cout << "\n\t\t\t\t         Administrator Menu         ";
    cout << "\n\t\t\t\t                                    ";
    cout << "\n\t\t\t\t____________________________________";
    cout << "\n\t\t\t\t                                    ";
    cout << "\n\t\t\t\t    |  1. Add Product           |";
    cout << "\n\t\t\t\t    |  2. Search Product        |";
    cout << "\n\t\t\t\t    |  3. Edit Product Details  |";
    cout << "\n\t\t\t\t    |  4. Remove Product        |";
    cout << "\n\t\t\t\t    |  5. Back to Main Menu     |";
    cout << "\n\n\t\t\t\tPlease enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        unpack();
        write();
        break;
    case 2:
        search();
        break;
    case 3:
        unpack();
        modify();
        break;
    case 4:
        unpack();
        remove();
        break;
    case 5:
        menu();
        break;
    default:
        cout << "\t\t\t\tPlease select from the given options";
    }
    goto m;
}

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

void unpackOneRecord(int k)
{
    fp1.open("database.txt", ios::in);
    fp1.seekg(k * 49, ios::beg);
    fp1.getline(buffer, 100);
    sscanf(buffer, "%[^|]|%[^|]|%[^|]|%[^|]|", t.pcode, t.pname, t.price, t.dis);
    c++;
    fp1.close();
}

void write()
{
    char tempcode[20];
    cout << "\n\n\t\t\t\tAdd new Product";
    cout << "\n\n\t\t\t\tEnter the Product Code: ";
    cin >> tempcode;
    int code = atoi(tempcode);
    key = code % 20;
    while (strcmp(s[key].pcode, "xx"))
    {
        key++;
        jump[key]++;
    }

    strcpy(s[key].pcode, tempcode);
    cout << "\n\t\t\t\tEnter the Product Name: ";
    cin >> s[key].pname;
    cout << "\n\t\t\t\tEnter the Product Price: ";
    cin >> s[key].price;
    cout << "\n\t\t\t\tEnter the Product Discount: ";
    cin >> s[key].dis;
    fp1.close();
    remove("database.txt");
    fp1.open("database.txt", ios::out);
    fp1.close();
    for (int j = 0; j < 20; j++)
        pack(s[j]);
}

void search()
{
    c = 0;
    char tempcode[20];
    cout << "\n\t\t\t\tEnter the Product Code to search for: ";
    cin >> tempcode;
    int code = atoi(tempcode);
    key = code % 20;
    unpackOneRecord(key + jump[key]);

    if (strcmp(t.pcode, tempcode) == 0)
    {
        cout << "\n\t\t\t\tItem found!";
        cout << "\n\n\t\t\t\tProduct Code : " << t.pcode;
        cout << "\n\t\t\t\tPrduct Name : " << t.pname;
        cout << "\n\t\t\t\tPrduct Price : " << t.price;
        cout << "\n\t\t\t\tDiscount on the Product : " << t.dis;

        return;
    }
    cout << "\n\t\t\t\tItem not found\n";
}

void modify()
{
    int tempKey;

    char tempcode[20];
    cout << "\n\n\t\t\t\tModify Product Details";
    cout << "\n\t\t\t\tEnter the Product Code ";
    cin >> tempcode;
    int code = atoi(tempcode);
    key = code % 20;
    if (strcmp(s[key + jump[key]].pcode, tempcode) != 0)
    {
        cout << "\n\t\t\t\tItem not found\n";
        return;
    }
    cout << "\n\t\t\t\tEnter the Modified Product details";
    cout << "\n\t\t\t\tEnter the Product Name ";
    cin >> s[key + jump[key]].pname;
    cout << "\n\t\t\t\tEnter the Product Price ";
    cin >> s[key + jump[key]].price;
    cout << "\n\t\t\t\tEnter the Product Discount ";
    cin >> s[key + jump[key]].dis;
    fp1.close();
    remove("database.txt");
    fp1.open("database.txt", ios::out);
    fp1.close();
    for (int j = 0; j < 20; j++)
        pack(s[j]);
}

void remove()
{
    int tempKey;
    char tempcode[20];
    cout << "\n\n\t\t\t\tDelete Product";
    cout << "\n\t\t\t\tEnter the Product Code ";
    cin >> tempcode;
    int code = atoi(tempcode);
    key = code % 20;
    if (strcmp(s[key + jump[key]].pcode, tempcode) != 0)
    {
        cout << "\n\t\t\t\tItem not found\n";
        return;
    }
    cout << "\n\t\t\t\tItem found!";
    cout << "\n\n\t\t\t\tProduct Code : " << s[key + jump[key]].pcode;
    cout << "\n\t\t\t\tPrduct Name : " << s[key + jump[key]].pname;
    cout << "\n\t\t\t\tPrduct Price : " << s[key + jump[key]].price;
    cout << "\n\t\t\t\tDiscount on the Product : " << s[key + jump[key]].dis;

    strcpy(s[key + jump[key]].pcode, "xx");
    strcpy(s[key + jump[key]].pname, "xx");
    strcpy(s[key + jump[key]].price, "xx");
    strcpy(s[key + jump[key]].dis, "xx");
    cout << "\n\n\t\t\t\tITEM DELETED!";
    fp1.close();
    remove("database.txt");
    fp1.open("database.txt", ios::out);
    fp1.close();
    for (int j = 0; j < 20; j++)
        pack(s[j]);
}

void buy()
{
m:
    int choice;
    cout << "\n\t\t\t\t_____________________________";
    cout << "\n\t\t\t\t                             ";
    cout << "\n\t\t\t\t            Menu             ";
    cout << "\n\t\t\t\t                             ";
    cout << "\n\t\t\t\t_____________________________";
    cout << "\n\t\t\t\t                             ";
    cout << "\n\t\t\t\t  | 1. Buy the Product    |  ";
    cout << "\n\t\t\t\t  | 2. Back to Main Menu  |  ";
    cout << "\n\n\t\t\t\tPlease enter your choice ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;
    case 2:
        menu();
        break;
    default:
        cout << "\t\t\t\tPlease select from the given options";
    }
    goto m;
}

void receipt()
{
    char tempcode[20];
    int quantity[20];
    int totalProd = 0;
    float amount, totalAmount, discount;
    char ch;
    fp1.close();
    cout << "\n\t\t\t\t________________________________";
    cout << "\n\t\t\t\t                                ";
    cout << "\n\t\t\t\t     Please place the order     ";
    cout << "\n\t\t\t\t                                ";
    cout << "\n\t\t\t\t________________________________";
    cout << "\n\t\t\t\t                                ";
    do
    {
        cout << "\n\t\t\t\tEnter the Product Code : ";
        cin >> tempcode;
        int code = atoi(tempcode);
        key = code % 20;
        unpackOneRecord(key + jump[key]);

        if (strcmp(t.pcode, tempcode) != 0)
        {
            cout << "\n\t\t\t\tItem not found\n";
        }

        else
        {
            strcpy(bill[totalProd].pcode, t.pcode);
            strcpy(bill[totalProd].pname, t.pname);
            strcpy(bill[totalProd].price, t.price);
            strcpy(bill[totalProd].dis, t.dis);

            cout << "\n\t\t\t\tEnter the Quantity ";
            cin >> quantity[totalProd];

            totalProd++;
        }

        cout << "\n\t\t\t\tDo you want to order more (y/n) ";
        cin >> ch;
    } while (ch == 'y');

    cout << "\n\n\t\t\t____________________RECEIPT____________________\n";
    cout << "\n\tProductNo\tProductName\tQuantity\tPrice\tAmount\tAmount after Discount\n";

    for (int i = 0; i < totalProd; i++)
    {
        amount = atoi(bill[i].price) * quantity[i];
        discount = (atoi(bill[i].dis) * amount) / 100.0;

        totalAmount = amount - discount;
        cout << "\t" << bill[i].pcode << "\t\t" << bill[i].pname << "\t\t" << quantity[i] << "\t\t" << bill[i].price << "\t" << amount << "\t\t" << totalAmount << "\n";
    }
}

int main()
{
    // init();
    for (int i = 0; i < 20; i++)
        jump[i] = 0;
    menu();
    return 0;
}