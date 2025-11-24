#include <iostream>
#include "Library.h"
#include "Utility.h"

using namespace std;

int mainMenu() {
    printHeader("LIBRARY MANAGEMENT SYSTEM");
    
    // Green Text for Menu Options
    setConsoleColor(10); 
    cout << " [1]  Add Book\n";
    cout << " [2]  List All Books\n";
    cout << " [3]  Search Book by Title\n";
    cout << " [4]  Search Book by Author\n";
    cout << " [5]  Search Book by ISBN\n";
    cout << " [6]  Sort Books by Title\n";
    cout << " [7]  Sort Books by Author\n";
    cout << " ------------------------\n";
    cout << " [8]  Add User\n";
    cout << " [9]  List Users\n";
    cout << " [10] Search User by Name\n";
    cout << " ------------------------\n";
    cout << " [11] Borrow Book\n";
    cout << " [12] Return Book\n";
    cout << " [13] List Transactions\n";
    cout << " ------------------------\n";
    cout << " [14] Remove Book\n";
    cout << " [15] Save Data to File\n"; 
    cout << " [0]  Exit\n";
    setConsoleColor(7); // Reset

    cout << "\nChoose an option: ";

    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore(10000, '\n');
    return choice;
}

int main(int argc, char* argv[]) {
    Library lib;
    
    // CLI MODE
    if (argc > 1) {
        lib.loadData(); // Load data for CLI operations
        string command = argv[1];

        if (command == "add_book" && argc >= 5) {
            // add_book <title> <author> <isbn>
            string title = argv[2];
            string author = argv[3];
            string isbn = argv[4];
            lib.addBook(title, author, isbn);
            lib.saveData();
            return 0;
        }
        else if (command == "remove_book" && argc >= 3) {
            string isbn = argv[2];
            if (lib.removeBookByISBN(isbn)) cout << "SUCCESS" << endl;
            else cout << "NOT_FOUND" << endl;
            lib.saveData();
            return 0;
        }
        else if (command == "add_user" && argc >= 4) {
            string name = argv[2];
            string contact = argv[3];
            lib.addUser(name, contact);
            lib.saveData();
            return 0;
        }
        else if (command == "borrow_book" && argc >= 4) {
            int uid = stoi(argv[2]);
            string isbn = argv[3];
            if (lib.borrowBook(uid, isbn)) cout << "SUCCESS" << endl;
            else cout << "FAILURE" << endl;
            lib.saveData();
            return 0;
        }
        else if (command == "return_book" && argc >= 4) {
            int uid = stoi(argv[2]);
            string isbn = argv[3];
            if (lib.returnBook(uid, isbn)) cout << "SUCCESS" << endl;
            else cout << "FAILURE" << endl;
            lib.saveData();
            return 0;
        }
        else {
            cout << "INVALID_COMMAND_OR_ARGS" << endl;
            return 1;
        }
    }

    // INTERACTIVE MODE
    printHeader("INITIALIZING SYSTEM");
    cout << "Loading previous data from file...\n";
    lib.loadData();
    cout << "Data Loaded. Starting System.\n";
    // Slight delay could go here, but pause is fine
    // pause(); 

    while (true) {
        int choice = mainMenu();
        
        if (choice == -1) { 
            cout << "INVALID INPUT. Please enter a number.\n"; 
            pause();
            continue; 
        }
        
        if (choice == 0) {
            printHeader("SHUTTING DOWN");
            cout << "Saving data before exit...\n";
            lib.saveData();
            cout << "Goodbye!\n";
            break;
        }

        switch(choice) {
            case 1: {  
                printHeader("ADD NEW BOOK");
                cout << "ENTER TITLE: "; string t; getline(cin, t);
                cout << "ENTER AUTHOR: "; string a; getline(cin, a);
                cout << "ENTER ISBN: "; string i; getline(cin, i);
                lib.addBook(t, a, i);
                pause();
                break;
            }
            case 2: 
                printHeader("LIST OF ALL BOOKS");
                lib.listAllBooks(); 
                pause();
                break;
            case 3: { 
                printHeader("SEARCH BOOK BY TITLE");
                cout << "ENTER TITLE: "; string t; getline(cin, t);
                lib.searchBooksByTitle(t);
                pause();
                break;
            }
            case 4: { 
                printHeader("SEARCH BOOK BY AUTHOR");
                cout << "ENTER AUTHOR: "; string a; getline(cin, a);
                lib.searchBooksByAuthor(a);
                pause();
                break;
            }
            case 5: { 
                printHeader("SEARCH BOOK BY ISBN");
                cout << "ENTER ISBN: "; string i; getline(cin, i);
                lib.searchBookByISBN(i);
                pause();
                break;
            }
            case 6: 
                printHeader("SORTING BOOKS");
                lib.sortBooksByTitle(); 
                pause();
                break;
            case 7: 
                printHeader("SORTING BOOKS");
                lib.sortBooksByAuthor(); 
                pause();
                break;
            case 8: {  
                printHeader("ADD NEW USER");
                cout << "NAME: "; string n; getline(cin, n);
                cout << "CONTACT: "; string c; getline(cin, c);
                lib.addUser(n, c);
                pause();
                break;
            }
            case 9: 
                printHeader("LIST OF USERS");
                lib.listAllUsers(); 
                pause();
                break;
            case 10: { 
                printHeader("SEARCH USER");
                cout << "NAME: "; string n; getline(cin, n);
                lib.searchUserByName(n);
                pause();
                break;
            }
            case 11: { 
                printHeader("BORROW BOOK");
                cout << "USER ID: "; int u; cin >> u; cin.ignore(10000, '\n');
                cout << "ISBN: "; string i; getline(cin, i);
                lib.borrowBook(u, i);
                pause();
                break;
            }
            case 12: { 
                printHeader("RETURN BOOK");
                cout << "USER ID: "; int u; cin >> u; cin.ignore(10000, '\n');
                cout << "ISBN: "; string i; getline(cin, i);
                lib.returnBook(u, i);
                pause();
                break;
            }
            case 13: 
                printHeader("TRANSACTION HISTORY");
                lib.listTransactions(); 
                pause();
                break;
            case 14: {
                printHeader("REMOVE BOOK");
                cout << "ISBN TO REMOVE: "; string i; getline(cin, i);
                if (lib.removeBookByISBN(i)) cout << "REMOVED SUCCESSFULLY" << endl; 
                else cout << "BOOK NOT FOUND" << endl;
                pause();
                break;
            }
            case 15: 
                printHeader("SAVING DATA");
                lib.saveData(); 
                pause();
                break; 
            default: 
                cout << "UNKNOWN OPTION" << endl; 
                pause();
                break;
        }
    }
    return 0;
}