#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

class shopping
{
private:
    char pcode[20];
    char price[20];
    char dis[20];
    char pname[20];

public:
    void menu();
    void administrator();
    void buyer();
    void pack(shopping p);
    void unpack();
    void search();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

shopping s[100], t;
char buffer[50], temp[50];
int i, count = 0;
fstream data;

void shopping ::menu()
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
        if (email == "swastik1710@gmail.com" && password == "swastik7777")
        {
            administrator();
        }
        else
        {
            cout << "\t\t\t Invalid Email or Password \n";
        }
        break;
    case 2:
        buyer();
    case 3:
        exit(0);
    default:
        cout << "Please select from the given options";
    }
    goto m;
}

void shopping::administrator()
{
m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator Menu";
    cout << "\n\t\t\t|_____1. Add the Product________|";
    cout << "\n\t\t\t|_____2. Edit the Product_______|";
    cout << "\n\t\t\t|_____3. Remove the Product_____|";
    cout << "\n\t\t\t|_____4. Back to Main Menu______|";
    cout << "\n\n\t Please enter your choice ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;
    case 2:
        edit();
        break;
    case 3:
        rem();
        break;
    case 4:
        menu();
        break;
    default:
        cout << "Please select from the given options";
    }
    goto m;
}

void shopping::buyer()
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

void shopping::pack(shopping p)
{
    fstream data;
    data.open("database.txt", ios::out | ios::app);
    strcpy(buffer, p.pcode);
    strcat(buffer, "|");
    strcat(buffer, p.pname);
    strcat(buffer, "|");
    strcat(buffer, p.price);
    strcat(buffer, "|");
    strcat(buffer, p.dis);
    strcat(buffer, "|");
    data << buffer << endl;
    data.close();
}

void shopping::unpack()
{
    fstream data;
    data.open("database.txt", ios::in);
    for (i = 0; i < count; i++)
    {
        data.getline(buffer, 100);
        sscanf(buffer, "%[^|]|%[^|]|%[^|]|%[^|]|", s[i].pcode, s[i].pname, s[i].price, s[i].dis);
    }
    data.close();
}

void shopping::search()
{

    cout << "\n\t\t\t Enter the Product Code ";
    cin >> temp;
    for (i = 0; i < count; i++)
    {
        if (!strcmp(s[i].pcode, temp))
        {
            cout << "Record found\n"
                 << s[i].pcode << "\t" << s[i].pname << "\t" << s[i].price << "\t" << s[i].dis << endl;
            break;
        }
    }
    if (i == count)
        cout << "Record not found";
}

void shopping::add()
{
m:
    fstream data;
    int c, token = 0;
    float p, d;
    string n;

    cout << "\n\n\t\t\t Add new Product";
    cout << "\n\t\t\t Enter the Product Code ";
    cin >> t.pcode;
    cout << "\n\t\t\t Enter the Product Name ";
    cin >> t.pname;
    cout << "\n\t\t\t Enter the Product Price ";
    cin >> t.price;
    cout << "\n\t\t\t Enter the Product Discount ";
    cin >> t.dis;
    pack(t);
    // data.open("database.txt", ios::app);
    // if (!data)
    // {
    //     data.open("database.txt", ios::app | ios::out);
    //     data << pcode << " " << pname << " " << price << " " << dis << "\n";
    //     data.close();
    // }
    // else
    // {
    //     data >> c >> n >> p >> d;
    //     while (!data.eof())
    //     {
    //         if (c == pcode)
    //         {
    //             token++;
    //         }
    //         data >> c >> n >> p >> d;
    //     }
    //     data.close();
    // }

    // if (token == 1)
    //     goto m;
    // else
    // {
    //     data.open("database.txt", ios::app | ios::out);
    //     data << pcode << " " << pname << " " << price << " " << dis << "\n";
    //     data.close();
    // }
    cout << "\n\t\t\t Product Added Successfully ";
}

void shopping::edit()
{
    fstream data, data1;
    int c, token = 0, pkey;
    float p, d;
    string n;

    cout << "\n\n\t\t\t Edit Product";
    // cout << "\n\t\t\t Enter the Product Code ";
    // cin >> pkey;
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\t\t\t File not found ";
    }
    else
    {
        data1.open("temp.txt", ios::app | ios::out);
        data >> c >> n >> p >> d;
        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "\n\t\t Product New Code :";
                cin >> c;
                cout << "\n\t\t\t Enter the Product Name ";
                cin >> n;
                cout << "\n\t\t\t Enter the Product Price ";
                cin >> p;
                cout << "\n\t\t\t Enter the Product Discount ";
                cin >> d;
                data1 << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\t\t Product Edited Successfully ";
                token++;
            }
            else
            {
                data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");
        if (token == 0)
        {
            cout << "\n\t\t Product Not Found ";
        }
    }
}

void shopping::rem()
{
    fstream data, data1;
    int token = 0, pkey;

    cout << "\n\n\t\t\t Remove Product";
    cout << "\n\t\t\t Enter the Product Code ";
    cin >> pkey;
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\t\t\t File not found ";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "\n\t\t Product Removed Successfully ";
                token++;
            }
            else
            {
                data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");
        if (token == 0)
        {
            cout << "\n\t\t Product Not Found ";
        }
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|-----------------------------------------------------|\n\n";
    cout << "ProNo\t\tName\t\tPrice";
    cout << "\n\n|-----------------------------------------------------|\n\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        cout << "\n"
             << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt()
{
m:
    fstream data;
    int arrc[100], arrq[100], c = 0;
    char choice;
    float amount = 0, dis = 0, total = 0;

    cout << "\n\n\t\t RECEIPT ";
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\t\t\t File not found ";
    }
    else
    {
        data.close();
        list();
        cout << "\n______________________________________\n";
        cout << "\n        Please place the order        \n";
        cout << "\n______________________________________\n";

        do
        {
            cout << "\n\t\t\t Enter the Product Code ";
            cin >> arrc[c];
            cout << "\n\t\t\t Enter the Quantity ";
            cin >> arrq[c];
            for (int i = 0; i < c; i++)
            {
                if (arrc[i] == arrc[c])
                {
                    cout << "\n\t\t\t Product Already Added ";
                    goto m;
                }
            }
            c++;
            cout << "\n\t\t\t Do you want to order more (y/n) ";
            cin >> choice;
        } while (choice == 'y');

        cout << "\n\n\t\t\t__________________RECEIPT____________________\n";
        cout << "\nProduct No\tProduct Name\tQuantity\tPrice\t\tAmount\t Amount with Discount\n";

        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;
            while (!data.eof())
            {
                if (arrc[i] == pcode)
                {
                    amount = price * arrq[i];
                    dis = amount - (amount * dis / 100);
                    total = total + dis;
                    cout << "\n"
                         << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << dis;
                }
                data >> pcode >> pname >> price >> dis;
            }
        }
        data.close();
    }
    cout << "\n\n____________________________________________________________________________________________";
    cout << "\n\n\t\t\t\t Total Amount : " << total << "\n";
}

int main()
{
    shopping s;
    s.menu();
}