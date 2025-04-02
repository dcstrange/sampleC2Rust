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
    "When": "系统初始化时，需要建立新的图书馆实例",
    "Why": "提供统一的图书馆对象创建接口，确保所有必要字段都被正确初始化，为后续的图书管理操作提供基础",
    "How": "动态分配内存，初始化图书数组和计数器",
    "Logic": "1. 使用malloc分配Library结构体大小的内存\n2. 检查内存分配是否成功，失败则返回NULL\n3. 初始化bookCount为0\n4. 使用循环将所有图书指针初始化为NULL\n5. 返回创建的图书馆对象",
    "ErrorHandling": {
        "MemoryAllocation": "检查malloc返回值，失败时返回NULL",
        "Initialization": "确保所有字段都被正确初始化",
        "NullPointer": "返回NULL表示创建失败"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书馆对象的创建和初始化，为图书管理提供基础设施",
        "Dependencies": "依赖标准库的内存分配函数"
    },
    "Hierarchy": {
        "Level": "系统初始化层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["图书管理功能", "借阅管理功能", "查询功能"],
        "AbstractionLevel": "高抽象，作为整个系统的核心对象",
        "Role": {
            "InParent": "作为图书管理系统的核心对象创建接口",
            "InChild": "为所有图书相关操作提供基础设施"
        }
    }
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
    "When": "图书馆对象不再需要时，如系统关闭、重置图书馆",
    "Why": "防止内存泄漏，确保所有资源被正确释放，维护系统稳定性",
    "How": "递归释放所有图书对象和图书馆对象的内存",
    "Logic": "1. 检查输入指针是否为NULL\n2. 遍历所有图书对象\n3. 调用destroyBook释放每本图书\n4. 释放图书馆对象本身\n5. 不返回任何值，因为释放后指针已失效",
    "ErrorHandling": {
        "NullPointer": "安全处理NULL指针输入",
        "MemoryLeak": "确保所有子对象内存被正确释放",
        "DanglingPointer": "调用者负责将指针设为NULL"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书馆对象的资源清理，确保内存管理安全",
        "Dependencies": "依赖book.h中的destroyBook函数"
    },
    "Hierarchy": {
        "Level": "资源清理层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["图书管理功能", "系统关闭处理"],
        "AbstractionLevel": "高抽象，负责整体资源管理",
        "Role": {
            "InParent": "作为图书管理系统的核心资源清理接口",
            "InChild": "为系统关闭和重置提供标准化的资源释放服务"
        }
    }
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
    "When": "需要添加新书到系统时，如新书入库、图书补充",
    "Why": "提供统一的图书添加接口，确保图书馆容量限制，维护数据一致性",
    "How": "检查容量限制，如果未满则添加图书并更新计数器",
    "Logic": "1. 检查输入参数的有效性\n2. 检查图书馆是否已满\n3. 将图书添加到数组末尾\n4. 更新图书计数\n5. 返回添加是否成功的状态",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "CapacityLimit": "检查是否超过最大图书数量限制",
        "AddStatus": "返回布尔值表示添加是否成功"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书的安全添加，确保数据完整性",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据管理层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["图书入库功能", "库存管理功能"],
        "AbstractionLevel": "中等抽象，专注于数据添加操作",
        "Role": {
            "InParent": "作为图书管理系统的核心数据添加接口",
            "InChild": "为图书入库和库存管理提供标准化的添加服务"
        }
    }
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
    "When": "需要删除图书时，如图书报废、信息错误",
    "Why": "提供统一的图书删除接口，确保安全移除，维护数据一致性",
    "How": "通过ISBN查找图书，移除后重新排列数组",
    "Logic": "1. 检查输入参数的有效性\n2. 遍历查找匹配的ISBN\n3. 找到后释放图书对象\n4. 重新排列数组以保持连续性\n5. 更新图书计数\n6. 返回删除是否成功的状态",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "NotFound": "处理未找到图书的情况",
        "ArrayReorganization": "确保数组连续性",
        "DeleteStatus": "返回布尔值表示删除是否成功"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书的安全删除，确保数据一致性",
        "Dependencies": "依赖book.h中的destroyBook函数"
    },
    "Hierarchy": {
        "Level": "数据管理层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["图书删除功能", "库存管理功能"],
        "AbstractionLevel": "中等抽象，专注于数据删除操作",
        "Role": {
            "InParent": "作为图书管理系统的核心数据删除接口",
            "InChild": "为图书删除和库存管理提供标准化的删除服务"
        }
    }
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
    "When": "需要查找特定图书时，如借阅、归还、查询",
    "Why": "提供快速查找接口，ISBN是唯一标识符，确保查找的准确性和效率",
    "How": "遍历图书数组查找匹配的ISBN",
    "Logic": "1. 检查输入参数的有效性\n2. 遍历所有图书\n3. 使用strcmp比较ISBN\n4. 找到匹配时返回图书对象\n5. 未找到时返回NULL",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "NotFound": "未找到时返回NULL",
        "StringComparison": "使用安全的字符串比较"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书的快速查找，支持各种业务操作",
        "Dependencies": "依赖标准库的字符串比较函数"
    },
    "Hierarchy": {
        "Level": "数据访问层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["借阅功能", "归还功能", "查询功能"],
        "AbstractionLevel": "中等抽象，专注于数据查找操作",
        "Role": {
            "InParent": "作为图书管理系统的核心查找接口",
            "InChild": "为借阅、归还和查询功能提供标准化的查找服务"
        }
    }
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
    "When": "需要按标题搜索图书时，如模糊查询、分类浏览",
    "Why": "提供按标题搜索的接口，支持模糊查找，提高用户查询便利性",
    "How": "使用strstr函数进行子串匹配",
    "Logic": "1. 检查输入参数的有效性\n2. 遍历所有图书\n3. 使用strstr进行子串匹配\n4. 找到匹配时返回图书对象\n5. 未找到时返回NULL",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "NotFound": "未找到时返回NULL",
        "StringMatching": "使用安全的字符串匹配"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书的模糊查找，支持用户友好的搜索",
        "Dependencies": "依赖标准库的字符串匹配函数"
    },
    "Hierarchy": {
        "Level": "数据访问层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["搜索功能", "浏览功能"],
        "AbstractionLevel": "中等抽象，专注于模糊查找操作",
        "Role": {
            "InParent": "作为图书管理系统的核心模糊查找接口",
            "InChild": "为搜索和浏览功能提供标准化的模糊查找服务"
        }
    }
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
    "When": "需要显示图书馆所有藏书时，如库存盘点、目录浏览",
    "Why": "提供完整的图书列表展示功能，支持系统管理和用户浏览",
    "How": "遍历并打印所有图书信息，包括总数统计",
    "Logic": "1. 检查输入指针的有效性\n2. 输出总藏书量信息\n3. 遍历所有图书\n4. 为每本图书输出序号\n5. 调用printBook显示详细信息",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "EmptyLibrary": "处理空图书馆的情况",
        "OutputError": "假设标准输出可用"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书列表的标准化展示，提供完整的库存视图",
        "Dependencies": "依赖book.h中的printBook函数"
    },
    "Hierarchy": {
        "Level": "信息展示层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["库存管理功能", "用户界面功能"],
        "AbstractionLevel": "较高抽象，专注于信息展示",
        "Role": {
            "InParent": "作为图书管理系统的核心列表展示接口",
            "InChild": "为库存管理和用户界面提供标准化的列表展示服务"
        }
    }
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
    "When": "用户需要借书时，如读者借阅、预约取书",
    "Why": "提供图书借阅功能，管理图书可用性，支持图书馆核心业务",
    "How": "查找图书并更新其可用性状态",
    "Logic": "1. 通过ISBN查找图书\n2. 检查图书是否存在\n3. 检查图书是否可用\n4. 更新图书可用性状态\n5. 返回借阅是否成功的状态",
    "ErrorHandling": {
        "NotFound": "处理图书不存在的情况",
        "NotAvailable": "处理图书不可借的情况",
        "BorrowStatus": "返回布尔值表示借阅是否成功"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书的安全借阅，确保借阅流程的可靠性",
        "Dependencies": "依赖book.h中的状态管理函数"
    },
    "Hierarchy": {
        "Level": "业务操作层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["借阅管理功能", "预约管理功能"],
        "AbstractionLevel": "高抽象，专注于业务逻辑",
        "Role": {
            "InParent": "作为图书管理系统的核心借阅接口",
            "InChild": "为借阅和预约管理提供标准化的借阅服务"
        }
    }
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
    "When": "用户归还图书时，如读者还书、预约归还",
    "Why": "提供图书归还功能，恢复图书可用性，完成借阅流程",
    "How": "查找图书并更新其可用性状态",
    "Logic": "1. 通过ISBN查找图书\n2. 检查图书是否存在\n3. 检查图书是否已借出\n4. 更新图书可用性状态\n5. 返回归还是否成功的状态",
    "ErrorHandling": {
        "NotFound": "处理图书不存在的情况",
        "AlreadyAvailable": "处理图书未借出的情况",
        "ReturnStatus": "返回布尔值表示归还是否成功"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书的安全归还，确保归还流程的可靠性",
        "Dependencies": "依赖book.h中的状态管理函数"
    },
    "Hierarchy": {
        "Level": "业务操作层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["归还管理功能", "预约管理功能"],
        "AbstractionLevel": "高抽象，专注于业务逻辑",
        "Role": {
            "InParent": "作为图书管理系统的核心归还接口",
            "InChild": "为归还和预约管理提供标准化的归还服务"
        }
    }
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
    "When": "需要查询图书馆藏书量时，如统计报表、容量管理",
    "Why": "提供图书馆容量查询接口，支持系统管理和决策",
    "How": "返回bookCount字段的值",
    "Logic": "1. 检查输入指针的有效性\n2. 如果有效，返回bookCount\n3. 如果无效，返回0",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "DefaultValue": "无效指针时返回0"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书馆容量的查询，支持系统管理",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据访问层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["统计功能", "管理功能"],
        "AbstractionLevel": "较低抽象，直接访问数据",
        "Role": {
            "InParent": "作为图书管理系统的核心容量查询接口",
            "InChild": "为统计和管理功能提供标准化的容量查询服务"
        }
    }
} */
int getBookCount(const Library* library) {
    return library != NULL ? library->bookCount : 0;
}

