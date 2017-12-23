#include "rpc_sql.h"
#include <cassert>

bool RPCExecute(string host_ip, string sql_statement){
    rpc::client client(host_ip, rpc::constants::DEFAULT_PORT);
    bool ok = client.call("localExecute", sql_statement).as<bool>();
    return ok;
}

string RPCExecuteQuery(string host_ip, string sql_statement){
	rpc::client client(host_ip, rpc::constants::DEFAULT_PORT);
    string result = client.call("localExecuteQuery", sql_statement).as<string>();
    return result;	
}

int RPCExecuteUpdate(string host_ip, string sql_statement){
	rpc::client client(host_ip, rpc::constants::DEFAULT_PORT);
    int cnt = client.call("localExecuteUpdate", sql_statement).as<int>();
    return cnt;
}

bool RPCInsertFileToTable(string host_ip, string sql_file, string table_name){
	rpc::client client(host_ip, rpc::constants::DEFAULT_PORT);
	bool ok = client.call("localInsertFileToTable", sql_file, table_name).as<bool>();
	return ok;
}