//
//  Catalog.cpp
//  CPSC5010_Project
//
//  Created by Stephanie Honore on 4/7/16.
//  Copyright © 2016 Stephanie Honore. All rights reserved.
//

#include <stdio.h>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "Catalog.h"
#include "Date.h"
#include <string.h>

using namespace std;

//create an empty catalog of an array of Book objects.
Catalog::Catalog()
{
   }
//copy constructor. Create a new instance of a Catalog with another Catalog as the Parameter
Catalog::Catalog(const Catalog& otherCatalog)
{

}
//destructor
Catalog::~Catalog()
{
    
}
//get the length of the catalog
int Catalog::Length(ifstream & file)
{
    for(int i = 0; !file.eof(); i++)
    {
        ProcessFile(file);
        sizeOfCatalog = i;
    }
    return sizeOfCatalog+1;
}
//a function for reading user input
string Catalog::readInput()
{
    //initialize values
    string input;
    bool value = false;
    do
    {
        getline(cin, input);
        //if the input value is an integer
        if (cin.good())
        {
            value = true;
           
        }
        //if the input value is not of the correct type
        else
        {
            //clear the input value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            //prompt the user to enter another value.
            cout << "Please enter valid input. Try again: " << endl;
        }
    }
    while (!value);
    return input;
}
void Catalog::SetTitle()
{
    cout << "Enter the the title of the book: ";
    string input;
    getline(cin, input);
    nb[sizeOfCatalog].title = input;
    cout << '\n';
   
}
string Catalog::GetTitle()
{
    return nb[sizeOfCatalog].title;
}
void Catalog::AddAuthor()
{
        cout << "Enter the the name of the author(Last Name, First Name): ";
        nb[sizeOfCatalog].lastName = readInput();
        cout << '\n';
}
string Catalog::GetAuthor()
{
    return nb[sizeOfCatalog].lastName;
}
void Catalog::setGenre()
{
    //ask the user which genre of book to know which catalog to add to.
    cout << "What Genre is Your Book? "<<endl;
    cout << "Options: Fiction(F), NonFiction(N), Fantasy(X), How-To(H) or Romance(R)"<< endl;
    nb[sizeOfCatalog].genre = readInput();
    cout << '\n';
}
string Catalog::getGenre()
{
    return nb[sizeOfCatalog].genre;
}
void Catalog::SetISBN()
{
    cout << "Enter the the 13 digit ISBN of the book(Press 'Q' to Cancel): ";
    string input = readInput();
    if(input.length() == 13)
    {
        nb[sizeOfCatalog].ISBN = input;
        cout << '\n';
    }
    else
    {
        cout << "Error. The ISBN is supposed to be 13 digits. Please try again"<<endl;
    }
}
string Catalog::GetISBN()
{
    return nb[sizeOfCatalog].ISBN;
}
void Catalog::SetPublisher()
{
    cout << "Enter the book's publisher(Press 'Q' to Cancel): ";
    nb[sizeOfCatalog].publisher = readInput();
    cout << '\n';
}
string Catalog::GetPublisher()
{
    return nb[sizeOfCatalog].publisher;
}
void Catalog::SetPrice()
{
    cout << "Enter the the price of the book(Press 'Q' to Cancel): $";
    double value;
    cin >> fixed >> showpoint >> setprecision(2) >>  value;
    nb[sizeOfCatalog].price = value;
    cout << '\n';
}
double Catalog::GetPrice()
{
    return nb[sizeOfCatalog].price;
}
void Catalog::SetStock()
{
    cout << "Enter the number of this book you have in stock(Press 'Q' to Cancel): ";
    int value1;
    cin >> value1;
    nb[sizeOfCatalog].numInStock = value1;
    cout << '\n';
}
int Catalog::GetStock()
{
    return nb[sizeOfCatalog].numInStock;
}
void Catalog::SetYear()
{
    cout << "Enter the year the book was published:"; 
    nb[sizeOfCatalog].year = readInput();
    cout << '\n';
}
string Catalog::GetYear()
{
    return nb[sizeOfCatalog].year;
}
//add a new instance of a Book
void Catalog::Add()
{
    cout << "How Many Books Would You Like to Insert?"<<endl;
    cout << "Response: "<<endl;
    int num;
    cin >> num;
    for(int i = 0; i < num; i++)
    {
        //insert a new book into the current position of the array. If the title already exists, do not add the book.
        cin.ignore();
        SetTitle();
        AddAuthor();
        SetISBN();
        SetStock();
        cin.ignore();
        SetPublisher();
        setGenre();
        SetYear();
        SetPrice();
       
    }
    //notify that the book ws added the to the main catalog.
    cout << "The Book Was Added to the Archive."<<endl;
}
//inserts the contents of the vector into the file
void Catalog::Insert(ofstream & out)
{
    //insert the contents of the array into the text file.
    out << GetTitle()<<endl;
    out << GetAuthor()<<endl;
    out << GetISBN()<<endl;
    out << GetStock()<<endl;
    out <<GetPublisher()<<endl;
    out <<getGenre()<<endl;
    out <<GetYear()<<endl;
    out <<fixed << showpoint << setprecision(2) << GetPrice()<<endl;
}
//search the catalog and delete a book
void Catalog::Delete(ifstream & file, ofstream & outfile, int length)
{
    bool flag2 = false;
    //this function allows you to delete a book from the catalog
    cout << "You Can Search By Title, Author, or ISBN: "<<endl;
    cout << "Search Bar: ";
    string search;
    string input;
    cin.ignore();
    getline(cin,input);
    cout<<'\n';
    if(cin.good())
    {
        flag2 = true;
    }
    else
    {
        //clear the input value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //prompt the user to enter another value.
        cout << "Please enter valid input. Try again: " << endl;
    }
    while(flag2 == true)
    {
        bool found = false;
        int indexFound = 0;
        //start reading at the beginning of the file.
        file.clear();
        file.seekg(0, ios::beg);
        for(int i = 0; !file.eof(); i++)
        {
            ProcessFile(file);
            indexFound = i;
            //so we can do partial word searches
            const char * ptr = strstr(GetTitle().c_str(), input.c_str());
            const char * ptr2 = strstr(GetAuthor().c_str(), input.c_str());
            const char * ptr3 = strstr(GetISBN().c_str(), input.c_str());
            
                //if the pointer is not NULL it means a match was found.
                if(ptr != NULL || ptr2 !=NULL || ptr3 != NULL)
                {
                    search = input;
                    found = true;
                }
        }
        if(!found)
        {
            cout << "The book "<<input<<" was not found."<<endl;
            flag2 = false;
        }
        
        if(found == true)
        {
            bool flag3 = false;
            //ask the user what they would like to edit
            cout <<"Delete Menu: "<< search << endl;
            cout<<"Are you sure you would like to delete this Book(Y/N)?"<<endl;
            char answer;
            cin >> answer;
            if(answer == 'Y' || answer == 'y')
            {
            //read from the beginning of the file to the end
            file.clear();
            file.seekg(0, ios::beg);
            while(!file.eof())
            {
                ProcessFile(file);
                //if the book does not match the search keyword insert it into the output file
                for (int i = 0; i < length; i++)
                {
                    if(search != nb[i].title || search != nb[i].ISBN || search != nb[i].lastName)
                    {
                        //iterate through all books and place them one index back
                        for(int j = i; j < length - 1; j++)
                            {
                               //swapping the instances themselves, but still comparing by the member.
                                nb[i].title = nb[i+1].title;
                                nb[i].lastName = nb[i+1].lastName;
                                nb[i].ISBN= nb[i+1].ISBN;
                                nb[i].year = nb[i+1].year;
                                nb[i].publisher = nb[i+1].publisher;
                                nb[i].genre = nb[i+1].genre;
                                nb[i].numInStock = nb[i+1].numInStock;
                                nb[i].price = nb[i+1].price;
                            }
                    }
                }
                Insert(outfile);
            }
            found = false;
            flag3 = false;
            flag2 = false;
            }
            else if(answer == 'N' || answer == 'n')
            {
                flag3 = false;
                flag2 = false;
            }
            else{
                //clear the input value
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                //prompt the user to enter another value.
                cout << "Please enter valid input. Try again: " << endl;
        }
    }
}
}
void Catalog::ProcessFile(ifstream & file)
{
    //gets each Book oject from the file.
        string emptyLine;
        getline(file, nb[sizeOfCatalog].title);
        getline(file, nb[sizeOfCatalog].lastName);
        getline(file, nb[sizeOfCatalog].ISBN);
        getline(file, nb[sizeOfCatalog].year);
        getline(file, nb[sizeOfCatalog].publisher);
        getline(file, nb[sizeOfCatalog].genre);
        file >> nb[sizeOfCatalog].numInStock ;
        file >> fixed >> showpoint >> setprecision(2) >> nb[sizeOfCatalog].price;
        getline(file, emptyLine);
}

