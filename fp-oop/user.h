#pragma once
// user.h
#ifndef USER_H
#define USER_H

#include <mysql_connection.h>

void create_user(sql::Connection* conn);
void read_users(sql::Connection* conn);
void delete_user(sql::Connection* conn);

#endif