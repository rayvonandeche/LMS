#ifndef MENU_H
#define MENU_H

#include <vector>
#include "Book.h"
#include "Person.h"

// Prototypes for CLI menu functions.
void adminMenu(std::vector<Book>& books, std::vector<Member>& members);
void memberMenu(Member &member, std::vector<Book>& books);

#endif 
