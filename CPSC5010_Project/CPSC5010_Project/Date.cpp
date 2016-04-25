//
//  Date.cpp
//  CPSC5010_Project
//
//  Created by Stephanie Honore on 4/18/16.
//  Copyright © 2016 Stephanie Honore. All rights reserved.
//  This is a Date Class
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Date.h"
#include <ctime>

using namespace std;


//constructor
Date::Date()
{
    time_t currentDate;
    struct tm * localDate;
    //get the current time
    time(&currentDate);
    localDate = localtime(&currentDate);
    //convert the current time to the local time
    month = localDate->tm_mon+1;
    day = localDate->tm_mday;
    year = localDate->tm_year+1900;
}
void Date::ExpirDate()
{
    bool flag = false;
    int expriationDate;
    cin >> expriationDate;
    if(cin.good())
    {
        flag = true;
    }
    else
    {
        //clear the input value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //prompt the user to enter another value.
        cout << "Please enter valid input. Try again: " << endl;
    }
    while(flag)
    {
        
    }
}
//sets a new date
void Date::SetDate()
{
    cout<<"Set Month: "<<endl;
    bool flag = false;
    int response;
    cin >> response;
    if(cin.good())
    {
        flag = true;
    }
    else
    {
        //clear the input value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //prompt the user to enter another value.
        cout << "Please enter valid input. Try again: " << endl;

    }
    while(flag)
    {
        //if the month is not between Jan and Dec
        if(response < 1 || response > 12)
        {
            //clear the input value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            //prompt the user to enter another value.
            cout << "Please enter valid input. Try again: " << endl;

        }
        month = response;
        //clear the input value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Please Set the Day"<<endl;
        cin >> response;
        //if the month is April, May, Sept, or November
        if(month == 4 || month == 6 || month == 9 || month == 11)
        {
            //and the number of days in the month are less than 30
            if(response > 30)
            {
                //clear the input value
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                //prompt the user to enter another value.
                cout << "Please enter valid input. Try again: " << endl;

            }
        }
        //if the month is Feb, use the leap year rules
        if(month == 2)
        {
            //if it is a leap year
            if((year%4==0)^(year%100==0)^(year%400==0))
            {
                if(response > 29)
                {
                    //clear the input value
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    //prompt the user to enter another value.
                    cout << "Please enter valid input. Try again: " << endl;
                }
            }
            else
            {
                if(response > 28)
                {
                    //clear the input value
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    //prompt the user to enter another value.
                    cout << "Please enter valid input. Try again: " << endl;

                }
        }
            day = response;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Please Enter the Year"<<endl;
            cin >> response;
            response = year;
    }
}
}
//returns the current date
void Date::GetDate()
{
    //prints out the current date
    cout << "Current Date: "<<month<<"/"<<day<<"/"<<year<<endl;
}
void Date::OutputDate(ofstream & out)
{
    //prints out the current date to output file
    out << "Current Date: "<<month<<"/"<<day<<"/"<<year<<endl;
}
