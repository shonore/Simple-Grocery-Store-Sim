//
//  Catalog.h
//  CPSC5010_Project
//
//  Created by Stephanie Honore on 4/6/16.
//  Copyright © 2016 Stephanie Honore. All rights reserved.
//  This class contains the list of books available in the Bookstore

#ifndef Catalog_h
#define Catalog_h

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//the maximum length the value can be in the Bookstore.
const int MAX_LENGTH = 500;

//need constructor (default and parameterized), destructor, and copy constructor.
class Catalog
{
public:
    //these are the units of the catalog.
    struct Book
    {
        string title;
        //the author's first and last name.Can have up to 4 authors
        string lastName;
        //the genre of the book
        string genre; 
        //the book's International Standard Book Number
        string ISBN;
        //the year the book was published 
        string year;
        //the price of the book
        double price;
        //the book's publisher
        string publisher;
        //the number of books the store has in stocks
        int numInStock;
                    };
    //contains the information needed to place an order.
    struct OrderInfo
    {
        string name;
        string address;
        string city;
        string state;
        string zipCode;
        string phoneNumber; 
    };
    //constructor
    //post: empty Catalog has been created
    Catalog();
    //destructor
    ~Catalog();
    //copy constructor
    Catalog(const Catalog& a);
    
    //setters and getters
    void SetTitle();
    string GetTitle();
    
    void AddAuthor();
    string GetAuthor();
    
    void setGenre();
    string getGenre();
    
    void SetISBN();
    string GetISBN();
    
    void SetPublisher();
    string GetPublisher();
    
    void SetYear();
    string GetYear();
    
    void SetStock();
    int GetStock();
    
    void SetPrice();
    double GetPrice();
    
    void SetPayment();
    
    
    //accessors
    void StoreInfo();//Returns the information about the Bookshop
    int Length(ifstream & file);//get the number of books in the catalog; 
    void Display(ifstream & file); //displays the entire catalog of books.
    void LinearSearch(ifstream & file); //for a single look-up
    string readInput(); //a function for reading user string input and returning them as ItemType values.
    void ProcessFile(ifstream & file);//reads each Book object of the txt file and adds into the array of Books
    void CashierMode(ifstream & file); //allows for the sale of a book

    //mutators
    void Add(); //adds values from the array. The parameters are the number of books to be added.
    void Insert(ofstream & out); //inserts a value into the array
    void Delete(ifstream & file, ofstream &newfile, int length); //deletes a value from the array
    void Sort(ifstream & file, ofstream & outfile, int length); //sorts the array in ascending order by either title, author, or price. Selection sort algorithm is used.
    void Order(ifstream & file, ofstream & out, ofstream & reciept); //order a book from the warehouse/wholesaler. 
    void Edit(ifstream & file, ofstream &newfile, int length);
    
    void Run(); //start the Bookshop program
    
    OrderInfo o;//an instance of the OrderInfo struct
    Book nb[MAX_LENGTH];//an array of books
    int sizeOfCatalog = 0;//the size of the catalog
    
private:
    
};

#endif /* Catalog_h */
