use crate::book::Book;
use std::cmp::Ordering;

const MAX_BOOKS: usize = 1000;

pub struct Library {
    books: Vec<Book>,
}

impl Library {
    pub fn new() -> Self {
        Library {
            books: Vec::with_capacity(MAX_BOOKS),
        }
    }

    pub fn add_book(&mut self, book: Book) -> bool {
        if self.books.len() >= MAX_BOOKS {
            return false;
        }
        self.books.push(book);
        true
    }

    pub fn remove_book(&mut self, isbn: &str) -> bool {
        if let Some(pos) = self.books.iter().position(|book| book.get_isbn() == isbn) {
            self.books.remove(pos);
            true
        } else {
            false
        }
    }

    pub fn find_book_by_isbn(&self, isbn: &str) -> Option<&Book> {
        self.books.iter().find(|book| book.get_isbn() == isbn)
    }

    pub fn find_book_by_title(&self, title: &str) -> Option<&Book> {
        self.books.iter().find(|book| book.get_title().contains(title))
    }

    pub fn list_all_books(&self) {
        if self.books.is_empty() {
            println!("图书馆暂无藏书");
            return;
        }

        println!("图书馆藏书列表（共{}本）：", self.books.len());
        for (i, book) in self.books.iter().enumerate() {
            println!("\n--- 第{}本书 ---", i + 1);
            book.print();
        }
    }

    pub fn borrow_book(&mut self, isbn: &str) -> bool {
        if let Some(book) = self.books.iter_mut().find(|book| book.get_isbn() == isbn) {
            if book.is_available() {
                book.set_availability(false);
                true
            } else {
                false
            }
        } else {
            false
        }
    }

    pub fn return_book(&mut self, isbn: &str) -> bool {
        if let Some(book) = self.books.iter_mut().find(|book| book.get_isbn() == isbn) {
            if !book.is_available() {
                book.set_availability(true);
                true
            } else {
                false
            }
        } else {
            false
        }
    }

    pub fn get_book_count(&self) -> usize {
        self.books.len()
    }

    pub fn sort_books_by_title(&mut self) {
        self.books.sort_by(|a, b| a.get_title().cmp(b.get_title()));
    }

    pub fn sort_books_by_author(&mut self) {
        self.books.sort_by(|a, b| a.get_author().cmp(b.get_author()));
    }
} 