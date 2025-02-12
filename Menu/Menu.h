#pragma once
#include <vector>
#include "../Book/book.h"
#include "../Person/person.h"

// Prototypes for CLI menu functions.
void adminMenu(std::vector<Book>& books, std::vector<Member>& members);
void memberMenu(Member &member, std::vector<Book>& books);
