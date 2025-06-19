#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

sql::Connection* connection() {
	string host = "tcp://127.0.0.1:3306";
	string user = "root";
	string password = "";
	string db = "catering";

	sql::mysql::MySQL_Driver* driver;
	sql::Connection* conn = nullptr;

	try {
		driver = sql::mysql::get_mysql_driver_instance();
		conn = driver->connect(host, user, password);
	}
	catch (sql::SQLException& e) {
		cerr << "SQLException: " << e.what() << endl;
		cerr << "Error Code: " << e.getErrorCode() << endl;
		cerr << "SQLState: " << e.getSQLState() << endl;
	}

	return conn;
}
