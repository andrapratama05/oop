#pragma once
#ifndef MENU_H
#define MENU_H

#include <mysql_connection.h>

void create_menu(sql::Connection* conn);
void read_menus(sql::Connection* conn);
void update_menu(sql::Connection* conn);
void delete_menu(sql::Connection* conn);

#endif
