#include "order_class.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <ctime>

Order::Order(int customer_id)
    : customer_id(customer_id), total_price(0), order_id(0) {
}

void Order::add_item(int id_menu, int quantity) {
    items.push_back({ id_menu, quantity });
}

double Order::calculate_total(sql::Connection* conn) {
    total_price = 0.0;
    for (auto& item : items) {
        sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT price FROM menus WHERE id_menu = ?");
        pstmt->setInt(1, item.id_menu);
        sql::ResultSet* res = pstmt->executeQuery();
        if (res->next()) {
            double price = res->getDouble("price");
            total_price += price * item.quantity;
        }
        delete res;
        delete pstmt;
    }
    return total_price;
}

bool Order::save(sql::Connection* conn) {
    calculate_total(conn);

    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    char dateStr[20];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &ltm);

    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "INSERT INTO orders (id_customer, total_price, order_date) VALUES (?, ?, ?)"
    );
    pstmt->setInt(1, customer_id);
    pstmt->setDouble(2, total_price);
    pstmt->setString(3, dateStr);
    pstmt->executeUpdate();
    delete pstmt;

    sql::Statement* stmt = conn->createStatement();
    sql::ResultSet* res = stmt->executeQuery("SELECT LAST_INSERT_ID() AS id");
    if (res->next()) {
        order_id = res->getInt("id");
    }
    delete res;
    delete stmt;

    for (auto& item : items) {
        pstmt = conn->prepareStatement(
            "INSERT INTO order_items (id_order, id_menu, number_of_product, subtotal) VALUES (?, ?, ?, ?)"
        );
        pstmt->setInt(1, order_id);
        pstmt->setInt(2, item.id_menu);
        pstmt->setInt(3, item.quantity);
        pstmt->setDouble(4, 0.0); // optional: bisa dihitung ulang jika ada harga
        pstmt->executeUpdate();
        delete pstmt;
    }
    return true;
}

int Order::get_order_id() const {
    return order_id;
}
