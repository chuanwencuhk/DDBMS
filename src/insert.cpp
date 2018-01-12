#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>
#include <malloc.h>
#include "../include/parser.h"
#include "../include/exec_mysql.h"
#include "../rpc_sql/rpc_sql.h"

using namespace std;
using std::string;
vector<string> stmts;
extern vector<string> ip_vec;
extern MYSQL *mysql_conn;
extern string dir;
string data_path_tmp[MAX_FRAG_NUM];

vector<string> db_names1 = {"db1","db2","db3","db4"};

std::vector<string> site_name = {"db1","db2","db3","db4"};

string GetTypeStringX(TYPE type, int used_size){
	string tmp_string = " ";
	if(type == 1)
		return " INTEGER";
	if(type == C){
		tmp_string = " CHAR";
		tmp_string = tmp_string+ "("+std::to_string(used_size)+")";
		return tmp_string;
	}
	if(type == V){
		tmp_string = " VARCHAR";
		tmp_string = tmp_string+ "("+std::to_string(used_size)+")";
		return tmp_string;
	}
	if(type == F){
		tmp_string = " FLOAT";
		tmp_string = tmp_string+ "("+std::to_string(used_size)+")";
		return tmp_string;
	}
	if(type == D)
		return " DATE";
}

int spliceFragToSelectX(string name){
	Fragment tmp_frag = MetadataManager::getInstance()->get_fragment_bystr(name);
	for (int i = 0; i < MAX_FRAGMENT_NUM; ++i)
	{
		if(tmp_frag.condition_slice[i].isValid == false)
			continue;
		string tmp_stmt = "SELECT ";
		if(tmp_frag.condition_slice[i].con_V1.isValid == false)
			tmp_stmt += " * ";
		if(tmp_frag.condition_slice[i].con_V1.isValid == true){
			int v_count = tmp_frag.condition_slice[i].con_V1.attr_num;
			if(v_count != 0)
				tmp_stmt += tmp_frag.condition_slice[i].con_V1.attr_frag_strlist[0];
			for (int j = 1; j < v_count; ++j)
			{
				tmp_stmt += ",";
				tmp_stmt += tmp_frag.condition_slice[i].con_V1.attr_frag_strlist[j];
			}
		}
		string tmp_name = name + "_tmp";

		data_path_tmp[i] = dir;
		data_path_tmp[i].append(tmp_name);
		data_path_tmp[i].append("_");
		data_path_tmp[i].append(site_name[i]);
		data_path_tmp[i].append(".data");
		cout<<"i "<<i<<" "<<data_path_tmp[i]<<endl;

		//stmp_stmt += tmp_name;

		tmp_stmt += " INTO OUTFILE '";
		tmp_stmt += data_path_tmp[i];
		tmp_stmt += "' FIELDS TERMINATED BY '\t'";
		tmp_stmt += " FROM ";
		tmp_stmt += tmp_name;

		if(tmp_frag.condition_slice[i].con_H1.isValid == true){
			tmp_stmt += " WHERE ";
			tmp_stmt += tmp_frag.condition_slice[i].con_H1.attr_name;
			tmp_stmt += tmp_frag.condition_slice[i].con_H1.attr_condition;
			tmp_stmt += tmp_frag.condition_slice[i].con_H1.attr_value;
		}
		if(tmp_frag.condition_slice[i].con_H2.isValid == true){
			tmp_stmt += " AND ";
			tmp_stmt += tmp_frag.condition_slice[i].con_H2.attr_name;
			tmp_stmt += tmp_frag.condition_slice[i].con_H2.attr_condition;
			tmp_stmt += tmp_frag.condition_slice[i].con_H2.attr_value;
		}
		tmp_stmt.append(";");
		stmts.push_back(tmp_stmt);
		cout<<stmts[i]<<endl;
	}
	int fcount = stmts.size();
	cout<<"fcount is " <<fcount<<endl;
	return fcount;
}

int get_frag_dataX(string name,int fcount){
	cout<<"get_frag_dataX."<<endl;
	if(stmts.size() == 0){
		cout<<"get_frag_dataX: 0"<<endl;
		return -1;
	}

	const char* c_sql_stmt;
	for(int i = 0; i < fcount; i++){
		cout << stmts[i]<<endl;
		c_sql_stmt = stmts[i].c_str();
		cout<<"c_sql_stmt "<<c_sql_stmt<<endl;
		if(exe_sql(c_sql_stmt))
			finish_with_error(NULL);
		cout<<"end exe_sql "<<i<<endl;
	}

	mysql_free_result(res);
	cout << "end get_frag_dataX" <<endl;
	return 0;
}

