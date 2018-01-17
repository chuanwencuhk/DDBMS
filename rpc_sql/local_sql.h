#include <mysql_connection.h>  
#include <mysql_driver.h>  
#include <cppconn/statement.h>  
#include <cassert>
#include <cppconn/resultset_metadata.h>
#include <string>
#include <fstream>

using sql::mysql::MySQL_Driver;
using sql::Connection;
using sql::Statement;
using std::string;
using sql::ResultSet;
using std::ofstream;


bool localExecute(string dbname, string sql_statement);

string localExecuteQuery(string dbname, string sql_statement);

int localExecuteUpdate(string dbname, string sql_statement);

bool localInsertFileToTable(string dbname, string sql_file, string table_name);

string getMySQLIp();
string getUsername();
string getPassword();