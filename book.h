/* {
    "File": "book.h",
    "Purpose": "定义图书管理系统中的图书相关数据结构和接口",
    "Architecture": {
        "DataStructures": {
            "Book": "包含图书基本信息的结构体，包括标题、作者、ISBN、出版年份、价格和可用性状态"
        },
        "Constants": {
            "MAX_TITLE_LEN": "图书标题最大长度限制",
            "MAX_AUTHOR_LEN": "作者名字最大长度限制",
            "MAX_ISBN_LEN": "ISBN号码最大长度限制"
        },
        "Functions": {
            "createBook": "创建新的图书对象",
            "destroyBook": "销毁图书对象",
            "printBook": "打印图书信息",
            "updateBookPrice": "更新图书价格",
            "updateBookYear": "更新出版年份",
            "isBookAvailable": "检查图书可用性",
            "setBookAvailability": "设置图书可用性",
            "getBookTitle": "获取图书标题",
            "getBookAuthor": "获取图书作者",
            "getBookISBN": "获取图书ISBN"
        }
    },
    "Dependencies": {
        "StandardLibraries": ["stdio.h", "stdlib.h", "string.h"],
        "CustomHeaders": []
    },
    "Usage": "作为图书管理系统的基础头文件，提供图书对象的基本操作接口",
    "DesignPatterns": ["封装", "访问器模式"]
} */

#ifndef BOOK_H
#define BOOK_H

/* {
    "What": "定义图书标题的最大长度",
    "When": "在创建新图书对象时使用",
    "Why": "限制图书标题的长度以确保内存使用合理",
    "How": "通过宏定义设置为100个字符"
} */
#define MAX_TITLE_LEN 100

/* {
    "What": "定义作者名字的最大长度",
    "When": "在创建新图书对象时使用",
    "Why": "限制作者名字的长度以确保内存使用合理",
    "How": "通过宏定义设置为50个字符"
} */
#define MAX_AUTHOR_LEN 50

/* {
    "What": "定义ISBN号码的最大长度",
    "When": "在创建新图书对象时使用",
    "Why": "限制ISBN的长度以符合标准ISBN-13格式",
    "How": "通过宏定义设置为13个字符"
} */
#define MAX_ISBN_LEN 13

/* {
    "What": "定义图书信息的数据结构",
    "When": "在创建和管理图书对象时使用",
    "Why": "将图书的所有相关信息组织在一个结构体中，便于管理和访问",
    "How": "使用C语言的结构体定义，包含标题、作者、ISBN、出版年份、价格和可用性等字段"
} */
typedef struct {
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    char isbn[MAX_ISBN_LEN];
    int year;
    float price;
    int available;
} Book;

/* {
    "What": "创建新的图书对象",
    "When": "需要添加新书到系统时",
    "Why": "提供统一的图书对象创建接口，确保所有必要字段都被正确初始化",
    "How": "动态分配内存并初始化所有字段"
} */
Book* createBook(const char* title, const char* author, const char* isbn, int year, float price);

/* {
    "What": "销毁图书对象并释放内存",
    "When": "图书对象不再需要时，如删除图书、系统关闭时",
    "Why": "防止内存泄漏，确保系统资源被正确释放，维护系统稳定性",
    "How": "检查指针非空后释放内存",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果非空，调用free释放内存\n3. 不返回任何值，因为释放后指针已失效",
    "ErrorHandling": {
        "NullPointer": "安全处理NULL指针输入",
        "MemoryLeak": "确保内存被正确释放",
        "DanglingPointer": "调用者负责将指针设为NULL"
    },
    "Context": {
        "Module": "图书基础信息管理模块",
        "DesignIntent": "实现图书对象的资源清理，确保内存管理安全",
        "Dependencies": "依赖标准库的内存释放函数"
    },
    "Hierarchy": {
        "Level": "基础对象销毁层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["图书馆管理模块", "图书删除功能"],
        "AbstractionLevel": "中等抽象，介于底层内存操作和高层业务逻辑之间",
        "Role": {
            "InParent": "作为图书管理系统的基础资源清理接口",
            "InChild": "为图书馆管理和删除功能提供标准化的图书对象销毁服务"
        }
    }
} */
void destroyBook(Book* book);

