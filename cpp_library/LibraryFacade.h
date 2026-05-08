#ifndef LIBRARYFACADE_H
#define LIBRARYFACADE_H

#include "LibraryManager.h"
#include "BookFactory.h"
#include "BookDecorator.h"
#include "Observer.h"
#include <iostream>

// Facade Pattern
class LibraryFacade {
private:
    LibraryManager* manager;

public:
    LibraryFacade() {
        manager = LibraryManager::getInstance();
    }

    void addBook(BookFactory::BookType type, std::string title, std::string author, std::string category) {
        Book* book = BookFactory::createBook(type, title, author, category);
        manager->addBook(book);
        std::cout << "Added: " << title << " to the library." << std::endl;
    }

    void borrowBook(std::string title, User* user) {
        Book* book = manager->findBookByTitle(title);
        if (book) {
            if (book->getAvailability()) {
                book->setAvailability(false);
                std::cout << user->getName() << " borrowed '" << title << "'." << std::endl;
            } else {
                std::cout << "'" << title << "' is currently unavailable. Adding " << user->getName() << " to the waiting list." << std::endl;
                book->addObserver(user);
            }
        } else {
            std::cout << "Book '" << title << "' not found." << std::endl;
        }
    }

    void returnBook(std::string title) {
        Book* book = manager->findBookByTitle(title);
        if (book) {
            book->setAvailability(true);
            std::cout << "Book '" << title << "' has been returned." << std::endl;
        }
    }

    void searchByTitle(std::string query) {
        manager->setSearchStrategy(new TitleSearch());
        displaySearchResults(manager->searchBooks(query));
    }

    void searchByAuthor(std::string query) {
        manager->setSearchStrategy(new AuthorSearch());
        displaySearchResults(manager->searchBooks(query));
    }

    void searchByCategory(std::string query) {
        manager->setSearchStrategy(new CategorySearch());
        displaySearchResults(manager->searchBooks(query));
    }

    void displayAllBooks() {
        std::cout << "\n--- Library Catalog ---" << std::endl;
        for (auto book : manager->getBooks()) {
            book->displayInfo();
        }
        std::cout << "-----------------------\n" << std::endl;
    }

private:
    void displaySearchResults(const std::vector<Book*>& results) {
        std::cout << "\n--- Search Results ---" << std::endl;
        if (results.empty()) {
            std::cout << "No books found." << std::endl;
        } else {
            for (auto book : results) {
                book->displayInfo();
            }
        }
        std::cout << "----------------------\n" << std::endl;
    }
};

#endif