//display all the books in the catalog
void Catalog::Display(ifstream & file)
{
    //display the main catalog
    cout << "Main Catalog: " << endl;
 
    cout << "Book Information: " << endl;
    
            cout << "Book Title: " << GetTitle() << endl;
            cout << "Author(s): " << GetAuthor() << endl;
            cout << "ISBN: " << GetISBN() << endl;
            cout << "Year: " << GetYear() << endl;
            cout << "Publisher: " << GetPublisher() << endl;
            cout << "Genre: "<<getGenre()<<endl;
            cout << "Number in Stock: " << GetStock() << endl;
            cout << "Price: " << fixed << showpoint << setprecision(2) << GetPrice() << endl;
            cout << '\n';
}
//perform linear search on the catalog for a book
void Catalog::LinearSearch(ifstream & file)
{
    bool flag2 = false;
    //read through the file and push each book object into a book array.
    cout << "You Can Search By Title, Author, or ISBN: "<<endl;
    cout << "Return to Main Menu"<< endl;
    cout << "Search Bar: ";
    string input;
    cin.ignore();
    getline(cin,input);
    cout << '\n';
    if(cin.good())
    {
        flag2 = true;
    }
    else
    {
        //clear the input value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //prompt the user to enter another value.
        cout << "Please enter valid input. Try again: " << endl;
    }
    while(flag2 == true)
    {
        int indexFound;
        bool found = false;
        //start reading at the beginning of the file.
        file.clear();
        file.seekg(0, ios::beg);
        for(int i = 0; !file.eof(); i++)
        {
            ProcessFile(file);
            indexFound = i;
            //so we can do partial word searches
            const char * ptr = strstr(GetTitle().c_str(), input.c_str());
            const char * ptr2 = strstr(GetAuthor().c_str(), input.c_str());
            const char * ptr3 = strstr(GetISBN().c_str(), input.c_str());
            
            {
                //if a match is found
                if(ptr != NULL || ptr2 !=NULL || ptr3 != NULL)
                {
                    cout << "Search Results for "<< input <<":"<<endl;
                    cout << '\n';
                    cout << "Found at index: "<<indexFound<<endl;
                    Display(file);
                    found = true;
                    flag2 = false;
                }
            }
        }
        if(!found)
        {
            cout << "The book "<<input<<" was not found."<<endl;
            flag2 = false;
        }
        
    }
}

