#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "conn.h"

using namespace std;

int dashboard_registrasi(int &pilihan);

int main() {
    sql::Connection* conn = connection();

    // Dashboard registrasi
    int pilihan;
    dashboard_registrasi(pilihan);
    

    system("cls");
    if (pilihan == 1) {

    }
    else if (pilihan == 2) {

    }
    else {
        dashboard_registrasi(pilihan);
    }

    delete conn;
    return 0;
}

int dashboard_registrasi(int &pilihan) {
    cout << "===SELAMAT DATANG DI CATERING DEZ===" << endl;
    cout << "       +------------------+" << endl;
    cout << "       | 1. Register User |" << endl;
    cout << "       | 2. Login User    |" << endl;
    cout << "       +------------------+" << endl;
    cout << "Silahkan masukkan pilihan anda: ";
    cin >> pilihan;

    return pilihan;
}