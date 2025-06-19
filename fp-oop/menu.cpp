#include "menu.h"
#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

Menu::Menu() : id(0), price(0.0) {}

Menu::Menu(int id, const std::string& name, const std::string& desc, const std::string& category, double price)
    : id(id), name(name), description(desc), category(category), price(price) {
}

void Menu::input_from_console() {
    std::cin.ignore();
    std::cout << "Nama menu: "; std::getline(std::cin, name);
    std::cout << "Deskripsi: "; std::getline(std::cin, description);
    std::cout << "Kategori: "; std::getline(std::cin, category);
    std::cout << "Harga: "; std::cin >> price;
}

void Menu::create(sql::Connection* conn) {
    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "INSERT INTO menus (name, description, category, price) VALUES (?, ?, ?, ?)"
    );
    pstmt->setString(1, name);
    pstmt->setString(2, description);
    pstmt->setString(3, category);
    pstmt->setDouble(4, price);
    pstmt->executeUpdate();
    delete pstmt;
    std::cout << "Menu berhasil ditambahkan.\n";
}

void Menu::read_all(sql::Connection* conn) {
    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT * FROM menus");
    sql::ResultSet* res = pstmt->executeQuery();
    std::cout << "\n=== DAFTAR MENU ===\n";
    while (res->next()) {
        std::cout << res->getInt("id_menu") << ". "
            << res->getString("name") << " - "
            << res->getString("category") << " - Rp"
            << res->getDouble("price") << "\n"
            << "   " << res->getString("description") << "\n";
    }
    delete res;
    delete pstmt;
}

void Menu::update(sql::Connection* conn) {
    input_from_console();
    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "UPDATE menus SET name=?, description=?, category=?, price=? WHERE id_menu=?"
    );
    pstmt->setString(1, name);
    pstmt->setString(2, description);
    pstmt->setString(3, category);
    pstmt->setDouble(4, price);
    pstmt->setInt(5, id);
    pstmt->executeUpdate();
    delete pstmt;
    std::cout << "Menu berhasil diperbarui.\n";
}

void Menu::remove(sql::Connection* conn) {
    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "DELETE FROM menus WHERE id_menu=?"
    );
    pstmt->setInt(1, id);
    pstmt->executeUpdate();
    delete pstmt;
    std::cout << "Menu berhasil dihapus.\n";
}

int Menu::get_id() const {
    return id;
}

void Menu::set_id(int menu_id) {
    id = menu_id;
}