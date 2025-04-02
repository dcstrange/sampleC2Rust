mod book;
mod library;

use book::Book;
use library::Library;
use std::io::{self, Write};

fn print_menu() {
    println!("\n=== 图书管理系统 ===");
    println!("1. 添加新书");
    println!("2. 删除图书");
    println!("3. 查找图书");
    println!("4. 借阅图书");
    println!("5. 归还图书");
    println!("6. 显示所有图书");
    println!("7. 按书名排序");
    println!("8. 按作者排序");
    println!("0. 退出");
    print!("请选择操作: ");
    io::stdout().flush().unwrap();
}

fn read_line() -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn read_number<T: std::str::FromStr>() -> T {
    loop {
        let input = read_line();
        if let Ok(num) = input.parse() {
            return num;
        }
        print!("请输入有效的数字: ");
        io::stdout().flush().unwrap();
    }
}

fn main() {
    let mut library = Library::new();

    // 添加测试数据
    let book1 = Book::new("C程序设计", "谭浩强", "9787111495482", 2015, 39.80);
    let book2 = Book::new("算法导论", "Thomas H. Cormen", "9787111187776", 2006, 89.00);
    let book3 = Book::new("深入理解计算机系统", "Randal E. Bryant", "9787111321330", 2010, 139.00);
    
    library.add_book(book1);
    library.add_book(book2);
    library.add_book(book3);

    loop {
        print_menu();
        let choice: i32 = read_number();

        match choice {
            1 => {
                print!("请输入书名: ");
                io::stdout().flush().unwrap();
                let title = read_line();
                print!("请输入作者: ");
                io::stdout().flush().unwrap();
                let author = read_line();
                print!("请输入ISBN: ");
                io::stdout().flush().unwrap();
                let isbn = read_line();
                print!("请输入出版年份: ");
                io::stdout().flush().unwrap();
                let year: i32 = read_number();
                print!("请输入价格: ");
                io::stdout().flush().unwrap();
                let price: f32 = read_number();

                let new_book = Book::new(&title, &author, &isbn, year, price);
                if library.add_book(new_book) {
                    println!("添加成功！");
                } else {
                    println!("添加失败！");
                }
            }
            2 => {
                print!("请输入要删除的图书ISBN: ");
                io::stdout().flush().unwrap();
                let isbn = read_line();
                if library.remove_book(&isbn) {
                    println!("删除成功！");
                } else {
                    println!("删除失败！");
                }
            }
            3 => {
                print!("请输入要查找的图书ISBN: ");
                io::stdout().flush().unwrap();
                let isbn = read_line();
                if let Some(book) = library.find_book_by_isbn(&isbn) {
                    book.print();
                } else {
                    println!("未找到该图书！");
                }
            }
            4 => {
                print!("请输入要借阅的图书ISBN: ");
                io::stdout().flush().unwrap();
                let isbn = read_line();
                if library.borrow_book(&isbn) {
                    println!("借阅成功！");
                } else {
                    println!("借阅失败！");
                }
            }
            5 => {
                print!("请输入要归还的图书ISBN: ");
                io::stdout().flush().unwrap();
                let isbn = read_line();
                if library.return_book(&isbn) {
                    println!("归还成功！");
                } else {
                    println!("归还失败！");
                }
            }
            6 => {
                library.list_all_books();
            }
            7 => {
                library.sort_books_by_title();
                println!("按书名排序完成！");
                library.list_all_books();
            }
            8 => {
                library.sort_books_by_author();
                println!("按作者排序完成！");
                library.list_all_books();
            }
            0 => {
                println!("感谢使用！再见！");
                break;
            }
            _ => {
                println!("无效的选择！");
            }
        }
    }
} 