#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Book {
private:
    string title;
    string author;
    string ISBN;
    bool available;
    string dateAdded;

public:
    void setBookDetails(string t, string a, string i, bool avail, string date) {
        title = t;
        author = a;
        ISBN = i;
        available = avail;
        dateAdded = date;
    }

    void displayBookDetails() {
        cout << left << setw(20) << title
             << setw(20) << author
             << setw(15) << ISBN
             << setw(10) << (available ? "Yes" : "No")
             << setw(15) << dateAdded << endl;
    }

    bool isAvailable() {
        return available;
    }

    string getISBN() {
        return ISBN;
    }

    void borrowBook() {
        if (available) {
            available = false;
            cout << "✅ Book borrowed successfully.\n";
        } else {
            cout << "❌ Book is currently unavailable.\n";
        }
    }

    void returnBook() {
        available = true;
    }

    static void sortBookData(Book books[], int size) {
        // Simple bubble sort by ISBN
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (books[j].getISBN() > books[j + 1].getISBN()) {
                    swap(books[j], books[j + 1]);
                }
            }
        }
    }

    static void displayAllBooks(Book books[], int size) {
        cout << "\n📖 Current list of books:\n\n";
        cout << left << setw(20) << "Title"
             << setw(20) << "Author"
             << setw(15) << "ISBN"
             << setw(10) << "Available"
             << setw(15) << "Date Added" << endl;

        for (int i = 0; i < size; i++) {
            books[i].displayBookDetails();
        }
    }
};

int main() {
    Book books[5];
    books[0].setBookDetails("The Alchemist", "Paulo Coelho", "1001", true, "2020-01-01");
    books[1].setBookDetails("1984", "George Orwell", "1005", true, "2019-06-15");
    books[2].setBookDetails("Brave New World", "Aldous Huxley", "1003", true, "2018-11-12");
    books[3].setBookDetails("The Hobbit", "J.R.R. Tolkien", "1004", true, "2021-03-27");
    books[4].setBookDetails("The Great Gatsby", "F. Scott Fitzgerald", "1002", true, "2022-08-20");

    Book::sortBookData(books, 5);

    cout << "\n📚 Welcome to the Library System 📚\n";
    Book::displayAllBooks(books, 5);

    string inputISBN;
    while (true) {
        cout << "\nEnter ISBN to borrow (0 to exit): ";
        cin >> inputISBN;

        if (inputISBN == "0") {
            cout << "👋 Exiting the system. Thank you!\n";
            break;
        }

        bool found = false;

        for (int i = 0; i < 5; i++) {
            if (books[i].getISBN() == inputISBN) {
                found = true;
                books[i].borrowBook();
                break;
            }
        }

        if (!found) {
            cout << "⚠️ Book with ISBN " << inputISBN << " not found.\n";
        }

        Book::displayAllBooks(books, 5); // Display updated list after borrow attempt
    }

    return 0;
}