/* {
    "What": "打印图书信息到标准输出",
    "When": "需要显示图书详细信息时，如查询结果、列表显示",
    "Why": "提供统一的图书信息展示格式，确保信息展示的一致性和可读性",
    "How": "格式化输出所有字段信息",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果为NULL，输出错误信息\n3. 按固定格式输出所有字段\n4. 使用printf进行格式化输出",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "FormatError": "使用安全的格式化字符串",
        "OutputError": "假设标准输出可用"
    },
    "Context": {
        "Module": "图书基础信息管理模块",
        "DesignIntent": "实现图书信息的标准化展示，提供用户友好的输出格式",
        "Dependencies": "依赖标准库的输入输出函数"
    },
    "Hierarchy": {
        "Level": "信息展示层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["图书馆管理模块", "用户界面模块"],
        "AbstractionLevel": "较高抽象，专注于信息展示逻辑",
        "Role": {
            "InParent": "作为图书管理系统的基础信息展示接口",
            "InChild": "为图书馆管理和用户界面提供标准化的图书信息展示服务"
        }
    }
} */
void printBook(const Book* book);

/* {
    "What": "更新图书价格",
    "When": "需要修改图书价格时，如价格调整、促销活动",
    "Why": "提供价格修改的安全接口，确保价格有效，维护数据一致性",
    "How": "检查新价格是否有效，如果有效则更新",
    "Logic": "1. 检查输入指针是否为NULL\n2. 检查新价格是否为负数\n3. 如果验证通过，更新价格\n4. 返回更新是否成功的状态",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "InvalidPrice": "验证价格非负",
        "UpdateStatus": "返回布尔值表示更新是否成功"
    },
    "Context": {
        "Module": "图书基础信息管理模块",
        "DesignIntent": "实现图书价格的验证和更新，确保数据有效性",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据更新层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["库存管理模块", "销售管理模块"],
        "AbstractionLevel": "中等抽象，专注于数据验证和更新",
        "Role": {
            "InParent": "作为图书管理系统的基础价格更新接口",
            "InChild": "为库存和销售管理提供标准化的价格更新服务"
        }
    }
} */
int updateBookPrice(Book* book, float newPrice);

/* {
    "What": "更新图书出版年份",
    "When": "需要修改图书出版年份时，如信息更正、版本更新",
    "Why": "提供年份修改的安全接口，确保年份在合理范围内，维护数据准确性",
    "How": "检查新年份是否有效，如果有效则更新",
    "Logic": "1. 检查输入指针是否为NULL\n2. 检查新年份是否在1800-2024范围内\n3. 如果验证通过，更新年份\n4. 返回更新是否成功的状态",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "InvalidYear": "验证年份在合理范围内",
        "UpdateStatus": "返回布尔值表示更新是否成功"
    },
    "Context": {
        "Module": "图书基础信息管理模块",
        "DesignIntent": "实现图书出版年份的验证和更新，确保数据准确性",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据更新层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["编目管理模块", "版本控制模块"],
        "AbstractionLevel": "中等抽象，专注于数据验证和更新",
        "Role": {
            "InParent": "作为图书管理系统的基础年份更新接口",
            "InChild": "为编目和版本管理提供标准化的年份更新服务"
        }
    }
} */
int updateBookYear(Book* book, int newYear);

/* {
    "What": "检查图书是否可用",
    "When": "需要查询图书状态时，如借阅前检查、库存查询",
    "Why": "提供图书可用性状态的查询接口，确保借阅操作的安全性",
    "How": "返回available字段的值",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果非空，返回available字段的值\n3. 如果为NULL，返回0表示不可用",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "DefaultState": "NULL指针时返回不可用状态"
    },
    "Context": {
        "Module": "图书基础信息管理模块",
        "DesignIntent": "实现图书可用性状态的查询，支持借阅管理",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "状态查询层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["借阅管理模块", "库存管理模块"],
        "AbstractionLevel": "较低抽象，直接访问状态信息",
        "Role": {
            "InParent": "作为图书管理系统的基础状态查询接口",
            "InChild": "为借阅和库存管理提供标准化的可用性查询服务"
        }
    }
} */
int isBookAvailable(const Book* book);

