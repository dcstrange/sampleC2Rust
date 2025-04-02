#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"

#define MAX_BOOKS 1000

typedef struct {
    Book* books[MAX_BOOKS];
    int bookCount;
} Library;

// 图书馆管理相关函数声明
Library* createLibrary(void);
void destroyLibrary(Library* library);
int addBook(Library* library, Book* book);
int removeBook(Library* library, const char* isbn);
Book* findBookByISBN(Library* library, const char* isbn);
Book* findBookByTitle(Library* library, const char* title);
void listAllBooks(const Library* library);
int borrowBook(Library* library, const char* isbn);
int returnBook(Library* library, const char* isbn);
int getBookCount(const Library* library);
void sortBooksByTitle(Library* library);
void sortBooksByAuthor(Library* library);

#endif // LIBRARY_H 