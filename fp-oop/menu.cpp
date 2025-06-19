#include <iostream>
#include <mysql_driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "menu.h"

using namespace std;

void create_menu(sql::Connection* conn) {
    string name, description, category;
    double price;
    cout << "\n=== Tambah Menu Baru ===\n";
    cin.ignore();
    cout << "Nama Menu: "; getline(cin, name);
    cout << "Deskripsi: "; getline(cin, description);
    cout << "Kategori: "; getline(cin, category);
    cout << "Harga: "; cin >> price;

    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "INSERT INTO menus (name, description, price, category) VALUES (?, ?, ?, ?)"
    );
    pstmt->setString(1, name);
    pstmt->setString(2, description);
    pstmt->setDouble(3, price);
    pstmt->setString(4, category);
    pstmt->executeUpdate();
    delete pstmt;

    cout << "Menu berhasil ditambahkan.\n";
}

void read_menus(sql::Connection* conn) {
    cout << "\n=== Daftar Menu ===\n";
    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT * FROM menus");
    sql::ResultSet* res = pstmt->executeQuery();

    while (res->next()) {
        cout << "ID: " << res->getInt("id_menu") << ", Nama: " << res->getString("name")
            << ", Harga: Rp" << res->getDouble("price") << ", Kategori: " << res->getString("category") << endl;
    }
    delete res;
    delete pstmt;
}

void update_menu(sql::Connection* conn) {
    int id;
    double new_price;
    cout << "\n=== Ubah Harga Menu ===\n";
    cout << "ID Menu: "; cin >> id;
    cout << "Harga Baru: "; cin >> new_price;

    sql::PreparedStatement* pstmt = conn->prepareStatement("UPDATE menus SET price = ? WHERE id_menu = ?");
    pstmt->setDouble(1, new_price);
    pstmt->setInt(2, id);
    pstmt->executeUpdate();
    delete pstmt;

    cout << "Harga menu berhasil diperbarui.\n";
}

void delete_menu(sql::Connection* conn) {
    int id;
    cout << "\n=== Hapus Menu ===\n";
    cout << "ID Menu: "; cin >> id;

    sql::PreparedStatement* pstmt = conn->prepareStatement("DELETE FROM menus WHERE id_menu = ?");
    pstmt->setInt(1, id);
    pstmt->executeUpdate();
    delete pstmt;

    cout << "Menu berhasil dihapus.\n";
}
