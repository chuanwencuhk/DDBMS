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

string GetVTypeStringX(TYPE type, int i, AttrInfo* attrs){
	string tmp_string;
	if(type == 1)
		return "INTEGER";
	if(type == C){
		tmp_string = "CHAR";
		tmp_string = tmp_string+ "("+std::to_string(attrs[i].used_size)+")";
		return tmp_string;
	}
	if(type == V){
		tmp_string = "VARCHAR";
		tmp_string = tmp_string+ "("+std::to_string(attrs[i].used_size)+")";
		return tmp_string;
	}
	if(type == F){
		tmp_string = "FLOAT";
		tmp_string = tmp_string+ "("+std::to_string(attrs[i].used_size)+")";
		return tmp_string;
	}
	if(type == D)
		return "DATE";
}


// string spliceCreateStmtX(string tb_name, int attr_count, AttrInfo* attr_list);
// int spliceFragToSelectX(vector<string> &strings,string name);
// void load_dataX(int fcount,string table_name,vector<string> &strings);

string spliceCreateStmtX(string tb_name, int attr_count, AttrInfo* attrs){
	cout <<"*************spliceCreateStmtX"<<endl;
	for (int i = 0; i < attr_count; ++i)
	{
		cout<<"attr_name:  "<< attrs[i].attr_name <<endl;
		cout<<"type  :"<<attrs[i].type<<endl;
		cout<<"used_size:    "<<attrs[i].used_size<<endl;
	}
	if(stmts.size()!=0)
		stmts.clear();
	cout<<"clear over"<<endl;
	if((attr_count == 0) || (tb_name =="")){
		cout<<"spliceCreateStmtX error"<<endl;
		return "";
	}
	cout<<"******count "<< attr_count<<endl;
	string tmp_stmt;
	tmp_stmt = "CREATE TABLE ";
	cout<<tmp_stmt<<endl;
	tmp_stmt.append(tb_name);
	cout<<tmp_stmt<<endl;
	tmp_stmt.append("(");
	tmp_stmt.append(attrs[0].attr_name);
	cout<<tmp_stmt<<endl;
	tmp_stmt.append(" ");
	string type_string = GetVTypeStringX(attrs[0].type,0,attrs);
	tmp_stmt.append(type_string);

	cout<<tmp_stmt<<endl;

	for (int i = 1; i < attr_count; i++)
	{
		tmp_stmt.append(", ");
		tmp_stmt.append(attrs[i].attr_name);
		cout<<"i:  "<<attrs[i].attr_name<<endl;
		tmp_stmt.append(" ");
		string type_string = GetVTypeStringX(attrs[i].type,i,attrs);
		tmp_stmt.append(type_string);
	}
	tmp_stmt.append(" );");
	cout << tmp_stmt << endl;
	return tmp_stmt;

}
int spliceFragToSelectX(vector<string>&strings,string name){
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

		tmp_stmt += tmp_name;

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
		strings.push_back(tmp_stmt);
		cout<<strings[i]<<endl;
	}
	int fcount = strings.size();
	cout<<"fcount is " <<fcount<<endl;string data_path_tmp[MAX_FRAG_NUM];
	return fcount;
}

int get_frag_dataX(vector<string> &stmts,string name){
	cout<<"get_frag_dataX."<<endl;
	if(stmts.size() == 0){
		cout<<"get_frag_dataX: 0"<<endl;
		return -1;
	}

	const char* c_sql_stmt;
	for(int i = 0; i < frag_count; i++){
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
	for(int i = 0; i < fcount; i++){
		cout<<"remove old frag data"<<data_path_tmp[i]<<endl;
		cout<<remove(data_path_tmp[i].c_str())<<endl;
	}

	/*
	get select stmt
	 */
	cout<<" table_name "<<table_name<<endl;

	spliceFragToSelectX(stmts,table_name);

	for (int i = 0; i < fcount; ++i)
	{
		cout<<stmts[i]<<endl;
	}
	/*
	exec select stmts to get fragment data
	 */
	if(init_mysql())
		finish_with_error(NULL);

	get_frag_dataX(stmts,table_name);

	fstream infile;
	/*
		send data to sites.
	 */
	cout<<"Start Sending Data."<<endl;
	for(int i = 0; i < frag_count; i++){
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

	for (int i = 0; i < count; i++)
	{
		cout<<"i "<<i<<endl;
		string s = tmp_tb_meta.Attr[i].attr_name;		 
		attrs[i].attr_name = (char*)s.c_str();
		//strcpy(attrs[i].attr_name,p);
		attrs[i].type = (TYPE)tmp_tb_meta.Attr[i].attr_datatype;
		attrs[i].used_size = tmp_tb_meta.Attr[i].attr_length;
		cout<<"attr_name:  "<<i<< attrs[i].attr_name <<endl;
		cout<<"type  :"<<i<<attrs[i].type<<endl;
		cout<<"used_size:    "<<i<<attrs[i].used_size<<endl;
	}

	string tmp_tb_name = table_name +"_tmp";
	cout << "tmp_tb_name "<<tmp_tb_name <<endl;
	cout <<"count  :"<<count<<endl;
	for (int i = 0; i < count; ++i)
	{
		cout<<"attr_name:  "<<i<< attrs[i].attr_name <<endl;
		cout<<"type  :"<<i<<attrs[i].type<<endl;
		cout<<"used_size:    "<<i<<attrs[i].used_size<<endl;
	}
	string tmp_crt = spliceCreateStmtX(tmp_tb_name, count, attrs);
	cout << "tmp crt   "<<tmp_crt<<endl;
	const char* c_sql_stmt = tmp_crt.c_str();
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
	load_dataX(table_name,stmts);
	return;
}