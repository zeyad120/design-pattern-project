#include "LibraryFacade.h"
#include "Observer.h"

int main() {
    LibraryFacade library;

    // 1. Factory Pattern: Adding different types of books
    library.addBook(BookFactory::PHYSICAL, "The C++ Programming Language", "Bjarne Stroustrup", "Programming");
    library.addBook(BookFactory::EBOOK, "Design Patterns", "Gang of Four", "Software Engineering");
    library.addBook(BookFactory::AUDIOBOOK, "Clean Code", "Robert C. Martin", "Programming");

    // 2. Decorator Pattern: Adding features to a book
    // Note: In a real system, you might wrap the book object.
    // Here we'll just demonstrate it by creating a decorated instance if needed,
    // but for simplicity, let's just show the catalog.
    library.displayAllBooks();

    // 3. Strategy Pattern: Searching
    std::cout << "Searching for books by 'Robert'..." << std::endl;
    library.searchByAuthor("Robert");

    std::cout << "Searching for 'Engineering' category..." << std::endl;
    library.searchByCategory("Engineering");

    // 4. Observer Pattern: Notifying users
    User* user1 = new User("Alice");
    User* user2 = new User("Bob");

    std::cout << "Alice tries to borrow 'Design Patterns'..." << std::endl;
    library.borrowBook("Design Patterns", user1);

    std::cout << "\nBob tries to borrow 'Design Patterns' (but it's taken)..." << std::endl;
    library.borrowBook("Design Patterns", user2);

    std::cout << "\nAlice returns 'Design Patterns'..." << std::endl;
    library.returnBook("Design Patterns"); // This should notify Bob

    // Clean up
    delete user1;
    delete user2;

    return 0;
}