/*
	load data from tmp table.
 */
void load_dataX(string table_name,vector<string> &stmts){
	cout<<"load_dataX"<<endl;
	int fcount = stmts.size();

	/*
	get select stmt
	 */
	cout<<" table_name "<<table_name<<endl;

	fcount = spliceFragToSelectX(table_name);
	for(int i = 0; i < fcount; i++){
		cout<<"remove old frag data"<<data_path_tmp[i]<<endl;
		cout<<remove(data_path_tmp[i].c_str())<<endl;
	}

	for (int i = 0; i < fcount; ++i)
	{
		cout<<i<<endl;
		cout<<stmts[i]<<endl;
	}
	/*
	exec select stmts to get fragment data
	 */
	if(init_mysql())
		finish_with_error(NULL);

	get_frag_dataX(table_name,fcount);

	fstream infile;
	/*
		send data to sites.
	 */
	cout<<"Start Sending Data."<<endl;
	for(int i = 0; i < fcount; i++){
		cout<<data_path_tmp[i]<<endl;
		string buf_string = readFileIntoString(data_path_tmp[i]);
		cout<<"abcde    "<<i<<" "<<buf_string.size()<<endl;
		RPCInsertFileToTable(ip_vec[i],db_names1[i],buf_string,table_name);
	}
	cout<<"load into "<<fcount<<" fragments."<<endl;
	mysql_close(mysql_conn);
	return;
}


void exec_insert_stmt(string tb_name){
	cout<<"********Insert Stmt*************"<<endl;
	string table_name = tb_name;
	TableMedata tmp_tb_meta = MetadataManager::getInstance()->get_tablemetadata(table_name);
	Fragment tmp_frag = MetadataManager::getInstance()->get_fragment_bystr(table_name);
	cout<<"Get Table Meta From config. "<<tmp_tb_meta.table_name<<endl;
	AttrInfo attrs[MAX_ATTR_NUM];
	cout<<"attrs malloc"<<endl;
	int count = tmp_tb_meta.table_attr_num;

	string tmp_tb_name = table_name +"_tmp";
	string create_stmt = "CREATE TABLE "+tmp_tb_name+"( ";
	cout << "tmp_tb_name "<<create_stmt <<endl;

	string s = tmp_tb_meta.Attr[0].attr_name;
	create_stmt += s;
	string type_string = GetTypeStringX((TYPE)tmp_tb_meta.Attr[0].attr_datatype, tmp_tb_meta.Attr[0].attr_length);
	create_stmt += type_string;

	for (int i = 1; i < count; i++)
	{
		create_stmt +=",";
		s = tmp_tb_meta.Attr[i].attr_name;
		create_stmt += s;
		type_string = GetTypeStringX((TYPE)tmp_tb_meta.Attr[i].attr_datatype, tmp_tb_meta.Attr[i].attr_length);
		create_stmt += type_string;
	}
	create_stmt+=");";
	cout<<"create_stmt********"<<create_stmt<<endl;
	const char* c_sql_stmt = create_stmt.c_str();
	if(c_sql_stmt == ""){
		cout<<"Create Tmp Table Error."<<endl;
		return;
	}
	if(init_mysql())
		finish_with_error(NULL);
	if(exe_sql(c_sql_stmt))
		finish_with_error(NULL);
	mysql_close(mysql_conn);
	
	string insert_stmt = spliceInsertStmt();
	cout<<"spliceInsertStmt "<< insert_stmt<<endl;
	const char* c_insert_stmt = insert_stmt.c_str();
	if(c_insert_stmt == ""){
		cout<<"Insert Tmp Table Error."<<endl;
		return;
	}
	if(init_mysql())
		finish_with_error(NULL);
	if(exe_sql(c_insert_stmt))
		finish_with_error(NULL);
	mysql_close(mysql_conn);
	cout<<"LOAD data X"<<endl;
	load_dataX(table_name,stmts);

	cout<<"drop tmp table!"<<endl;
	string drop_stmt = "DROP TABLE "+tmp_tb_name;
	const char* c_delete_stmt = drop_stmt.c_str();
	if(init_mysql())
		finish_with_error(NULL);
	if(exe_sql(c_delete_stmt))
		finish_with_error(NULL);
	mysql_close(mysql_conn);

	return;
}