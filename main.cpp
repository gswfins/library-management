#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Classe base
class Book {
protected:
    string title;
    string author;
    string ISBN;
    bool available;
    string dateAdded;

public:
    virtual void setBookDetails(string t, string a, string i, bool avail, string date) {
        title = t;
        author = a;
        ISBN = i;
        available = avail;
        dateAdded = date;
    }

    virtual void displayBookDetails() const {
        cout << left << setw(20) << title
             << setw(20) << author
             << setw(15) << ISBN
             << setw(10) << (available ? "Yes" : "No")
             << setw(15) << dateAdded;
    }

    bool isAvailable() const {
        return available;
    }

    string getISBN() const {
        return ISBN;
    }

    virtual void borrowBook() {
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
};

// Subclasse HardcopyBook
class HardcopyBook : public Book {
private:
    string shelfNumber;

public:
    void setBookDetails(string t, string a, string i, bool avail, string date, string shelf) {
        Book::setBookDetails(t, a, i, avail, date);
        shelfNumber = shelf;
    }

    void displayBookDetails() const override {
        Book::displayBookDetails();
        cout << setw(15) << shelfNumber << endl;
    }
};

// Subclasse EBook
class EBook : public Book {
private:
    string licenseEndDate;

public:
    void setBookDetails(string t, string a, string i, bool avail, string date, string licenseEnd) {
        Book::setBookDetails(t, a, i, avail, date);
        licenseEndDate = licenseEnd;
    }

    void displayBookDetails() const override {
        Book::displayBookDetails();
        cout << setw(15) << licenseEndDate << endl;
    }
};

// Função para exibir estoque
void displayStock(Book* books[], int size) {
    cout << "\n📦 Current Book Stock:\n\n";
    cout << left << setw(20) << "Title"
         << setw(20) << "Author"
         << setw(15) << "ISBN"
         << setw(10) << "Available"
         << setw(15) << "Date Added"
         << setw(15) << "Extra Info" << endl;

    for (int i = 0; i < size; i++) {
        books[i]->displayBookDetails();
    }
}

// Função para ordenação (Bubble Sort por ISBN)
void sortBookData(Book* books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (books[j]->getISBN() > books[j + 1]->getISBN()) {
                swap(books[j], books[j + 1]);
            }
        }
    }
}

int main() {
    const int size = 5;
    Book* books[size];

    // Criando livros (alguns físicos, outros e-books)
    books[0] = new HardcopyBook();
    dynamic_cast<HardcopyBook*>(books[0])->setBookDetails("The Alchemist", "Paulo Coelho", "1001", true, "2020-01-01", "Shelf A1");

    books[1] = new EBook();
    dynamic_cast<EBook*>(books[1])->setBookDetails("1984", "George Orwell", "1005", true, "2019-06-15", "2024-12-31");

    books[2] = new HardcopyBook();
    dynamic_cast<HardcopyBook*>(books[2])->setBookDetails("Brave New World", "Aldous Huxley", "1003", true, "2018-11-12", "Shelf B2");

    books[3] = new EBook();
    dynamic_cast<EBook*>(books[3])->setBookDetails("The Hobbit", "J.R.R. Tolkien", "1004", true, "2021-03-27", "2025-03-01");

    books[4] = new HardcopyBook();
    dynamic_cast<HardcopyBook*>(books[4])->setBookDetails("The Great Gatsby", "F. Scott Fitzgerald", "1002", true, "2022-08-20", "Shelf C3");

    sortBookData(books, size);

    cout << "\n📚 Welcome to the Library System 📚\n";
    displayStock(books, size);

    string inputISBN;
    while (true) {
        cout << "\nEnter ISBN to borrow (0 to exit): ";
        cin >> inputISBN;

        if (inputISBN == "0") {
            cout << "👋 Exiting the system. Thank you!\n";
            break;
        }

        bool found = false;

        for (int i = 0; i < size; i++) {
            if (books[i]->getISBN() == inputISBN) {
                found = true;
                books[i]->borrowBook();
                displayStock(books, size); // Atualiza visualização do estoque
                break;
            }
        }

        if (!found) {
            cout << "⚠️ Book with ISBN " << inputISBN << " not found.\n";
        }
    }

    // Liberação de memória
    for (int i = 0; i < size; i++) {
        delete books[i];
    }

    return 0;
}
