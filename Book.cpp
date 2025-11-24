#include "Book.h"
#include <iostream>
using namespace std;

Book::Book() {
    title = "";
    author = "";
    isbn = "";
    available = true;
    timestamp = "";
    next = nullptr; 
}
 
// Updated Constructor
Book::Book(const string& _title, const string& _author, const string& _isbn, const string& _ts) {
    title = _title;
    author = _author;
    isbn = _isbn;
    timestamp = _ts; // Set timestamp
    available = true;
    next = nullptr;  
}
 
void Book::printSummary() const {
    cout << "TITLE: " << title << endl;
    cout << "AUTHOR: " << author << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "ADDED: " << timestamp << endl; // Print timestamp
    cout << "STATUS: " << (available ? "Available" : "Borrowed") << endl;
}