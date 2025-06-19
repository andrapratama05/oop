#include <iostream>
#include <mysql_driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "user.h"

using namespace std;

void create_user(sql::Connection* conn) {
    string name, email, password, role;
    cout << "\n=== Tambah User Baru ===\n";
    cin.ignore();
    cout << "Nama: "; getline(cin, name);
    cout << "Email: "; getline(cin, email);
    cout << "Password: "; getline(cin, password);
    cout << "Role (admin/customer): "; getline(cin, role);

    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "INSERT INTO users (name, email, password, role) VALUES (?, ?, ?, ?)"
    );
    pstmt->setString(1, name);
    pstmt->setString(2, email);
    pstmt->setString(3, password);
    pstmt->setString(4, role);
    pstmt->executeUpdate();
    delete pstmt;

    cout << "User berhasil ditambahkan.\n";
}

void read_users(sql::Connection* conn) {
    cout << "\n=== Daftar User ===\n";
    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT * FROM users");
    sql::ResultSet* res = pstmt->executeQuery();

    while (res->next()) {
        cout << "ID: " << res->getInt("id") << ", Nama: " << res->getString("name")
            << ", Email: " << res->getString("email") << ", Role: " << res->getString("role") << endl;
    }
    delete res;
    delete pstmt;
}

void delete_user(sql::Connection* conn) {
    int id;
    cout << "\n=== Hapus User ===\n";
    cout << "ID User: "; cin >> id;

    sql::PreparedStatement* pstmt = conn->prepareStatement("DELETE FROM users WHERE id = ?");
    pstmt->setInt(1, id);
    pstmt->executeUpdate();
    delete pstmt;

    cout << "User berhasil dihapus.\n";
}
