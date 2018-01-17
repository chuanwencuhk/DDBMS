// #include <malloc.h>
// #include <iostream>
// #include <string>
// #include "../include/metaCheck.h"
// #include "../include/metadatamanager.h"
// using namespace std;
// using std::string;

// // bool deleteFromMeta(string tb_name){
// // 	TableMedata tmp_tb_meta;
// // 	MetadataManager::getInstance()->delete_tablemetadata(tb_name);
// // 	MetadataManager::getInstance()->delete_fragmemt_info(tb_name);
// // 	return true;
// // }
// // bool isTableExists(string table_name){
// // 	cout<<"Enter isTableExists."<<endl;
// // 	TableMedata tmp_tb_meta;
// // 	tmp_tb_meta = MetadataManager::getInstance()->get_tablemetadata(table_name);
	
// // 	if(tmp_tb_meta.table_name == "")
// // 	{
// // 		cout<<"table not exist."<<endl;isTableExists
// // 		return false;
// // 	}
// // 	cout<<"table exists"<<endl;
// // 	return true;
// // }
// bool isAttrExists(string col_name, string table_name){
// 	TableMedata tmp_tb_meta;
// 	tmp_tb_meta = MetadataManager::getInstance()->get_tablemetadata(table_name);
// 	if(tmp_tb_meta.table_name == "")
// 		return false;
// 	for(int i = 0; i < tmp_tb_meta.table_attr_num; i++){
// 		if(tmp_tb_meta.Attr[i].attr_name == col_name)
// 			return true;
// 	}
// 	return false;
// }

// bool isAttrFitsMeta(AttrInfo attr_info,string table_name){
// 	TableMedata tmp_tb_meta;
// 	tmp_tb_meta = MetadataManager::getInstance()->get_tablemetadata(table_name);
// 	if(tmp_tb_meta.table_name == "")
// 		return false;
// 	//&&(tmp_tb_meta.Attr[i].attr_length==attr_info.used_size)
// 	for(int i = 0; i < tmp_tb_meta.table_attr_num; i++){
// 		if(tmp_tb_meta.Attr[i].attr_datatype==V)
// 			tmp_tb_meta.Attr[i].attr_datatype = C;
// 		if((tmp_tb_meta.Attr[i].attr_name == attr_info.attr_name)&&(tmp_tb_meta.Attr[i].attr_datatype == attr_info.type))
// 			return true;
// 	}
// 	return false;
// }


// // bool checkIsDStmtValid(){
// // 	string tmp_tb_name = delete_query->tb_name;
// // 	if(!isTableExists(tmp_tb_name)){
// // 		cout<<"Table "<<tmp_tb_name<<" not exists."<<endl;
// // 		return false;
// // 	}
// // 	return true;
// // }
// // bool checkIsUStmtValid(){
// // 	string tmp_tb_name = update_query->tb_name;
// // 	if(!isTableExists(tmp_tb_name)){
// // 		cout<<"Table "<<tmp_tb_name<<" not exists."<<endl;
// // 		return false;
// // 	}
// // 	for (int i = 0; i < update_query->col_count; ++i)
// // 	{
// // 		AttrInfo attr_info;
// // 		attr_info.table_name = update_query->tb_name;
// // 		attr_info.attr_name = update_query->col_name[i];
// // 		attr_info.type = update_query->type[i];
// // 		if(!isAttrFitsMeta(attr_info,attr_info.table_name))
// // 			return false;
// // 	}
// // 	return true;
// // }
// // bool checkIsCondValid(int cond_count, Condition* cond_list){
// // 	string tmp_name = tb_name;
// // 	for (int i = 0; i < cond_count; ++i)
// // 	{
// // 		AttrInfo attr_info;
// // 		if(cond_list[i].tb_name!=NULL)
// // 			attr_info.table_name = cond_list[i].tb_name;
// // 		attr_info.table_name = tb_name;
// // 		attr_info.attr_name = cond_list[i].col_name;
// // 		attr_info.type = cond_list[i].value_type;
// // 		if(!isAttrFitsMeta(attr_info,attr_info.table_name))
// // 			return false;
// // 		return true;

// // 	}
// // }
// // /*
// // TODO: add site check.
// //  */
// // bool checkIsFragStmtValid(){
// // 	for (int i = 0; i < frag_count; ++i)
// // 	{
// // 		for (int j = 0; j < frag_list[i].attr_count; ++j)
// // 		{
// // 			string tmp_attr_name = frag_list[i].attr_names[j];
// // 			if(!isAttrExists(tmp_attr_name,frag_tb_name)){
// // 				cout<<"ERROR: attribute not exists."<<endl;
// // 				cout<<tmp_attr_name<<endl;
// // 				return false;
// // 			}
// // 		}
// // 		if(!checkIsCondValid(frag_list[i].cond_count,frag_list[i].CondList))
// // 			return false;
// // 	}
// // 	return true;
// // }
