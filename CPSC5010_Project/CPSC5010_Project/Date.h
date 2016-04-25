//
//  Date.h
//  CPSC5010_Project
//
//  Created by Stephanie Honore on 4/18/16.
//  Copyright © 2016 Stephanie Honore. All rights reserved.
//

#ifndef Date_h
#define Date_h
#include <ctime>
#include <fstream>

using namespace std;

class Date
{
public:
    //constructor
    Date();
    //displays the current time
    void GetDate();
    //Sets the Date
    void SetDate();
    //sets the expiration date of a Credit Card. (MM/YY)
    void ExpirDate();
    //increments the date by a given input
    void incrementDate();
    // prints date to output file
    void OutputDate(ofstream & out);
    
    time_t currentDate;
    struct tm * localDate;
private:
    int year;
    int month;
    int day;
};

#endif /* Date_h */
