
//
//  Stephanie Honore
//  CPSC 5010 Lab 2
//  02/08/2016

#ifndef CashRegistar_h
#define CashRegistar_h

class CashRegistar
{
public:
    int readInteger(int minValue);
    void displayInvoice(int subTotal , int tax, int total);
    void makeChangeInCoins(int coins[], int cents);
    void makeChangeInBills(int bills[], int dollars);
    void displayChangeInBills(int bills[]);
    void displayChangeInCoins(int coins[]);
        
private:
    int minValue;
};
#endif /* CashRegistar_h */