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
} s[100],bill[100], t;
char buffer[50], temp[50];
int i, count = 0, key,c;
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
        if (email == "a" && password == "a")
        {
            administrator();
        }
        else
        {
            cout << "\t\t\t Invalid Email or Password \n";
        }
        break;
    case 2:
        buy();
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
    cout << "\n\t\t\t|_____3. Edit Product Details_______|";
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
        cout << "Please select from the given options";
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
    fp1.open("database.txt",ios::in);
    fp1.seekg(k*49,ios::beg);
    fp1.getline(buffer,100);
    sscanf(buffer, "%[^|]|%[^|]|%[^|]|%[^|]|", t.pcode, t.pname, t.price, t.dis);
    c++;
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
    while(strcmp(s[key].pcode,"xx"))
    {
        key++;
        jump[key]++;
    }
    
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

void search()
{
    c = 0;
    char tempcode[20];
    cout << "\nEnter the Product Code to search for : ";
    cin >> tempcode;
    int code = atoi(tempcode);
    key = code % 20;
    unpackOneRecord(key+jump[key]);
        
    if(strcmp(t.pcode,tempcode)==0)
    {
            cout << "Item found!\n\n";
            cout << "Product Code : " << t.pcode << endl;
            cout << "Prduct Name : " << t.pname << endl;
            cout << "Prduct Price : " << t.price << endl;
            cout << "Discount on the Product : " << t.dis << endl;
            
            return;
    }
    cout << "Item not found\n";
}

void modify()
{
    int tempKey;
    
    char tempcode[20];
    cout << "\n\n\t\t\t Modify Product Details";
    cout << "\n\t\t\t Enter the Product Code ";
    cin >> tempcode;
    int code = atoi(tempcode);
    key = code % 20;
    if(strcmp(s[key+jump[key]].pcode,tempcode)!=0)
    {
        cout << "\nItem not found\n";
        return;
    }
    cout << "Enter the Modified Product details";
    cout << "\n Enter the Product Name ";
    cin >> s[key+jump[key]].pname;
    cout << "\n Enter the Product Price ";
    cin >> s[key+jump[key]].price;
    cout << "\n Enter the Product Discount ";
    cin >> s[key+jump[key]].dis;
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
    cout << "\n\n\t\t\t Delete Product";
    cout << "\n\t\t\t Enter the Product Code ";
    cin >> tempcode;
    int code = atoi(tempcode);
    key = code % 20;
    if(strcmp(s[key+jump[key]].pcode,tempcode)!=0)
    {
        cout << "\nItem not found\n";
        return;
    }
    cout << "Item found!\n\n";
    cout << "Product Code : " << s[key + jump[key]].pcode << endl;
    cout << "Prduct Name : " << s[key + jump[key]].pname << endl;
    cout << "Prduct Price : " << s[key + jump[key]].price << endl;
    cout << "Discount on the Product : " << s[key + jump[key]].dis << endl;

    strcpy(s[key + jump[key]].pcode, "xx");
    strcpy(s[key + jump[key]].pname, "xx");
    strcpy(s[key + jump[key]].price, "xx");
    strcpy(s[key + jump[key]].dis, "xx");
    cout << "ITEM DELETED!";
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
    cout << "\n\t\t\t\t\t Menu";
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
        break;
    default:
        cout << "Please select from the given options";
    }
    goto m;
}


void receipt()
{
    char tempcode[20];
    int quantity[20];
    int totalProd = 0;
    float amount, totalAmount,discount;
    char ch;
    
   
        fp1.close();
        cout << "\n______________________________________\n";
        cout << "\n        Please place the order        \n";
        cout << "\n______________________________________\n";

        do
        {
            cout << "\nEnter the Product Code : ";
            cin >> tempcode;
            int code = atoi(tempcode);
            key = code % 20;
            unpackOneRecord(key+jump[key]);

            if(strcmp(t.pcode,tempcode)!=0)
            {
                cout << "\nItem not found\n";
                
            }

            else
            {
                strcpy(bill[totalProd].pcode, t.pcode);
                strcpy(bill[totalProd].pname, t.pname);
                strcpy(bill[totalProd].price, t.price);
                strcpy(bill[totalProd].dis, t.dis);
                
                cout << "\n\t\t\t Enter the Quantity ";
                cin >> quantity[totalProd];

                totalProd++;
            }

            cout << "\n\t\t\t Do you want to order more (y/n) ";
            cin >> ch;
        } while (ch == 'y');

        cout << "\n\n\t\t\t__________________RECEIPT____________________\n";
        cout << "\nProductNo\tProductName\tQuantity\tPrice\tAmount\t Amount after Discount\n";

        for (int i = 0; i < totalProd; i++)
        {
            amount = atoi(bill[i].price) * quantity[i];
            discount = (atoi(bill[i].dis) * amount) / 100.0;

            totalAmount = amount - discount ;
            cout << bill[i].dis << "\n";
            cout << bill[i].pcode << "\t" << bill[i].pname << "\t" << quantity[i] << "\t" << bill[i].price << "\t" << amount << "\t" << totalAmount << "\n";
        }
    
}      
            
        
int main()
{
    //init();
    for (int i = 0; i < 20;i++)
        jump[i] = 0;
    menu();
    return 0;
}