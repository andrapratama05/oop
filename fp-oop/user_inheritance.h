#pragma once
#ifndef USER_INHERITANCE_H
#define USER_INHERITANCE_H

#include "user_class.h"
#include <mysql_connection.h>
#include <string>

class Admin : public User {
public:
    Admin();
    void add_menu(sql::Connection* conn);
    void view_users(sql::Connection* conn);
};

class Customer : public User {
public:
    Customer();
    void search_menu(sql::Connection* conn, const std::string& keyword);
};

#endif
