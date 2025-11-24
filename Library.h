#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include "Transaction.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Library {
private:
    Book* booksHead;
    User* usersHead;
    Transaction* txHead;
    int nextUserId;
    int nextTxId;

    Book* findBookByISBN(const string& isbn) const;
    User* findUserById(int id) const;

public:
    Library();
    ~Library();

    void addBook(const string& title, const string& author, const string& isbn);
    bool removeBookByISBN(const string& isbn);
    void listAllBooks() const;
    void searchBooksByTitle(const string& title) const;
    void searchBooksByAuthor(const string& author) const;
    void searchBookByISBN(const string& isbn) const;

    int addUser(const string& name, const string& contact);
    void listAllUsers() const;
    void searchUserByName(const string& name) const;

    bool borrowBook(int userId, const string& isbn);
    bool returnBook(int userId, const string& isbn);

    void listTransactions() const;

    // REMOVED: seedSampleData();

    void sortBooksByTitle();
    void sortBooksByAuthor();

    void saveData();
    void loadData();
};

#endif