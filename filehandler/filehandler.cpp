#include <fstream>    // For file operations
#include <sstream>    // For string stream operations
#include <iostream>   // For console I/O
#include <ctime>      // For time functions
#include "filehandler.h" // Include the header file

// Function to load book data from a CSV file into a vector of Book objects
void loadBooks(std::vector<Book> &books, const std::string &filename)
{
    std::ifstream file(filename); // Open the specified file for reading
    if (!file.is_open())          // Check if the file was successfully opened
    {
        std::cout << "Could not open " << filename << ". Starting with an empty book list.\n";
        return; // Exit the function if the file could not be opened
    }
    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line)) // Read file line by line
    {
        std::stringstream ss(line); // Create a stringstream from the line
        std::string isbn, title, author, year, status;
        std::getline(ss, isbn, ',');   // Extract ISBN
        std::getline(ss, title, ',');  // Extract Title
        std::getline(ss, author, ','); // Extract Author
        std::getline(ss, year, ',');   // Extract Year
        std::getline(ss, status, ','); // Extract Status
        books.push_back(Book(isbn, title, author, year, status)); // Create a Book object and add it to the vector
    }
    file.close(); // Close the file
}

// Function to save book data from a vector of Book objects to a CSV file
void saveBooks(const std::vector<Book> &books, const std::string &filename)
{
    std::ofstream file(filename); // Open the specified file for writing
    if (!file.is_open())          // Check if the file was successfully opened
    {
        std::cerr << "Error saving books to " << filename << "\n";
        return; // Exit the function if the file could not be opened
    }
    file << "ISBN,Title,Author,Year,Status\n"; // Write the header line
    for (const auto &book : books)              // Iterate through the vector of books
    {
        file << book.isbn << "," << book.title << "," << book.author << ","
             << book.year << "," << book.status << "\n"; // Write the book data to the file
    }
    file.close(); // Close the file
}

// Function to load member data from a CSV file into a vector of Member objects
void loadMembers(std::vector<Member> &members, const std::string &filename)
{
    std::ifstream file(filename); // Open the specified file for reading
    if (!file.is_open())          // Check if the file was successfully opened
    {
        std::cout << "Could not open " << filename << ". Starting with an empty member list.\n";
        return; // Exit the function if the file could not be opened
    }
    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) // Read file line by line
    {
        std::stringstream ss(line); // Create a stringstream from the line
        std::string id, name, contact, borrowed;
        std::getline(ss, id, ',');      // Extract ID
        std::getline(ss, name, ',');    // Extract Name
        std::getline(ss, contact, ','); // Extract Contact
        std::getline(ss, borrowed, ','); // Extract Borrowed books
        Member m(name, id, contact);    // Create a Member object
        if (!borrowed.empty())           // If the member has borrowed books
        {
            std::stringstream bss(borrowed);
            std::string isbn;
            while (std::getline(bss, isbn, ';')) // Extract ISBNs separated by semicolons
            {
                m.borrowedBooks.push_back(isbn); // Add the borrowed book to the member's list
            }
        }
        members.push_back(m); // Add the member to the vector
    }
    file.close(); // Close the file
}

// Function to save member data from a vector of Member objects to a CSV file
void saveMembers(const std::vector<Member> &members, const std::string &filename)
{
    std::ofstream file(filename); // Open the specified file for writing
    if (!file.is_open())          // Check if the file was successfully opened
    {
        std::cerr << "Error saving members to " << filename << "\n";
        return; // Exit the function if the file could not be opened
    }
    file << "ID,Name,Contact,BorrowedBooks\n"; // Write the header line
    for (const auto &member : members)              // Iterate through the vector of members
    {
        file << member.getId() << "," << member.getName() << "," << member.contact << ","; // Write member details
        for (size_t i = 0; i < member.borrowedBooks.size(); i++) // Iterate through the borrowed books
        {
            file << member.borrowedBooks[i]; // Write the ISBN of the borrowed book
            if (i != member.borrowedBooks.size() - 1)
                file << ";"; // Add a semicolon if it's not the last book
        }
        file << "\n"; // End the line
    }
    file.close(); // Close the file
}

// Function to log transactions to a CSV file
void logTransaction(const std::string &memberId, const std::string &isbn, const std::string &action)
{
    std::ofstream file("transactions.csv", std::ios::app); // Open the file in append mode
    if (!file.is_open())                                     // Check if the file was successfully opened
    {
        std::cerr << "Error opening transactions file.\n";
        return; // Exit the function if the file could not be opened
    }
    std::time_t t = std::time(nullptr); // Get the current time
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&t)); // Format the time
    file << memberId << "," << isbn << "," << action << "," << timeStr << "\n"; // Write the transaction data
    file.close(); // Close the file
}
