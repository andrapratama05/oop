#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "auth.h"

using namespace std;

int current_user_id = 0;
string current_user_role = "";
bool is_logged_in = false;

bool login(sql::Connection* conn) {
    string email, password;
    cout << "\n=== LOGIN ===\n";
    cout << "Email: "; cin >> email;
    cout << "Password: "; cin >> password;

    sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT * FROM users WHERE email = ? AND password = ?");
    pstmt->setString(1, email);
    pstmt->setString(2, password);
    sql::ResultSet* res = pstmt->executeQuery();

    if (res->next()) {
        current_user_id = res->getInt("id");
        current_user_role = res->getString("role");
        is_logged_in = true;
        cout << "\nLogin berhasil. Selamat datang, " << res->getString("name") << "!\n";
        delete res;
        delete pstmt;
        return true;
    }
    else {
        cout << "\nLogin gagal. Email atau password salah.\n";
        delete res;
        delete pstmt;
        return false;
    }
}

void logout() {
    current_user_id = 0;
    current_user_role = "";
    is_logged_in = false;
    cout << "\nAnda berhasil logout.\n";
}

void register_user(sql::Connection* conn) {
    string name, email, password;
    cout << "\n=== REGISTRASI USER BARU ===\n";
    cin.ignore(); // membersihkan newline dari input sebelumnya
    cout << "Nama: ";
    getline(cin, name);
    cout << "Email: ";
    getline(cin, email);
    cout << "Password: ";
    getline(cin, password);

    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "INSERT INTO users (name, email, password, role) VALUES (?, ?, ?, 'customer')"
    );
    pstmt->setString(1, name);
    pstmt->setString(2, email);
    pstmt->setString(3, password);
    pstmt->executeUpdate();
    delete pstmt;

    cout << "\nRegistrasi berhasil. Silakan login.\n";
}
