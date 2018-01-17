#include "rpc_sql.h"
#include <cassert>

bool RPCExecute(string host_ip, string dbname, string sql_statement){
    rpc::client client(host_ip, rpc::constants::DEFAULT_PORT);
    cout << "    rpc::client client(host_ip, rpc::constants::DEFAULT_PORT);" << endl;
    bool ok = client.call("localExecute",  dbname, sql_statement).as<bool>();
    cout << "    bool ok = client.call(\"localExecute\", sql_statement).as<bool>();";
    return ok;
}

string RPCExecuteQuery(string host_ip, string dbname, string sql_statement){
	rpc::client client(host_ip, rpc::constants::DEFAULT_PORT);
    string result = client.call("localExecuteQuery",  dbname, sql_statement).as<string>();
    return result;	
}

int RPCExecuteUpdate(string host_ip, string dbname,  string sql_statement){
	rpc::client client(host_ip, rpc::constants::DEFAULT_PORT);
    int cnt = client.call("localExecuteUpdate",  dbname, sql_statement).as<int>();
    return cnt;
}

bool RPCInsertFileToTable(string host_ip, string dbname, string sql_file, string table_name){
	rpc::client client(host_ip, rpc::constants::DEFAULT_PORT);
	bool ok = client.call("localInsertFileToTable",  dbname, sql_file, table_name).as<bool>();
	return ok;
}