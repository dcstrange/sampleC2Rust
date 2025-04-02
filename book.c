#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

Book* createBook(const char* title, const char* author, const char* isbn, int year, float price) {
    Book* book = (Book*)malloc(sizeof(Book));
    if (book == NULL) return NULL;

    strncpy(book->title, title, MAX_TITLE_LEN - 1);
    strncpy(book->author, author, MAX_AUTHOR_LEN - 1);
    strncpy(book->isbn, isbn, MAX_ISBN_LEN - 1);
    book->year = year;
    book->price = price;
    book->available = 1;

    return book;
}

void destroyBook(Book* book) {
    if (book != NULL) {
        free(book);
    }
}

void printBook(const Book* book) {
    if (book == NULL) {
        printf("无效的图书信息\n");
        return;
    }
    printf("书名: %s\n", book->title);
    printf("作者: %s\n", book->author);
    printf("ISBN: %s\n", book->isbn);
    printf("出版年份: %d\n", book->year);
    printf("价格: %.2f\n", book->price);
    printf("状态: %s\n", book->available ? "可借" : "已借出");
}

int updateBookPrice(Book* book, float newPrice) {
    if (book == NULL || newPrice < 0) return 0;
    book->price = newPrice;
    return 1;
}

int updateBookYear(Book* book, int newYear) {
    if (book == NULL || newYear < 1800 || newYear > 2024) return 0;
    book->year = newYear;
    return 1;
}

int isBookAvailable(const Book* book) {
    return book != NULL && book->available;
}

void setBookAvailability(Book* book, int available) {
    if (book != NULL) {
        book->available = available;
    }
}

const char* getBookTitle(const Book* book) {
    return book != NULL ? book->title : NULL;
}

const char* getBookAuthor(const Book* book) {
    return book != NULL ? book->author : NULL;
}

const char* getBookISBN(const Book* book) {
    return book != NULL ? book->isbn : NULL;
} 