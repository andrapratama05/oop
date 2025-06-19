#ifndef USER_H
#define USER_H

#include <string>
#include <mysql_connection.h>

class User {
private:
    int id;
    std::string name;
    std::string email;
    std::string password;
    std::string role;

public:
    User();
    virtual ~User();
    bool login(sql::Connection* conn);
    bool register_user(sql::Connection* conn);
    int get_id() const;
    std::string get_role() const;
    std::string get_name() const;
};

#endif
