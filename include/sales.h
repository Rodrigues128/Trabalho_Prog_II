// Structs
// Date type
struct date
{
    int year; 
    int month;
    int day;
};

// Time type
struct time
{
    int h; // hours
    int m; // minute
    int s; // seconds
};

// Type Itens sold
struct product {
    char code[4];
    float price;
    int qty_sold;
};

struct sale {
    date sale_date;
    time sale_time;
    char CPF[11];
    product itens_sold[];

};


// Prototypes
void register_sale();

void list_sales_by_date();

void change_product_stock_and_price();

void remove_product_from_stock();

int menu(int option);