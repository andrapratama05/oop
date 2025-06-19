#include "user_inheritance.h"
#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

Admin::Admin() : User() {}

void Admin::add_menu(sql::Connection* conn) {
    std::string name, desc, category;
    double price;
    std::cin.ignore();
    std::cout << "\n=== TAMBAH MENU ===\n";
    std::cout << "Nama menu: "; std::getline(std::cin, name);
    std::cout << "Deskripsi: "; std::getline(std::cin, desc);
    std::cout << "Kategori: "; std::getline(std::cin, category);
    std::cout << "Harga: "; std::cin >> price;

    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "INSERT INTO menus (name, description, category, price) VALUES (?, ?, ?, ?)"
    );
    pstmt->setString(1, name);
    pstmt->setString(2, desc);
    pstmt->setString(3, category);
    pstmt->setDouble(4, price);
    pstmt->executeUpdate();
    delete pstmt;

    std::cout << "Menu berhasil ditambahkan.\n";
}

void Admin::view_users(sql::Connection* conn) {
    std::cout << "\n=== DAFTAR USER ===\n";
    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT id, name, email, role FROM users");
    sql::ResultSet* res = pstmt->executeQuery();
    while (res->next()) {
        std::cout << res->getInt("id") << ". "
            << res->getString("name") << " ("
            << res->getString("role") << ") - "
            << res->getString("email") << "\n";
    }
    delete res;
    delete pstmt;
}

Customer::Customer() : User() {}

void Customer::search_menu(sql::Connection* conn, const std::string& keyword) {
    std::cout << "\n=== HASIL PENCARIAN MENU ===\n";
    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "SELECT * FROM menus WHERE name LIKE ? OR category LIKE ?"
    );
    std::string like_keyword = "%" + keyword + "%";
    pstmt->setString(1, like_keyword);
    pstmt->setString(2, like_keyword);
    sql::ResultSet* res = pstmt->executeQuery();
    while (res->next()) {
        std::cout << "- " << res->getString("name") << ": Rp"
            << res->getDouble("price") << "\n";
    }
    delete res;
    delete pstmt;
}
