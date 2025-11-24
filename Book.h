#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>
using namespace std;

class Book {
public:
    string title;
    string author;
    string isbn;
    bool available;
    string timestamp; // NEW: To store when the book was added
    Book* next;   
 
    Book();  
    // Updated constructor
    Book(const string& _title, const string& _author, const string& _isbn, const string& _ts);

    void printSummary() const;
};

#endif