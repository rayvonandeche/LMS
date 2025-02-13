#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
// Custom module includes for system functionality
#include "FileHandler/filehandler.h"  // Handles file I/O operations
#include "Person/Person.h"            // Contains Person and Member classes
#include "Book/Book.h"               // Contains Book class definition
#include "Menu/menu.h"               // Contains menu handling functions

int main() {
    // Initialize containers for storing library data
    std::vector<Book> books;      // Container for all books in the library
    std::vector<Member> members;   // Container for all registered members
    
    // Initialize system by loading data from persistent storage
    loadBooks(books, "books.csv");      // Load book records
    loadMembers(members, "members.csv"); // Load member records

    int choice;
    // Main program loop - continues until user chooses to exit
    while (true) {
        // Display main menu interface
        std::cout << "\n=== Library Management System ===\n";
        std::cout << "1. Login as Admin\n";
        std::cout << "2. Login as Member\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer

        if (choice == 1) {
            // Administrator Authentication
            std::string username, password;
            std::cout << "Enter admin username: ";
            std::getline(std::cin, username);
            std::cout << "Enter admin password: ";
            std::getline(std::cin, password);
            
            // Verify admin credentials
            if (username == "admin" && password == "admin123") {
                std::cout << "Admin login successful!\n";
                adminMenu(books, members);        // Launch admin interface
                // Save changes after admin operations
                saveBooks(books, "books.csv");
                saveMembers(members, "members.csv");
            } else {
                std::cout << "Invalid admin credentials!\n";
            }
        } else if (choice == 2) {
            // Member Authentication
            std::string memberId;
            std::cout << "Enter Member ID: ";
            std::getline(std::cin, memberId);
            
            // Search for member in the system
            auto it = std::find_if(members.begin(), members.end(), 
                [&](const Member &m) { return m.getId() == memberId; });
            
            if (it != members.end()) {
                std::cout << "Welcome " << it->getName() << "!\n";
                memberMenu(*it, books);           // Launch member interface
                // Save changes after member operations
                saveBooks(books, "books.csv");
                saveMembers(members, "members.csv");
            } else {
                std::cout << "Member not found!\n";
            }
        } else if (choice == 3) {
            // Exit the system
            std::cout << "Exiting the system. Goodbye!\n";
            break;
        } else {
            // Handle invalid menu selections
            std::cout << "Invalid choice!\n";
        }
    }
    return 0;
}
