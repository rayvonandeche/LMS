#include <iostream>
#include <algorithm>
#include "Menu.h"
#include "FileHandler.h"

void adminMenu(std::vector<Book>& books, std::vector<Member>& members) {
    int choice;
    while (true) {
        std::cout << "\n--- Admin Menu ---\n";
        std::cout << "1. Manage Books\n";
        std::cout << "2. Manage Members\n";
        std::cout << "3. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // clear newline

        if (choice == 1) { // Manage Books
            int bookChoice;
            std::cout << "\n--- Books Management ---\n";
            std::cout << "1. Add Book\n";
            std::cout << "2. View Books\n";
            std::cout << "3. Update Book\n";
            std::cout << "4. Delete Book\n";
            std::cout << "5. Back\n";
            std::cout << "Enter your choice: ";
            std::cin >> bookChoice;
            std::cin.ignore();
            if (bookChoice == 1) {
                std::string isbn, title, author, year;
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                std::cout << "Enter Title: ";
                std::getline(std::cin, title);
                std::cout << "Enter Author: ";
                std::getline(std::cin, author);
                std::cout << "Enter Year: ";
                std::getline(std::cin, year);
                books.push_back(Book(isbn, title, author, year, "Available"));
                std::cout << "Book added successfully!\n";
                saveBooks(books, "books.csv");
            } else if (bookChoice == 2) {
                std::cout << "\n--- List of Books ---\n";
                for (const auto &book : books) {
                    book.displayDetails();
                    std::cout << "-----------------\n";
                }
            } else if (bookChoice == 3) {
                std::string isbn;
                std::cout << "Enter ISBN of the book to update: ";
                std::getline(std::cin, isbn);
                bool found = false;
                for (auto &book : books) {
                    if (book.isbn == isbn) {
                        found = true;
                        std::string newTitle, newAuthor, newYear, newStatus;
                        std::cout << "Enter new Title (leave blank to keep current): ";
                        std::getline(std::cin, newTitle);
                        std::cout << "Enter new Author (leave blank to keep current): ";
                        std::getline(std::cin, newAuthor);
                        std::cout << "Enter new Year (leave blank to keep current): ";
                        std::getline(std::cin, newYear);
                        std::cout << "Enter new Status (Available/Borrowed, leave blank to keep current): ";
                        std::getline(std::cin, newStatus);
                        if (!newTitle.empty())  book.title  = newTitle;
                        if (!newAuthor.empty()) book.author = newAuthor;
                        if (!newYear.empty())   book.year   = newYear;
                        if (!newStatus.empty()) book.status = newStatus;
                        std::cout << "Book updated successfully!\n";
                        break;
                    }
                }
                if (!found)
                    std::cout << "Book not found!\n";
                saveBooks(books, "books.csv");
            } else if (bookChoice == 4) {
                std::string isbn;
                std::cout << "Enter ISBN of the book to delete: ";
                std::getline(std::cin, isbn);
                auto it = std::remove_if(books.begin(), books.end(), [&](const Book &b) {
                    return b.isbn == isbn;
                });
                if (it != books.end()) {
                    books.erase(it, books.end());
                    std::cout << "Book deleted successfully!\n";
                } else {
                    std::cout << "Book not found!\n";
                }
                saveBooks(books, "books.csv");
            } else if (bookChoice == 5) {
                continue; // Back to Admin Menu
            } else {
                std::cout << "Invalid choice!\n";
            }
        } else if (choice == 2) { // Manage Members
            int memberChoice;
            std::cout << "\n--- Members Management ---\n";
            std::cout << "1. Add Member\n";
            std::cout << "2. View Members\n";
            std::cout << "3. Update Member\n";
            std::cout << "4. Delete Member\n";
            std::cout << "5. Back\n";
            std::cout << "Enter your choice: ";
            std::cin >> memberChoice;
            std::cin.ignore();
            if (memberChoice == 1) {
                std::string id, name, contact;
                std::cout << "Enter Member ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Contact: ";
                std::getline(std::cin, contact);
                members.push_back(Member(name, id, contact));
                std::cout << "Member added successfully!\n";
                saveMembers(members, "members.csv");
            } else if (memberChoice == 2) {
                std::cout << "\n--- List of Members ---\n";
                for (const auto &member : members) {
                    member.displayDetails();
                    std::cout << "-----------------\n";
                }
            } else if (memberChoice == 3) {
                std::string id;
                std::cout << "Enter Member ID to update: ";
                std::getline(std::cin, id);
                bool found = false;
                for (auto &member : members) {
                    if (member.getId() == id) {
                        found = true;
                        std::string newName, newContact;
                        std::cout << "Enter new Name (leave blank to keep current): ";
                        std::getline(std::cin, newName);
                        std::cout << "Enter new Contact (leave blank to keep current): ";
                        std::getline(std::cin, newContact);
                        if (!newName.empty())  member.setName(newName);
                        if (!newContact.empty()) member.contact = newContact;
                        std::cout << "Member updated successfully!\n";
                        break;
                    }
                }
                if (!found)
                    std::cout << "Member not found!\n";
                saveMembers(members, "members.csv");
            } else if (memberChoice == 4) {
                std::string id;
                std::cout << "Enter Member ID to delete: ";
                std::getline(std::cin, id);
                auto it = std::remove_if(members.begin(), members.end(), [&](const Member &m) {
                    return m.getId() == id;
                });
                if (it != members.end()) {
                    members.erase(it, members.end());
                    std::cout << "Member deleted successfully!\n";
                } else {
                    std::cout << "Member not found!\n";
                }
                saveMembers(members, "members.csv");
            } else if (memberChoice == 5) {
                continue; // Back to Admin Menu
            } else {
                std::cout << "Invalid choice!\n";
            }
        } else if (choice == 3) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid choice!\n";
        }
    }
}

void memberMenu(Member &member, std::vector<Book>& books) {
    int choice;
    while (true) {
        std::cout << "\n--- Member Menu ---\n";
        std::cout << "1. View Books\n";
        std::cout << "2. Borrow Book\n";
        std::cout << "3. Return Book\n";
        std::cout << "4. View Borrowed Books\n";
        std::cout << "5. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 1) {
            std::cout << "\n--- List of Books ---\n";
            for (const auto &book : books) {
                book.displayDetails();
                std::cout << "-----------------\n";
            }
        } else if (choice == 2) {
            std::string isbn;
            std::cout << "Enter ISBN of the book to borrow: ";
            std::getline(std::cin, isbn);
            try {
                member.borrowBook(books, isbn);
                logTransaction(member.getId(), isbn, "borrow");
            } catch (const std::runtime_error &e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } else if (choice == 3) {
            std::string isbn;
            std::cout << "Enter ISBN of the book to return: ";
            std::getline(std::cin, isbn);
            try {
                member.returnBook(books, isbn);
                logTransaction(member.getId(), isbn, "return");
            } catch (const std::runtime_error &e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        } else if (choice == 4) {
            std::cout << "\n--- Borrowed Books ---\n";
            if (member.borrowedBooks.empty())
                std::cout << "No borrowed books.\n";
            else {
                for (const auto &isbn : member.borrowedBooks)
                    std::cout << "ISBN: " << isbn << "\n";
            }
        } else if (choice == 5) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid choice!\n";
        }
    }
}
