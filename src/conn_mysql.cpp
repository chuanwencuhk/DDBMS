/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: wcw
 *	
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>

#include "../include/parser.h"
#include "../include/exec_mysql.h"
#include "../rpc_sql/rpc_sql.h"
#include "../include/metadatamanager.h"

using namespace std;
#define MAX_BUF_SIZE 1024
//#define DATA_PATH = "/var/lib/mysql-files/data.csv"
//#define RAW_DATA_PATH = "/raw_data"


extern int frag_count;
extern string frag_select_stmt[MAX_FRAG_NUM];
extern string frag_creat_stmt[MAX_FRAG_NUM];

extern string data_path[MAX_FRAG_NUM];
extern char* frag_tb_name;
extern char* tb_name;

MYSQL *mysql_conn;
MYSQL_RES *res;
MYSQL_FIELD *fd;
MYSQL_ROW row;

const char *pHostName = "localhost";
const char *pUserName = "root";
const char *pPassword = " ";
const char *pDbName = "db1";
const unsigned int iDbPort = 3306;

vector<string> ip_vec = {"10.48.139.126","10.48.224.134","10.77.30.189","10.77.30.189"};
vector<string> db_names = {"db1","db2","db3","db4"};
//vector<string> ip_vec = {"127.0.0.1"};

// vector<string> raw_data_name = {"asg.tsv","emp.tsv","job.tsv","sal.tsv"};
// vector<string> test_tb_name = {"asg","emp","job","sal"};

void finish_with_error(const char* msg){
	if(msg)
		cout<<"Error message "<<msg<<" : "<<mysql_error(mysql_conn)<<"."<<endl;
	else
		cout<<"Error message "<<mysql_error(mysql_conn)<<"."<<endl;
	mysql_close(mysql_conn);
	exit(-1);
}
int exe_sql(const char *sql){
	cout<<"exe_sql"<<endl;
	cout<<sql<<endl;
	int ret = mysql_real_query(mysql_conn,sql,strlen(sql));
	//int ret = mysql_real_query(mysql_conn,"LOAD DATA INFILE '/var/lib/mysql-files/raw_data/emp.tsv' INTO TABLE emp FIELDS TERMINATED BY '\t' LINES TERMINATED BY '\n'",strlen("LOAD DATA INFILE '/var/lib/mysql-files/raw_data/emp.tsv' INTO TABLE emp FIELDS TERMINATED BY '\t' LINES TERMINATED BY '\n'"));
	cout<<ret<<endl;
	if(ret)
		return -1;
	return 0;
}
int init_mysql(){
	mysql_conn = mysql_init(NULL);
	if(mysql_conn == NULL)
		return -1;
	if(!mysql_real_connect(mysql_conn,pHostName,pUserName,pPassword,pDbName,iDbPort,NULL,0))
		return -2;
	if(exe_sql("set names utf8"))
		return -3;
	return 0;
}


/*
	execute LOAD sql.
 */
int load_data_into_local_db(string tb_name){
	cout<<"load_data"<<endl;
	if(init_mysql())
		finish_with_error(NULL);
	string file_name = "'/var/lib/mysql-files/raw_data/"+tb_name+".tsv'";
	string load_stmt = "LOAD DATA INFILE "+ file_name +" INTO TABLE " + tb_name + " FIELDS TERMINATED BY '\\t' LINES TERMINATED BY '\\n'";
	const char* cLoadData = load_stmt.c_str();
	cout<<"cLoadData is "<<cLoadData<<endl;
	//cout<<"load_data end"<<endl;
	if(exe_sql(cLoadData))
		finish_with_error(NULL);
	mysql_close(mysql_conn);
	return 0;
}



int get_frag_data(){
	cout<<"get_frag_data."<<endl;
	if(frag_count == 0){
		cout<<"get_frag_data: 0"<<endl;
		return -1;
	}

	const char* c_sql_stmt;
	for(int i = 0; i < frag_count; i++){
		cout << frag_select_stmt[i]<<endl;
		c_sql_stmt = frag_select_stmt[i].c_str();
		cout<<"c_sql_stmt "<<c_sql_stmt<<endl;
		if(exe_sql(c_sql_stmt))
			finish_with_error(NULL);
		cout<<"end exe_sql "<<i<<endl;
	}

	mysql_free_result(res);
	cout << "end get_frag_data" <<endl;
	return 0;
}
string readFileIntoString(string filename){
	cout<<"enter readFile"<<endl;
	ifstream infile(filename, std::ios::in);
	cout << "filename "<<filename<<endl;
	ostringstream os_buf;
	char buffer[1024];
	while(!infile.eof()){
		//cout<<"infile"<<endl;
		infile.getline(buffer,1024);
		//cout<<"buffer"<<buffer<<endl;
		os_buf << buffer;
		os_buf << "\n";
	}
	string result = os_buf.str();
	result.erase(result.size()-1, 1);
	//cout<<os_buf.str()<<endl;
	return result;
}


/*
	fragments for one table a time.
 */