void Catalog::SetPayment()
{
    //this method processes a payment for an order.
    cout<<"Enter Type of Card:"<<endl;
    cout<<"1.Visa"<<endl;
    cout<<"2.Mastercard"<<endl;
    cout<<"3.American Express"<<endl;
    cout<<"4.Giftcard"<<endl;
    int ans;
    cin >> ans;
    if(ans == 1 || ans == 2 || ans == 3)
    {
        cout<<"Please Enter Card Number: ";
        cin.ignore();
        string paymentId = readInput();
        if(paymentId.length() == 12)
        {
            cout<<"Please Enter Expiration Data(MM/YY):"<<endl;
            string expirationDate = readInput();
            //will have to come back and edit this after I add the date class...
            if(expirationDate.length() == 5)
            {
                cout <<"Please Enter 3 Digit CVS On Back Of Card: ";
                string CVS = readInput();
                if(CVS.length() == 3)
                {
                    cout <<"Thank You for Your Order!"<<endl;
                }
            }
        }
    }
    else if(ans == 4)
    {
        cout<<"Please Enter Card Number: ";
        string paymentId = readInput();
        if(paymentId.length() == 12)
        {
            cout <<"Thank You for Your Order!"<<endl;
        }
        
    }
    else
    {
        //clear the input value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //prompt the user to enter another value.
        cout << "Please enter valid input. Try again: " << endl;
    }
}
//Order more stock of a particular book.
void Catalog::Order(ifstream & file, ofstream & out, ofstream & receipt)
{
    bool flag2 = false;

    cout << "You Can Search By Title, Author, or ISBN: "<<endl;
    cout << "Return to Main Menu"<< endl;
    cout << "Search Bar: ";
    string input;
    cin.ignore();
    getline(cin,input);
    cout << '\n';
    if(cin.good())
    {
        flag2 = true;
    }
    else
    {
        //clear the input value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //prompt the user to enter another value.
        cout << "Please enter valid input. Try again: " << endl;
    }
    while(flag2 == true)
    {
        int indexFound;
        bool found = false;
        //start reading at the beginning of the file.
        file.clear();
        file.seekg(0, ios::beg);
        for(int i = 0; !file.eof(); i++)
        {
            ProcessFile(file);
            indexFound = i;
            //so we can do partial word searches
            const char * ptr = strstr(GetTitle().c_str(), input.c_str());
            const char * ptr2 = strstr(GetAuthor().c_str(), input.c_str());
            const char * ptr3 = strstr(GetISBN().c_str(), input.c_str());
            {
                //if a match is found
                if(ptr != NULL || ptr2 !=NULL || ptr3 != NULL)
                {
                    cout << "Search Results for "<< input <<":"<<endl;
                    cout << '\n';
                    cout << "Found at index: "<<indexFound<<endl;
                    //get the information about the purchase from the user.
                    found = true;
                    int quantity;
                    double tax = 9;
                    cout <<"Enter Quantity: ";
                    cin >> quantity;
                    double subTotal = (quantity * GetPrice());
                    double total = subTotal + (tax/100);
                    cout <<"Subtotal: "<< fixed << showpoint << setprecision(2)<< subTotal<<endl;
                    cout <<"Tax: "<< fixed << showpoint << setprecision(2) << (tax/100)<<"%"<<endl;
                    cout <<"_______________"<<endl;
                    cout <<"Total: " << fixed << showpoint << setprecision(2) <<total<<endl;
                    
                    cout<<"Please Enter Shipping Information: "<<endl;
                    cin.ignore();
                    cout<<"Name: ";
                    o.name = readInput();
                    cout<<'\n';
                    cout<<"Address Line: ";
                    o.address = readInput();
                    cout<<'\n';
                    cout<<"City: ";
                    o.city = readInput();
                    cout<<'\n';
                    cout<<"State: ";
                    o.state = readInput();
                    cout<<'\n';
                    cout<<"Zip Code: ";
                    o.zipCode = readInput();
                    cout<<'\n';
                    cout<<"Phone Number: ";
                    o.phoneNumber = readInput();
                    cout<<'\n';
                    
                    SetPayment();
                    
                    Date d;
                    
                    cout<< '\n';
                    cout << "Review Order: "<<endl;
                    d.GetDate(); 
                    cout << "Book Title: "<<GetTitle()<<endl;
                    cout << "Quantity: "<<quantity<<endl;
                    cout << "Total: "<<total<<endl;
                    cout << "Name: "<<o.name<<endl;
                    cout << "Address: "<<o.address<<endl;
                    cout << "City: "<<o.city<<endl;
                    cout << "State: "<<o.state<<endl;
                    cout << "Zip Code: "<<o.zipCode<<endl;
                    
                    //the receipt should be stored in a txt file called invoice
                    receipt << "Order Receipt: "<<endl;
                    d.OutputDate(receipt);
                    receipt << "Book Title: "<<GetTitle()<<endl;
                    receipt << "Quantity: "<<quantity<<endl;
                    receipt << "Total: "<<total<<endl;
                    receipt << "Name: "<<o.name<<endl;
                    receipt << "Address: "<<o.address<<endl;
                    receipt << "City: "<<o.city<<endl;
                    receipt << "State: "<<o.state<<endl;
                    receipt << "Zip Code: "<<o.zipCode<<endl;
                    
                }
            }
        }
        if(!found)
        {
            cout << "The book "<<input<<" was not found."<<endl;
        }
    }
}
void Catalog::StoreInfo()
{
    //to get the information about the company. 
    cout<<"Store Name: Novel Idea Books"<<endl;
    cout<<"Owner: Stephanie Honore"<<endl;
    cout<<"Shipping Address: 5555 Cherry St"<<endl;
    cout<<"City: Chattanooga"<<endl;
    cout<<"State: TN"<<endl;
    cout<<"Zip Code: 37421"<<endl;
    cout<<"Phone Number: 555-555-5555"<<endl;
    cout<<"Email: stephanie@novelbooks.com"<<endl;
}
void Catalog::Edit(ifstream & file, ofstream & newfile, int length)
{
    bool flag2 = false;
    //this function allows us to edit the contents of a Book in the catalog
    //Make sure you enter the exact title and there is no spaces at the end.
    cout << "You Can Search By Title or ISBN: "<<endl;
    cout << "Search Bar: ";
    string search;
    string input;
    cin.ignore();
    getline(cin,input);
    cout<<'\n';
    if(cin.good())
    {
        flag2 = true;
    }
    else
    {
        //clear the input value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //prompt the user to enter another value.
        cout << "Please enter valid input. Try again: " << endl;
    }
    while(flag2 == true)
    {
    bool found = false;
    int indexFound = 0;
    //start reading at the beginning of the file.
    file.clear();
    file.seekg(0, ios::beg);
    for(int i = 0; !file.eof(); i++)
    {
        //iterate through the txt file
        ProcessFile(file);
        indexFound = i;
        //so we can do partial word searches
        const char * ptr = strstr(GetTitle().c_str(), input.c_str());
        const char * ptr2 = strstr(GetISBN().c_str(), input.c_str());
        {
            //if the pointer is not NULL it means a match was found.
            if(ptr != NULL || ptr2 !=NULL)
            {
                search = input;
                cout << "Search Results for "<< input <<":"<<endl;
                cout << '\n';
                cout << "Found at index: "<<indexFound<<endl;
                found = true;
            }
        }
    }
        //if the search results do not turn up anything notify the user
        if(!found)
        {
            cout << "The book "<<input<<" was not found."<<endl;
            flag2 = false;
        }
        if(found == true)
        {
            bool flag3 = false;
            //ask the user what they would like to edit
                cout <<"Edit Menu: "<< search << endl;
            
                cout<<"What would you like to edit?"<<endl;
                cout << "1. Book Title "<< endl;
                cout << "2. Author(s) "<< endl;
                cout << "3. ISBN " << endl;
                cout << "4. Year "<< endl;
                cout << "5. Publisher " << endl;
                cout << "6. Number in Stock: " << endl;
                cout << "7. Price " << endl;
                cout << "8. Genre"<<endl;
                cout << '\n';
                cin.clear();
                int x;
                cin >> x;
            if(cin.good())
            {
                flag3 = true;
            }
            else
            {
                //clear the input value
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                //prompt the user to enter another value.
                cout << "Please enter valid input. Try again: " << endl;
            }
            while(flag3 == true)
            {
                if(x == 1)
                {
                    //create a new Book with the updated information
                    //Book nb;
                    cout<<"Enter the New Title"<<endl;
                    //get the new title from the user;
                    string newTitle;
                    cin.ignore();
                    getline(cin, newTitle);
                    cout << newTitle<<endl;
                    //read from the beginning of the file to the end
                    file.clear();
                    file.seekg(0, ios::beg);
                    while(!file.eof())
                    {
                        //iterate through the txt file and push the results into the array
                        ProcessFile(file);
                        for(int i = 0; i < length; i++)
                        {
                            if(search == nb[i].title || search == nb[i].ISBN)
                            {
                                //set the title at this index to the new title
                                nb[i].title = newTitle;
                            }
                            
                        }
                        //insert into the output file
                        Insert(newfile);
                    }
                    flag3 = false;
                    flag2 = false;
                }
                else if(x == 2)
                {
                        cout<<"Enter the New Author(Last, First)"<<endl;
                        //get the new Author from the user;
                        string newAuthor;
                        cin.ignore();
                        getline(cin, newAuthor);
                        //read from the beginning of the file to the end
                        file.clear();
                        file.seekg(0, ios::beg);
                        while(!file.eof())
                        {
                             ProcessFile(file);
                            for(int i = 0; i < length; i++)
                            {
                                if(search == nb[i].title || search == nb[i].ISBN)
                                {
                                    //set the author at this index to the new author
                                    nb[i].lastName = newAuthor;
                                }
                            }
                            //insert the updated array of Books into the text file
                            Insert(newfile);
                        }
                        flag3 = false;
                        flag2 = false;
                }
                else if(x == 3)
                {
                    cout<<"Enter the New ISBN"<<endl;
                    
                        //get the new ISBN from the user;
                        string newISBN;
                        cin.ignore();
                        getline(cin, newISBN);
                    if(newISBN.length() == 13)
                    {
                        //read from the beginning of the file to the end
                        file.clear();
                        file.seekg(0, ios::beg);
                        while(!file.eof())
                        {
                            ProcessFile(file);
                            for(int i = 0; i < length; i++)
                            {
                                if(search == nb[i].title || search == nb[i].ISBN)
                                {
                                    //set the ISBN at this index to the new ISBN
                                    nb[i].ISBN= newISBN;
                                }
                            }
                        Insert(newfile);
                        }
                        flag3 = false;
                        flag2 = false;
                    }
                }
                else if(x == 4)
                {
                    cout<<"Enter the New Year"<<endl;
                        //get the new year from the user;
                        string newYear;
                        cin.ignore();
                        getline(cin, newYear);
                        //read from the beginning of the file to the end
                        file.clear();
                        file.seekg(0, ios::beg);
                        while(!file.eof())
                        {
                            ProcessFile(file);
                            for(int i = 0; i < length; i++)
                            {
                                if(search == nb[i].title || search == nb[i].ISBN)
                                {
                                    //set the year at this index to the new year
                                    nb[i].year = newYear;
                                }
                            }
                              Insert(newfile);
                        }
                        flag3 = false;
                        flag2 = false;

                }
                else if(x == 5)
                {
                    cout<<"Enter the New Publisher"<<endl;
                        //get the new publisher from the user;
                        string newPublisher;
                        cin.ignore();
                        getline(cin, newPublisher);
                        //read from the beginning of the file to the end
                        file.clear();
                        file.seekg(0, ios::beg);
                        while(!file.eof())
                        {
                            ProcessFile(file);
                            for(int i = 0; i < length; i++)
                            {
                                if(search == nb[i].title || search == nb[i].ISBN)
                                {
                                    //set the publisher at this index to the new publisher
                                    nb[i].publisher = newPublisher;
                                }
                            }
                            Insert(newfile);
                        }
                        flag3 = false;
                        flag2 = false;

                }
                else if(x == 7)
                {
                    cout<<"Enter the New Price"<<endl;
                        double newPrice;
                        cin >> newPrice;
                        //read from the beginning of the file to the end
                        file.clear();
                        file.seekg(0, ios::beg);
                        while(!file.eof())
                        {
                            ProcessFile(file);
                            for(int i = 0; i < length; i++)
                            {
                                if(search == nb[i].title || search == nb[i].ISBN)
                                {
                                    //set the price at this index to the new price
                                    nb[i].price = newPrice;
                                }
                            }
                    
                            Insert(newfile);
                        }
                    flag3 = false;
                    flag2 = false;
                }
                else if(x == 6)
                {
                    cout<<"Update Inventory"<<endl;
                        //temp book to get the new stock value from the user;
                        int newStock;
                        cin.ignore();
                        cin >> newStock;
                        //read from the beginning of the file to the end
                        file.clear();
                        file.seekg(0, ios::beg);
                        while(!file.eof())
                        {
                            ProcessFile(file);
                            for(int i = 0; i < length; i++)
                            {
                                if(search == nb[i].title || search == nb[i].ISBN || search == nb[i].lastName)
                                {
                                    //set the title at this index to the new title
                                    nb[i].numInStock = newStock;
                                }
                            }
                            //insert the contents of the array into the text file
                            Insert(newfile);
                        }
                
                        flag3 = false;
                }
                else
                {
                    cout << "Please enter valid input. " << endl;
                    flag3 = false;
                }
            }
        }
    }
}
//sort the catalog by either author, title, or price. Merge Sort is used
void Catalog::Sort(ifstream & file, ofstream & outfile, int length)
{
    bool flag = false;
    int y;
    
        cout << "How Would You Like to Sort?"<<endl;
        cout << "1. By Title"<<endl;
        cout << "2. By Author's Last Name"<<endl;
        cout << "3. By Price?"<<endl;
        cin.ignore();
        cin >> y;
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

    
    while(flag == true)
    {
        if(y == 1)
        {
            //sort by title
            //start reading from the beginning of the file
            file.clear();
            file.seekg(0, ios::beg);
            //get each Book object from the file
           if(!file.eof())
           {
               ProcessFile(file);
               Book temp; //Book instance instead of string
               //perform the sort
                for (int i = 0; i < length; i++)
                {
                    for(int j = 0; j < length - i; j++)
                    {
                            if (strcmp((nb[j].title).c_str(), (nb[j + 1].title).c_str()) < 0)
                            {
                                    //swapping the instances themselves, but still comparing by the member.
                                    temp = nb[j];
                                    nb[j] = nb[j + 1];
                                    nb[j + 1] = temp;
                            }
                    }
                }
               cout << "Sorted:"<<endl;
               //sorts in ascending order
               for(int i = length-1; i >= 0; i--)
               {
                   cout << nb[i].title<<endl;
                   cout << nb[i].lastName<<endl;
                   cout << nb[i].ISBN<<endl;
                   cout << nb[i].year<<endl;
                   cout << nb[i].publisher<<endl;
                   cout << nb[i].genre<<endl;
                   cout << nb[i].numInStock<<endl;
                   cout << fixed << showpoint << setprecision(2)<<nb[i].price<<endl;
                   cout <<'\n';
               }
           }
            flag = false;
        }
    else if(y == 2)
    {
        //sort by last name
        file.clear();
        file.seekg(0, ios::beg);
        
        ProcessFile(file);
        Book temp; //Book instance instead of string
        
        for (int i = 0; i < length; i++)
        {
            
            for(int j = 0; j < length - i; j++)
            {
                if (strcmp((nb[j].lastName).c_str(), (nb[j + 1].lastName).c_str()) < 0)
                {
                    //swapping the instances themselves, but still comparing by the member.
                    temp = nb[j];
                    nb[j] = nb[j + 1];
                    nb[j + 1] = temp;
                    
                }
            }
        }
        cout << "Sorted:"<<endl;
        //sorts in acsending order
        for(int i = length-1; i >= 0; i--)
        {
            cout << nb[i].title<<endl;
            cout << nb[i].lastName<<endl;
            cout << nb[i].ISBN<<endl;
            cout << nb[i].year<<endl;
            cout << nb[i].publisher<<endl;
            cout << nb[i].genre<<endl;
            cout << nb[i].numInStock<<endl;
            cout << fixed << showpoint << setprecision(2)<<nb[i].price<<endl;
            cout <<'\n';
        }
        flag = false;
    }
    else if(y == 3)
    {
        file.clear();
        file.seekg(0, ios::beg);
        //iterate through the file to find the book
        ProcessFile(file);
        Book temp; //Book instance instead of string
        
        for (int i = 0; i < length; i++)
        {
            for(int j = 0; j < length - i; j++)
            {
                if(nb[j].price < nb[j + 1].price)
                {
                    //swapping the instances themselves, but still comparing by the member.
                    temp = nb[j];
                    nb[j] = nb[j + 1];
                    nb[j + 1] = temp;
                }
            }
        }
        cout << "Sorted Catalog:"<<endl;
        //sorts in acsending order
        for(int i = length-1; i >= 0; i--)
        {
            cout << nb[i].title<<endl;
            cout << nb[i].lastName<<endl;
            cout << nb[i].ISBN<<endl;
            cout << nb[i].year<<endl;
            cout << nb[i].publisher<<endl;
            cout << nb[i].genre<<endl;
            cout << nb[i].numInStock<<endl;
            cout << fixed << showpoint << setprecision(2)<<nb[i].price<<endl;
            cout <<'\n';
        }
        flag = false;
    }
    else
    {
        //clear the input value
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        //prompt the user to enter another value.
        cout << "Please enter valid input. " << endl;
        flag = false;
    }
}
}
void Catalog::CashierMode(ifstream & file)
{
        Date d;
        bool flag = false;
        cout<<"Store Mode"<<endl;
        cout<<'\n';
        cout<<"Would You Like to Make a Purchase?(Y/N)"<<endl;
        char answer;
        cin >> answer;
        
    if((answer == 'Y' || answer == 'y') && cin.good())
    {
        flag = true;
    }
    else if(answer == 'N' || answer == 'n')
    {
        cout <<"End of Store Mode"<<endl;
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
        bool flag2;
        //you would enter the ISBN as a bar scan code in real life.
        cout <<"Enter the ISBN of the Book"<<endl;
        cout << "Search Bar: ";
        string input;
        cin.ignore();
        getline(cin,input);
        cout<<'\n';
        if(cin.good())
        {
            flag2 = true;
        }
        else
        {
            //clear the input value
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            //prompt the user to enter another value.
            cout << "Please enter valid input. Try again: " << endl;
        }
        while(flag2 == true)
        {
            bool found = false;
            int indexFound = 0;
            //start reading at the beginning of the file.
            file.clear();
            file.seekg(0, ios::beg);
            for(int i = 0; !file.eof(); i++)
            {
                //iterate through the txt file
                ProcessFile(file);
                indexFound = i;
                //use a char pointer to compare each value as a c string
                const char * ptr = strstr(GetISBN().c_str(), input.c_str());
                {
                    //if the pointer is not NULL it means a match was found.
                    if(ptr != NULL)
                    {
                        found = true;
                    }
                }
            }
            int quantity;
            double tax = 9;
            cout <<"Enter Quantity: ";
            cin >> quantity;
            double subTotal = (quantity * GetPrice());
            double total = subTotal + (tax/100);
            
        SetPayment();
        cout<< '\n';
        //display a receipt for the purchase
        cout << "Novel Idea Books Order Receipt: "<<endl;
        cout<<'\n'; 
        d.GetDate();
        cout << "Book Title: "<<GetTitle()<<endl;
        cout << "Quantity: "<<quantity<<endl;
        cout <<"Subtotal: "<< fixed << showpoint << setprecision(2)<< subTotal<<endl;
        cout <<"Tax: "<< fixed << showpoint << setprecision(2) << (tax/100)<<"%"<<endl;
        cout <<"_______________"<<endl;
        cout <<"Total: " << fixed << showpoint << setprecision(2) <<total<<endl;
        flag = false;
    }
    }
}
//run the book store program
void Catalog::Run()
{
    ifstream in;
    ifstream itemp;
    ofstream out;
    ofstream otemp;
    ifstream ibackup;
    ofstream obackup;
    ofstream invoice;
    
    //open the file and have output position start at the end of the file
    in.open("Catalog.txt");
    ibackup.open("Catalog Copy.txt");
    itemp.open("temp.txt");
    
    invoice.open("Invoice.txt");
    obackup.open("Catalog Copy.txt", std::ofstream::in | std::ofstream::out);
    //the Catalog text output file is in append mode.
    out.open("Catalog.txt", std::ofstream::in | std::ofstream::out | std::ofstream::app);
    otemp.open("temp.txt",std::ofstream::in | std::ofstream::out);
    
    cout << "Welcome to the Bookstore!" << endl;
    
    //the length of the catalog.
    
    //create a new Catalog which is an array of Books. The Catalog can hold up to 500 books.
    Date today;
    //pointer to the array;
    bool flag = false;
    int response;
    
    do
    {
        //get response from user.
        today.GetDate();
        cout<<'\n';
        cout<<"  8b  8                    8    888    8               888b.             8"<<endl;
        cout<<"  8Ybm8 .d8b. Yb  dP .d88b 8     8  .d88 .d88b .d88    8wwwP .d8b. .d8b. 8.dP d88b"<<endl;
        cout<<"  8  '8 8' .8  YbdP  8.dP' 8     8  8  8 8.dP' 8  8    8   b 8' .8 8' .8 88b  `Yb."<<endl;
        cout<<"  8   8 `Y8P'   YP   `Y88P 8    888 `Y88 `Y88P `Y88    888P' `Y8P' `Y8P' 8 Yb Y88P"<<endl;
        cout << '\n' << endl;
        cout << "Main Menu:"<<endl;
        
        cout << '\n' << endl;
        cout << "What Would You Like to do?: "<< endl;
        cout << "1.Insert New Book in Catalog" << endl;
        cout << "2.Display Catalog" << endl;
        cout << "3.Search for a Book" << endl;
        cout << "4.Backup Catalog"<<endl;
        cout << "5.Edit Catalog" << endl;
        cout << "6.Order Book"<<endl;
        cout << "7.Get Store Information"<<endl;
        cout << "8.Cashier Mode"<<endl;
        cout << "9.Exit"<<endl;
        cout << "Response: " << endl;
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
        
        if(flag == true)
        {
            int cataloglength;
            if(response == 1)
            {
                //insert a book at the end of the catalog
                Add();
                flag = false;
            }
            else if(response == 2)
            {
                //display the current catalog
                in.clear();
                in.seekg(0, ios::beg);
                while(!in.eof())
                {
                    ProcessFile(in);
                    Display(in);
                    cataloglength++;
                    
                }
                
                cout << "The catalog length is: "<< cataloglength << endl;
                cout << '\n';
                flag = false;
            }
            else if(response == 3)
            {
                //search for a book in the catalog by title, author or ISBN
                LinearSearch(in);
                flag = false;
            }
            else if(response == 4)
            {
                cout << "What Would You Like To Do?:"<<endl;
                cout << "1.Backup the Catalog"<<endl;
                cout << "2.Display Last Backup"<<endl;
                int value;
                cin >> value;
                if(value == 1)
                {
                //create backup file
                //read in the catalog
                    //start at the beginning of the file
                    in.clear();
                    in.seekg(0, ios::beg);
                while(!in.eof())
                {
                    //get the book objects from the text file and push it into the array
                    ProcessFile(in);
                    //insert contents into the output backup file
                    Insert(obackup);
                }
                //notify the user that the catalog was edited
                cout << ("Backup Complete")<<endl;
                    //set the date of the backup;
                    today.GetDate();
                cout << '\n';
                }
                else if(value == 2)
                {
                    //display the last backup catalog
                    //start at the beginning of the file
                    ibackup.clear();
                    ibackup.seekg(0, ios::beg);
                    while(!ibackup.eof())
                    {
                        ProcessFile(ibackup);
                        Display(ibackup);
                        cataloglength++;
                    }
                                        cout << '\n';
                    //notify the user that the catalog was edited
                    cout << ("Catalog Date:")<<endl;
                    today.GetDate();
                    cout << '\n';
                    flag = false;
                }
                else
                {
                    //clear the input value
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    //prompt the user to enter another value.
                    cout << "Please enter valid input. Try again: " << endl;
                }
                
                flag = false;
            }
            else if(response == 5)
            {
                //edit catalog by either deleting entry, updating stock, or modifying book inforamion.
                cout << "How Would You Like to Edit the Catalog?"<<endl;
                cout << "1. Modify an Existing Book"<<endl;
                cout << "2. Delete"<<endl;
                cout << "3. Sort Catalog"<<endl;
                cout << "4. Exit"<<endl;
                int x;
                cin >> x;
                if(x == 1)
                {
                    //edit the contents of the catalog
                    Edit(in, otemp, Length(in));
                    
                    //or we could close the files so we can rename them.
                    in.close();
                    otemp.close();
                    remove("Catalog.txt");
                    rename("temp.txt", "Catalog.txt");
                    
                    //reopen the file and have output position start at the end of the file
                    out.open("Catalog.txt", std::ofstream::in | std::ofstream::out | std::ofstream::app);
                    otemp.open("temp.txt",std::ofstream::in | std::ofstream::out | std::ofstream::app);
                    
                    cout << ("The Catalog Was Edited")<<endl;
                    cout << '\n';
                    
                    flag = false;
                }
                else if(x == 2)
                {
                    //delete a book from the catalog
                    Delete(in, otemp, Length(in));
                    
                    //close the files so we can rename them.
                    in.close();
                    otemp.close();
                    remove("Catalog.txt");
                    rename("temp.txt", "Catalog.txt");
                    
                    //reopen the file and have output position start at the end of the file
                    out.open("Catalog.txt", std::ofstream::in | std::ofstream::out | std::ofstream::app);
                    otemp.open("temp.txt",std::ofstream::in | std::ofstream::out | std::ofstream::app);
                    
                    //notify the user that the catalog was edited
                    today.GetDate();
                    cout << ("The Catalog Was Edited")<<endl;
                    cout << '\n';
                    
                    flag = false;
                }
                else if(x == 3)
                {
                    //sort the file by title, author or price
                        Sort(in, otemp, Length(in));
                        flag = false;
                }
                else if(x == 4)
                {
                    //return to main menu
                    flag = false;
                }
                else
                {
                    //prompt the user again if the response is invalid
                    cout << "Please Enter a Valid Response. Try Again" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }
            }
            else if(response == 6)
            {
                //order a book and recieve an invoice
                Order(in, invoice, invoice);
                flag = false;
                
            }
            else if(response == 7)
            {
                //get information about the book store
                StoreInfo();
                flag = false;
            }
            else if(response == 8)
            {
                //allows for the sale of a Book to a customer.
                CashierMode(in);
            }
            else if(response == 9)
            {
                //exit the program
                cout << "Thank you and have a nice day!";
            }
            else
            {
                //clear the input value
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                //prompt the user to enter another value.
                cout << "Please Enter a Valid Respnse. Try again"<<endl;
            }
        }
    }while(!flag);
    in.close();
    ibackup.close();
    itemp.close();
    otemp.close();
    out.close();
}


   