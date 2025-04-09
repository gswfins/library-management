#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// -------------------- Book Class --------------------
class Book {
private:
    string title;
    string author;
    string ISBN;
    bool available;
    string dateAdded;

public:
    void setDetails(string t, string a, string i, bool avail, string date) {
        title = t;
        author = a;
        ISBN = i;
        available = avail;
        dateAdded = date;
    }

    void display() {
        cout << left << setw(20) << title
             << setw(20) << author
             << setw(15) << ISBN
             << setw(10) << (available ? "Yes" : "No")
             << setw(15) << dateAdded << endl;
    }

    string getISBN() {
        return ISBN;
    }

    bool isAvailable() {
        return available;
    }

    void markAsBorrowed() {
        available = false;
    }

    void markAsReturned() {
        available = true;
    }
};

// -------------------- BookManager Class --------------------
class BookManager {
private:
    Book books[5];

public:
    void initBooks() {
        books[0].setDetails("The Alchemist", "Paulo Coelho", "1001", true, "2020-01-01");
        books[1].setDetails("1984", "George Orwell", "1005", true, "2019-06-15");
        books[2].setDetails("Brave New World", "Aldous Huxley", "1003", true, "2018-11-12");
        books[3].setDetails("The Hobbit", "J.R.R. Tolkien", "1004", true, "2021-03-27");
        books[4].setDetails("The Great Gatsby", "F. Scott Fitzgerald", "1002", true, "2022-08-20");

        sortBooks();
    }

    void sortBooks() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4 - i; j++) {
                if (books[j].getISBN() > books[j + 1].getISBN()) {
                    swap(books[j], books[j + 1]);
                }
            }
        }
    }

    void showAllBooks() {
        cout << "\n📖 Current list of books:\n\n";
        cout << left << setw(20) << "Title"
             << setw(20) << "Author"
             << setw(15) << "ISBN"
             << setw(10) << "Available"
             << setw(15) << "Date Added" << endl;

        for (int i = 0; i < 5; i++) {
            books[i].display();
        }
    }

    Book* findBookByISBN(string isbn) {
        for (int i = 0; i < 5; i++) {
            if (books[i].getISBN() == isbn) {
                return &books[i];
            }
        }
        return nullptr;
    }
};

// -------------------- BorrowManager Class --------------------
class BorrowManager {
public:
    void borrow(Book* book) {
        if (book->isAvailable()) {
            book->markAsBorrowed();
            cout << "✅ Book borrowed successfully.\n";
        } else {
            cout << "❌ Book is currently unavailable.\n";
        }
    }
};

// -------------------- Main Function --------------------
int main() {
    BookManager manager;
    BorrowManager borrower;

    manager.initBooks();

    cout << "\n📚 Welcome to the Library System 📚\n";
    manager.showAllBooks();

    string inputISBN;

    while (true) {
        cout << "\nEnter ISBN to borrow (0 to exit): ";
        cin >> inputISBN;

        if (inputISBN == "0") {
            cout << "👋 Exiting the system. Thank you!\n";
            break;
        }

        Book* book = manager.findBookByISBN(inputISBN);

        if (book != nullptr) {
            borrower.borrow(book);
        } else {
            cout << "⚠️ Book with ISBN " << inputISBN << " not found.\n";
        }

        manager.showAllBooks();
    }

    return 0;
}
