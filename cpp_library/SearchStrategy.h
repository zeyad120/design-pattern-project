#ifndef SEARCHSTRATEGY_H
#define SEARCHSTRATEGY_H

#include "Book.h"
#include <vector>
#include <string>

// Strategy Pattern
class SearchStrategy {
public:
    virtual ~SearchStrategy() {}
    virtual std::vector<Book*> search(const std::vector<Book*>& books, const std::string& query) = 0;
};

class TitleSearch : public SearchStrategy {
public:
    std::vector<Book*> search(const std::vector<Book*>& books, const std::string& query) override {
        std::vector<Book*> results;
        for (auto book : books) {
            if (book->getTitle().find(query) != std::string::npos) {
                results.push_back(book);
            }
        }
        return results;
    }
};

class AuthorSearch : public SearchStrategy {
public:
    std::vector<Book*> search(const std::vector<Book*>& books, const std::string& query) override {
        std::vector<Book*> results;
        for (auto book : books) {
            if (book->getAuthor().find(query) != std::string::npos) {
                results.push_back(book);
            }
        }
        return results;
    }
};

class CategorySearch : public SearchStrategy {
public:
    std::vector<Book*> search(const std::vector<Book*>& books, const std::string& query) override {
        std::vector<Book*> results;
        for (auto book : books) {
            if (book->getCategory().find(query) != std::string::npos) {
                results.push_back(book);
            }
        }
        return results;
    }
};

#endif
