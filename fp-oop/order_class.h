#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <mysql_connection.h>

struct OrderItem {
    int id_menu;
    int quantity;
};

class Order {
private:
    int order_id;
    int customer_id;
    double total_price;
    std::string order_date;
    std::vector<OrderItem> items;

public:
    Order(int customer_id);
    void add_item(int id_menu, int quantity);
    double calculate_total(sql::Connection* conn);
    bool save(sql::Connection* conn);
    int get_order_id() const;
};

#endif
