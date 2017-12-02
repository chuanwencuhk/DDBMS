#ifndef MYSQLCONNECTOR_H
#define MYSQLCONNECTOR_H

#include "global.h"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


class MysqlConnector
{
public:
    MysqlConnector();

private:
    sql::Driver* p_mysql_driver;
    sql::Connection* p_mysql_connection;
    sql::Statement* p_mysql_statement;
    sql::ResultSet* p_mysql_resultset;

};

#endif // MYSQLCONNECTOR_H
