#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
using namespace std;

// This class represents a Book in the library system
class Book {
private:
    string title;       // Title of the book
    string author;      // Author of the book
    string isbn;        // Unique identifier (ISBN)
    bool available;     // true = available, false = borrowed

public:
    // Set the book's details
    void setBookDetails(string t, string a, string i) {
        title = t;
        author = a;
        isbn = i;
        available = true;  // When a book is added, it's available by default
    }

    // Display book details
    void displayBookDetails() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Availability: " << (available ? "Available" : "Borrowed") << endl;
    }

    // Borrow the book if it's available
    bool borrowBook() {
        if (available) {
            available = false;
            return true;
        } else {
            return false;
        }
    }

    // Return the book and make it available again
    void returnBook() {
        available = true;
    }

    // Get the ISBN to compare with user input
    string getISBN() {
        return isbn;
    }
};

#endif