/* {
    "What": "按标题比较两本图书",
    "When": "在排序函数中使用",
    "Why": "提供qsort函数所需的比较函数，支持图书标题的标准化排序",
    "How": "使用strcmp比较图书标题",
    "Logic": "1. 将void指针转换为Book指针\n2. 使用strcmp比较两本图书的标题\n3. 返回比较结果",
    "ErrorHandling": {
        "NullPointer": "假设输入指针有效（由qsort保证）",
        "StringComparison": "使用标准库的字符串比较函数"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书标题的标准化比较，支持排序功能",
        "Dependencies": "依赖标准库的字符串比较函数"
    },
    "Hierarchy": {
        "Level": "数据组织层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["排序功能"],
        "AbstractionLevel": "低抽象，专注于比较操作",
        "Role": {
            "InParent": "作为排序功能的辅助函数",
            "InChild": "为排序算法提供标准化的比较服务"
        }
    }
} */
static int compareByTitle(const void* a, const void* b) {
    return strcmp((*(Book**)a)->title, (*(Book**)b)->title);
}

/* {
    "What": "按作者比较两本图书",
    "When": "在排序函数中使用",
    "Why": "提供qsort函数所需的比较函数，支持图书作者的标准化排序",
    "How": "使用strcmp比较作者名字",
    "Logic": "1. 将void指针转换为Book指针\n2. 使用strcmp比较两本图书的作者\n3. 返回比较结果",
    "ErrorHandling": {
        "NullPointer": "假设输入指针有效（由qsort保证）",
        "StringComparison": "使用标准库的字符串比较函数"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书作者的标准化比较，支持排序功能",
        "Dependencies": "依赖标准库的字符串比较函数"
    },
    "Hierarchy": {
        "Level": "数据组织层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["排序功能"],
        "AbstractionLevel": "低抽象，专注于比较操作",
        "Role": {
            "InParent": "作为排序功能的辅助函数",
            "InChild": "为排序算法提供标准化的比较服务"
        }
    }
} */
static int compareByAuthor(const void* a, const void* b) {
    return strcmp((*(Book**)a)->author, (*(Book**)b)->author);
}

