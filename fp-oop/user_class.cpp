#include "user_class.h"
#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

User::User() : id(0), name(""), email(""), password(""), role("") {}

bool User::login(sql::Connection* conn) {
    std::cout << "\n=== LOGIN ===\n";
    std::cout << "Email: "; std::cin >> email;
    std::cout << "Password: "; std::cin >> password;

    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT * FROM users WHERE email = ? AND password = ?");
    pstmt->setString(1, email);
    pstmt->setString(2, password);
    sql::ResultSet* res = pstmt->executeQuery();

    if (res->next()) {
        id = res->getInt("id");
        name = res->getString("name");
        role = res->getString("role");
        std::cout << "\nLogin berhasil. Selamat datang, " << name << "!\n";
        delete res;
        delete pstmt;
        return true;
    }
    else {
        std::cout << "\nLogin gagal. Email atau password salah.\n";
        delete res;
        delete pstmt;
        return false;
    }
}

User::~User() {}


bool User::register_user(sql::Connection* conn) {
    std::cin.ignore();
    std::cout << "\n=== REGISTRASI ===\n";
    std::cout << "Nama: "; std::getline(std::cin, name);
    std::cout << "Email: "; std::getline(std::cin, email);
    std::cout << "Password: "; std::getline(std::cin, password);

    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "INSERT INTO users (name, email, password, role) VALUES (?, ?, ?, 'customer')"
    );
    pstmt->setString(1, name);
    pstmt->setString(2, email);
    pstmt->setString(3, password);
    pstmt->executeUpdate();
    delete pstmt;

    std::cout << "\nRegistrasi berhasil. Silakan login.\n";
    return true;
}

int User::get_id() const {
    return id;
}

std::string User::get_role() const {
    return role;
}

std::string User::get_name() const {
    return name;
}