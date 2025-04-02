/* {
    "File": "library.h",
    "Purpose": "定义图书管理系统中的图书馆相关数据结构和接口",
    "Architecture": {
        "DataStructures": {
            "Library": "包含图书集合的结构体，使用固定大小数组存储图书指针"
        },
        "Constants": {
            "MAX_BOOKS": "图书馆最大藏书量限制"
        },
        "Functions": {
            "createLibrary": "创建新的图书馆对象",
            "destroyLibrary": "销毁图书馆对象",
            "addBook": "添加新书到图书馆",
            "removeBook": "从图书馆移除图书",
            "findBookByISBN": "通过ISBN查找图书",
            "findBookByTitle": "通过标题查找图书",
            "listAllBooks": "列出所有图书",
            "borrowBook": "借出图书",
            "returnBook": "归还图书",
            "getBookCount": "获取当前图书数量",
            "sortBooksByTitle": "按标题排序图书",
            "sortBooksByAuthor": "按作者排序图书"
        }
    },
    "Dependencies": {
        "StandardLibraries": ["stdio.h", "stdlib.h", "string.h"],
        "CustomHeaders": ["book.h"]
    },
    "Usage": "作为图书管理系统的核心头文件，提供图书馆管理的主要功能接口",
    "DesignPatterns": ["集合模式", "迭代器模式"]
} */

#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"

/* {
    "What": "定义图书馆可以存储的最大图书数量",
    "When": "在创建图书馆对象和添加新书时使用",
    "Why": "限制图书馆容量以确保系统性能和内存使用合理",
    "How": "通过宏定义设置为1000本"
} */
#define MAX_BOOKS 1000

/* {
    "What": "定义图书馆数据结构",
    "When": "在创建和管理图书馆对象时使用",
    "Why": "将图书馆的所有图书信息组织在一个结构体中，便于管理和访问",
    "How": "使用C语言的结构体定义，包含图书指针数组和当前图书数量"
} */
typedef struct {
    Book* books[MAX_BOOKS];
    int bookCount;
} Library;

/* {
    "What": "创建新的图书馆对象",
    "When": "系统初始化时",
    "Why": "提供统一的图书馆对象创建接口，确保所有必要字段都被正确初始化",
    "How": "动态分配内存并初始化所有字段"
} */
Library* createLibrary(void);

/* {
    "What": "销毁图书馆对象并释放内存",
    "When": "图书馆对象不再需要时",
    "Why": "防止内存泄漏，确保系统资源被正确释放",
    "How": "释放所有图书对象和图书馆对象的内存"
} */
void destroyLibrary(Library* library);

/* {
    "What": "添加新书到图书馆",
    "When": "需要添加新书到系统时",
    "Why": "提供统一的图书添加接口，确保图书馆容量限制",
    "How": "检查容量限制，如果未满则添加图书"
} */
int addBook(Library* library, Book* book);

/* {
    "What": "从图书馆移除图书",
    "When": "需要删除图书时",
    "Why": "提供统一的图书删除接口，确保安全移除",
    "How": "通过ISBN查找并移除图书"
} */
int removeBook(Library* library, const char* isbn);

/* {
    "What": "通过ISBN查找图书",
    "When": "需要查找特定图书时",
    "Why": "提供快速查找接口，ISBN是唯一标识符",
    "How": "遍历图书数组查找匹配的ISBN"
} */
Book* findBookByISBN(Library* library, const char* isbn);

/* {
    "What": "通过标题查找图书",
    "When": "需要按标题搜索图书时",
    "Why": "提供按标题搜索的接口，支持模糊查找",
    "How": "遍历图书数组查找匹配的标题"
} */
Book* findBookByTitle(Library* library, const char* title);

/* {
    "What": "列出所有图书",
    "When": "需要显示图书馆所有藏书时",
    "Why": "提供完整的图书列表展示功能",
    "How": "遍历并打印所有图书信息"
} */
void listAllBooks(const Library* library);

/* {
    "What": "借出图书",
    "When": "用户需要借书时",
    "Why": "提供图书借阅功能，管理图书可用性",
    "How": "检查图书是否存在和可用，然后更新状态"
} */
int borrowBook(Library* library, const char* isbn);

/* {
    "What": "归还图书",
    "When": "用户归还图书时",
    "Why": "提供图书归还功能，恢复图书可用性",
    "How": "检查图书是否存在，然后更新状态"
} */
int returnBook(Library* library, const char* isbn);

/* {
    "What": "获取当前图书数量",
    "When": "需要查询图书馆藏书量时",
    "Why": "提供图书馆容量查询接口",
    "How": "返回bookCount字段的值"
} */
int getBookCount(const Library* library);

/* {
    "What": "按标题排序图书",
    "When": "需要按标题组织图书时",
    "Why": "提供图书排序功能，便于查找和管理",
    "How": "使用排序算法按标题字母顺序排序"
} */
void sortBooksByTitle(Library* library);

/* {
    "What": "按作者排序图书",
    "When": "需要按作者组织图书时",
    "Why": "提供图书排序功能，便于查找和管理",
    "How": "使用排序算法按作者名字字母顺序排序"
} */
void sortBooksByAuthor(Library* library);

#endif // LIBRARY_H 