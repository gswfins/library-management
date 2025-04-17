#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Book {
protected:
    string title, author, ISBN, dateAdded;
    bool available;

public:
    Book(string t, string a, string i, bool avail, string date)
        : title(t), author(a), ISBN(i), available(avail), dateAdded(date) {}

    virtual void display() const {
        cout << "Title: " << title << ", "
             << "Author: " << author << ", "
             << "ISBN: " << ISBN << ", "
             << "Available: " << (available ? "Yes" : "No") << ", "
             << "Date Added: " << dateAdded;
    }

    string getISBN() const { return ISBN; }
    bool isAvailable() const { return available; }

    virtual void borrow() {
        if (available) {
            available = false;
            cout << "✅ Book borrowed successfully.\n";
        } else {
            cout << "❌ Book is currently unavailable.\n";
        }
    }

    void returnBook() { available = true; }
};

class HardcopyBook : public Book {
    string shelfNumber;

public:
    HardcopyBook(string t, string a, string i, bool avail, string date, string shelf)
        : Book(t, a, i, avail, date), shelfNumber(shelf) {}

    void display() const override {
        Book::display();
        cout << ", Shelf: " << shelfNumber << endl;
    }
};

class EBook : public Book {
    string licenseEndDate;

public:
    EBook(string t, string a, string i, bool avail, string date, string license)
        : Book(t, a, i, avail, date), licenseEndDate(license) {}

    void display() const override {
        Book::display();
        cout << ", License Ends: " << licenseEndDate << endl;
    }
};

void displayStock(Book* books[], int size) {
    cout << "\n📦 Current Book Stock:\n" << endl;
    for (int i = 0; i < size; ++i) {
        books[i]->display();
    }
}

void sortBooks(Book* books[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (books[j]->getISBN() > books[j + 1]->getISBN()) {
                swap(books[j], books[j + 1]);
            }
        }
    }
}

int main() {
    const int size = 5;
    Book* books[size] = {
        new HardcopyBook("The Alchemist", "Paulo Coelho", "1001", true, "2020-01-01", "Shelf A1"),
        new EBook("1984", "George Orwell", "1005", true, "2019-06-15", "2024-12-31"),
        new HardcopyBook("Brave New World", "Aldous Huxley", "1003", true, "2018-11-12", "Shelf B2"),
        new EBook("The Hobbit", "J.R.R. Tolkien", "1004", true, "2021-03-27", "2025-03-01"),
        new HardcopyBook("The Great Gatsby", "F. Scott Fitzgerald", "1002", true, "2022-08-20", "Shelf C3")
    };

    sortBooks(books, size);
    cout << "\n📚 Welcome to the Library System 📚\n";
    displayStock(books, size);

    string isbn;
    while (true) {
        cout << "\nEnter ISBN to borrow (0 to exit): ";
        cin >> isbn;
        if (isbn == "0") break;

        bool found = false;
        for (int i = 0; i < size; ++i) {
            if (books[i]->getISBN() == isbn) {
                books[i]->borrow();
                displayStock(books, size);
                found = true;
                break;
            }
        }
        if (!found) cout << "⚠️ Book with ISBN " << isbn << " not found.\n";
    }

    for (int i = 0; i < size; ++i) delete books[i];
    cout << "👋 Exiting the system. Thank you!\n";
    return 0;
}
