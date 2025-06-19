#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "auth.h"
#include "menu.h"
#include "order.h"
#include "user.h"

using namespace std;

// variabel login global dideklarasikan di auth.cpp, cukup deklarasi ekstern di sini
extern int current_user_id;
extern std::string current_user_role;
extern bool is_logged_in;

sql::Connection* connect_db() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* conn;
    driver = sql::mysql::get_mysql_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "");
    conn->setSchema("catering");
    return conn;
}

int main() {
    sql::Connection* conn = connect_db();

    int auth_choice;
    do {
        cout << "\n=== SELAMAT DATANG DI APLIKASI CATERING ===\n";
        cout << "1. Login\n";
        cout << "2. Registrasi\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> auth_choice;

        if (auth_choice == 1) {
            if (login(conn)) break;
        }
        else if (auth_choice == 2) {
            register_user(conn);
        }
        else if (auth_choice == 0) {
            delete conn;
            return 0;
        }
        else {
            cout << "Pilihan tidak valid.\n";
        }
    } while (true);

    int pilih;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        if (current_user_role == "admin") {
            cout << "1. Tambah Menu\n";
            cout << "2. Lihat Menu\n";
            cout << "3. Ubah Harga Menu\n";
            cout << "4. Hapus Menu\n";
            cout << "5. Tambah User\n";
            cout << "6. Lihat User\n";
            cout << "7. Hapus User\n";
        }
        if (current_user_role == "customer") {
            cout << "1. Lihat Menu\n";
            cout << "2. Buat Pesanan\n";
            cout << "3. Lihat Pesanan\n";
            cout << "4. Update Pesanan\n";
            cout << "5. Hapus Pesanan\n";
        }
        cout << "0. Logout dan Keluar\n";
        cout << "Pilih: "; cin >> pilih;

        if (current_user_role == "admin") {
            switch (pilih) {
            case 1: create_menu(conn); break;
            case 2: read_menus(conn); break;
            case 3: update_menu(conn); break;
            case 4: delete_menu(conn); break;
            case 5: create_user(conn); break;
            case 6: read_users(conn); break;
            case 7: delete_user(conn); break;
            case 0: logout(); break;
            default: cout << "Pilihan tidak valid.\n"; break;
            }
        }
        else if (current_user_role == "customer") {
            switch (pilih) {
            case 1: read_menus(conn); break;
            case 2: create_order(conn); break;
            case 3: read_orders(conn); break;
            case 4: update_order(conn); break;
            case 5: delete_order(conn); break;
            case 0: logout(); break;
            default: cout << "Pilihan tidak valid.\n"; break;
            }
        }

    } while (is_logged_in);

    delete conn;
    return 0;
}
