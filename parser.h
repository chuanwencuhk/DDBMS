/*
 * paser.h *
 *  Created on: Nov 30, 2017
 *      Author: wcw
 */
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
using namespace std;

#define MAX_SELITEM_NUM 20
#define MAX_ATTR_NUM 20
#define MAX_FROM_NUM 20
#define MAX_COND_NUM 20
#define MAX_JOIN_NUM 20
#define MAX_ORDER_BY 20
#define MAX_ATTR_NAME_LENGTH 50
#define MAX_FRAG_NUM 4
#define MAX_TUPLE_SIZE 512
#define MAX_INT_LENGTH 16
#define MAX_SQL_SIZE 1024


enum FRAG_TYPE
{
	HOR=1,VER,M,N
};
enum TYPE{
	I=1,C,V,F,D
};
enum OP{
	E=1,GE,G,LE,L,NE
};


/*
 * for create, store table meta data info
 * create table_name
 * 					attr1 type1 size1
 * 					attr2 type2 size2
 * 					...;
 */
struct AttrInfo{
	char* table_name;
	char* attr_name;
	TYPE type;
	int used_size;
};

/*
 * select sellist from fromlist where condlist orderby orrderlist;
 */

struct SelItem{
	char* table_name;
	char* col_name;
	int col_id;
};


struct FromItem{
	//Relname
	char* tb_name;
	int tb_id;
//	struct FromList *next;
};

struct Condition{
	/*
	 * cond1:tb1.col_name1 op tb2.col_name2
	 * cond2:tb1.col_name1 op value;
	 */
	
	OP op;
	char* tb_name;
	int tb_id;
	char* col_name;
	char* value;
	TYPE value_type;
//	struct Condition* next;
};

struct Join{
	OP op;
	char* tb_name1;
	char* tb_name2;
	char* col_name1;
	char* col_name2;

//	struct Join* next;
};
struct Orderby{
	char* col_name;
	int   col_id;
};

struct SelectQuery{
	int distinct;
	int all;
	int sel_count;
	int cond_count;
	int from_count;
	int join_count;
	SelItem		SelList[MAX_SELITEM_NUM];
	FromItem 	FromList[MAX_FROM_NUM];
	Join 		JoinList[MAX_JOIN_NUM];
	Condition 	CondList[MAX_COND_NUM];
	Orderby 	OrderbyList[MAX_ORDER_BY];
	SelectQuery* next;
};

struct DeleteQuery{
	char* tb_name;
	int cond_count;
	Condition	CondList[MAX_JOIN_NUM];
};

struct UpdateQuery{
	char* tb_name;
	char* col_name[256];
	char* col_value[256];
	int col_count;
	int cond_count;
	Condition	CondList[MAX_COND_NUM];
};


struct FragInfo{
	//FRAG_TYPE frag_type;
	char* site_name;
	int cond_count;
	int attr_count;
	Condition CondList[MAX_COND_NUM];
	char* attr_names[MAX_ATTR_NAME_LENGTH];
};

extern int frag_count;
extern char* frag_tb_name;
extern FRAG_TYPE frag_type;
extern FragInfo frag_list[MAX_FRAG_NUM];
extern string frag_select_stmt[MAX_FRAG_NUM];

extern SelectQuery* query;
extern DeleteQuery* delete_query;

extern int attr_count;
extern char* tb_name;
extern AttrInfo attr_list[MAX_ATTR_NUM];

extern UpdateQuery* update_query;



 /* if necessary, query stack for nested query.*/
int PrintSelectQuery();
int PrintAttrList();
int PrintCondList();
void InitQuery();
void DestoryQuery();
void parser_init();
bool GetFragInfo(FragInfo *g_frag_list,char* g_tb_name, int g_frag_count,int g_frag_type);
void printFraglist();
void print();


/*
	funcs called in conn_mysql.cpp
*/
void spliceFragToSelect();
string spliceSelectStmt();
string spliceCreateStmt();
string spliceDropStmt();
string spliceDeleteStmt();
string spliceUpdateStmt();

/*
	funcs called in yacc.y
 */
void exec_drop_table_stmt();
void exec_create_stmt();
void exec_select_stmt();
void exec_delete_stmt();
void exec_update_stmt();
void exec_show_table_stmt();
int load_data_into_local_db(string tb_name);
void load_data();

