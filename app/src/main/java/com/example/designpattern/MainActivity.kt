package com.example.designpattern

import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.designpattern.logic.Book
import com.example.designpattern.logic.LibraryFacade
import com.example.designpattern.logic.User
import com.example.designpattern.ui.theme.DesignPatternTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            DesignPatternTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    LibraryScreen()
                }
            }
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun LibraryScreen() {
    val context = LocalContext.current
    val facade = remember { 
        LibraryFacade { message -> 
            Toast.makeText(context, message, Toast.LENGTH_SHORT).show()
        } 
    }
    
    // Initial setup
    LaunchedEffect(Unit) {
        facade.setupInitialBooks()
    }

    val books = facade.getAllBooks()
    val currentUser = remember { User("Alice") { msg ->
        Toast.makeText(context, "NOTIFICATION: $msg", Toast.LENGTH_LONG).show()
    }}

    Scaffold(
        topBar = {
            TopAppBar(title = { Text("Smart Library System") })
        }
    ) { padding ->
        Column(modifier = Modifier.padding(padding).padding(16.dp)) {
            Text(
                "Design Patterns Demo", 
                fontSize = 20.sp, 
                fontWeight = FontWeight.Bold,
                color = MaterialTheme.colorScheme.primary
            )
            Spacer(modifier = Modifier.height(8.dp))
            Text("Patterns: Singleton, Factory, Observer, Strategy, Facade", fontSize = 12.sp)
            
            HorizontalDivider(modifier = Modifier.padding(vertical = 12.dp))

            LazyColumn(verticalArrangement = Arrangement.spacedBy(8.dp)) {
                items(books) { book ->
                    BookItem(
                        book = book,
                        onBorrow = { facade.borrowBook(book.title, currentUser) },
                        onReturn = { facade.returnBook(book.title) }
                    )
                }
            }
        }
    }
}

@Composable
fun BookItem(book: Book, onBorrow: () -> Unit, onReturn: () -> Unit) {
    Card(
        modifier = Modifier.fillMaxWidth(),
        elevation = CardDefaults.cardElevation(defaultElevation = 2.dp)
    ) {
        Row(
            modifier = Modifier.padding(16.dp).fillMaxWidth(),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Column(modifier = Modifier.weight(1f)) {
                Text(book.title, fontWeight = FontWeight.Bold, fontSize = 16.sp)
                Text("${book.getType()} | ${book.author}", fontSize = 14.sp, color = Color.Gray)
                Text(
                    if (book.isAvailable) "Available" else "Borrowed",
                    color = if (book.isAvailable) Color(0xFF4CAF50) else Color.Red,
                    fontSize = 12.sp,
                    fontWeight = FontWeight.Bold
                )
            }
            
            if (book.isAvailable) {
                Button(onClick = onBorrow) {
                    Text("Borrow")
                }
            } else {
                Button(
                    onClick = onReturn,
                    colors = ButtonDefaults.buttonColors(containerColor = MaterialTheme.colorScheme.secondary)
                ) {
                    Text("Return")
                }
            }
        }
    }
}
