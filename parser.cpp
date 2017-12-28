/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: wcw
 *	
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

extern DeleteQuery* delete_query;

extern UpdateQuery* update_query;

extern int attr_count;
extern char* tb_name;
extern AttrInfo attr_list[MAX_ATTR_NUM];

string frag_select_stmt[MAX_FRAG_NUM];
string data_path[MAX_FRAG_NUM];
string dir = string("/var/lib/mysql-files/");


string GetTypeString(OP op_type){
	string type_string = " ";
	switch(op_type){
		case E:
			type_string += "= ";
			break;
		case GE:
			type_string += ">= ";
			break;
		case G:
			type_string +=	"> ";
			break;
		case LE:
			type_string += "<= ";
			break;
		case L:
			type_string += "< ";
			break;

		case NE:
			type_string += "!= ";
			break;
		default:
			cout<<"Invalid Operator!"<<endl;
			return "";
	}
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
	if((attr_count == 0) || (tb_name ==NULL)){
		cout<<"spliceCreateStmt error"<<endl;
		return "";
	}
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
		return "";
	}
	string tmp_stmt;
	tmp_stmt = "DROP TABLE ";
	tmp_stmt.append(tb_name);
	tmp_stmt.append(";");
	cout<<tmp_stmt<<endl;
	return tmp_stmt;
}

string spliceCondStmt(int cond_count, Condition* cond_list){
	if((cond_count == 0)|(NULL == cond_list))
		return "";
	string cond_stmt = " WHERE ";
	if(cond_list[0].tb_name != NULL){
		cond_count.append(cond_list[0].tb_name);
		cond_count += ".";
	}
	cond_stmt.append(cond_list[0].col_name);
	string type_string = GetTypeString(cond_list[0].op);
	cond_stmt.append(type_string);
	cond_stmt.append(cond_list[0].value);
	for(int i = 1;i < cond_count;i++){
		cond_stmt.append(" AND ");
		if(cond_list[i].tb_name != NULL){
			cond_count.append(cond_list[i].tb_name);
			cond_count += ".";
		}
		cond_stmt.append(cond_list[i].col_name);
		string type_string = GetTypeString(cond_list[i].op);
		cond_stmt.append(type_string);
		cond_stmt.append(cond_list[i].value);
	}
	return cond_stmt;
}

string spliceDeleteStmt(){
	if(NULL == delete_query){
		cout<<"spliceDeleteStmt error. no delete stmt."<<endl;
		return "";
	}
	string tmp_stmt = "DELETE FROM ";
	tmp_stmt.append(delete_query->tb_name);
	/*
		slpice cond_list same as where_cond in select.
	 */
	string cond_stmt = spliceCondStmt(delete_query->cond_count,delete_query->CondList);
	if(cond_stmt != "")
		tmp_stmt.append(cond_stmt);
		tmp_stmt.append(";");
		cout<< tmp_stmt <<endl;
		return tmp_stmt;
}

string spliceUpdateStmt(){
	if((NULL == update_query)|(update_query->col_count ==0)){
		cout<<"spliceUpdateStmt error. no update stmt."<<endl;
		return "";
	}
	string tmp_stmt = "UPDATE ";
	string tmp_tb_name(update_query->tb_name);
	tmp_stmt.append(tmp_tb_name);
	tmp_stmt += " SET ";
	tmp_stmt.append(update_query->col_name[0]);
	tmp_stmt += " = ";
	tmp_stmt.append(update_query->col_value[0]);
	for(int i = 1; i < update_query->col_count; i++){
		tmp_stmt += ", ";
		tmp_stmt.append(update_query->col_name[i]);
		tmp_stmt += " = ";
		tmp_stmt.append(update_query->col_value[i]);
				
	}
	string cond_stmt = spliceCondStmt(update_query->cond_count,update_query->CondList);
	tmp_stmt += cond_stmt;
	tmp_stmt += ";";
	return tmp_stmt;
}

string spliceSelectStmt(){
		cout<<"spliceSelectStmt"<<endl;
		if(NULL == query){
			cout<<"spliceSelectStmt error"<<endl;
			return "";
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
		tmp_stmt.append(query->FromList[0].tb_name);
		for(int i = 1; i < query->from_count; i++){
			tmp_stmt.append(", ");
			tmp_stmt.append(query->FromList[i].tb_name);
		}
		string cond_stmt = spliceCondStmt(query->cond_count,query->CondList);
		if(cond_stmt != "")
			tmp_stmt.append(cond_stmt);
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
			string cond_stmt = spliceCondStmt(frag_list[i].cond_count,frag_list[i].CondList);
			if(cond_stmt != "")
				tmp_stmt.append(cond_stmt);
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
