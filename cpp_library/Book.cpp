#include "Book.h"
#include "Observer.h"

void Book::setAvailability(bool status) {
    bool wasBorrowed = !isAvailable;
    isAvailable = status;
    if (wasBorrowed && isAvailable) {
        notifyObservers();
    }
}

void Book::addObserver(IObserver* observer) {
    observers.push_back(observer);
}

void Book::removeObserver(IObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Book::notifyObservers() {
    for (IObserver* observer : observers) {
        observer->update(title);
    }
}