/* {
    "What": "按标题排序图书",
    "When": "需要按标题组织图书时，如目录整理、展示优化",
    "Why": "提供图书排序功能，便于查找和管理，提高系统可用性",
    "How": "使用qsort函数和compareByTitle比较函数进行排序",
    "Logic": "1. 检查输入指针的有效性\n2. 使用qsort函数进行排序\n3. 使用compareByTitle作为比较函数\n4. 排序完成后数组按标题字母顺序排列",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "EmptyLibrary": "处理空图书馆的情况",
        "SortError": "假设qsort不会失败"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书的标准化排序，提高系统可用性",
        "Dependencies": "依赖标准库的排序函数"
    },
    "Hierarchy": {
        "Level": "数据组织层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["目录管理功能", "展示功能"],
        "AbstractionLevel": "中等抽象，专注于数据组织",
        "Role": {
            "InParent": "作为图书管理系统的核心排序接口",
            "InChild": "为目录管理和展示功能提供标准化的排序服务"
        }
    }
} */
void sortBooksByTitle(Library* library) {
    if (library == NULL) return;
    qsort(library->books, library->bookCount, sizeof(Book*), compareByTitle);
}

/* {
    "What": "按作者排序图书",
    "When": "需要按作者组织图书时，如作者作品集整理、分类浏览",
    "Why": "提供图书排序功能，便于按作者查找和管理，提高系统可用性",
    "How": "使用qsort函数和compareByAuthor比较函数进行排序",
    "Logic": "1. 检查输入指针的有效性\n2. 使用qsort函数进行排序\n3. 使用compareByAuthor作为比较函数\n4. 排序完成后数组按作者名字字母顺序排列",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "EmptyLibrary": "处理空图书馆的情况",
        "SortError": "假设qsort不会失败"
    },
    "Context": {
        "Module": "图书馆管理模块",
        "DesignIntent": "实现图书的标准化排序，提高系统可用性",
        "Dependencies": "依赖标准库的排序函数"
    },
    "Hierarchy": {
        "Level": "数据组织层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["作者作品管理功能", "分类浏览功能"],
        "AbstractionLevel": "中等抽象，专注于数据组织",
        "Role": {
            "InParent": "作为图书管理系统的核心排序接口",
            "InChild": "为作者作品管理和分类浏览提供标准化的排序服务"
        }
    }
} */
void sortBooksByAuthor(Library* library) {
    if (library == NULL) return;
    qsort(library->books, library->bookCount, sizeof(Book*), compareByAuthor);
} 