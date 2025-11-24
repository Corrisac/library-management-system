#include "Library.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

Library::Library() {
    booksHead = nullptr;
    usersHead = nullptr;
    txHead = nullptr;
    nextUserId = 1;
    nextTxId = 1;
}

Library::~Library() {
    while (booksHead) { Book* tmp = booksHead->next; delete booksHead; booksHead = tmp; }
    while (usersHead) { User* tmp = usersHead->next; delete usersHead; usersHead = tmp; }
    while (txHead) { Transaction* tmp = txHead->next; delete txHead; txHead = tmp; }
}

void Library::addBook(const string& title, const string& author, const string& isbn) {
    if (findBookByISBN(isbn)) {
         cout << "Book already exists." << endl; 
         return; 
    }
    string ts = getTimestamp();
    Book* b = new Book(title, author, isbn, ts);
    b->next = booksHead;
    booksHead = b;
    cout << "Book added: " << title << " on " << ts << endl;
}

bool Library::removeBookByISBN(const string& isbn) {
    Book *cur = booksHead, *prev = nullptr;
    while (cur) {
        if (cur->isbn == isbn) {
            if (prev) prev->next = cur->next;
            else booksHead = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

void Library::listAllBooks() const {
    if (!booksHead) { cout << "BOOK UNAVAILABLE" << endl; return; }
    for (Book* cur = booksHead; cur; cur = cur->next) {
        cur->printSummary();
        cout << "----------------" << endl;
    }
}

void Library::searchBooksByTitle(const string& title) const {
    bool found = false;
    string lowq = toLower(title);
    for (Book* cur = booksHead; cur; cur = cur->next) {
        if (toLower(cur->title).find(lowq) != string::npos) {
            cur->printSummary(); cout << "----------------\n"; found = true;
        }
    }
    if (!found) cout << "NO MATCHING BOOKS" << endl;
}

void Library::searchBooksByAuthor(const string& author) const {
    bool found = false;
    string lowq = toLower(author);
    for (Book* cur = booksHead; cur; cur = cur->next) {
        if (toLower(cur->author).find(lowq) != string::npos) {
            cur->printSummary(); cout << "----------------" << endl; found = true;
        }
    }
    if (!found) cout << "NO MATCHING BOOKS" << endl;
}

void Library::searchBookByISBN(const string& isbn) const {
    Book* b = findBookByISBN(isbn);
    if (b) b->printSummary();
    else cout <<  "NO MATCHING BOOKS" << endl;
}

int Library::addUser(const string& name, const string& contact) {
    User* u = new User(nextUserId++, name, contact);
    u->next = usersHead;
    usersHead = u;
    cout << "User added: " << name << " (ID: " << u->id << ")" << endl;
    return u->id;
}

void Library::listAllUsers() const {
    if (!usersHead) { cout << "USERS NOT FOUND" << endl; return; }
    for (User* u = usersHead; u; u = u->next) {
        u->printSummary();
        cout << "----------------" << endl;
    }
}

void Library::searchUserByName(const string& name) const {
    bool found = false;
    string lowq = toLower(name);
    for (User* u = usersHead; u; u = u->next) {
        if (toLower(u->name).find(lowq) != string::npos) {
            u->printSummary(); cout << "----------------" << endl; found = true;
        }
    }
    if (!found) cout << "NO MATCHING USERS FOUND" << endl;
}

Book* Library::findBookByISBN(const string& isbn) const {
    for (Book* cur = booksHead; cur; cur = cur->next)
        if (cur->isbn == isbn) return cur;
    return nullptr;
}

User* Library::findUserById(int id) const {
    for (User* u = usersHead; u; u = u->next)
        if (u->id == id) return u;
    return nullptr;
}

bool Library::borrowBook(int userId, const string& isbn) {
    User* u = findUserById(userId);
    Book* b = findBookByISBN(isbn);
    if (!u || !b) { cout << "USER OR BOOK NOT FOUND" << endl; return false; }
    if (!b->available) { cout << "BOOK ALREADY BORROWED " << endl; return false; }
    if (!u->borrowBook(isbn)) { cout << "USER CANNOT BORROW MORE BOOKS" << endl; return false; }

    b->available = false;
    string ts = getTimestamp();
    Transaction* t = new Transaction(nextTxId++, isbn, userId, 'B', ts);
    t->next = txHead; txHead = t;
    cout << "BOOK BORROWED SUCCESSFULLY" << endl;
    return true;
}

bool Library::returnBook(int userId, const string& isbn) {
    User* u = findUserById(userId);
    Book* b = findBookByISBN(isbn);
    if (!u || !b) { cout << "USER OR BOOK NOT FOUND" << endl; return false; }
    if (!u->returnBook(isbn)) { cout << "USER DIDN'T BORROW THIS BOOK" << endl; return false; }

    b->available = true;
    string ts = getTimestamp();
    Transaction* t = new Transaction(nextTxId++, isbn, userId, 'R', ts);
    t->next = txHead; txHead = t;
    cout << "BOOK RETURNED SUCCESSFULLY" << endl;
    return true;
}

void Library::listTransactions() const {
    if (!txHead) { cout << "NO TRANSACTIONS" << endl; return; }
    for (Transaction* t = txHead; t; t = t->next) t->printSummary();
}

// REMOVED: seedSampleData function

void Library::sortBooksByTitle() {
    if (!booksHead || !booksHead->next) return;
    bool swapped;
    do {
        swapped = false;
        Book* cur = booksHead;
        Book* prev = nullptr;
        while (cur && cur->next) {
            if (toLower(cur->title) > toLower(cur->next->title)) {
                Book* tmp = cur->next;
                cur->next = tmp->next;
                tmp->next = cur;
                if (prev) prev->next = tmp; else booksHead = tmp;
                swapped = true;
                prev = tmp;
            } else { prev = cur; cur = cur->next; }
        }
    } while (swapped);
    cout << "BOOKS SORTED BY TITLE" << endl;
}

void Library::sortBooksByAuthor() {
    if (!booksHead || !booksHead->next) return;
    bool swapped;
    do {
        swapped = false;
        Book* cur = booksHead;
        Book* prev = nullptr;
        while (cur && cur->next) {
            if (toLower(cur->author) > toLower(cur->next->author)) {
                Book* tmp = cur->next;
                cur->next = tmp->next;
                tmp->next = cur;
                if (prev) prev->next = tmp; else booksHead = tmp;
                swapped = true;
                prev = tmp;
            } else { prev = cur; cur = cur->next; }
        }
    } while (swapped);
    cout << "BOOKS SORTED BY AUTHOR" << endl;
}

void Library::saveData() {
    ofstream out("library_data.txt");
    if (!out) { cout << "ERROR SAVING DATA" << endl; return; }

    for (Book* b = booksHead; b; b = b->next) {
        out << "B|" << b->title << "|" << b->author << "|" << b->isbn 
            << "|" << b->available << "|" << b->timestamp << "\n";
    }

    for (User* u = usersHead; u; u = u->next) {
        out << "U|" << u->id << "|" << u->name << "|" << u->contact 
            << "|" << u->borrowedCount;
        for(int i=0; i<MAX_BORROW; i++) {
            if(u->borrowedISBNs[i] != "") out << "|" << u->borrowedISBNs[i];
        }
        out << "\n";
    }
    out.close();
    cout << "DATA SAVED TO library_data.txt" << endl;
}

void Library::loadData() {
    ifstream in("library_data.txt");
    if (!in) { cout << "NO PREVIOUS DATA FOUND." << endl; return; }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string segment;
        vector<string> parts;
        
        while(getline(ss, segment, '|')) {
            parts.push_back(segment);
        }

        if (parts[0] == "B" && parts.size() >= 6) {
            Book* b = new Book(parts[1], parts[2], parts[3], parts[5]);
            b->available = (parts[4] == "1");
            b->next = booksHead;
            booksHead = b;
        }
        else if (parts[0] == "U" && parts.size() >= 5) {
            int id = stoi(parts[1]);
            User* u = new User(id, parts[2], parts[3]);
            int count = stoi(parts[4]);
            
            int isbnIndex = 5;
            for(int i=0; i<count && (size_t)isbnIndex < parts.size(); i++) {
                u->borrowBook(parts[isbnIndex++]);
            }
            
            u->next = usersHead;
            usersHead = u;
            
            if (id >= nextUserId) nextUserId = id + 1;
        }
    }
    in.close();
    cout << "DATA LOADED SUCCESSFULLY." << endl;
}