#[derive(Debug, Clone)]
pub struct Book {
    title: String,
    author: String,
    isbn: String,
    year: i32,
    price: f32,
    available: bool,
}

impl Book {
    pub fn new(title: &str, author: &str, isbn: &str, year: i32, price: f32) -> Self {
        Book {
            title: title.to_string(),
            author: author.to_string(),
            isbn: isbn.to_string(),
            year,
            price,
            available: true,
        }
    }

    pub fn print(&self) {
        println!("书名: {}", self.title);
        println!("作者: {}", self.author);
        println!("ISBN: {}", self.isbn);
        println!("出版年份: {}", self.year);
        println!("价格: {:.2}", self.price);
        println!("状态: {}", if self.available { "可借" } else { "已借出" });
    }

    pub fn update_price(&mut self, new_price: f32) -> bool {
        if new_price < 0.0 {
            return false;
        }
        self.price = new_price;
        true
    }

    pub fn update_year(&mut self, new_year: i32) -> bool {
        if new_year < 1800 || new_year > 2024 {
            return false;
        }
        self.year = new_year;
        true
    }

    pub fn is_available(&self) -> bool {
        self.available
    }

    pub fn set_availability(&mut self, available: bool) {
        self.available = available;
    }

    pub fn get_title(&self) -> &str {
        &self.title
    }

    pub fn get_author(&self) -> &str {
        &self.author
    }

    pub fn get_isbn(&self) -> &str {
        &self.isbn
    }
} 