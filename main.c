/* {
    "File": "main.c",
    "Purpose": "实现图书管理系统的主程序入口和用户界面",
    "Implementation": {
        "UserInterface": {
            "printMenu": "提供交互式命令行菜单",
            "main": "实现主程序循环和用户交互逻辑"
        },
        "MenuOptions": {
            "addBook": "添加新书到图书馆",
            "removeBook": "从图书馆移除图书",
            "findBook": "查找特定图书",
            "borrowBook": "借阅图书",
            "returnBook": "归还图书",
            "listAllBooks": "显示所有图书",
            "sortBooks": "按书名或作者排序"
        },
        "DataInitialization": {
            "testData": "初始化包含示例图书的测试数据"
        }
    },
    "Dependencies": {
        "StandardLibraries": ["stdio.h"],
        "CustomHeaders": ["book.h", "library.h"]
    },
    "ErrorHandling": {
        "InputValidation": "使用gets和scanf安全读取用户输入",
        "MemoryManagement": "检查对象创建是否成功",
        "OperationStatus": "显示操作成功或失败的反馈"
    },
    "UserExperience": {
        "MenuSystem": "清晰的菜单选项和操作提示",
        "Feedback": "每个操作后提供状态反馈",
        "DataDisplay": "格式化的图书信息展示"
    }
} */

#include <stdio.h>
#include "book.h"
#include "library.h"

/* {
    "What": "显示图书管理系统的主菜单",
    "When": "系统启动时和每次操作完成后",
    "Why": "提供清晰的用户界面，展示所有可用功能，引导用户进行系统操作",
    "How": "使用printf函数格式化输出菜单选项",
    "Logic": "1. 输出系统标题\n2. 按功能分类输出所有菜单选项\n3. 使用数字编号标识每个选项\n4. 为每个选项提供简短描述\n5. 输出退出选项",
    "ErrorHandling": {
        "OutputError": "假设标准输出可用",
        "Formatting": "使用统一的格式确保显示一致性"
    },
    "Context": {
        "Module": "用户界面模块",
        "DesignIntent": "实现直观的用户交互界面，提供清晰的功能导航",
        "Dependencies": "依赖标准库的输出函数"
    },
    "Hierarchy": {
        "Level": "用户界面层",
        "ParentModule": "图书管理系统",
        "ChildModules": ["菜单导航", "用户交互"],
        "AbstractionLevel": "高抽象，专注于用户交互",
        "Role": {
            "InParent": "作为系统的主要用户界面入口",
            "InChild": "为用户提供标准化的功能导航服务"
        }
    }
} */
void printMenu(void) {
    printf("\n=== 图书管理系统 ===\n");
    printf("1. 添加新书\n");
    printf("2. 删除图书\n");
    printf("3. 查找图书\n");
    printf("4. 显示所有图书\n");
    printf("5. 借阅图书\n");
    printf("6. 归还图书\n");
    printf("7. 按标题排序\n");
    printf("8. 按作者排序\n");
    printf("0. 退出系统\n");
    printf("请选择操作 (0-8): ");
}