void load_data(){
	cout<<"load_data"<<endl;
	
	// if(!checkIsFragStmtValid())
	// 	return;
	/*
	 tb_name = emp
	 */
	string tb_name(frag_tb_name);
	/*
	LOAD DATA LOCAL INFILE 'raw/emp.tsv' INTO TABLE emp;
	 */
	load_data_into_local_db(tb_name);
	/*
	get select stmt
	 */
	spliceFragToSelect();

	for(int i = 0; i < frag_count; i++){
		cout<<"remove old frag data "<<data_path[i]<<endl;
		cout<<remove(data_path[i].c_str())<<endl;
	}

	/*
	exec select stmts to get fragment data
	 */
	if(init_mysql())
		finish_with_error(NULL);

	get_frag_data();

	if(frag_creat_stmt[0]!=""){
		cout<<"VERTICL OR MIXED. RECreate Table."<<endl;
		for(int i = 0; i < frag_count; i++){
			cout<<"tb_name"<<tb_name<<endl;
			cout<<"executing drop table "<<i<<endl;
			RPCExecute( ip_vec[i],db_names[i], "DROP TABLE "+tb_name);
			cout<<"executing create table "<<i<<endl;
			cout<<frag_creat_stmt[i]<<endl;
			RPCExecute( ip_vec[i],db_names[i], frag_creat_stmt[i]);
		}
	}

	fstream infile;
	/*
		send data to sites.
	 */
	string del_stmt = "DELETE FROM " + tb_name +";";
	cout<<"del_stmt "<<del_stmt;

	exe_sql(del_stmt.c_str());

	cout<<"Start Sending Data."<<endl;
	for(int i = 0; i < frag_count; i++){
		cout<<data_path[i]<<endl;
		string buf_string = readFileIntoString(data_path[i]);
		cout<<"abcde    "<<i<<" "<<buf_string.size()<<endl;
		cout<<ip_vec[i]<<endl;
		cout << db_names[i]<<endl;
		cout<<tb_name<<endl;
		cout<<"RPCInsertFileToTable"<<endl;
		RPCInsertFileToTable(ip_vec[i],db_names[i],buf_string,tb_name);
	}
	cout<<"load into"<<frag_count<<" fragments."<<endl;
	mysql_close(mysql_conn);
	insertFragMeta();
	return;
}
void exec_select_stmt(){
	cout<<"exec_select_stmt"<<endl;
	// if(!checkIsSelStmtValid())
	// 	return;

	string c_sql_stmt = spliceSelectStmt();
	string res;
	cout<<"c_sql_stmt    "<<c_sql_stmt<<endl;
	MetadataManager::getInstance()->execute_SQL(c_sql_stmt, 0);
	// for(int i = 0; i < ip_vec.size(); i++){
	// 	cout<<"i "<<i<<endl;
	// 	cout<<ip_vec[i]<<endl;
	// 	res = RPCExecuteQuery(ip_vec[i], c_sql_stmt);
	// 	cout << "select result" << i << " "<< res << endl;
	// }
	return;
}
void exec_create_stmt(){
	cout<<"exec_create_stmt"<<endl;
	// if(!checkIsCStmtValid())
	// 	return;
	string c_sql_stmt = spliceCreateStmt();

	if(c_sql_stmt == ""){
		cout<<"exec_create_stmt() Empty."<<endl;
		return;
	}
	
	bool res = false;

	for(int i = 0; i < ip_vec.size(); i++){
		bool resi = RPCExecute( ip_vec[i],db_names[i], c_sql_stmt);
		res = res && resi;
		cout << "send i " << i <<"" <<resi <<endl;
	}
	if(res){
		cout<<"Create Error."<<endl;
		return;
	}
	cout <<"Inserted-------------------"<<endl;
	insertIntoTableMeta();
	cout<<"New Metadata Inserted!"<<endl;
	return;
}


void exec_drop_table_stmt(){
	cout<<"exec_drop_table_stmt"<<endl;
	// if(!checkIsDtStmtValid())
	// 	return;
	string c_sql_stmt = spliceDropStmt();
	cout<<"c_sql_stmt    "<<c_sql_stmt<<endl;
	for(int i = 0; i < ip_vec.size(); i++){
		if(RPCExecute(ip_vec[i], db_names[i],c_sql_stmt))
			cout<<"site "<<i+1<<" drop table ok."<<endl;
	}
	string table_name = tb_name;
	cout<<"deleteFromMeta "<< table_name<<endl;
	deleteFromMeta(table_name);
	return;
}
void exec_show_table_stmt(){
	for(int i = 0; i < ip_vec.size(); i++){
		cout<<"exec_show_table_stmt"<<i<<endl;
		cout<<"db_names[i] "<<db_names[i]<<endl;
		cout<<"ip_vec[i] "<<ip_vec[i]<<endl;
		string res = RPCExecuteQuery(ip_vec[i], db_names[i],"show tables;");
		cout<<"site "<< i+1 <<": "<<res<<endl;
	}	
	return;
}
void exec_delete_stmt(){
	cout<<"exec_delete_stmt"<<endl;
	// if(!checkIsDStmtValid())
	// 	return;
	string c_sql_stmt = spliceDeleteStmt();
	cout<<"c_sql_stmt    "<<c_sql_stmt<<endl;
	for(int i = 0; i < ip_vec.size(); i++){
		cout<<"exec_delete_stmt"<<i<<endl;
		if(RPCExecute(ip_vec[i], db_names[i],c_sql_stmt))
			cout<<"site "<<i+1<<" delete ok."<<endl;
	}	
	return;
}
void exec_update_stmt(){
	cout<<"exec_update_stmt"<<endl;
	// if(!checkIsUStmtValid())
	// 	return;
	string c_sql_stmt = spliceUpdateStmt();
	cout<<"c_sql_stmt    "<<c_sql_stmt<<endl;
	for (int i = 0; i < ip_vec.size(); ++i)
	{
		cout<<"exec_update_stmt"<<i<<endl;
		if(RPCExecute(ip_vec[i],db_names[i],c_sql_stmt))
			cout<<"site "<<i+1<<" update ok."<<endl;
	}
	return;
}
