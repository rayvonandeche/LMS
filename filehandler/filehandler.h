// FileHandler.h
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
#include "Book.h"
#include "Person.h"

// Loads books from a CSV file into the provided vector.
void loadBooks(std::vector<Book>& books, const std::string &filename);

// Saves the books vector to a CSV file.
void saveBooks(const std::vector<Book>& books, const std::string &filename);

// Loads members from a CSV file into the provided vector.
void loadMembers(std::vector<Member>& members, const std::string &filename);

// Saves the members vector to a CSV file.
void saveMembers(const std::vector<Member>& members, const std::string &filename);

// Logs a transaction (borrow/return) to a CSV file.
void logTransaction(const std::string &memberId, const std::string &isbn, const std::string &action);

#endif // FILEHANDLER_H