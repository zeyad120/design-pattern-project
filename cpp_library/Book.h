#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Observer Pattern: Forward declaration
class IObserver;

class Book {
protected:
    std::string title;
    std::string author;
    std::string category;
    bool isAvailable;
    std::vector<IObserver*> observers;

public:
    Book(std::string t, std::string a, std::string c)
        : title(t), author(a), category(c), isAvailable(true) {}

    virtual ~Book() {}

    virtual void displayInfo() const {
        std::cout << "[" << getType() << "] " << title << " by " << author
                  << " (" << category << ") - "
                  << (isAvailable ? "Available" : "Borrowed") << std::endl;
    }

    virtual std::string getType() const = 0;

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getCategory() const { return category; }
    bool getAvailability() const { return isAvailable; }

    void setAvailability(bool status);

    void addObserver(IObserver* observer);
    void removeObserver(IObserver* observer);
    void notifyObservers();
};

class PhysicalBook : public Book {
public:
    PhysicalBook(std::string t, std::string a, std::string c) : Book(t, a, c) {}
    std::string getType() const override { return "Physical Book"; }
};

class EBook : public Book {
public:
    EBook(std::string t, std::string a, std::string c) : Book(t, a, c) {}
    std::string getType() const override { return "E-Book"; }
};

class AudioBook : public Book {
public:
    AudioBook(std::string t, std::string a, std::string c) : Book(t, a, c) {}
    std::string getType() const override { return "Audio Book"; }
};

#endif
