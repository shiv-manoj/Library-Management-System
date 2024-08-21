// Author: Mandla Siva Manoj  IIT MADRAS 

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits> 

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    time_t issueDate;
    int dueMinutes;
    string issuerName;
    string issuerRollNo;
};

class Library {
    vector<Book> books;
    int bookCount = 0;

public:
    void menu();
    void addBook();
    void issueBook();
    void returnBook();
    void searchBook();
    void overdueBooks();
    int getValidatedIntInput();
};

void Library::menu() {
    int choice;
    do {
        cout << "\n\nLibrary Management System";
        cout << "\n1. Add New Book";
        cout << "\n2. Issue a Book";
        cout << "\n3. Return a Book";
        cout << "\n4. Search a Book";
        cout << "\n5. View Overdue Books";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        choice = getValidatedIntInput();

        switch (choice) {
            case 1: addBook(); break;
            case 2: issueBook(); break;
            case 3: returnBook(); break;
            case 4: searchBook(); break;
            case 5: overdueBooks(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
}

int Library::getValidatedIntInput() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please enter a number: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return input;
        }
    }
}

void Library::addBook() {
    Book newBook;
    newBook.id = ++bookCount;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    newBook.isIssued = false;
    books.push_back(newBook);
    cout << "Book added successfully with ID: " << newBook.id << "\n";
}

void Library::issueBook() {
    cout << "Enter book ID to issue: ";
    int id = getValidatedIntInput();
    
    for (auto &book : books) {
        if (book.id == id) {
            if (book.isIssued) {
                cout << "Book is already issued.\n";
                return;
            }
            book.isIssued = true;
            book.issueDate = time(0);
            cout << "Enter number of minutes for due: ";
            book.dueMinutes = getValidatedIntInput();
            cout << "Enter issuer's name: ";
            getline(cin, book.issuerName);
            cout << "Enter issuer's roll number: ";
            getline(cin, book.issuerRollNo);
            cout << "Book issued successfully.\n";
            return;
        }
    }
    cout << "Book ID not found.\n";
}

void Library::returnBook() {
    cout << "Enter book ID to return: ";
    int id = getValidatedIntInput();
    
    for (auto &book : books) {
        if (book.id == id) {
            if (!book.isIssued) {
                cout << "Book is not issued.\n";
                return;
            }
            book.isIssued = false;
            cout << "Book returned successfully.\n";
            return;
        }
    }
    cout << "Book ID not found.\n";
}

void Library::searchBook() {
    string query;
    cout << "Enter book title or author to search: ";
    cin.ignore();
    getline(cin, query);
    for (const auto &book : books) {
        if (book.title.find(query) != string::npos || book.author.find(query) != string::npos) {
            cout << "Book ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author;
            if (book.isIssued) {
                cout << " (Issued on: " << put_time(localtime(&book.issueDate), "%Y-%m-%d %H:%M:%S") << ")";
                cout << ", Issuer Name: " << book.issuerName << ", Roll No: " << book.issuerRollNo;
            }
            cout << "\n";
        }
    }
}

void Library::overdueBooks() {
    time_t now = time(0);
    cout << "Overdue Books:\n";
    int f = 0;
    for (const auto &book : books) {
        if (book.isIssued && difftime(now, book.issueDate) > book.dueMinutes * 60) { 
            cout << "Book ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author;
            cout << ", Issuer Name: " << book.issuerName << ", Roll No: " << book.issuerRollNo;
            cout << ", Issued on: " << put_time(localtime(&book.issueDate), "%Y-%m-%d %H:%M:%S") << "\n";
            f = 1;
        }
    }
    if (f == 0) cout << "No books overdue" << endl;
}

int main() {
    Library lib;
    lib.menu();
    return 0;
}
