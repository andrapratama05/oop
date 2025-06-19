#ifndef MENU_H
#define MENU_H

#include <string>
#include <mysql_connection.h>

class Menu {
private:
    int id;
    std::string name;
    std::string description;
    std::string category;
    double price;

public:
    Menu();
    Menu(int id, const std::string& name, const std::string& desc, const std::string& category, double price);

    void create(sql::Connection* conn);
    static void read_all(sql::Connection* conn);
    void update(sql::Connection* conn);
    void remove(sql::Connection* conn);

    void input_from_console();
    int get_id() const;
    void set_id(int menu_id);
};

#endif
