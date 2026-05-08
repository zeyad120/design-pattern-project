#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <vector>
#include <mutex>
#include "Book.h"
#include "SearchStrategy.h"

// Singleton Pattern
class LibraryManager {
private:
    static LibraryManager* instance;
    static std::mutex mutex;
    std::vector<Book*> books;
    SearchStrategy* searchStrategy;

    LibraryManager() : searchStrategy(nullptr) {}

public:
    // Delete copy constructor and assignment operator
    LibraryManager(const LibraryManager&) = delete;
    void operator=(const LibraryManager&) = delete;

    static LibraryManager* getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (instance == nullptr) {
            instance = new LibraryManager();
        }
        return instance;
    }

    void addBook(Book* book) {
        books.push_back(book);
    }

    const std::vector<Book*>& getBooks() const {
        return books;
    }

    void setSearchStrategy(SearchStrategy* strategy) {
        if (searchStrategy) delete searchStrategy;
        searchStrategy = strategy;
    }

    std::vector<Book*> searchBooks(const std::string& query) {
        if (searchStrategy) {
            return searchStrategy->search(books, query);
        }
        return {};
    }

    Book* findBookByTitle(const std::string& title) {
        for (auto book : books) {
            if (book->getTitle() == title) return book;
        }
        return nullptr;
    }

    ~LibraryManager() {
        for (auto book : books) delete book;
        if (searchStrategy) delete searchStrategy;
    }
};

#endif
