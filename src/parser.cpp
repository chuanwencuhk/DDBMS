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
#include "../include/parser.h"
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

extern int insert_count;
extern char* insert_record[MAX_TUPLE_SIZE];

bool isTableExists(string table_name);
bool isAttrExists(string col_name, string table_name);

//save one select sql for one db.
string frag_select_stmt[MAX_FRAG_NUM];
string frag_creat_stmt[MAX_FRAG_NUM];

string data_path[MAX_FRAG_NUM];
string dir = string("/var/lib/mysql-files/");

//MetadataManager* MetadataManager::pmtr = 0;
bool deleteFromMeta(string tb_name){
	TableMedata tmp_tb_meta;
	MetadataManager::getInstance()->delete_tablemetadata(tb_name);
	MetadataManager::getInstance()->delete_fragmemt_info(tb_name);
	return true;
}
bool isTableExists(string table_name){
	cout<<"Enter isTableExists."<<endl;
	TableMedata tmp_tb_meta;
	tmp_tb_meta = MetadataManager::getInstance()->get_tablemetadata(table_name);
	
	if(tmp_tb_meta.table_name == "")
	{
		cout<<"table not exist."<<endl;
		return false;
	}
	cout<<"table exists"<<endl;
	return true;
}
string GetTypeString(OP op_type){
	string type_string = "";
	switch(op_type){
		case E:
			type_string += "=";
			break;
		case GE:
			type_string += ">=";
			break;
		case G:
			type_string +=	">";
			break;
		case LE:
			type_string += "<=";
			break;
		case L:
			type_string += "<";
			break;

		case NE:
			type_string += "!=";
			break;
		default:
			cout<<"Invalid Operator!"<<endl;
			return "";
	}
	return type_string;
}
string GetTypeStringF(TYPE type, int used_size){
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

bool insertFragMeta(){
	cout<<"insertFragMeta  *************"<<endl;
	cout<<"Frag****"<<frag_tb_name<<endl;
	string tmp_tb_name(frag_tb_name);
	Fragment tmp_frag;
	tmp_frag.frag_table_name = tmp_tb_name;
	cout<<frag_count<<endl;
	//MetadataManager::getInstance()->add_fragment_name_intolist(tmp_tb_name);
	if(frag_type == HOR){
		for (int i = 0; i < frag_count; ++i)
		{
			tmp_frag.condition_slice[i].isValid = true;
			tmp_frag.condition_slice[i].con_H1.isValid = true;
			tmp_frag.condition_slice[i].con_H1.attr_name = frag_list[i].CondList[0].col_name;
			tmp_frag.condition_slice[i].con_H1.attr_condition = GetTypeString(frag_list[i].CondList[0].op);
			tmp_frag.condition_slice[i].con_H1.attr_value = frag_list[i].CondList[0].value;

			if(frag_list[i].cond_count > 1){
				tmp_frag.condition_slice[i].con_H2.isValid = true;
				tmp_frag.condition_slice[i].con_H2.attr_name = frag_list[i].CondList[1].col_name;
				tmp_frag.condition_slice[i].con_H2.attr_condition = GetTypeString(frag_list[i].CondList[1].op);
				tmp_frag.condition_slice[i].con_H2.attr_value = frag_list[i].CondList[1].value;
			}

			tmp_frag.condition_slice[i].con_V1.attr_num = 0;
			tmp_frag.condition_slice[i].con_V1.isValid = false;
		}
		MetadataManager::getInstance()->set_fargment_info(tmp_frag);
		return true;
	}
	if(frag_type == VER){
		for (int i = 0; i < frag_count; ++i)
		{
			tmp_frag.condition_slice[i].isValid = true;
			tmp_frag.condition_slice[i].con_H1.isValid = false;
			tmp_frag.condition_slice[i].con_H2.isValid = false;

			tmp_frag.condition_slice[i].con_V1.isValid = true;
			tmp_frag.condition_slice[i].con_V1.attr_num = frag_list[i].attr_count;
			for (int j = 0; j < frag_list[i].attr_count; ++j)
				{
					tmp_frag.condition_slice[i].con_V1.attr_frag_strlist[j] = frag_list[i].attr_names[j];
				}
		}
		MetadataManager::getInstance()->set_fargment_info(tmp_frag);
		return true;
	}
	if(frag_type == M){
		for (int i = 0; i < frag_count; ++i)
		{
			tmp_frag.condition_slice[i].isValid = true;
			tmp_frag.condition_slice[i].con_H1.isValid = true;
			tmp_frag.condition_slice[i].con_V1.isValid = true;

			tmp_frag.condition_slice[i].con_H1.attr_name = frag_list[i].CondList[0].col_name;
			tmp_frag.condition_slice[i].con_H1.attr_condition = GetTypeString(frag_list[i].CondList[0].op);
			tmp_frag.condition_slice[i].con_H1.attr_value = frag_list[i].CondList[0].value;
			if(frag_list[i].cond_count > 1){
				tmp_frag.condition_slice[i].con_H2.isValid = true;
				tmp_frag.condition_slice[i].con_H2.attr_name = frag_list[i].CondList[1].col_name;
				tmp_frag.condition_slice[i].con_H2.attr_condition = GetTypeString(frag_list[i].CondList[1].op);
				tmp_frag.condition_slice[i].con_H2.attr_value = frag_list[i].CondList[1].value;
			}

			tmp_frag.condition_slice[i].con_V1.attr_num = frag_list[i].attr_count;
			for (int j = 0; j < frag_list[i].attr_count; ++j)
				{
					tmp_frag.condition_slice[i].con_V1.attr_frag_strlist[j] = frag_list[i].attr_names[j];
				}
		}
		MetadataManager::getInstance()->set_fargment_info(tmp_frag);
		return true;
	}
	if(frag_type == N){
		cout<<"N "<<frag_count<<endl;
		MetadataManager::getInstance()->set_fargment_info(tmp_frag);
		return true;
	}
	return false;
}
bool insertIntoTableMeta(){
	string tmp_tb_name(tb_name);
	/*
	 if table already exists, error.
	 */
	if(isTableExists(tmp_tb_name)){
		cout<<"Table "<<tmp_tb_name<<" has already existed. updateTableMeta() Error."<<endl;
		return "";
	}
	TableMedata tmp_tb_meta;
	tmp_tb_meta.table_name = tmp_tb_name;
	tmp_tb_meta.table_attr_num = attr_count;
	for(int i = 0; i < attr_count; i++){
		tmp_tb_meta.Attr[i].attr_name = attr_list[i].attr_name;
		tmp_tb_meta.Attr[i].attr_datatype = attr_list[i].type;
		tmp_tb_meta.Attr[i].attr_length = attr_list[i].used_size;
		if(attr_list[i].is_key){
			tmp_tb_meta.Attr[i].attr_rulestype = 1;
		}		
		cout<<"insertIntoTableMeta COPY "<< tmp_tb_meta.Attr[i].attr_name<<tmp_tb_meta.Attr[i].attr_datatype<<tmp_tb_meta.Attr[i].attr_length <<" "<< tmp_tb_meta.Attr[i].attr_rulestype <<endl;
	}

	MetadataManager::getInstance()->set_tablemetadata(tmp_tb_meta);
	cout<<"SET META."<<endl;
	return true;
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
	if(attr_list[0].is_key)
		tmp_stmt += " KEY ";
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
string spliceJoinStmt(int join_count, Join* join_list){
	if((join_count == 0)|(NULL == join_list))
		return "";
	string join_stmt = "(";
	join_stmt.append(join_list[0].tb_name1);
	join_stmt += ".";
	join_stmt.append(join_list[0].col_name1);
	string type_string = GetTypeString(join_list[0].op);
	join_stmt += type_string;
	join_stmt.append(join_list[0].tb_name2);
	join_stmt += ".";
	join_stmt.append(join_list[0].col_name2);
	join_stmt+=")";
	for(int i = 1; i<join_count;i++){
		cout << "i" << i <<endl;
		join_stmt.append(" and ");
		join_stmt += "(";
		join_stmt.append(join_list[i].tb_name1);
		join_stmt += ".";
		join_stmt.append(join_list[i].col_name1);
		string type_string = GetTypeString(join_list[i].op);
		join_stmt += type_string;
		join_stmt.append(join_list[i].tb_name2);
		join_stmt += ".";
		join_stmt.append(join_list[i].col_name2);
		join_stmt+=")";
	}
	cout << "join_stmt" <<join_stmt<<endl;
	return join_stmt;
}
string spliceCondStmt(int cond_count, Condition* cond_list){
	if((cond_count == 0)|(NULL == cond_list))
		return "";
	//string cond_stmt = " where "
	// if(cond_list[0].tb_name != ""){
	// 	cout<<"ok"<<endl;
	// 	cond_stmt.append(cond_list[0].tb_name);
	// 	cond_stmt += ".";
	// }
	string cond_stmt = "(";
	if(*(cond_list[0].tb_name)!= 0){
		cond_stmt.append(cond_list[0].tb_name);

		cond_stmt.append(".");
	}
	cond_stmt.append(cond_list[0].col_name);
	string type_string = GetTypeString(cond_list[0].op);
	cond_stmt.append(type_string);
	cond_stmt.append(cond_list[0].value);
	cond_stmt += ")";
	for(int i = 1;i < cond_count;i++){
		cond_stmt.append(" and ");
		// if(cond_list[i].tb_name != ""){
		// 	cout<<"ok"<<endl;
		// 	cond_stmt.append(cond_list[i].tb_name);
		// 	cond_stmt += ".";
		// }
		cond_stmt += "(";
		if(*(cond_list[i].tb_name)!=0){
			cond_stmt.append(cond_list[i].tb_name);
			cond_stmt.append(".");
		}			
		cond_stmt.append(cond_list[i].col_name);
		string type_string = GetTypeString(cond_list[i].op);
		cond_stmt.append(type_string);
		cond_stmt.append(cond_list[i].value);
		cond_stmt += ")";
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
	if(delete_query->cond_count!=0)
		tmp_stmt += " WHERE ";
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
	if(update_query->cond_count!=0)
		tmp_stmt+=" WHERE ";

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

		tmp_stmt = string("select ");
		//cout<<tmp_stmt<<endl;
		if(query->all == 1)
			tmp_stmt.append("*");
		if(query->sel_count!=0){
			for(int i = 0; i<query->sel_count-1;i++){
				if(query->SelList[i].table_name!= NULL){
					tmp_stmt.append(query->SelList[i].table_name);
					tmp_stmt += ".";
				}
				tmp_stmt.append(query->SelList[i].col_name);
				tmp_stmt.append(",");
			}
			tmp_stmt.append(query->SelList[query->sel_count-1].col_name);
			//cout<<tmp_stmt<<endl;
		}
		tmp_stmt.append(" from ");
		tmp_stmt.append(query->FromList[0].tb_name);
		for(int i = 1; i < query->from_count; i++){
			tmp_stmt.append(",");
			tmp_stmt.append(query->FromList[i].tb_name);
		}
		if((query->cond_count!=0)||(query->join_count!=0))
			tmp_stmt += " where ";
		string cond_stmt = spliceCondStmt(query->cond_count,query->CondList);
		if(cond_stmt != ""){
			tmp_stmt.append(cond_stmt);
			if(query->join_count!=0)
				tmp_stmt += " and ";
		}

		string join_stmt = spliceJoinStmt(query->join_count,query->JoinList);
		if(join_stmt != ""){
			tmp_stmt.append(join_stmt);
		}
		//tmp_stmt.append(";");
		cout<<tmp_stmt<<endl;
		return tmp_stmt;
}

/*
	handle InsertStmt
 */

string spliceInsertStmt(){
	//cout<<"InsertStmt"<<endl;
	if(insert_count == 0)
		return "";
	string insert_stmt = "INSERT INTO ";
	string tmp_tb_name = tb_name;
	tmp_tb_name += "_tmp";
	insert_stmt += tmp_tb_name;
	insert_stmt += " VALUES (";
	insert_stmt.append(insert_record[0]);
	for(int i = 1; i < insert_count; i++){
		insert_stmt += ",";
		insert_stmt.append(insert_record[i]);
	}
	insert_stmt += ");";
	cout<<"insert_stmt "<<insert_stmt<<endl;
	return insert_stmt;
}

/*
	already tested;
	SELECT jno, loc INTO OUTFILE '/var/lib/mysql-files/job_db4.data' FIELDS TERMINATED BY '	' FROM job WHERE jno >= 'J0500';
 */
void spliceFragToSelect(){
	cout<<"INTO spliceFragToSelect"<<endl;
	if(frag_count == 0){
		cout << "there is no frag info."<<endl;
		return;
	}
	for(int i = 0; i<MAX_FRAG_NUM;i++){
		cout<<"empty frag_creat_stmt"<<endl;
		frag_creat_stmt[i] ="";
		frag_select_stmt[i]="";
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
			if(frag_list[i].cond_count!=0)
				tmp_stmt += " WHERE ";
			// for (int j = 0; i < frag_list[j].cond_count; ++j)
			// {
			// 	frag_list[i].CondList.tb_name = NULL;
			// }
			string cond_stmt = spliceCondStmt(frag_list[i].cond_count,frag_list[i].CondList);
			if(cond_stmt != "")
				tmp_stmt.append(cond_stmt);
			tmp_stmt.append(";");
			frag_select_stmt[i] = tmp_stmt;
			cout<<frag_select_stmt[i]<<endl;
		}
		return;
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
			cout<<"****VERTICAL********"<<endl;
			cout<<tmp_stmt<<endl;
			frag_select_stmt[i] = tmp_stmt;
			cout<<frag_select_stmt[i]<<endl;

			/*splice Create Stmt*/
			string f_name = frag_tb_name;
			TableMedata tmp_tb_meta = MetadataManager::getInstance()->get_tablemetadata(f_name);
			int meta_attr_num = tmp_tb_meta.table_attr_num;
			cout<<"meta_attr_num "<<meta_attr_num<<endl;
			string tmp_create_stmt = "";
			tmp_create_stmt += "CREATE TABLE " + f_name + "(";

			string tmp_attr_name = frag_list[i].attr_names[0];
			tmp_create_stmt.append(frag_list[i].attr_names[0]);
			bool flag = false;
			for(int m=0; m<meta_attr_num;m++){
				if(tmp_attr_name == tmp_tb_meta.Attr[m].attr_name){
					string type_string =  GetTypeStringF((TYPE)tmp_tb_meta.Attr[m].attr_datatype,tmp_tb_meta.Attr[m].attr_length);
					tmp_create_stmt += type_string;
					if(tmp_tb_meta.Attr[m].attr_rulestype==1)
						tmp_create_stmt += " key ";
					flag = true;
					break;
				}
			}
			if(flag == false){
				cout<<"error frag."<<endl;
				return;
			}
			for (int j = 1; j < frag_list[i].attr_count; ++j)
			{
				tmp_create_stmt += ",";
				tmp_attr_name = frag_list[i].attr_names[j];
				tmp_create_stmt.append(frag_list[i].attr_names[j]);
				flag = false;
				for(int m=0; m<meta_attr_num;m++){
					if(tmp_attr_name == tmp_tb_meta.Attr[m].attr_name){
						string type_string =  GetTypeStringF((TYPE)tmp_tb_meta.Attr[m].attr_datatype,tmp_tb_meta.Attr[m].attr_length);
						tmp_create_stmt += type_string;
						if(tmp_tb_meta.Attr[m].attr_rulestype==1)
							tmp_create_stmt += " key ";
						flag = true;
						break;
					}
				}
				if(flag == false){
					cout<<"error frag."<<endl;
					return;
				}

			}
			tmp_create_stmt += ");";
			frag_creat_stmt[i] = tmp_create_stmt;
			cout<<"frag_creat_stmt[i] "<<frag_creat_stmt[i]<<endl;
		}
		return;
	} 
	if(frag_type == M){
		for (int i = 0; i < frag_count; ++i)
		{
			tmp_stmt = "SELECT ";
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
			if(frag_list[i].cond_count!=0)
				tmp_stmt += " WHERE ";
			// for (int j = 0; i < frag_list[j].cond_count; ++j)
			// {
			// 	frag_list[i].CondList.tb_name = NULL;
			// }
			string cond_stmt = spliceCondStmt(frag_list[i].cond_count,frag_list[i].CondList);
			if(cond_stmt != "")
				tmp_stmt.append(cond_stmt);
			tmp_stmt.append(";");
			frag_select_stmt[i] = tmp_stmt;
			cout<<frag_select_stmt[i]<<endl;

			/*splice Create Stmt*/
			string f_name = frag_tb_name;
			TableMedata tmp_tb_meta = MetadataManager::getInstance()->get_tablemetadata(f_name);
			int meta_attr_num = tmp_tb_meta.table_attr_num;
			cout<<"meta_attr_num "<<meta_attr_num<<endl;
			string tmp_create_stmt = "";
			tmp_create_stmt += "CREATE TABLE " + f_name + "(";

			string tmp_attr_name = frag_list[i].attr_names[0];
			tmp_create_stmt.append(frag_list[i].attr_names[0]);
			bool flag = false;
			for(int m=0; m<meta_attr_num;m++){
				if(tmp_attr_name == tmp_tb_meta.Attr[m].attr_name){
					string type_string =  GetTypeStringF((TYPE)tmp_tb_meta.Attr[m].attr_datatype,tmp_tb_meta.Attr[m].attr_length);
					tmp_create_stmt += type_string;
					if(tmp_tb_meta.Attr[m].attr_rulestype==1)
						tmp_create_stmt += " key ";
					flag = true;
					break;
				}
			}
			if(flag == false){
				cout<<"error frag."<<endl;
				return;
			}
			for (int j = 1; j < frag_list[i].attr_count; ++j)
			{
				tmp_create_stmt += ",";
				tmp_attr_name = frag_list[i].attr_names[j];
				tmp_create_stmt.append(frag_list[i].attr_names[j]);
				flag = false;
				for(int m=0; m<meta_attr_num;m++){
					if(tmp_attr_name == tmp_tb_meta.Attr[m].attr_name){
						string type_string =  GetTypeStringF((TYPE)tmp_tb_meta.Attr[m].attr_datatype,tmp_tb_meta.Attr[m].attr_length);
						tmp_create_stmt += type_string;
						if(tmp_tb_meta.Attr[m].attr_rulestype==1)
						tmp_create_stmt += " key ";
						flag = true;
						break;
					}
				}
				if(flag == false){
					cout<<"error frag."<<endl;
					return;
				}

			}
			tmp_create_stmt += ");";
			frag_creat_stmt[i] = tmp_create_stmt;
			cout<<"frag_creat_stmt[i] "<<frag_creat_stmt[i]<<endl;
		}
		return;
	}
	if(frag_type == N){
		for (int i = 0; i < frag_count; ++i)
		{
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
			tmp_stmt.append(";");
			frag_select_stmt[i] = tmp_stmt;
			cout<<frag_select_stmt[i]<<endl;
		}
		return;
	}	
	return;
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
