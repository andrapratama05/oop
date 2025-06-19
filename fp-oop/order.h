#pragma once
#ifndef ORDER_H
#define ORDER_H

#include <mysql_connection.h>

void create_order(sql::Connection* conn);
void read_orders(sql::Connection* conn);
void update_order(sql::Connection* conn);
void delete_order(sql::Connection* conn);

#endif
