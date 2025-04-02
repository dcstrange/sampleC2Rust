/* {
    "File": "library.c",
    "Purpose": "实现图书管理系统中的图书馆管理功能",
    "Implementation": {
        "MemoryManagement": {
            "createLibrary": "动态分配内存并初始化图书馆对象",
            "destroyLibrary": "递归释放所有图书对象和图书馆对象",
            "addBook": "安全添加图书到数组",
            "removeBook": "安全移除图书并重新排列数组"
        },
        "SearchOperations": {
            "findBookByISBN": "线性搜索ISBN（O(n)复杂度）",
            "findBookByTitle": "使用strstr进行模糊标题匹配"
        },
        "SortingOperations": {
            "sortBooksByTitle": "使用qsort实现标题排序",
            "sortBooksByAuthor": "使用qsort实现作者排序"
        },
        "BookManagement": {
            "borrowBook": "通过ISBN查找并更新图书状态",
            "returnBook": "通过ISBN查找并恢复图书状态"
        }
    },
    "Dependencies": {
        "StandardLibraries": ["stdio.h", "stdlib.h", "string.h"],
        "CustomHeaders": ["library.h"]
    }
} */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/* {
    "What": "创建新的图书馆对象并初始化所有字段",
    "When": "系统初始化时",
    "Why": "提供统一的图书馆对象创建接口，确保所有必要字段都被正确初始化",
    "How": "动态分配内存，初始化图书数组和计数器"
} */
Library* createLibrary(void) {
    Library* library = (Library*)malloc(sizeof(Library));
    if (library == NULL) return NULL;
    
    library->bookCount = 0;
    for (int i = 0; i < MAX_BOOKS; i++) {
        library->books[i] = NULL;
    }
    
    return library;
}

/* {
    "What": "销毁图书馆对象并释放所有资源",
    "When": "图书馆对象不再需要时",
    "Why": "防止内存泄漏，确保系统资源被正确释放",
    "How": "释放所有图书对象和图书馆对象的内存"
} */
void destroyLibrary(Library* library) {
    if (library == NULL) return;
    
    for (int i = 0; i < library->bookCount; i++) {
        destroyBook(library->books[i]);
    }
    free(library);
}

/* {
    "What": "添加新书到图书馆",
    "When": "需要添加新书到系统时",
    "Why": "提供统一的图书添加接口，确保图书馆容量限制",
    "How": "检查容量限制，如果未满则添加图书并更新计数器"
} */
int addBook(Library* library, Book* book) {
    if (library == NULL || book == NULL || library->bookCount >= MAX_BOOKS) {
        return 0;
    }
    
    library->books[library->bookCount++] = book;
    return 1;
}

/* {
    "What": "从图书馆移除图书",
    "When": "需要删除图书时",
    "Why": "提供统一的图书删除接口，确保安全移除",
    "How": "通过ISBN查找图书，移除后重新排列数组"
} */
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

/* {
    "What": "通过ISBN查找图书",
    "When": "需要查找特定图书时",
    "Why": "提供快速查找接口，ISBN是唯一标识符",
    "How": "遍历图书数组查找匹配的ISBN"
} */
Book* findBookByISBN(Library* library, const char* isbn) {
    if (library == NULL || isbn == NULL) return NULL;
    
    for (int i = 0; i < library->bookCount; i++) {
        if (strcmp(library->books[i]->isbn, isbn) == 0) {
            return library->books[i];
        }
    }
    return NULL;
}

/* {
    "What": "通过标题查找图书",
    "When": "需要按标题搜索图书时",
    "Why": "提供按标题搜索的接口，支持模糊查找",
    "How": "使用strstr函数进行子串匹配"
} */
Book* findBookByTitle(Library* library, const char* title) {
    if (library == NULL || title == NULL) return NULL;
    
    for (int i = 0; i < library->bookCount; i++) {
        if (strstr(library->books[i]->title, title) != NULL) {
            return library->books[i];
        }
    }
    return NULL;
}

/* {
    "What": "列出所有图书",
    "When": "需要显示图书馆所有藏书时",
    "Why": "提供完整的图书列表展示功能",
    "How": "遍历并打印所有图书信息，包括总数统计"
} */
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

/* {
    "What": "借出图书",
    "When": "用户需要借书时",
    "Why": "提供图书借阅功能，管理图书可用性",
    "How": "查找图书并更新其可用性状态"
} */
int borrowBook(Library* library, const char* isbn) {
    Book* book = findBookByISBN(library, isbn);
    if (book == NULL || !isBookAvailable(book)) {
        return 0;
    }
    
    setBookAvailability(book, 0);
    return 1;
}

/* {
    "What": "归还图书",
    "When": "用户归还图书时",
    "Why": "提供图书归还功能，恢复图书可用性",
    "How": "查找图书并更新其可用性状态"
} */
int returnBook(Library* library, const char* isbn) {
    Book* book = findBookByISBN(library, isbn);
    if (book == NULL || isBookAvailable(book)) {
        return 0;
    }
    
    setBookAvailability(book, 1);
    return 1;
}

/* {
    "What": "获取当前图书数量",
    "When": "需要查询图书馆藏书量时",
    "Why": "提供图书馆容量查询接口",
    "How": "返回bookCount字段的值"
} */
int getBookCount(const Library* library) {
    return library != NULL ? library->bookCount : 0;
}

/* {
    "What": "按标题比较两本图书",
    "When": "在排序函数中使用",
    "Why": "提供qsort函数所需的比较函数",
    "How": "使用strcmp比较图书标题"
} */
static int compareByTitle(const void* a, const void* b) {
    return strcmp((*(Book**)a)->title, (*(Book**)b)->title);
}

/* {
    "What": "按作者比较两本图书",
    "When": "在排序函数中使用",
    "Why": "提供qsort函数所需的比较函数",
    "How": "使用strcmp比较作者名字"
} */
static int compareByAuthor(const void* a, const void* b) {
    return strcmp((*(Book**)a)->author, (*(Book**)b)->author);
}

/* {
    "What": "按标题排序图书",
    "When": "需要按标题组织图书时",
    "Why": "提供图书排序功能，便于查找和管理",
    "How": "使用qsort函数和compareByTitle比较函数进行排序"
} */
void sortBooksByTitle(Library* library) {
    if (library == NULL) return;
    qsort(library->books, library->bookCount, sizeof(Book*), compareByTitle);
}

/* {
    "What": "按作者排序图书",
    "When": "需要按作者组织图书时",
    "Why": "提供图书排序功能，便于查找和管理",
    "How": "使用qsort函数和compareByAuthor比较函数进行排序"
} */
void sortBooksByAuthor(Library* library) {
    if (library == NULL) return;
    qsort(library->books, library->bookCount, sizeof(Book*), compareByAuthor);
} 