
#include <iostream>
#include <limits>
using namespace std;

class CItem
{
public:
    string Name;
    int Price;
};

CItem NOTHING = { "NOTHING", -1 };

class CPlayer
{
public:
    void PrintInv()
    {
        if(ItemCount)
        {
            cout << "-----Inventory-----" << endl;
            for(int i = 0; i < ItemCount; ++i)
            {
                cout << Inventory[i].Name << endl;
            }
            cout << "---End Inventory---";
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
            cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        }
        else cout << "You have nothing" << endl;
    }
    void Pay(int amount)
    {
        Gold -= amount;
    }
    void AddInv(CItem item)
    {
        Inventory[ItemCount] = item;
        Inventory[ItemCount].Price = (int) Inventory[ItemCount].Price / 2;
        ++ItemCount;
    }
    void DropInv(int item)
    {
        do
        {
            Inventory[item] = Inventory[item + 1];
            ++item;
        } while(item < 8);
        Inventory[8] = NOTHING;
        --ItemCount;
    }
    int Gold;
    int ItemCount;
    CItem Inventory[9];
};

class CShop
{
public:
    bool MainMenu(CPlayer& customer)
    {
        cout << "Welcome." << endl
             << "We deal in weapons and armor" << endl
             << "What dost thou want to do?" << endl
             << "1) Buy" << endl
             << "2) Sell" << endl
             << "i) Inventory" << endl
             << "q) Quit" << endl
             << "> ";
        char c;
        cin >> c;
        switch((int) c)
        {
        case '1':
            while(BuyMenu(customer));
            break;
        case '2':
            while(SellMenu(customer));
            break;
        case 'i':
            customer.PrintInv();
            return true;
            break;
        default:
            return false;
            break;
        }
        return true;
    }
    bool BuyMenu(CPlayer &customer)
    {
        cout << "What dost thou wish to buy?" << endl
             << "$" << customer.Gold << endl;
        for(int i = 0; i < ItemCount; ++i)
        {
            cout << i << ") $" << Inventory[i].Price
                 << "\t\t\t" << Inventory[i].Name << endl;
        }
        cout << "i) Inventory" << endl
             << "q) Quit" << endl
             << "> ";
        char c;
        cin >> c;
        if('0' <= c && c <= '0' + ItemCount)
        {
            int i = c - '0';
            cout << "The " << Inventory[i].Name << "?" << endl
                 << "Is that okay (y/n)?" << endl
                 << "> ";
            char d;
            cin >> d;
            if(d == 'y' || d == 'Y')
            {
                if(customer.Gold > Inventory[i].Price)
                {
                    if(customer.ItemCount < 9)
                    {
                        customer.Pay(Inventory[i].Price);
                        customer.AddInv(Inventory[i]);
                        cout << "You bought the "
                             << Inventory[i].Name << "!" << endl;
                    }
                    else cout << "You cannot hold anymore." << endl;
                }
                else cout << "Sorry, Thous hast not enough money." << endl;
            }
        }
        else if(c == 'i') customer.PrintInv();
        else return false;
        cout << "Dost though want anything else (y/n)?" << endl
             << "> ";
        cin >> c;
        if(c == 'y' || c == 'Y') return true;
        return false;
    }
    bool SellMenu(CPlayer &customer)
    {
        if(customer.ItemCount)
        {
            cout << "What art thou selling?" << endl
                 << "$" << customer.Gold << endl;
            for(int i = 0; i < customer.ItemCount; ++i)
            {
                cout << i << ") $" << customer.Inventory[i].Price
                     << "\t\t\t" << customer.Inventory[i].Name << endl;
            }
            cout << "q) Quit" << endl
                 << "> ";
            char c;
            cin >> c;
            if('0' <= c && c <= '0' + customer.ItemCount)
            {
                int i = c - '0';
                cout << "The " << customer.Inventory[i].Name << "?" << endl
                     << "Is that okay (y/n)?" << endl
                     << "> ";
                char d;
                cin >> d;
                if(d == 'y' || d == 'Y')
                {
                    string tempName = customer.Inventory[i].Name;
                    customer.Pay(-customer.Inventory[i].Price);
                    customer.DropInv(i);
                    cout << "You sold the " << tempName << "!" << endl;
                }
            }
            cout << "Dost thou have anything more to sell (y/n)?" << endl
                 << "> ";
            cin >> c;
            if(c == 'y' || c == 'Y') return true;
            return false;
        }
        else cout << "You have nothing." << endl;
        return false;
    }
    int ItemCount;
    CItem Inventory[6];
};

int main()
{
    CPlayer myPlayer = { 120, 0, { } };
    CShop myShop = {
        6,
        { {"Bamboo Pole", 10},
          {"Club", 60},
          {"Copper Sword", 180},
          {"Clothes", 20},
          {"Leather Clothes", 70},
          {"Small Shield", 90} }
    };

    while(myShop.MainMenu(myPlayer));
}
