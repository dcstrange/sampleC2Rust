/* {
    "File": "book.c",
    "Purpose": "实现图书管理系统中的图书相关功能",
    "Implementation": {
        "MemoryManagement": {
            "createBook": "动态分配内存并初始化图书对象",
            "destroyBook": "安全释放图书对象内存"
        },
        "DataValidation": {
            "updateBookPrice": "确保价格非负",
            "updateBookYear": "确保年份在合理范围内(1800-2024)",
            "setBookAvailability": "安全设置可用性状态"
        },
        "StringHandling": {
            "createBook": "使用strncpy安全复制字符串",
            "getBookTitle/Author/ISBN": "提供只读访问接口"
        }
    },
    "Dependencies": {
        "StandardLibraries": ["stdio.h", "stdlib.h", "string.h"],
        "CustomHeaders": ["book.h"]
    }
} */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

/* {
    "What": "创建新的图书对象并初始化所有字段",
    "When": "需要添加新书到系统时",
    "Why": "提供统一的图书对象创建接口，确保所有必要字段都被正确初始化",
    "How": "动态分配内存，使用strncpy安全复制字符串，初始化其他字段"
} */
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

/* {
    "What": "销毁图书对象并释放内存",
    "When": "图书对象不再需要时",
    "Why": "防止内存泄漏，确保系统资源被正确释放",
    "How": "检查指针非空后释放内存"
} */
void destroyBook(Book* book) {
    if (book != NULL) {
        free(book);
    }
}

/* {
    "What": "打印图书的详细信息到标准输出",
    "When": "需要显示图书信息时",
    "Why": "提供统一的图书信息展示格式",
    "How": "检查指针非空后，格式化输出所有字段信息"
} */
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

/* {
    "What": "更新图书价格",
    "When": "需要修改图书价格时",
    "Why": "提供价格修改的安全接口，确保价格有效",
    "How": "检查指针非空和价格非负后更新价格"
} */
int updateBookPrice(Book* book, float newPrice) {
    if (book == NULL || newPrice < 0) return 0;
    book->price = newPrice;
    return 1;
}

/* {
    "What": "更新图书出版年份",
    "When": "需要修改图书出版年份时",
    "Why": "提供年份修改的安全接口，确保年份在合理范围内",
    "How": "检查指针非空和年份在1800-2024范围内后更新年份"
} */
int updateBookYear(Book* book, int newYear) {
    if (book == NULL || newYear < 1800 || newYear > 2024) return 0;
    book->year = newYear;
    return 1;
}

/* {
    "What": "检查图书是否可用",
    "When": "需要查询图书状态时",
    "Why": "提供图书可用性状态的查询接口",
    "How": "检查指针非空后返回available字段的值"
} */
int isBookAvailable(const Book* book) {
    return book != NULL && book->available;
}

/* {
    "What": "设置图书的可用性状态",
    "When": "需要修改图书状态时",
    "Why": "提供图书状态修改的安全接口",
    "How": "检查指针非空后更新available字段的值"
} */
void setBookAvailability(Book* book, int available) {
    if (book != NULL) {
        book->available = available;
    }
}

/* {
    "What": "获取图书标题",
    "When": "需要访问图书标题时",
    "Why": "提供只读访问接口，保护数据封装性",
    "How": "检查指针非空后返回title字段的指针"
} */
const char* getBookTitle(const Book* book) {
    return book != NULL ? book->title : NULL;
}

/* {
    "What": "获取图书作者",
    "When": "需要访问图书作者信息时",
    "Why": "提供只读访问接口，保护数据封装性",
    "How": "检查指针非空后返回author字段的指针"
} */
const char* getBookAuthor(const Book* book) {
    return book != NULL ? book->author : NULL;
}

/* {
    "What": "获取图书ISBN",
    "When": "需要访问图书ISBN时",
    "Why": "提供只读访问接口，保护数据封装性",
    "How": "检查指针非空后返回isbn字段的指针"
} */
const char* getBookISBN(const Book* book) {
    return book != NULL ? book->isbn : NULL;
} 