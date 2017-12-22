#include "rpc_sql.h"
#include <cassert>

bool RPCExecute(string host_port, string sql_statement){
    rpc::client client(host_port, rpc::constants::DEFAULT_PORT);
    bool ok = client.call("localExecute", sql_statement).as<bool>();
    return ok;
}

string RPCExecuteQuery(string host_port, string sql_statement){
	rpc::client client(host_port, rpc::constants::DEFAULT_PORT);
    string result = client.call("localExecuteQuery", sql_statement).as<string>();
    return result;	
}

int RPCExecuteUpdate(string host_port, string sql_statement){
	rpc::client client(host_port, rpc::constants::DEFAULT_PORT);
    int cnt = client.call("localExecuteUpdate", sql_statement).as<string>();
    return cnt;
}

bool RPCInsertFileToTable((string host_port, string sql_file, string table_name){
	rpc::client client(host_port, rpc::constants::DEFAULT_PORT);
	bool ok = client.call("localInsertFileToTable", sql_file, table_name);
	return ok;
}