# Library Management System

A library management system with a **C++ object-oriented core** and a **Python Tkinter GUI**.

The C++ program manages books, users and borrowing, and saves everything to a plain-text data file. It runs two ways: as an interactive console menu, or as a command-line tool that the GUI drives.

## Features

- **Books:** add, remove, list, search by title / author / ISBN, sort by title or author
- **Users:** add, list, search by name
- **Borrowing:** borrow and return books, with a transaction log
- **Persistence:** all data is saved to `library_data.txt`
- **GUI:** a Tkinter front-end calls the C++ program through commands (`add_book`, `remove_book`, `add_user`, `borrow_book`, `return_book`)

## Structure

| File | Role |
|------|------|
| `Book.h/.cpp`, `User.h/.cpp` | Data classes |
| `Library.h/.cpp` | Core logic: catalogue, users, transactions, file I/O |
| `Utility.h/.cpp` | Console helpers (colours, headers, screen clearing) |
| `main.cpp` | Entry point: console menu, or command mode when run with arguments |
| `gui.py` | Tkinter GUI that runs the compiled program |
| `library_data.txt` | Sample data |

## Build & run (Windows)

The console helpers use `windows.h`, so this builds on Windows (MinGW `g++` or MSVC).

```powershell
# 1. Build the C++ core
g++ -std=c++17 main.cpp Book.cpp Library.cpp User.cpp Utility.cpp -o library_app.exe

# 2a. Console menu
.\library_app.exe

# 2b. GUI (needs Python 3; it calls library_app.exe in the same folder)
python gui.py
```
