#pragma once

#include <iostream>
#include <string>

// Abstract base class for library entities.
class LibraryEntity {
public:
    virtual void addEntity() = 0;
    virtual void removeEntity() = 0;
    virtual void displayDetails() const = 0;
    virtual ~LibraryEntity() {}
};

// Book class inheriting from LibraryEntity.
class Book : public LibraryEntity {
public:
    std::string isbn;
    std::string title;
    std::string author;
    std::string year;
    std::string status; // "Available" or "Borrowed"

    Book() {}
    Book(std::string isbn, std::string title, std::string author, std::string year, std::string status)
        : isbn(isbn), title(title), author(author), year(year), status(status) {}

    // (Not used directly in this project.)
    void addEntity() override {}
    void removeEntity() override {}

    void displayDetails() const override {
        std::cout << "ISBN: "   << isbn   << "\n"
                  << "Title: "  << title  << "\n"
                  << "Author: " << author << "\n"
                  << "Year: "   << year   << "\n"
                  << "Status: " << status << "\n";
    }
};