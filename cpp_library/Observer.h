#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <iostream>
#include <vector>

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void update(const std::string& bookTitle) = 0;
    virtual std::string getName() const = 0;
};

class User : public IObserver {
private:
    std::string name;
public:
    User(std::string n) : name(n) {}
    void update(const std::string& bookTitle) override {
        std::cout << "Notification for " << name << ": The book '"
                  << bookTitle << "' is now available!" << std::endl;
    }
    std::string getName() const override { return name; }
};

#endif