/* {
    "What": "设置图书的可用性状态",
    "When": "需要修改图书状态时，如借出、归还、库存调整",
    "Why": "提供图书状态修改的安全接口，确保状态变更的可靠性",
    "How": "直接修改available字段的值",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果非空，更新available字段的值\n3. 不返回任何值，因为这是状态修改操作",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "StateTransition": "直接设置状态值，不进行状态转换验证"
    },
    "Context": {
        "Module": "图书基础信息管理模块",
        "DesignIntent": "实现图书可用性状态的修改，支持借阅流程",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "状态修改层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["借阅管理模块", "库存管理模块"],
        "AbstractionLevel": "较低抽象，直接修改状态信息",
        "Role": {
            "InParent": "作为图书管理系统的基础状态修改接口",
            "InChild": "为借阅和库存管理提供标准化的可用性修改服务"
        }
    }
} */
void setBookAvailability(Book* book, int available);

/* {
    "What": "获取图书标题",
    "When": "需要访问图书标题时，如显示、搜索、排序",
    "Why": "提供只读访问接口，保护数据封装性，确保数据访问的安全性",
    "How": "返回title字段的指针",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果非空，返回title字段的指针\n3. 如果为NULL，返回NULL",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "ReturnValue": "NULL指针时返回NULL"
    },
    "Context": {
        "Module": "图书基础信息管理模块",
        "DesignIntent": "实现图书标题的安全访问，保护数据封装",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据访问层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["搜索模块", "显示模块", "排序模块"],
        "AbstractionLevel": "较低抽象，提供原始数据访问",
        "Role": {
            "InParent": "作为图书管理系统的基础数据访问接口",
            "InChild": "为搜索、显示和排序功能提供标准化的标题访问服务"
        }
    }
} */
const char* getBookTitle(const Book* book);

/* {
    "What": "获取图书作者",
    "When": "需要访问图书作者信息时，如显示、搜索、排序",
    "Why": "提供只读访问接口，保护数据封装性，确保数据访问的安全性",
    "How": "返回author字段的指针",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果非空，返回author字段的指针\n3. 如果为NULL，返回NULL",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "ReturnValue": "NULL指针时返回NULL"
    },
    "Context": {
        "Module": "图书基础信息管理模块",
        "DesignIntent": "实现图书作者信息的安全访问，保护数据封装",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据访问层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["搜索模块", "显示模块", "排序模块"],
        "AbstractionLevel": "较低抽象，提供原始数据访问",
        "Role": {
            "InParent": "作为图书管理系统的基础数据访问接口",
            "InChild": "为搜索、显示和排序功能提供标准化的作者信息访问服务"
        }
    }
} */
const char* getBookAuthor(const Book* book);

/* {
    "What": "获取图书ISBN",
    "When": "需要访问图书ISBN时，如查找、借阅、归还",
    "Why": "提供只读访问接口，保护数据封装性，确保数据访问的安全性",
    "How": "返回isbn字段的指针",
    "Logic": "1. 检查输入指针是否为NULL\n2. 如果非空，返回isbn字段的指针\n3. 如果为NULL，返回NULL",
    "ErrorHandling": {
        "NullPointer": "检查并处理NULL指针输入",
        "ReturnValue": "NULL指针时返回NULL"
    },
    "Context": {
        "Module": "图书基础信息管理模块",
        "DesignIntent": "实现图书ISBN的安全访问，保护数据封装",
        "Dependencies": "无外部依赖"
    },
    "Hierarchy": {
        "Level": "数据访问层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["查找模块", "借阅模块", "归还模块"],
        "AbstractionLevel": "较低抽象，提供原始数据访问",
        "Role": {
            "InParent": "作为图书管理系统的基础数据访问接口",
            "InChild": "为查找、借阅和归还功能提供标准化的ISBN访问服务"
        }
    }
} */
const char* getBookISBN(const Book* book);

#endif // BOOK_H 