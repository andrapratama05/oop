#pragma once
#ifndef AUTH_H
#define AUTH_H

#include <mysql_connection.h>
#include <string>

extern int current_user_id;
extern std::string current_user_role;
extern bool is_logged_in;

bool login(sql::Connection* conn);
void logout();
void register_user(sql::Connection* conn);

#endif
