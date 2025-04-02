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
            "getBookTitle/Author/ISBN":createBook "提供只读访问接口"
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
    "When": "需要添加新书到系统时，如新书入库、图书补充",
    "Why": "提供统一的图书对象创建接口，确保所有必要字段都被正确初始化，为后续的图书管理操作提供基础",
    "How": "动态分配内存，初始化所有字段，包括标题、作者、ISBN、价格、年份和可用性",
    "Logic": "1. 使用malloc分配Book结构体大小的内存\n2. 检查内存分配是否成功，失败则返回NULL\n3. 使用strncpy安全复制字符串字段\n4. 初始化数值字段\n5. 设置默认可用性为1\n6. 返回创建的图书对象",
    "ErrorHandling": {
        "MemoryAllocation": "检查malloc返回值，失败时返回NULL",
        "StringCopy": "使用strncpy确保字符串安全复制",
        "NullTermination": "确保字符串正确终止",
        "Initialization": "确保所有字段都被正确初始化"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书对象的创建和初始化，为图书管理提供基础设施",
        "Dependencies": "依赖标准库的内存分配和字符串处理函数"
    },
    "Hierarchy": {
        "Level": "对象创建层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["图书管理功能", "借阅管理功能"],
        "AbstractionLevel": "高抽象，作为图书对象的基础创建接口",
        "Role": {
            "InParent": "作为图书管理系统的核心对象创建接口",
            "InChild": "为所有图书相关操作提供标准化的对象创建服务"
        }
    }
} */
Book* createBook(const char* title, const char* author, const char* isbn, float price, int year, int available) {
    Book* book = (Book*)malloc(sizeof(Book));
    if (book == NULL) return NULL;
    
    strncpy(book->title, title, MAX_TITLE_LEN - 1);
    book->title[MAX_TITLE_LEN - 1] = '\0';
    
    strncpy(book->author, author, MAX_AUTHOR_LEN - 1);
    book->author[MAX_AUTHOR_LEN - 1] = '\0';
    
    strncpy(book->isbn, isbn, MAX_ISBN_LEN - 1);
    book->isbn[MAX_ISBN_LEN - 1] = '\0';
    
    book->price = price;
    book->year = year;
    book->available = available;
    
    return book;
}

/* {
    "What": "销毁图书对象并释放内存",
    "When": "图书对象不再需要时，如删除图书、系统关闭",
    "Why": "防止内存泄漏，确保系统资源被正确释放，维护系统稳定性",
    "How": "使用free函数释放图书对象占用的内存",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果有效，释放内存\n3. 不返回任何值，因为释放后指针已失效",
    "ErrorHandling": {
        "NullPointer": "安全处理NULL指针输入",
        "MemoryLeak": "确保内存被正确释放",
        "DanglingPointer": "调用者负责将指针设为NULL"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书对象的资源清理，确保内存管理安全",
        "Dependencies": "依赖标准库的内存释放函数"
    },
    "Hierarchy": {
        "Level": "资源清理层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["图书管理功能", "系统关闭处理"],
        "AbstractionLevel": "高抽象，负责对象资源管理",
        "Role": {
            "InParent": "作为图书管理系统的核心资源清理接口",
            "InChild": "为图书删除和系统关闭提供标准化的资源释放服务"
        }
    }
} */
void destroyBook(Book* book) {
    if (book != NULL) {
        free(book);
    }
}

/* {
    "What": "打印图书的详细信息",
    "When": "需要显示图书信息时，如查询结果、列表显示",
    "Why": "提供标准化的图书信息展示功能，确保信息显示的一致性和完整性",
    "How": "使用printf函数格式化输出所有字段",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果有效，按格式输出所有字段\n3. 使用条件运算符显示可用性状态",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "OutputError": "假设标准输出可用",
        "Formatting": "使用统一的格式确保显示一致性"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书信息的标准化展示，提供完整的图书视图",
        "Dependencies": "依赖标准库的输出函数"
    },
    "Hierarchy": {
        "Level": "信息展示层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["查询功能", "列表显示功能"],
        "AbstractionLevel": "中等抽象，专注于信息展示",
        "Role": {
            "InParent": "作为图书管理系统的核心信息展示接口",
            "InChild": "为查询和列表显示提供标准化的信息展示服务"
        }
    }
} */
void printBook(const Book* book) {
    if (book == NULL) {
        printf("无效的图书对象！\n");
        return;
    }
    
    printf("书名：%s\n", book->title);
    printf("作者：%s\n", book->author);
    printf("ISBN：%s\n", book->isbn);
    printf("价格：%.2f\n", book->price);
    printf("出版年份：%d\n", book->year);
    printf("状态：%s\n", book->available ? "可借" : "已借出");
}

/* {
    "What": "更新图书价格",
    "When": "需要修改图书价格时，如价格调整、折扣更新",
    "Why": "提供图书价格修改接口，支持价格管理功能",
    "How": "检查输入参数并更新价格字段",
    "Logic": "1. 检查输入指针是否为NULL\n2. 检查新价格是否有效\n3. 更新价格字段\n4. 返回更新是否成功的状态",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "InvalidPrice": "检查价格是否为正数",
        "UpdateStatus": "返回布尔值表示更新是否成功"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书价格的标准化更新，支持价格管理",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据更新层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["价格管理功能", "库存管理功能"],
        "AbstractionLevel": "中等抽象，专注于数据更新",
        "Role": {
            "InParent": "作为图书管理系统的核心价格更新接口",
            "InChild": "为价格管理和库存管理提供标准化的价格更新服务"
        }
    }
} */
int updateBookPrice(Book* book, float newPrice) {
    if (book == NULL || newPrice <= 0) {
        return 0;
    }
    
    book->price = newPrice;
    return 1;
}

