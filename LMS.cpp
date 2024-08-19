#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// Structure to represent a book
struct Book {
    string title;
    string author;
    bool isIssued;
    time_t issueDate;
};

// Class to manage the library
class Library {
private:
    vector<Book> books;

public:
    // Add a new book to the library
    void addBook(const string& title, const string& author) {
        Book newBook = {title, author, false, 0};
        books.push_back(newBook);
        cout << "Book added successfully.\n";
    }

    // Issue a book to a user
    void issueBook(const string& title) {
        for (auto& book : books) {
            if (book.title == title && !book.isIssued) {
                book.isIssued = true;
                book.issueDate = time(0); // Current time
                cout << "Book issued successfully.\n";
                return;
            }
        }
        cout << "Book not found or already issued.\n";
    }

    // Return a book to the library
    void returnBook(const string& title) {
        for (auto& book : books) {
            if (book.title == title && book.isIssued) {
                book.isIssued = false;
                book.issueDate = 0;
                cout << "Book returned successfully.\n";
                return;
            }
        }
        cout << "Book not found or not issued.\n";
    }

    // Search for a book by title
    void searchBook(const string& title) {
        for (const auto& book : books) {
            if (book.title == title) {
                cout << "Title: " << book.title << ", Author: " << book.author
                     << ", Status: " << (book.isIssued ? "Issued" : "Available") << endl;
                return;
            }
        }
        cout << "Book not found.\n";
    }

    // Track overdue items (books issued for more than 30 days)
    void trackOverdueItems() {
        time_t now = time(0);
        for (const auto& book : books) {
            if (book.isIssued) {
                double daysIssued = difftime(now, book.issueDate) / (60 * 60 * 24);
                if (daysIssued > 30) {
                    cout << "Overdue Book - Title: " << book.title << ", Author: " << book.author
                         << ", Days Overdue: " << static_cast<int>(daysIssued - 30) << endl;
                }
            }
        }
    }
};

int main() {
    Library library;

    library.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    library.addBook("1984", "George Orwell");

    library.searchBook("1984");

    library.issueBook("The Great Gatsby");
    library.returnBook("The Great Gatsby");

    library.trackOverdueItems();

    return 0;
}
