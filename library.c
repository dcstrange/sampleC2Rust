#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

Library* createLibrary(void) {
    Library* library = (Library*)malloc(sizeof(Library));
    if (library == NULL) return NULL;
    
    library->bookCount = 0;
    for (int i = 0; i < MAX_BOOKS; i++) {
        library->books[i] = NULL;
    }
    
    return library;
}

void destroyLibrary(Library* library) {
    if (library == NULL) return;
    
    for (int i = 0; i < library->bookCount; i++) {
        destroyBook(library->books[i]);
    }
    free(library);
}

int addBook(Library* library, Book* book) {
    if (library == NULL || book == NULL || library->bookCount >= MAX_BOOKS) {
        return 0;
    }
    
    library->books[library->bookCount++] = book;
    return 1;
}

int removeBook(Library* library, const char* isbn) {
    if (library == NULL || isbn == NULL) return 0;
    
    for (int i = 0; i < library->bookCount; i++) {
        if (strcmp(library->books[i]->isbn, isbn) == 0) {
            destroyBook(library->books[i]);
            for (int j = i; j < library->bookCount - 1; j++) {
                library->books[j] = library->books[j + 1];
            }
            library->bookCount--;
            return 1;
        }
    }
    return 0;
}

Book* findBookByISBN(Library* library, const char* isbn) {
    if (library == NULL || isbn == NULL) return NULL;
    
    for (int i = 0; i < library->bookCount; i++) {
        if (strcmp(library->books[i]->isbn, isbn) == 0) {
            return library->books[i];
        }
    }
    return NULL;
}

Book* findBookByTitle(Library* library, const char* title) {
    if (library == NULL || title == NULL) return NULL;
    
    for (int i = 0; i < library->bookCount; i++) {
        if (strstr(library->books[i]->title, title) != NULL) {
            return library->books[i];
        }
    }
    return NULL;
}

void listAllBooks(const Library* library) {
    if (library == NULL) {
        printf("图书馆不存在\n");
        return;
    }
    
    printf("图书馆藏书列表（共%d本）：\n", library->bookCount);
    for (int i = 0; i < library->bookCount; i++) {
        printf("\n--- 第%d本书 ---\n", i + 1);
        printBook(library->books[i]);
    }
}

int borrowBook(Library* library, const char* isbn) {
    Book* book = findBookByISBN(library, isbn);
    if (book == NULL || !isBookAvailable(book)) {
        return 0;
    }
    
    setBookAvailability(book, 0);
    return 1;
}

int returnBook(Library* library, const char* isbn) {
    Book* book = findBookByISBN(library, isbn);
    if (book == NULL || isBookAvailable(book)) {
        return 0;
    }
    
    setBookAvailability(book, 1);
    return 1;
}

int getBookCount(const Library* library) {
    return library != NULL ? library->bookCount : 0;
}

static int compareByTitle(const void* a, const void* b) {
    return strcmp((*(Book**)a)->title, (*(Book**)b)->title);
}

static int compareByAuthor(const void* a, const void* b) {
    return strcmp((*(Book**)a)->author, (*(Book**)b)->author);
}

void sortBooksByTitle(Library* library) {
    if (library == NULL) return;
    qsort(library->books, library->bookCount, sizeof(Book*), compareByTitle);
}

void sortBooksByAuthor(Library* library) {
    if (library == NULL) return;
    qsort(library->books, library->bookCount, sizeof(Book*), compareByAuthor);
} 