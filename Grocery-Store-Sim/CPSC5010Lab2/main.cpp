/**
Created by Stephanie Honore on 2/8/16
CPSC 5010 Lab 2
*/

#include <iostream>
#include<string>
#include <sstream>
#include <iomanip>
#include "CashRegistar.h"

using namespace std;

int main()
{
    //local variables
    int cost = 0; //keeps track of the cost in coins
    int totalCost = 0; //total cost of # of coins * number of items purchsed
    int numOfItems = 0; //the number of items purchased
    int subTotal = 0; //total before tax
    const int TAX_RATE_PERCENT = 9;
    static int bills[6]; //array of dollars bill denominations
    static int coins[5]; //array of coin denominations
    int amountGiven = 0; //the total amount of money given in cents
    int change; //the amount of change due.
    int minCentsExpected = 0;
    
    //create a new CashRegistar object
    CashRegistar registar;
    
    cout << "Welcome to WholeFoods!" << endl;
    cout <<"How many Locally grown, Organic, Non-GMO, Dairy-Free Cakes would you like to buy? ";
    //the number of items must at least be 0.
    numOfItems = registar.readInteger(0);
    
    cout << "How much does each Cake cost? " << endl;
    cout << "Dollars: ";
    //keep track of the total in cents; the min value must be 0.
    cost += (registar.readInteger(0) * 100);
    cout << "Cents: ";
    cost += registar.readInteger(0);
    subTotal = cost * numOfItems;
    totalCost = (subTotal + (TAX_RATE_PERCENT));
    cout << '\n';
    registar.displayInvoice(subTotal, TAX_RATE_PERCENT, totalCost);
    cout << '\n';
    
    cout << "How much money are you going to give me for this invoice?" << endl;
    cout << "Dollars: ";
    //keepting track of the dollars given in cents
    amountGiven = ((registar.readInteger(totalCost/100))*100);
    minCentsExpected = totalCost - amountGiven;
    cout << "Cents: ";
    amountGiven += registar.readInteger(minCentsExpected);
    change = amountGiven - totalCost;
    registar.makeChangeInBills(bills, change);
    registar.makeChangeInCoins(coins, change);
    cout << '\n';

    cout<< "Your change is: $ "<<fixed<<setprecision(2)<<((double)change/100)<< endl;
    cout<<'\n'; 
    registar.displayChangeInBills(bills);
    registar.displayChangeInCoins(coins);
    
    return 0;
}
