package com.example.designpattern.logic

import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue

// --- Base Book and Factory (Factory Pattern) ---
sealed class Book(
    val title: String,
    val author: String,
    val category: String,
    initialAvailable: Boolean = true
) {
    var isAvailable by mutableStateOf(initialAvailable)
    private val observers = mutableListOf<UserObserver>()

    abstract fun getType(): String

    fun addObserver(observer: UserObserver) {
        if (!observers.contains(observer)) observers.add(observer)
    }

    fun notifyObservers() {
        observers.forEach { it.update(title) }
        observers.clear()
    }

    fun setAvailability(status: Boolean) {
        val wasBorrowed = !isAvailable
        isAvailable = status
        if (wasBorrowed && isAvailable) {
            notifyObservers()
        }
    }
}

class PhysicalBook(title: String, author: String, category: String) : Book(title, author, category) {
    override fun getType() = "Physical"
}

class EBook(title: String, author: String, category: String) : Book(title, author, category) {
    override fun getType() = "E-Book"
}

class AudioBook(title: String, author: String, category: String) : Book(title, author, category) {
    override fun getType() = "Audio Book"
}

object BookFactory {
    enum class Type { PHYSICAL, EBOOK, AUDIOBOOK }
    fun createBook(type: Type, title: String, author: String, category: String): Book {
        return when (type) {
            Type.PHYSICAL -> PhysicalBook(title, author, category)
            Type.EBOOK -> EBook(title, author, category)
            Type.AUDIOBOOK -> AudioBook(title, author, category)
        }
    }
}

// --- Observer Pattern ---
interface UserObserver {
    fun update(bookTitle: String)
}

class User(val name: String, val onNotify: (String) -> Unit) : UserObserver {
    override fun update(bookTitle: String) {
        onNotify("Hi $name, '$bookTitle' is now available!")
    }
}

// --- Strategy Pattern ---
interface SearchStrategy {
    fun search(books: List<Book>, query: String): List<Book>
}

class TitleSearch : SearchStrategy {
    override fun search(books: List<Book>, query: String) = books.filter { it.title.contains(query, ignoreCase = true) }
}

class AuthorSearch : SearchStrategy {
    override fun search(books: List<Book>, query: String) = books.filter { it.author.contains(query, ignoreCase = true) }
}

// --- Decorator Pattern ---
// In Kotlin/Compose, we can use a simpler approach for "decorating" UI, 
// but let's keep the logic structure.
interface BookDisplay {
    fun getLabel(): String
}

class FeaturedDecorator(val book: Book) : BookDisplay {
    override fun getLabel() = "FEATURED"
}

// --- Singleton Pattern ---
class LibraryManager private constructor() {
    val books = mutableStateListOf<Book>()
    var searchStrategy: SearchStrategy = TitleSearch()

    companion object {
        private var instance: LibraryManager? = null
        fun getInstance(): LibraryManager {
            if (instance == null) instance = LibraryManager()
            return instance!!
        }
    }

    fun addBook(book: Book) = books.add(book)
    
    fun search(query: String): List<Book> = searchStrategy.search(books, query)
}

// --- Facade Pattern ---
class LibraryFacade(val onLog: (String) -> Unit) {
    private val manager = LibraryManager.getInstance()

    fun setupInitialBooks() {
        if (manager.books.isEmpty()) {
            manager.addBook(BookFactory.createBook(BookFactory.Type.PHYSICAL, "The C++ Programming Language", "Bjarne Stroustrup", "Programming"))
            manager.addBook(BookFactory.createBook(BookFactory.Type.EBOOK, "Design Patterns", "GoF", "Software Engineering"))
            manager.addBook(BookFactory.createBook(BookFactory.Type.AUDIOBOOK, "Clean Code", "Robert C. Martin", "Programming"))
        }
    }

    fun borrowBook(title: String, user: User) {
        val book = manager.books.find { it.title == title }
        if (book != null) {
            if (book.isAvailable) {
                book.setAvailability(false)
                onLog("${user.name} borrowed '$title'")
            } else {
                book.addObserver(user)
                onLog("'$title' is busy. ${user.name} added to waitlist.")
            }
        }
    }

    fun returnBook(title: String) {
        manager.books.find { it.title == title }?.setAvailability(true)
        onLog("Returned '$title'")
    }

    fun getAllBooks() = manager.books
}
