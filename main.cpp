#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Função que verifica se uma string possui apenas números
typedef string Texto;
bool isNumeric(const Texto& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Função que valida a data no formato YYYY-MM-DD
typedef string Texto;
bool isValidDate(const Texto& date) {
    if (date.length() != 10) return false;
    return (isdigit(date[0]) && isdigit(date[1]) && isdigit(date[2]) && isdigit(date[3]) &&
            date[4] == '-' &&
            isdigit(date[5]) && isdigit(date[6]) &&
            date[7] == '-' &&
            isdigit(date[8]) && isdigit(date[9]));
}

// Classe Book (modelo de um livro)
class Book {
public:
    Texto title, author, isbn, dateAdd;
    bool available;
    Texto type;

    void setDetails(Texto t, Texto a, Texto i, bool avail, Texto date, Texto bookType) {
        title = t;
        author = a;
        isbn = i;
        available = avail;
        dateAdd = date;
        type = bookType;
    }

    void displayRow() {
        cout << left << setw(20) << title
             << setw(20) << author
             << setw(10) << isbn
             << setw(10) << (available ? "Yes" : "No")
             << setw(12) << dateAdd;
    }

    void borrow() {
        if (available) {
            available = false;
            cout << "\nBook borrowed successfully!\n";
        } else {
            cout << "\nThis book is already borrowed.\n";
        }
    }

    void returnBook() {
        if (!available) {
            available = true;
            cout << "\nBook returned successfully!\n";
        } else {
            cout << "\nThis book is already available.\n";
        }
    }
};

class HardcopyBook : public Book {
public:
    Texto shelfNumber;
    void setShelf(Texto shelf) { shelfNumber = shelf; }
    Texto getShelf() { return shelfNumber; }
};

class EBook : public Book {
public:
    Texto licenseEndDate;
    void setLicense(Texto license) { licenseEndDate = license; }
    Texto getLicense() { return licenseEndDate; }
};

void sortBooks(Book* books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (books[j]->isbn > books[j + 1]->isbn) {
                Book* temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

int main() {
    const int MAX_SIZE = 100;
    Book* books[MAX_SIZE];
    int bookCount = 5;

    books[0] = new HardcopyBook();
    books[0]->setDetails("The Hobbit", "J.R.R. Tolkien", "111", true, "2023-01-01", "hardcopy");
    static_cast<HardcopyBook*>(books[0])->setShelf("A-01");

    books[1] = new EBook();
    books[1]->setDetails("1984", "George Orwell", "222", true, "2023-01-02", "ebook");
    static_cast<EBook*>(books[1])->setLicense("2025-12-31");

    books[2] = new HardcopyBook();
    books[2]->setDetails("Dune", "Frank Herbert", "333", true, "2023-01-03", "hardcopy");
    static_cast<HardcopyBook*>(books[2])->setShelf("C-03");

    books[3] = new EBook();
    books[3]->setDetails("Hamlet", "W. Shakespeare", "444", true, "2023-01-04", "ebook");
    static_cast<EBook*>(books[3])->setLicense("2024-06-01");

    books[4] = new HardcopyBook();
    books[4]->setDetails("Frankenstein", "M. Shelley", "555", true, "2023-01-05", "hardcopy");
    static_cast<HardcopyBook*>(books[4])->setShelf("B-02");

    int choice;
    string input;

    while (true) {
        cout << "\nLibrary Menu:\n";
        cout << "1. List all Books\n";
        cout << "2. Borrow a Book\n";
        cout << "3. Return a Book\n";
        cout << "4. Add a new Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 5) {
            cout << "\nExiting... Have a great day!\n";
            break;
        }

        if (choice == 1 || choice == 2 || choice == 3) {
            sortBooks(books, bookCount);
            cout << "\nBooks:\n";
            cout << "===========================================================================================\n";
            cout << left << setw(20) << "Title"
                 << setw(20) << "Author"
                 << setw(10) << "ISBN"
                 << setw(10) << "Available"
                 << setw(12) << "Date Added"
                 << setw(15) << "Extra Info" << endl;
            cout << "-------------------------------------------------------------------------------------------\n";

            for (int i = 0; i < bookCount; i++) {
                books[i]->displayRow();
                if (books[i]->type == "hardcopy") {
                    cout << setw(15) << static_cast<HardcopyBook*>(books[i])->getShelf() << endl;
                } else if (books[i]->type == "ebook") {
                    cout << setw(15) << static_cast<EBook*>(books[i])->getLicense() << endl;
                }
            }

            if (choice == 2 || choice == 3) {
                cout << "\nEnter ISBN: ";
                cin >> input;
                bool found = false;
                for (int i = 0; i < bookCount; i++) {
                    if (books[i]->isbn == input) {
                        if (choice == 2)
                            books[i]->borrow();
                        else
                            books[i]->returnBook();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\nBook with ISBN " << input << " not found.\n";
                }
            }
        }

        else if (choice == 4) {
            Texto title, author, isbn, dateAdd, type, extraInfo;
            bool available;

            cout << "\nAdd New Book\n";
            cout << "Title: "; cin.ignore(); getline(cin, title);
            cout << "Author: "; getline(cin, author);

            while (true) {
                cout << "ISBN (only numbers): ";
                getline(cin, isbn);
                if (isNumeric(isbn)) break;
                cout << "Invalid ISBN. Please enter only numeric values.\n";
            }

            int tempAvailable;
            while (true) {
                cout << "Available (1 = Yes, 0 = No): ";
                cin >> tempAvailable;
                if (cin.fail() || (tempAvailable != 1 && tempAvailable != 0)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter 1 for Yes or 0 for No.\n";
                } else {
                    available = static_cast<bool>(tempAvailable);
                    break;
                }
            }

            while (true) {
                cout << "Date Added (YYYY-MM-DD): ";
                cin >> dateAdd;
                if (isValidDate(dateAdd)) break;
                cout << "Invalid date format. Please use YYYY-MM-DD.\n";
            }

            while (true) {
                cout << "Type (hardcopy/ebook): ";
                cin >> type;
                if (type == "hardcopy" || type == "ebook") break;
                cout << "Invalid type. Please enter 'hardcopy' or 'ebook'.\n";
            }

            if (type == "hardcopy") {
                cout << "Shelf Number: "; cin >> extraInfo;
                HardcopyBook* newBook = new HardcopyBook();
                newBook->setDetails(title, author, isbn, available, dateAdd, type);
                newBook->setShelf(extraInfo);
                books[bookCount++] = newBook;
            } else if (type == "ebook") {
                cout << "License End Date (YYYY-MM-DD): "; cin >> extraInfo;
                EBook* newBook = new EBook();
                newBook->setDetails(title, author, isbn, available, dateAdd, type);
                newBook->setLicense(extraInfo);
                books[bookCount++] = newBook;
            }
        }

        else {
            cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}
