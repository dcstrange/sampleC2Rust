#include <stdio.h>
#include "book.h"
#include "library.h"

/* {
    "What": "打印系统主菜单",
    "When": "用户需要选择操作时",
    "Why": "提供清晰的操作界面，展示所有可用功能",
    "How": "使用printf函数格式化输出菜单选项"
} */
void printMenu() {
    printf("\n=== 图书管理系统 ===\n");
    printf("1. 添加新书\n");
    printf("2. 删除图书\n");
    printf("3. 查找图书\n");
    printf("4. 借阅图书\n");
    printf("5. 归还图书\n");
    printf("6. 显示所有图书\n");
    printf("7. 按书名排序\n");
    printf("8. 按作者排序\n");
    printf("0. 退出\n");
    printf("请选择操作: ");
}

/* {
    "What": "系统主函数，实现图书管理系统的核心功能",
    "When": "系统启动时",
    "Why": "提供完整的图书管理系统功能，包括图书的增删改查和排序",
    "How": "创建图书馆对象，初始化测试数据，实现交互式菜单系统"
} */
int main() {
    Library* library = createLibrary();
    if (library == NULL) {
        printf("创建图书馆失败！\n");
        return 1;
    }

    // 添加一些测试数据
    Book* book1 = createBook("C程序设计", "谭浩强", "9787111495482", 2015, 39.80);
    Book* book2 = createBook("算法导论", "Thomas H. Cormen", "9787111187776", 2006, 89.00);
    Book* book3 = createBook("深入理解计算机系统", "Randal E. Bryant", "9787111321330", 2010, 139.00);
    
    addBook(library, book1);
    addBook(library, book2);
    addBook(library, book3);

    int choice;
    char isbn[20];
    char title[100];
    char author[50];
    int year;
    float price;

    do {
        printMenu();
        scanf("%d", &choice);
        getchar(); // 清除换行符

        switch (choice) {
            case 1:
                printf("请输入书名: ");
                gets(title);
                printf("请输入作者: ");
                gets(author);
                printf("请输入ISBN: ");
                gets(isbn);
                printf("请输入出版年份: ");
                scanf("%d", &year);
                printf("请输入价格: ");
                scanf("%f", &price);
                
                Book* newBook = createBook(title, author, isbn, year, price);
                if (addBook(library, newBook)) {
                    printf("添加成功！\n");
                } else {
                    printf("添加失败！\n");
                    destroyBook(newBook);
                }
                break;

            case 2:
                printf("请输入要删除的图书ISBN: ");
                gets(isbn);
                if (removeBook(library, isbn)) {
                    printf("删除成功！\n");
                } else {
                    printf("删除失败！\n");
                }
                break;

            case 3:
                printf("请输入要查找的图书ISBN: ");
                gets(isbn);
                Book* found = findBookByISBN(library, isbn);
                if (found) {
                    printBook(found);
                } else {
                    printf("未找到该图书！\n");
                }
                break;

            case 4:
                printf("请输入要借阅的图书ISBN: ");
                gets(isbn);
                if (borrowBook(library, isbn)) {
                    printf("借阅成功！\n");
                } else {
                    printf("借阅失败！\n");
                }
                break;

            case 5:
                printf("请输入要归还的图书ISBN: ");
                gets(isbn);
                if (returnBook(library, isbn)) {
                    printf("归还成功！\n");
                } else {
                    printf("归还失败！\n");
                }
                break;

            case 6:
                listAllBooks(library);
                break;

            case 7:
                sortBooksByTitle(library);
                printf("按书名排序完成！\n");
                listAllBooks(library);
                break;

            case 8:
                sortBooksByAuthor(library);
                printf("按作者排序完成！\n");
                listAllBooks(library);
                break;

            case 0:
                printf("感谢使用！再见！\n");
                break;

            default:
                printf("无效的选择！\n");
        }
    } while (choice != 0);

    destroyLibrary(library);
    return 0;
} 