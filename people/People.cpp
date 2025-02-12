// Person.h
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Book.h"  // For using the Book class in Member methods

// Base class for persons.
class Person {
protected:
    std::string name;
    std::string id;
public:
    Person(std::string name, std::string id) : name(name), id(id) {}
    virtual void displayDetails() const = 0;
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    void setName(const std::string &newName) { name = newName; }
    virtual ~Person() {}
};

// Derived class for Members.
class Member : public Person {
public:
    std::string contact;
    std::vector<std::string> borrowedBooks; // List of ISBNs

    Member(std::string name, std::string id, std::string contact)
        : Person(name, id), contact(contact) {}

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

    // Borrow a book; throws an exception on error.
    void borrowBook(std::vector<Book>& books, const std::string &isbn) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book &b) {
            return b.isbn == isbn;
        });
        if(it == books.end())
            throw std::runtime_error("Book not found!");
        if(it->status == "Borrowed")
            throw std::runtime_error("Book already borrowed!");
        it->status = "Borrowed";
        borrowedBooks.push_back(isbn);
        std::cout << "Book borrowed successfully!\n";
    }

    // Return a book; throws an exception if the book isn’t borrowed.
    void returnBook(std::vector<Book>& books, const std::string &isbn) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
        if(it == borrowedBooks.end())
            throw std::runtime_error("This book is not borrowed by you!");
        auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book &b) {
            return b.isbn == isbn;
        });
        if(bookIt == books.end())
            throw std::runtime_error("Book not found in library records!");
        bookIt->status = "Available";
        borrowedBooks.erase(it);
        std::cout << "Book returned successfully!\n";
    }
};

// Derived class for Librarians (Admins).
class Librarian : public Person {
public:
    Librarian(std::string name, std::string id) : Person(name, id) {}

    void displayDetails() const override {
        std::cout << "Librarian ID: " << id << "\n"
                  << "Name: " << name << "\n";
    }
};

#endif // PERSON_H
