import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
import subprocess
import os

# CONFIGURATION
DATA_FILE = "library_data.txt"
CPP_EXE = "library_app.exe"

class LibraryGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Library Management System")
        self.root.geometry("1000x700")
        self.root.configure(bg="#f0f2f5")

        self.style = ttk.Style()
        self.style.theme_use('clam')
        self.style.configure("Treeview", rowheight=30, font=('Segoe UI', 10))
        self.style.configure("Treeview.Heading", font=('Segoe UI', 11, 'bold'), background="#e1e4e8")

        # HEADER
        header_frame = tk.Frame(root, bg="#2c3e50", pady=15)
        header_frame.pack(fill=tk.X)
        tk.Label(header_frame, text="Library Management System", font=("Segoe UI", 24, "bold"), bg="#2c3e50", fg="white").pack()

        # TOOLBAR
        toolbar = tk.Frame(root, bg="white", pady=10, padx=10)
        toolbar.pack(fill=tk.X, pady=(0, 10))

        self.create_button(toolbar, "Add Book", self.add_book, "#27ae60")
        self.create_button(toolbar, "Remove Book", self.remove_book, "#c0392b")
        self.create_button(toolbar, "Add User", self.add_user, "#2980b9")
        self.create_button(toolbar, "Borrow Book", self.borrow_book, "#e67e22")
        self.create_button(toolbar, "Return Book", self.return_book, "#8e44ad")
        self.create_button(toolbar, "Refresh", self.load_data, "#7f8c8d")
        self.create_button(toolbar, "Launch CLI", self.launch_cpp, "#34495e")

        # TABS
        self.notebook = ttk.Notebook(root)
        self.notebook.pack(fill=tk.BOTH, expand=True, padx=20, pady=10)

        # BOOKS TAB
        self.frame_books = tk.Frame(self.notebook, bg="#f0f2f5")
        self.notebook.add(self.frame_books, text="Books")
        self.tree_books = self.create_table(self.frame_books, ["Title", "Author", "ISBN", "Available", "Added"])

        # USERS TAB
        self.frame_users = tk.Frame(self.notebook, bg="#f0f2f5")
        self.notebook.add(self.frame_users, text="Users")
        self.tree_users = self.create_table(self.frame_users, ["ID", "Name", "Contact", "Borrowed Count", "Borrowed ISBNs"])

        self.load_data()

    def create_button(self, parent, text, command, color):
        btn = tk.Button(parent, text=text, command=command, bg=color, fg="white", 
                        font=("Segoe UI", 10, "bold"), relief=tk.FLAT, padx=15, pady=5, cursor="hand2")
        btn.pack(side=tk.LEFT, padx=5)
        return btn

    def create_table(self, parent, columns):
        frame = tk.Frame(parent)
        frame.pack(fill=tk.BOTH, expand=True)
        
        scrollbar_y = ttk.Scrollbar(frame)
        scrollbar_y.pack(side=tk.RIGHT, fill=tk.Y)
        
        tree = ttk.Treeview(frame, columns=columns, show="headings", yscrollcommand=scrollbar_y.set)
        scrollbar_y.config(command=tree.yview)
        
        for col in columns:
            tree.heading(col, text=col)
            tree.column(col, width=150)
        
        tree.pack(fill=tk.BOTH, expand=True)
        return tree

    def run_cpp(self, args):
        if not os.path.exists(CPP_EXE):
            messagebox.showerror("Error", f"Executable {CPP_EXE} not found!")
            return False
        
        cmd = [CPP_EXE] + args
        try:
            # Hide console window on Windows
            startupinfo = None
            if os.name == 'nt':
                startupinfo = subprocess.STARTUPINFO()
                startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
                
            result = subprocess.run(cmd, capture_output=True, text=True, startupinfo=startupinfo)
            if result.returncode == 0:
                return True
            else:
                messagebox.showerror("Error", f"Command failed:\n{result.stdout}\n{result.stderr}")
                return False
        except Exception as e:
            messagebox.showerror("Error", str(e))
            return False

    def add_book(self):
        title = simpledialog.askstring("Add Book", "Enter Title:")
        if not title: return
        author = simpledialog.askstring("Add Book", "Enter Author:")
        if not author: return
        isbn = simpledialog.askstring("Add Book", "Enter ISBN:")
        if not isbn: return

        if self.run_cpp(["add_book", title, author, isbn]):
            messagebox.showinfo("Success", "Book added successfully!")
            self.load_data()

    def remove_book(self):
        selected = self.tree_books.selection()
        if not selected:
            messagebox.showwarning("Select Book", "Please select a book to remove.")
            return
        item = self.tree_books.item(selected[0])
        isbn = item['values'][2]

        if messagebox.askyesno("Confirm", f"Delete book with ISBN {isbn}?"):
            if self.run_cpp(["remove_book", str(isbn)]):
                messagebox.showinfo("Success", "Book removed.")
                self.load_data()

    def add_user(self):
        name = simpledialog.askstring("Add User", "Enter Name:")
        if not name: return
        contact = simpledialog.askstring("Add User", "Enter Contact:")
        if not contact: return

        if self.run_cpp(["add_user", name, contact]):
            messagebox.showinfo("Success", "User added successfully!")
            self.load_data()

    def borrow_book(self):
        # Simple implementation: Ask for IDs. 
        # Better UX would be selecting from tables, but this is robust.
        uid = simpledialog.askinteger("Borrow Book", "Enter User ID:")
        if not uid: return
        isbn = simpledialog.askstring("Borrow Book", "Enter Book ISBN:")
        if not isbn: return

        if self.run_cpp(["borrow_book", str(uid), isbn]):
            messagebox.showinfo("Success", "Book borrowed successfully!")
            self.load_data()

    def return_book(self):
        uid = simpledialog.askinteger("Return Book", "Enter User ID:")
        if not uid: return
        isbn = simpledialog.askstring("Return Book", "Enter Book ISBN:")
        if not isbn: return

        if self.run_cpp(["return_book", str(uid), isbn]):
            messagebox.showinfo("Success", "Book returned successfully!")
            self.load_data()

    def launch_cpp(self):
        if os.path.exists(CPP_EXE):
            subprocess.Popen(f'start {CPP_EXE}', shell=True)
        else:
            messagebox.showerror("Error", f"Could not find {CPP_EXE}")

    def load_data(self):
        for item in self.tree_books.get_children(): self.tree_books.delete(item)
        for item in self.tree_users.get_children(): self.tree_users.delete(item)

        if not os.path.exists(DATA_FILE):
            return

        try:
            with open(DATA_FILE, "r") as f:
                for line in f:
                    parts = line.strip().split('|')
                    if not parts: continue
                    
                    if parts[0] == 'B' and len(parts) >= 6:
                        status = "Yes" if parts[4] == "1" else "No"
                        self.tree_books.insert("", tk.END, values=(parts[1], parts[2], parts[3], status, parts[5]))
                    
                    elif parts[0] == 'U' and len(parts) >= 5:
                        borrowed_isbns = ", ".join(parts[5:]) if len(parts) > 5 else ""
                        self.tree_users.insert("", tk.END, values=(parts[1], parts[2], parts[3], parts[4], borrowed_isbns))
        except Exception as e:
            print(f"Error loading data: {e}")

if __name__ == "__main__":
    root = tk.Tk()
    app = LibraryGUI(root)
    root.mainloop()