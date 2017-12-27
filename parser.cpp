/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: gpadmin
 */
#include <malloc.h>
#include <iostream>
#include <string>
#include "parser.h"
using namespace std;
using std::string;

extern int frag_count;
extern char* frag_tb_name;
extern FRAG_TYPE frag_type;
extern FragInfo frag_list[MAX_FRAG_NUM];

extern SelectQuery* query;

extern int attr_count;
extern char* tb_name;
extern AttrInfo attr_list[MAX_ATTR_NUM];

string frag_select_stmt[MAX_FRAG_NUM];
string data_path[MAX_FRAG_NUM];
string dir = string("/var/lib/mysql-files/");
///var/lib/mysql-files/data.csv

// "SELECT * INTO OUTFILE '/var/lib/mysql-files/data.csv' FIELDS TERMINATED BY ',' FROM EMP;",
// strlen("SELECT * INTO OUTFILE '/var/lib/mysql-files/data.csv' FIELDS TERMINATED BY ',' FROM EMP;"


string	GetTypeString(OP op_type,string type_string){
		if(op_type ==  G)
			type_string.append("=");
		if(op_type == GE)
			type_string.append(">=");
		if(op_type == G)
			type_string.append(">");
		if(op_type == LE)
			type_string.append(">=");
		if(op_type == L)
			type_string.append("<");
		if(op_type == NE)
			type_string.append("!=");
		return type_string;
}

string GetVTypeString(TYPE type, int i){
	string tmp_string;
	if(type == 1)
		return "INTEGER";
	if(type == C){
		tmp_string = "CHAR";
		tmp_string = tmp_string+ "("+std::to_string(attr_list[i].used_size)+")";
		return tmp_string;
	}
	if(type == V){
		tmp_string = "VARCHAR";
		tmp_string = tmp_string+ "("+std::to_string(attr_list[i].used_size)+")";
		return tmp_string;
	}
	if(type == F){
		tmp_string = "FLOAT";
		tmp_string = tmp_string+ "("+std::to_string(attr_list[i].used_size)+")";
		return tmp_string;
	}
	if(type == D)
		return "DATE";
}

