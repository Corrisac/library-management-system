#ifndef USER_H
#define USER_H

#include <string>
using namespace std;   

const int MAX_BORROW = 10;

class User {
public:
    int id;
    string name;
    string contact; // <--- NEW REQUIREMENT
    string borrowedISBNs[MAX_BORROW];
    int borrowedCount;
    User* next;
 
    User();
    // Updated constructor to include contact
    User(int _id, const string& _name, const string& _contact);

    bool borrowBook(const string& isbn);
    bool returnBook(const string& isbn);
 
    void printSummary() const;
};

#endif