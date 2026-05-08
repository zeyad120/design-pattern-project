#ifndef BOOKDECORATOR_H
#define BOOKDECORATOR_H

#include "Book.h"

// Decorator Pattern
class BookDecorator : public Book {
protected:
    Book* decoratedBook;

public:
    BookDecorator(Book* book)
        : Book(book->getTitle(), book->getAuthor(), book->getCategory()), decoratedBook(book) {}

    virtual void displayInfo() const override {
        decoratedBook->displayInfo();
    }

    std::string getType() const override {
        return decoratedBook->getType();
    }
};

class FeaturedBook : public BookDecorator {
public:
    FeaturedBook(Book* book) : BookDecorator(book) {}

    void displayInfo() const override {
        std::cout << "[FEATURED] ";
        BookDecorator::displayInfo();
    }
};

class DiscountedBook : public BookDecorator {
public:
    DiscountedBook(Book* book) : BookDecorator(book) {}

    void displayInfo() const override {
        std::cout << "[DISCOUNTED] ";
        BookDecorator::displayInfo();
    }
};

class HighlightedBook : public BookDecorator {
public:
    HighlightedBook(Book* book) : BookDecorator(book) {}

    void displayInfo() const override {
        std::cout << ">>> ";
        BookDecorator::displayInfo();
    }
};

#endif