string spliceCreateStmt(){
	if((attr_count == 0) || (tb_name ==NULL))
		cout<<"spliceCreateStmt error"<<endl;
	string tmp_stmt;
	tmp_stmt = "CREATE TABLE ";
	tmp_stmt.append(tb_name);
	tmp_stmt.append("(");
	tmp_stmt.append(attr_list[0].attr_name);
	tmp_stmt.append(" ");
	string type_string = GetVTypeString(attr_list[0].type,0);
	tmp_stmt.append(type_string);
	for (int i = 1; i < attr_count; i++)
	{
		tmp_stmt.append(", ");
		tmp_stmt.append(attr_list[i].attr_name);
		tmp_stmt.append(" ");
		string type_string = GetVTypeString(attr_list[i].type,i);
		tmp_stmt.append(type_string);
	}
	tmp_stmt.append(" );");
	cout << tmp_stmt << endl;
	return tmp_stmt;

}
string spliceDropStmt(){
	cout<<"spliceDropStmt"<<endl;
	if(NULL == tb_name){
		cout << "spliceDropStmt error"<<endl;
		return NULL;
	}
	string tmp_stmt;
	tmp_stmt = "DROP TABLE ";
	tmp_stmt.append(tb_name);
	tmp_stmt.append(";");
	cout<<tmp_stmt<<endl;
	return tmp_stmt;
}
string spliceSelectStmt(){
		cout<<"spliceSelectStmt"<<endl;
		if(NULL == query){
			cout<<"spliceSelectStmt error"<<endl;
			return NULL;
		}
		string tmp_stmt;

		tmp_stmt = string("SELECT ");
		//cout<<tmp_stmt<<endl;
		if(query->all == 1)
			tmp_stmt.append("* ");
		if(query->sel_count!=0){
			for(int i = 0; i<query->sel_count-1;i++){
				tmp_stmt.append(query->SelList[i].col_name);
				tmp_stmt.append(", ");
			}
			tmp_stmt.append(query->SelList[query->sel_count-1].col_name);
			//cout<<tmp_stmt<<endl;
		}
		tmp_stmt.append(" FROM ");
		//cout<<tmp_stmt<<endl;
		//cout<<"from_count"<<query->from_count<<endl;
		//cout<<query->FromList[0].tb_name<<endl;
		tmp_stmt.append(query->FromList[0].tb_name);
		for(int i = 1; i < query->from_count; i++){
			tmp_stmt.append(", ");
			tmp_stmt.append(query->FromList[i].tb_name);
		}
		//cout<<tmp_stmt<<endl;
		if(query->cond_count!=0){
			tmp_stmt.append(" WHERE ");
			tmp_stmt.append(query->CondList[0].col_name);
			tmp_stmt.append(" ");
			string type_string = string(" ");
			type_string = GetTypeString(query->CondList[0].op,type_string);
			tmp_stmt.append(type_string);
			tmp_stmt.append(query->CondList[0].value);
		}
		//cout<<tmp_stmt<<endl;
		for(int i=1;i< query->cond_count;i++){
			tmp_stmt.append(" AND ");
			tmp_stmt.append(query->CondList[i].col_name);
			tmp_stmt.append(" ");
			string type_string = string(" ");
			type_string = GetTypeString(query->CondList[i].op,type_string);
			tmp_stmt.append(type_string);
			tmp_stmt.append(query->CondList[i].value);
		}
		//cout<<tmp_stmt<<endl;
		tmp_stmt.append(";");
		cout<<tmp_stmt<<endl;
		return tmp_stmt;
}
void spliceFragToSelect(){
	if(frag_count == 0){
		cout << "there is no frag info."<<endl;
		return;
	}
	string tmp_stmt = string("SELECT ");
	if(frag_type == HOR){
		/*
			SELECT * FROM tb_name WHERE condlist;
		 */
		for(int i = 0; i < frag_count; i++){
			cout<<"site_name: "<<frag_list[i].site_name<<endl;
			data_path[i] = dir;
			data_path[i].append(frag_tb_name);
			data_path[i].append("_");
			data_path[i].append(frag_list[i].site_name);
			data_path[i].append(".data");
			cout<<"i "<<i<<" "<<data_path[i]<<endl;
			tmp_stmt = string("SELECT ");
			tmp_stmt.append("* INTO OUTFILE '");
			tmp_stmt.append(data_path[i]);
			tmp_stmt.append("' FIELDS TERMINATED BY '\t'");
			tmp_stmt.append(" FROM ");
			tmp_stmt.append(frag_tb_name);
			tmp_stmt.append(" WHERE ");
			if(frag_list[i].cond_count != 0){
				tmp_stmt.append(frag_list[i].CondList[0].col_name);
				string type_string = string(" ");
				type_string = GetTypeString(frag_list[i].CondList[0].op,type_string);
				tmp_stmt.append(type_string);
				tmp_stmt.append(frag_list[i].CondList[0].value);

			}
			for(int j = 1; j < frag_list[i].cond_count; j++){
				tmp_stmt.append(" AND ");
				tmp_stmt.append(frag_list[i].CondList[j].col_name);
				string type_string = string(" ");
				type_string = GetTypeString(frag_list[i].CondList[j].op,type_string);
				tmp_stmt.append(type_string);
				tmp_stmt.append(frag_list[i].CondList[j].value);			
			}
			tmp_stmt.append(";");
			frag_select_stmt[i] = tmp_stmt;
			cout<<frag_select_stmt[i]<<endl;
		}
	}	
	if(frag_type == VER){
		for(int i = 0; i < frag_count; i++){
			tmp_stmt = string("SELECT ");
			cout<<"site_name: "<<frag_list[i].site_name<<endl;
			data_path[i] = dir;
			data_path[i].append(frag_tb_name);
			data_path[i].append("_");
			data_path[i].append(frag_list[i].site_name);
			data_path[i].append(".data");
			cout<<"i "<<i<<" "<<data_path[i]<<endl;
			if(frag_list[i].attr_count != 0){
				tmp_stmt.append(frag_list[i].attr_names[0]);
			}
			for(int j = 1; j<frag_list[i].attr_count;j++){
				tmp_stmt.append(", ");
				tmp_stmt.append(frag_list[i].attr_names[j]);
			}
			tmp_stmt.append(" INTO OUTFILE '");
			tmp_stmt.append(data_path[i]);
			tmp_stmt.append("' FIELDS TERMINATED BY '\t'");
			tmp_stmt.append(" FROM ");
			tmp_stmt.append(frag_tb_name);
			tmp_stmt.append(";");
			// cout<<tmp_stmt<<endl;
			frag_select_stmt[i] = tmp_stmt;
			cout<<frag_select_stmt[i]<<endl;
		}
	} 
}

void printFragInfo(){
	cout<<"tab_name "<<frag_tb_name<<endl;
	cout<<"frag_type "<< frag_type<<endl;
	cout<<"frag_count "<< frag_count <<endl; 
	for(int i = 0; i < frag_count; i++){
		cout<<"site_name: "<<frag_list[i].site_name<<endl;
		for(int j = 0; j < frag_list[i].cond_count; j++)
			cout<< "cond " << j <<" "<<frag_list[i].CondList[j].col_name <<" op " 
					<<frag_list[i].CondList[j].op <<" "<<frag_list[i].CondList[j].value<<endl;
		for(int j = 0; j< frag_list[i].attr_count;j++)
			cout<<frag_list[i].attr_names[j]<<",";
		cout<<endl;
	}
	return;
}
