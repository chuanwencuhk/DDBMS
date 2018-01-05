#ifndef DISPATHER_H
#define DISPATHER_H

#include "global.h"
#include "../MetadataManager/metadatamanager.h"


//to use LHH's RPC interface
extern bool RPCExecute(string host_ip, string sql_statement);

extern string RPCExecuteQuery(string host_ip, string sql_statement);

extern int RPCExecuteUpdate(string host_ip, string sql_statement);

extern bool RPCInsertFileToTable(string host_ip, string sql_file, string table_name);

class Dispather
{
public:
    Dispather();


};

#endif // DISPATHER_H