/* {
    "What": "图书管理系统的主函数，实现系统的核心功能",
    "When": "系统启动时",
    "Why": "作为程序的入口点，初始化系统并处理用户交互，实现图书管理的完整功能",
    "How": "创建图书馆对象，初始化测试数据，进入主循环处理用户输入",
    "Logic": "1. 创建并初始化图书馆对象\n2. 添加测试数据\n3. 进入主循环：\n   - 显示菜单\n   - 获取用户输入\n   - 处理用户选择\n   - 执行相应操作\n4. 清理资源并退出",
    "ErrorHandling": {
        "Initialization": "检查图书馆创建是否成功",
        "InputValidation": "验证用户输入的有效性",
        "MemoryManagement": "确保资源正确释放",
        "OperationStatus": "提供操作结果的反馈"
    },
    "Context": {
        "Module": "系统主模块",
        "DesignIntent": "实现完整的图书管理系统功能，提供用户友好的交互界面",
        "Dependencies": "依赖library.h和book.h中的所有功能"
    },
    "Hierarchy": {
        "Level": "系统顶层",
        "ParentModule": "无",
        "ChildModules": ["用户界面", "图书管理", "数据持久化"],
        "AbstractionLevel": "最高抽象，负责整体系统协调",
        "Role": {
            "InParent": "作为整个系统的入口点和协调者",
            "InChild": "为所有子系统提供统一的运行环境"
        }
    }
} */
int main(void) {
    Library* library = createLibrary();
    if (library == NULL) {
        printf("系统初始化失败！\n");
        return 1;
    }
    
    // 添加测试数据
    Book* book1 = createBook("C程序设计", "谭浩强", "9787111495482", 39.00, 2015, 1);
    Book* book2 = createBook("数据结构", "严蔚敏", "9787302147726", 35.00, 2012, 1);
    Book* book3 = createBook("算法导论", "Thomas H. Cormen", "9787111187776", 89.00, 2009, 1);
    
    addBook(library, book1);
    addBook(library, book2);
    addBook(library, book3);
    
    int choice;
    char isbn[MAX_ISBN_LEN];
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    float price;
    int year;
    
    while (1) {
        printMenu();
        scanf("%d", &choice);
        getchar(); // 清除换行符
        
        switch (choice) {
            case 1:
                printf("请输入书名：");
                fgets(title, MAX_TITLE_LEN, stdin);
                title[strcspn(title, "\n")] = 0;
                
                printf("请输入作者：");
                fgets(author, MAX_AUTHOR_LEN, stdin);
                author[strcspn(author, "\n")] = 0;
                
                printf("请输入ISBN：");
                fgets(isbn, MAX_ISBN_LEN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;
                
                printf("请输入价格：");
                scanf("%f", &price);
                getchar();
                
                printf("请输入出版年份：");
                scanf("%d", &year);
                getchar();
                
                Book* newBook = createBook(title, author, isbn, price, year, 1);
                if (newBook != NULL && addBook(library, newBook)) {
                    printf("添加成功！\n");
                } else {
                    printf("添加失败！\n");
                    destroyBook(newBook);
                }
                break;
                
            case 2:
                printf("请输入要删除的图书ISBN：");
                fgets(isbn, MAX_ISBN_LEN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;
                
                if (removeBook(library, isbn)) {
                    printf("删除成功！\n");
                } else {
                    printf("删除失败！\n");
                }
                break;
                
            case 3:
                printf("请输入要查找的图书ISBN：");
                fgets(isbn, MAX_ISBN_LEN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;
                
                Book* foundBook = findBookByISBN(library, isbn);
                if (foundBook != NULL) {
                    printBook(foundBook);
                } else {
                    printf("未找到该图书！\n");
                }
                break;
                
            case 4:
                listAllBooks(library);
                break;
                
            case 5:
                printf("请输入要借阅的图书ISBN：");
                fgets(isbn, MAX_ISBN_LEN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;
                
                if (borrowBook(library, isbn)) {
                    printf("借阅成功！\n");
                } else {
                    printf("借阅失败！\n");
                }
                break;
                
            case 6:
                printf("请输入要归还的图书ISBN：");
                fgets(isbn, MAX_ISBN_LEN, stdin);
                isbn[strcspn(isbn, "\n")] = 0;
                
                if (returnBook(library, isbn)) {
                    printf("归还成功！\n");
                } else {
                    printf("归还失败！\n");
                }
                break;
                
            case 7:
                sortBooksByTitle(library);
                printf("按标题排序完成！\n");
                break;
                
            case 8:
                sortBooksByAuthor(library);
                printf("按作者排序完成！\n");
                break;
                
            case 0:
                printf("感谢使用！再见！\n");
                destroyLibrary(library);
                return 0;
                
            default:
                printf("无效的选择，请重试！\n");
        }
        printf("\n");
    }
    
    return 0;
} 