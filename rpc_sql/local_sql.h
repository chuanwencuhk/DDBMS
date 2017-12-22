#include <mysql_connection.h>  
#include <mysql_driver.h>  
#include <statement.h>  
#include <cassert>
#include <resultset_metadata.h>
#include <string>
#include <fstream>

using sql::mysql::MySQL_Driver;
using sql::Connection;
using sql::Statement;
using std::string;
using sql::ResultSet;
using std::ofstream;


bool localExecute(string sql_statement);

string localExecuteQuery(string sql_statement);

int localExecuteUpdate(string sql_statement);

bool localInsertFileToTable(string sql_file, string table_name);

string getMySQLIp();
string getUsername();
string getPassword();