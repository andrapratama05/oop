#include <iostream>
#include <ctime>
#include <mysql_driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "order.h"

using namespace std;

extern int current_user_id;

void create_order(sql::Connection* conn) {
    int id_menu, quantity;
    double total = 0;

    cout << "\n=== Buat Pesanan Baru ===\n";
    cout << "ID Menu: "; cin >> id_menu;
    cout << "Jumlah Pesanan: "; cin >> quantity;

    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT price FROM menus WHERE id_menu = ?");
    pstmt->setInt(1, id_menu);
    sql::ResultSet* res = pstmt->executeQuery();

    if (!res->next()) {
        cout << "Menu tidak ditemukan.\n";
        delete res;
        delete pstmt;
        return;
    }

    double price = res->getDouble("price");
    total = price * quantity;
    delete res;
    delete pstmt;

    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    char dateStr[20];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &ltm);

    pstmt = conn->prepareStatement("INSERT INTO orders (id_customer, total_price, order_date) VALUES (?, ?, ?)");
    pstmt->setInt(1, current_user_id);
    pstmt->setDouble(2, total);
    pstmt->setString(3, dateStr);
    pstmt->executeUpdate();
    delete pstmt;

    sql::Statement* stmt = conn->createStatement();
    sql::ResultSet* res2 = stmt->executeQuery("SELECT LAST_INSERT_ID() AS id");
    int order_id = 0;
    if (res2->next()) {
        order_id = res2->getInt("id");
    }
    delete res2;
    delete stmt;

    pstmt = conn->prepareStatement("INSERT INTO order_items (id_order, id_menu, number_of_product, subtotal) VALUES (?, ?, ?, ?)");
    pstmt->setInt(1, order_id);
    pstmt->setInt(2, id_menu);
    pstmt->setInt(3, quantity);
    pstmt->setDouble(4, total);
    pstmt->executeUpdate();
    delete pstmt;

    cout << "Pesanan berhasil dibuat dengan total: Rp " << total << endl;
}

void read_orders(sql::Connection* conn) {
    cout << "\n=== Riwayat Pesanan ===\n";
    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "SELECT o.id_order, o.total_price, o.order_date, m.name, oi.number_of_product FROM orders o "
        "JOIN order_items oi ON o.id_order = oi.id_order "
        "JOIN menus m ON oi.id_menu = m.id_menu WHERE o.id_customer = ?"
    );
    pstmt->setInt(1, current_user_id);
    sql::ResultSet* res = pstmt->executeQuery();

    while (res->next()) {
        cout << "Order ID: " << res->getInt("id_order")
            << ", Menu: " << res->getString("name")
            << ", Jumlah: " << res->getInt("number_of_product")
            << ", Total: Rp" << res->getDouble("total_price")
            << ", Tanggal: " << res->getString("order_date") << endl;
    }
    delete res;
    delete pstmt;
}

void update_order(sql::Connection* conn) {
    int id_order, new_quantity;
    cout << "\n=== Update Pesanan ===\n";
    cout << "ID Order: "; cin >> id_order;
    cout << "Jumlah Baru: "; cin >> new_quantity;

    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT id_menu FROM order_items WHERE id_order = ?");
    pstmt->setInt(1, id_order);
    sql::ResultSet* res = pstmt->executeQuery();

    if (!res->next()) {
        cout << "Pesanan tidak ditemukan.\n";
        delete res;
        delete pstmt;
        return;
    }

    int id_menu = res->getInt("id_menu");
    delete res;
    delete pstmt;

    pstmt = conn->prepareStatement("SELECT price FROM menus WHERE id_menu = ?");
    pstmt->setInt(1, id_menu);
    res = pstmt->executeQuery();
    res->next();
    double price = res->getDouble("price");
    double new_total = new_quantity * price;
    delete res;
    delete pstmt;

    pstmt = conn->prepareStatement("UPDATE order_items SET number_of_product = ?, subtotal = ? WHERE id_order = ?");
    pstmt->setInt(1, new_quantity);
    pstmt->setDouble(2, new_total);
    pstmt->setInt(3, id_order);
    pstmt->executeUpdate();
    delete pstmt;

    pstmt = conn->prepareStatement("UPDATE orders SET total_price = ? WHERE id_order = ?");
    pstmt->setDouble(1, new_total);
    pstmt->setInt(2, id_order);
    pstmt->executeUpdate();
    delete pstmt;

    cout << "Pesanan berhasil diperbarui.\n";
}

void delete_order(sql::Connection* conn) {
    int id_order;
    cout << "\n=== Hapus Pesanan ===\n";
    cout << "ID Order: "; cin >> id_order;

    sql::PreparedStatement* pstmt = conn->prepareStatement("DELETE FROM order_items WHERE id_order = ?");
    pstmt->setInt(1, id_order);
    pstmt->executeUpdate();
    delete pstmt;

    pstmt = conn->prepareStatement("DELETE FROM orders WHERE id_order = ?");
    pstmt->setInt(1, id_order);
    pstmt->executeUpdate();
    delete pstmt;

    cout << "Pesanan berhasil dihapus.\n";
}
