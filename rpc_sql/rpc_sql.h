#include <string>
#include <iostream>
#include "rpc/client.h"

using std::string;


bool RPCExecute(string host_ip, string sql_statement);

string RPCExecuteQuery(string host_ip, string sql_statement);

int RPCExecuteUpdate(string host_ip, string sql_statement);

bool RPCInsertFileToTable(string host_ip, string sql_file, string table_name);