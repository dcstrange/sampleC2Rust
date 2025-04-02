#ifndef BOOK_H
#define BOOK_H

#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 50
#define MAX_ISBN_LEN 13

typedef struct {
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    char isbn[MAX_ISBN_LEN];
    int year;
    float price;
    int available;
} Book;

// 图书相关函数声明
Book* createBook(const char* title, const char* author, const char* isbn, int year, float price);
void destroyBook(Book* book);
void printBook(const Book* book);
int updateBookPrice(Book* book, float newPrice);
int updateBookYear(Book* book, int newYear);
int isBookAvailable(const Book* book);
void setBookAvailability(Book* book, int available);
const char* getBookTitle(const Book* book);
const char* getBookAuthor(const Book* book);
const char* getBookISBN(const Book* book);

#endif // BOOK_H 