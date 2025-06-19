#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include "user_class.h"
#include "user_inheritance.h"
#include "menu.h"
#include "order_class.h"

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

    User* user = nullptr;
    bool success = false;
    int auth_choice;

    do {
        std::cout << "\n=== SELAMAT DATANG DI APLIKASI CATERING ===\n";
        std::cout << "1. Login\n";
        std::cout << "2. Registrasi\n";
        std::cout << "0. Keluar\n";
        std::cout << "Pilihan: ";
        std::cin >> auth_choice;

        if (auth_choice == 1) {
            std::cout << "Login sebagai: [1] Admin, [2] Customer: ";
            int tipe; std::cin >> tipe;
            if (tipe == 1) user = new Admin();
            else user = new Customer();
            success = user->login(conn);
        }
        else if (auth_choice == 2) {
            user = new Customer();
            success = user->register_user(conn);
            delete user;
            user = nullptr;
        }
        else if (auth_choice == 0) {
            break;
        }
    } while (!success);

    if (!user) {
        delete conn;
        return 0;
    }

    int pilih;
    if (user->get_role() == "admin") {
        Admin* admin = dynamic_cast<Admin*>(user);
        do {
            std::cout << "\n=== MENU ADMIN ===\n";
            std::cout << "1. Tambah Menu\n";
            std::cout << "2. Lihat Menu\n";
            std::cout << "3. Ubah Menu\n";
            std::cout << "4. Hapus Menu\n";
            std::cout << "5. Lihat Users\n";
            std::cout << "0. Logout\n";
            std::cout << "Pilihan: "; std::cin >> pilih;

            switch (pilih) {
            case 1: {
                Menu m;
                m.input_from_console();
                m.create(conn);
                break;
            }
            case 2: Menu::read_all(conn); break;
            case 3: {
                int id;
                std::cout << "Masukkan ID menu yang ingin diubah: ";
                std::cin >> id;
                Menu m;
                m.set_id(id);
                m.update(conn);
                break;
            }
            case 4: {
                int id;
                std::cout << "Masukkan ID menu yang ingin dihapus: ";
                std::cin >> id;
                Menu m;
                m.set_id(id);
                m.remove(conn);
                break;
            }
            case 5: admin->view_users(conn); break;
            case 0: break;
            default: std::cout << "Pilihan tidak valid.\n"; break;
            }
        } while (pilih != 0);

    }
    else {
        Customer* customer = dynamic_cast<Customer*>(user);
        do {
            std::cout << "\n=== MENU CUSTOMER ===\n";
            std::cout << "1. Lihat Menu\n";
            std::cout << "2. Cari Menu\n";
            std::cout << "3. Buat Pesanan\n";
            std::cout << "0. Logout\n";
            std::cout << "Pilihan: "; std::cin >> pilih;

            switch (pilih) {
            case 1: Menu::read_all(conn); break;
            case 2: {
                std::string keyword;
                std::cout << "Masukkan kata kunci: ";
                std::cin >> keyword;
                customer->search_menu(conn, keyword);
                break;
            }
            case 3: {
                Order order(customer->get_id());
                char lanjut;
                do {
                    int id, qty;
                    std::cout << "Masukkan ID Menu: "; std::cin >> id;
                    std::cout << "Jumlah: "; std::cin >> qty;
                    order.add_item(id, qty);
                    std::cout << "Tambah menu lagi? (y/n): "; std::cin >> lanjut;
                } while (lanjut == 'y' || lanjut == 'Y');
                order.save(conn);
                break;
            }
            case 0: break;
            default: std::cout << "Pilihan tidak valid.\n"; break;
            }
        } while (pilih != 0);
    }

    delete user;
    delete conn;
    return 0;
}
