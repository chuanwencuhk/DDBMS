#ifndef Dispatcher_H
#define Dispatcher_H

#include "global.h"
#include "../QueryTree/query_tree.h"
#include <set>
#include <vector>

//to use LHH's RPC interface
extern bool RPCExecute(string host_ip, string sql_statement);
extern string RPCExecuteQuery(string host_ip, string sql_statement);//use for exec sql
extern int RPCExecuteUpdate(string host_ip, string sql_statement);
extern bool RPCInsertFileToTable(string host_ip, string sql_file, string table_name);

//to use WHY's query tree
extern struct schema sch;//global definition for his metadata
extern struct query_tree get_original_tree(string s);

class Dispatcher
{
public:
    Dispatcher();
    void set_treevector_from_querytree(query_tree &qtree);
    struct query_tree get_querytree_fromSQL(string sql);
    void exec_SQL_query(std::string SQL);
    void exec_SQL_query_poor_optimal(std::string SQL);

    //to create tmp data file's name without sepcial char like "+-=<*..."
    std::string get_hash_fromstr(std::string str);
    std::string get_attr_ruletypestring(int rule_type);
    std::string get_attr_typestring(int type);

    std::string&  replace_SQL_tablename_byhash(string&   str,const   string&   old_value,const   string&   new_value);

private:
    //MetadataManager* pmtr;

    set<std::string> tree_set;
    set<std::string> cplmnt_set;
    vector<int> tree_vector;

    std::hash<std::string> hash_function;

};

#endif // Dispatcher_H
