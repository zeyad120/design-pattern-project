#ifndef BOOKFACTORY_H
#define BOOKFACTORY_H

#include "Book.h"
#include <memory>

// Factory Pattern
class BookFactory {
public:
    enum BookType { PHYSICAL, EBOOK, AUDIOBOOK };

    static Book* createBook(BookType type, std::string title, std::string author, std::string category) {
        switch (type) {
            case PHYSICAL: return new PhysicalBook(title, author, category);
            case EBOOK:    return new EBook(title, author, category);
            case AUDIOBOOK: return new AudioBook(title, author, category);
            default: return nullptr;
        }
    }
};

#endif
