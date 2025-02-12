// FileHandler.cpp
#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>

void loadBooks(std::vector<Book>& books, const std::string &filename) {
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Could not open " << filename << ". Starting with an empty book list.\n";
        return;
    }
    std::string line;
    // Skip header
    std::getline(file, line);
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string isbn, title, author, year, status;
        std::getline(ss, isbn, ',');
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, year, ',');
        std::getline(ss, status, ',');
        books.push_back(Book(isbn, title, author, year, status));
    }
    file.close();
}

void saveBooks(const std::vector<Book>& books, const std::string &filename) {
    std::ofstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error saving books to " << filename << "\n";
        return;
    }
    file << "ISBN,Title,Author,Year,Status\n";
    for(const auto &book : books) {
        file << book.isbn << "," << book.title << "," << book.author << ","
             << book.year << "," << book.status << "\n";
    }
    file.close();
}

void loadMembers(std::vector<Member>& members, const std::string &filename) {
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Could not open " << filename << ". Starting with an empty member list.\n";
        return;
    }
    std::string line;
    std::getline(file, line); // Skip header
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, name, contact, borrowed;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, contact, ',');
        std::getline(ss, borrowed, ',');
        Member m(name, id, contact);
        if(!borrowed.empty()){
            std::stringstream bss(borrowed);
            std::string isbn;
            while(std::getline(bss, isbn, ';')){
                m.borrowedBooks.push_back(isbn);
            }
        }
        members.push_back(m);
    }
    file.close();
}

void saveMembers(const std::vector<Member>& members, const std::string &filename) {
    std::ofstream file(filename);
    if(!file.is_open()){
        std::cerr << "Error saving members to " << filename << "\n";
        return;
    }
    file << "ID,Name,Contact,BorrowedBooks\n";
    for(const auto &member : members) {
        file << member.getId() << "," << member.getName() << "," << member.contact << ",";
        for(size_t i = 0; i < member.borrowedBooks.size(); i++){
            file << member.borrowedBooks[i];
            if(i != member.borrowedBooks.size()-1)
                file << ";";
        }
        file << "\n";
    }
    file.close();
}

void logTransaction(const std::string &memberId, const std::string &isbn, const std::string &action) {
    std::ofstream file("transactions.csv", std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error opening transactions file.\n";
        return;
    }
    std::time_t t = std::time(nullptr);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    file << memberId << "," << isbn << "," << action << "," << timeStr << "\n";
    file.close();
}