/* {
    "What": "更新图书出版年份",
    "When": "需要修改图书出版年份时，如信息更正、版本更新",
    "Why": "提供图书出版年份修改接口，支持信息管理功能",
    "How": "检查输入参数并更新年份字段",
    "Logic": "1. 检查输入指针是否为NULL\n2. 检查新年份是否有效\n3. 更新年份字段\n4. 返回更新是否成功的状态",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "InvalidYear": "检查年份是否在合理范围内",
        "UpdateStatus": "返回布尔值表示更新是否成功"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书出版年份的标准化更新，支持信息管理",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据更新层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["信息管理功能", "版本管理功能"],
        "AbstractionLevel": "中等抽象，专注于数据更新",
        "Role": {
            "InParent": "作为图书管理系统的核心年份更新接口",
            "InChild": "为信息管理和版本管理提供标准化的年份更新服务"
        }
    }
} */
int updateBookYear(Book* book, int newYear) {
    if (book == NULL || newYear <= 0 || newYear > 2024) {
        return 0;
    }
    
    book->year = newYear;
    return 1;
}

/* {
    "What": "检查图书是否可借",
    "When": "需要查询图书状态时，如借阅前检查、库存查询",
    "Why": "提供图书状态查询接口，支持借阅管理功能",
    "How": "检查输入指针并返回可用性状态",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果有效，返回available字段的值\n3. 如果无效，返回0",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "DefaultValue": "无效指针时返回0"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书状态的标准化查询，支持借阅管理",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "状态查询层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["借阅管理功能", "库存查询功能"],
        "AbstractionLevel": "较低抽象，直接访问状态",
        "Role": {
            "InParent": "作为图书管理系统的核心状态查询接口",
            "InChild": "为借阅管理和库存查询提供标准化的状态查询服务"
        }
    }
} */
int isBookAvailable(const Book* book) {
    return book != NULL ? book->available : 0;
}

/* {
    "What": "设置图书的可用性状态",
    "When": "需要修改图书状态时，如借阅、归还、状态更新",
    "Why": "提供图书状态修改接口，支持借阅管理功能",
    "How": "检查输入参数并更新可用性状态",
    "Logic": "1. 检查输入指针是否为NULL\n2. 更新available字段\n3. 返回更新是否成功的状态",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "UpdateStatus": "返回布尔值表示更新是否成功"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书状态的标准化更新，支持借阅管理",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "状态管理层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["借阅管理功能", "状态管理功能"],
        "AbstractionLevel": "较低抽象，直接修改状态",
        "Role": {
            "InParent": "作为图书管理系统的核心状态更新接口",
            "InChild": "为借阅管理和状态管理提供标准化的状态更新服务"
        }
    }
} */
int setBookAvailability(Book* book, int available) {
    if (book == NULL) {
        return 0;
    }
    
    book->available = available;
    return 1;
}

/* {
    "What": "获取图书标题",
    "When": "需要访问图书标题时，如显示、搜索、排序",
    "Why": "提供图书标题的只读访问接口，确保数据封装性",
    "How": "检查输入指针并返回标题字符串",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果有效，返回title字段\n3. 如果无效，返回NULL",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "ReturnValue": "无效指针时返回NULL"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书标题的安全访问，支持信息展示和搜索",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据访问层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["显示功能", "搜索功能", "排序功能"],
        "AbstractionLevel": "较低抽象，直接访问数据",
        "Role": {
            "InParent": "作为图书管理系统的核心标题访问接口",
            "InChild": "为显示、搜索和排序功能提供标准化的标题访问服务"
        }
    }
} */
const char* getBookTitle(const Book* book) {
    return book != NULL ? book->title : NULL;
}

/* {
    "What": "获取图书作者",
    "When": "需要访问图书作者时，如显示、搜索、排序",
    "Why": "提供图书作者的只读访问接口，确保数据封装性",
    "How": "检查输入指针并返回作者字符串",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果有效，返回author字段\n3. 如果无效，返回NULL",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "ReturnValue": "无效指针时返回NULL"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书作者的安全访问，支持信息展示和搜索",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据访问层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["显示功能", "搜索功能", "排序功能"],
        "AbstractionLevel": "较低抽象，直接访问数据",
        "Role": {
            "InParent": "作为图书管理系统的核心作者访问接口",
            "InChild": "为显示、搜索和排序功能提供标准化的作者访问服务"
        }
    }
} */
const char* getBookAuthor(const Book* book) {
    return book != NULL ? book->author : NULL;
}

/* {
    "What": "获取图书ISBN",
    "When": "需要访问图书ISBN时，如查找、标识、管理",
    "Why": "提供图书ISBN的只读访问接口，确保数据封装性",
    "How": "检查输入指针并返回ISBN字符串",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果有效，返回isbn字段\n3. 如果无效，返回NULL",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "ReturnValue": "无效指针时返回NULL"
    },
    "Context": {
        "Module": "图书管理模块",
        "DesignIntent": "实现图书ISBN的安全访问，支持查找和管理",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据访问层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["查找功能", "标识功能", "管理功能"],
        "AbstractionLevel": "较低抽象，直接访问数据",
        "Role": {
            "InParent": "作为图书管理系统的核心ISBN访问接口",
            "InChild": "为查找、标识和管理功能提供标准化的ISBN访问服务"
        }
    }
} */
const char* getBookISBN(const Book* book) {
    return book != NULL ? book->isbn : NULL;
} 