/**
 Stephanie Honore`
 02/08/2016
 CPSC 5010 Lab 2
 */

//implementation file for the header file
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "CashRegistar.h"

using namespace std;

/**
 this function will read an integer value from the user
 */
int CashRegistar::readInteger(int minValue)
{
    //initialize values
    minValue = 0;
    int numValue = 0;
    bool value = false;
    bool value1 = false;
    
    do
    {
        cin >> numValue;
        //if the input value is an integer
        if (cin.good())
        {
            value = true;
            //if the input value is >= minValue then the condition is valid
            if(numValue >= minValue)
            {
                value1 = true;
            }
            else
            {
                //clear the input value
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                //prompt the user to enter another value
                cout << "Please enter a value >= 0. Try again: ";
            }
        }
        //if the input value is not an integer
        else
        {
            //clear the input value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            //prompt the user to enter another value.
            cout << "Please enter valid input. Try again: " << endl;
        }
    }
    while ((!value) || (!value1));
    
    return (numValue);
    
}
void CashRegistar::displayInvoice(int subTotal , int tax, int total)
{
    double x = (double)subTotal/100;
    double y = (double)tax/100;
    double z = (double)total/100;
    
    cout << "You Invoice Statement:" << endl;
    cout << '\n';
    cout << "Subtotal: $" <<fixed<<setprecision(2)<< x << endl;
    cout << "Tax: $" << y << endl;
    cout << "---------------------"<< endl;
    cout << "Total: $ " <<fixed<<setprecision(2)<< z << endl;
}
//This function gives the amount of coins to be distibuted based on the amount given.
void CashRegistar:: makeChangeInCoins(int coins[], int cents)
{
    static int remainChange = 0;
    
    if((cents%100) <= 1)
    {
        coins[4] = (cents%100);
    }
    else if(cents%100 <= 5)
    {
        coins[3] = (cents%100) / 5;
        remainChange = cents % 5;
        
        if(remainChange >= 1)
        {
            coins[4] = remainChange / 1;
        }
    }
    else if (cents%100 <= 10)
    {
        coins[2] = (cents%100) /10;
        remainChange = (cents%100) % 10;
        
        if(remainChange >= 5)
        {
            coins[3] = remainChange / 5;
            remainChange = remainChange % 5;
        }
        if(remainChange >= 1)
        {
            coins[4] = remainChange / 1;
        }
        
    }
    else if (cents%100 <= 25)
    {
        coins[1] = (cents%100) /25;
        remainChange = (cents%100) % 25;
        
        if(remainChange >= 10)
        {
            coins[2] = remainChange / 10;
            remainChange = remainChange % 10;
        }
        if(remainChange >= 5)
        {
            coins[3] = remainChange / 5;
            remainChange = remainChange % 5;
        }
        if(remainChange >= 1)
        {
            coins[4] = remainChange / 1;
        }
    }
    else if(cents <= 50)
    {
        coins[0] = (cents%100) /50;
        remainChange = cents%100 % 50;
        
        if(remainChange >= 25)
        {
            coins[1] = remainChange / 25;
            remainChange = remainChange % 25;
        }
        if(remainChange >= 10)
        {
            coins[2] = remainChange / 10;
            remainChange = remainChange % 10;
        }
        if(remainChange >= 5)
        {
            coins[3] = remainChange / 5;
            remainChange = remainChange % 5;
        }
        if(remainChange >= 1)
        {
            coins[4] = remainChange / 1;
        }
    }
    else if(cents%100 <= 100)
    {
        coins[0] = (cents%100) /50;
        remainChange = (cents%100) % 50;
        
        if(remainChange >= 25)
        {
            coins[1] = remainChange / 25;
            remainChange = remainChange % 25;
        }
        if(remainChange >= 10)
        {
            coins[2] = remainChange / 10;
            remainChange = remainChange % 10;
        }
        if(remainChange >= 5)
        {
            coins[3] = remainChange / 5;
            remainChange = remainChange % 5;
        }
        if(remainChange >= 1)
        {
            coins[4] = remainChange / 1;
        }
    }
}
void CashRegistar::makeChangeInBills(int bills[], int dollars)
{
    /**the input value for the change needed in dollars given is in cents
     so we have to divide by 100 to get the dollar value.
     */
    cout<<dollars<<endl;
    static int remainChange = 0;
    double change = (double)dollars/100;
    if(change <= 1)
    {
        //this amount of change to be given if we get a $1 bill
        bills[5] = change;
    }
    else if(change <= 5)
    {
        bills[4] = change/ 5;
        remainChange = (dollars/100) % 5;
        
        if(remainChange >= 1)
        {
            bills[5] = remainChange / 1;
        }
    }
    else if(change <= 10)
    {
        bills[3] = change / 10;
        remainChange = (dollars/100) % 10;
        
        if(remainChange >= 5)
        {
            bills[4] = remainChange / 5;
            remainChange = remainChange % 5;
        }
        if(remainChange >= 1)
        {
            bills[5] = remainChange / 1;
        }
        
    }
    else if(change <= 20)
    {
        bills[2] = change / 20;
        remainChange = (dollars/100) % 20;
        
        if(remainChange >= 10)
        {
            bills[3] = remainChange / 10;
            remainChange = remainChange % 10;
        }
        if(remainChange >= 5)
        {
            bills[4] = remainChange / 5;
            remainChange = remainChange % 5;
        }
        if(remainChange >= 1)
        {
            bills[5] = remainChange / 1;
        }
    }
    else if(change <= 50)
    {
        bills[1] = change / 50;
        remainChange = (dollars/100) % 50;
        
        if(remainChange % 20 >= 1)
        {
            bills[2] = remainChange / 20;
            remainChange = remainChange % 20;
        }
        if(remainChange >= 10)
        {
            bills[3] = remainChange / 10;
            remainChange = remainChange % 10;
        }
        if(remainChange >= 5)
        {
            bills[4] = remainChange / 5;
            remainChange = remainChange % 5;
        }
        if(remainChange >= 1)
        {
            bills[5] = remainChange / 1;
        }
        
    }
    else if(change <= 100)
    {
        bills[0] = change/ 100;
        remainChange = (dollars/100) % 100;
        
        if(remainChange >= 50)
        {
            bills[1] = remainChange / 50;
            remainChange = remainChange % 50;
        }
        if(remainChange >= 20)
        {
            bills[2] = remainChange / 20;
            remainChange = remainChange % 20;
        }
        if(remainChange >= 10)
        {
            bills[3] = remainChange / 10;
            remainChange = remainChange % 10;
        }
        if(remainChange >= 5)
        {
            bills[4] = remainChange / 5;
            remainChange = remainChange % 5;
        }
        if(remainChange >= 1)
        {
            bills[5] = remainChange / 1;
        }
    }
    
}
void CashRegistar::displayChangeInBills(int bills[])
{
    int length = 6;
    
    for(int i = 0; i < length; i++)
    {
        if(bills[i] > 0)
        {
            if(i == 0)
            {
                cout<<bills[0]<< " $100 bills(s)"<< endl;
            }
            if(i == 1)
            {
                cout<<bills[1]<<" $50 bills(s)"<<endl;
            }
            if(i == 2)
            {
                cout<<bills[2]<<" $20 bills(s)"<<endl;
            }
            if(i == 3)
            {
                cout<<bills[3]<<" $10 bills(s)"<<endl;
            }
            if(i == 4)
            {
                cout<<bills[4]<<" $5 bills(s)"<<endl;
            }
            if(i == 5)
            {
                cout<<bills[5]<<" $1 bills(s)"<<endl;
            }
        }
    }
}
void CashRegistar::displayChangeInCoins(int coins[])
{
    int length = 5;
    for(int i = 0; i < length; i++)
    {
        if(coins[i] > 0)
        {
            if(i == 0)
            {
                cout<<coins[0]<< " Half Dollar coin(s)"<< endl;
            }
            if(i == 1)
            {
                cout<<coins[1]<<" Quarter coin(s)"<<endl;
            }
            if(i == 2)
            {
                cout<<coins[2]<<" Dime coin(s)"<<endl;
            }
            if(i == 3)
            {
                cout<<coins[3]<<" Nickle coin(s)"<<endl;
            }
            if(i == 4)
            {
                cout<<coins[4]<<" Penny coin(s)"<<endl;
            }
        }
    }
    
    
}



