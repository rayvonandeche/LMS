#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../Book/book.h"  

// Abstract base class that defines the common interface for all persons in the library system (both Members and Librarians).
class Person {
protected:
    std::string name;    // Person's full name
    std::string id;      // Unique identifier

public:
    // Constructor initializes name and ID
    Person(std::string name, std::string id) : name(name), id(id) {}
    
    // Pure virtual function that derived classes must implement
    virtual void displayDetails() const = 0;
    
    // Accessor methods
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    void setName(const std::string &newName) { name = newName; }
    
    // Virtual destructor for proper cleanup of derived classes
    virtual ~Person() {}
};
// Represents library members who can borrow books.
// Inherits from Person and adds borrowing functionality.
class Member : public Person {
public:
    std::string contact;                     // Member's contact information
    std::vector<std::string> borrowedBooks;  // ISBNs of books currently borrowed

    // Constructor initializes member data
    Member(std::string name, std::string id, std::string contact)
        : Person(name, id), contact(contact) {}

    // Implementation of abstract method to display member information
    void displayDetails() const override {
        std::cout << "Member ID: " << id << "\n"
                  << "Name: " << name << "\n"
                  << "Contact: " << contact << "\n"
                  << "Borrowed Books: ";
        if(borrowedBooks.empty())
            std::cout << "None";
        else {
            for(const auto &isbn : borrowedBooks)
                std::cout << isbn << " ";
        }
        std::cout << "\n";
    }
    
    // Borrow a book by ISBN
    void borrowBook(std::vector<Book>& books, const std::string &isbn) {
        // Find the book in the library
        auto it = std::find_if(books.begin(), books.end(), [&](const Book &b) {
            return b.isbn == isbn;
        });
        
        // Validation checks
        if(it == books.end())
            throw std::runtime_error("Book not found!");
        if(it->status == "Borrowed")
            throw std::runtime_error("Book already borrowed!");
            
        // Update book status and member's borrowed books list
        it->status = "Borrowed";
        borrowedBooks.push_back(isbn);
        std::cout << "Book borrowed successfully!\n";
    }

    // Return a borrowed book
    void returnBook(std::vector<Book>& books, const std::string &isbn) {
        // Check if the member has borrowed this book
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
        if(it == borrowedBooks.end())
            throw std::runtime_error("This book is not borrowed by you!");
            
        // Find the book in the library system
        auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book &b) {
            return b.isbn == isbn;
        });
        if(bookIt == books.end())
            throw std::runtime_error("Book not found in library records!");
            
        // Update book status and remove from borrowed list
        bookIt->status = "Available";
        borrowedBooks.erase(it);
        std::cout << "Book returned successfully!\n";
    }
};

//  * Represents library staff with administrative privileges.
class Librarian : public Person {
public:
    // Constructor initializes librarian data
    Librarian(std::string name, std::string id) : Person(name, id) {}

    // Implementation of abstract method to display librarian information
    void displayDetails() const override {
        std::cout << "Librarian ID: " << id << "\n"
                  << "Name: " << name << "\n";
    }
};

