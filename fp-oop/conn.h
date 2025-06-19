#pragma once

#ifndef CONN_H
#define CONN_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

sql::Connection* connection();

#endif CON_H
