#pragma once

#include <iostream>
#include <string>

// Base class defining common operations for library items
class LibraryEntity {
public:
    virtual void addEntity() = 0;      // Add new entity to system
    virtual void removeEntity() = 0;    // Remove entity from system
    virtual void displayDetails() const = 0;  // Show entity information
    virtual ~LibraryEntity() {}        // Virtual destructor for inheritance
};

// Represents a book in the library system
class Book : public LibraryEntity {
public:
    std::string isbn;     // Unique identifier for the book
    std::string title;    // Book title
    std::string author;   // Book author
    std::string year;     // Publication year
    std::string status;   // Current status (Available/Borrowed)

    // Default constructor
    Book() {}

    // Parameterized constructor
    Book(std::string isbn, std::string title, std::string author, std::string year, std::string status)
        : isbn(isbn), title(title), author(author), year(year), status(status) {}

    // Implementation of base class virtual functions
    void addEntity() override {}
    void removeEntity() override {}

    // Display book information
    void displayDetails() const override {
        std::cout << "ISBN: "   << isbn   << "\n"
                  << "Title: "  << title  << "\n"
                  << "Author: " << author << "\n"
                  << "Year: "   << year   << "\n"
                  << "Status: " << status << "\n";
    }
};