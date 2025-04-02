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
    "When": "图书对象不再需要时",
    "Why": "防止内存泄漏，确保系统资源被正确释放",
    "How": "释放动态分配的内存"
} */
void destroyBook(Book* book);

/* {
    "What": "打印图书信息到标准输出",
    "When": "需要显示图书详细信息时",
    "Why": "提供统一的图书信息展示格式",
    "How": "格式化输出所有字段信息"
} */
void printBook(const Book* book);

/* {
    "What": "更新图书价格",
    "When": "需要修改图书价格时",
    "Why": "提供价格修改的安全接口，确保价格有效",
    "How": "检查新价格是否有效，如果有效则更新"
} */
int updateBookPrice(Book* book, float newPrice);

/* {
    "What": "更新图书出版年份",
    "When": "需要修改图书出版年份时",
    "Why": "提供年份修改的安全接口，确保年份有效",
    "How": "检查新年份是否有效，如果有效则更新"
} */
int updateBookYear(Book* book, int newYear);

/* {
    "What": "检查图书是否可用",
    "When": "需要查询图书状态时",
    "Why": "提供图书可用性状态的查询接口",
    "How": "返回available字段的值"
} */
int isBookAvailable(const Book* book);

/* {
    "What": "设置图书的可用性状态",
    "When": "需要修改图书状态时",
    "Why": "提供图书状态修改的安全接口",
    "How": "直接修改available字段的值"
} */
void setBookAvailability(Book* book, int available);

/* {
    "What": "获取图书标题",
    "When": "需要访问图书标题时",
    "Why": "提供只读访问接口，保护数据封装性",
    "How": "返回title字段的指针"
} */
const char* getBookTitle(const Book* book);

/* {
    "What": "获取图书作者",
    "When": "需要访问图书作者信息时",
    "Why": "提供只读访问接口，保护数据封装性",
    "How": "返回author字段的指针"
} */
const char* getBookAuthor(const Book* book);

/* {
    "What": "获取图书ISBN",
    "When": "需要访问图书ISBN时",
    "Why": "提供只读访问接口，保护数据封装性",
    "How": "返回isbn字段的指针"
} */
const char* getBookISBN(const Book* book);

#endif // BOOK_H 