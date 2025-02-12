// main.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "FileHandler/filehandler.h"
#include "Person/Person.h"
#include "Book/Book.h"
#include "Menu/menu.h"

int main() {
    std::vector<Book> books;
    std::vector<Member> members;
    
    // Load persistent data from CSV files.
    loadBooks(books, "books.csv");
    loadMembers(members, "members.csv");

    int choice;
    while (true) {
        std::cout << "\n=== Library Management System ===\n";
        std::cout << "1. Login as Admin\n";
        std::cout << "2. Login as Member\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // clear newline

        if (choice == 1) {
            // Simple hard-coded admin credentials.
            std::string username, password;
            std::cout << "Enter admin username: ";
            std::getline(std::cin, username);
            std::cout << "Enter admin password: ";
            std::getline(std::cin, password);
            if (username == "admin" && password == "admin123") {
                std::cout << "Admin login successful!\n";
                adminMenu(books, members);
                saveBooks(books, "books.csv");
                saveMembers(members, "members.csv");
            } else {
                std::cout << "Invalid admin credentials!\n";
            }
        } else if (choice == 2) {
            std::string memberId;
            std::cout << "Enter Member ID: ";
            std::getline(std::cin, memberId);
            auto it = std::find_if(members.begin(), members.end(), [&](const Member &m) {
                return m.getId() == memberId;
            });
            if (it != members.end()) {
                std::cout << "Welcome " << it->getName() << "!\n";
                memberMenu(*it, books);
                saveBooks(books, "books.csv");
                saveMembers(members, "members.csv");
            } else {
                std::cout << "Member not found!\n";
            }
        } else if (choice == 3) {
            std::cout << "Exiting the system. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice!\n";
        }
    }
    return 0;
}
