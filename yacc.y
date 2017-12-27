%{
#include <string.h>
#include "parser.h"

extern "C"{
	extern int yylex(void);
	extern int lex_init();
	//extern void parser_init();
	extern int yyerror(char *s);
}//extern "C" is necessary

OP Operator(char* opstr);
TYPE GetType(char* type_str);
int SaveSelItem(char* tb_name, char* col_name);
int SaveFromItem(char* tb_name);
int SaveCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op);
int SaveJoin(char* tb_name1, char* col_name1, char* tb_name2, char* col_name2, OP op);
int SaveOrderbyItem(char *col_name);
int SaveFragCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op);
int SaveFragCondition();
int FillSelectCond();
int FillDeleteCond();
/*
for insert stmt
 */
int insert_count = 0;
char* insert_record[MAX_TUPLE_SIZE];

/*
for create stmt.
 */
int attr_count = 0;
char* tb_name;
AttrInfo attr_list[MAX_ATTR_NUM];

/*
frag stmt.
 */
char frag_sql[10][MAX_SQL_SIZE];
char data_paths[10][MAX_SQL_SIZE];
int frag_count = 0;
int frag_cond_count = 0;
int frag_attr_count = 0;
char* frag_tb_name;
FRAG_TYPE frag_type;
FragInfo frag_list[MAX_FRAG_NUM];


SelectQuery* query;
DeleteQuery* delete_query;
int cond_count = 0;
int join_count = 0;
int sel_count = 0;
int from_count = 0;
int orderby_count = 0;
int curPos = 0;
int funcRnt;
Condition cond_list[MAX_COND_NUM];
static char errmsg[4096];
static char recordstr[4096];
%}

%union{
	int intval;
	char* strval;
}

%start sql_start

%token <strval> NAME
%token <strval> STRING
%token <strval> NUMBER
%token <strval> COMPARISION

	/* operator */
%left	 AND OR
%left COMPARISION /* < <= > >= <> = */
%left '+' '-'
%left '*' '/'

	/* reserved keywords */
%token SELECT FROM WHERE ORDER BY ASC DESC FRAGMENT
%token ALL UNIQUE DISTINCT
%token CREATE TABLE DROP INDEX
%token INSERT INTO VALUES DELETE
%token CHARACTER INTEGER DATE FLOAT VARCHAR
%token HORIZONAL VERTICAL MIX
%token SHOW TABLES
%token EXIT

%%

sql_start:
		sql_func
		{
			if(funcRnt == 0)
			{
				cout << "Success" <<endl;
			}
			else if(funcRnt < 0)
			{
				cout << "Failure："<<funcRnt<<errmsg<<endl; 
			}
			return 0;
		}
	|	EXIT
		{
			cout<<"Should Flush Table Here.\n"<<endl;
		}
	;
sql_func:
		';'
		{
			funcRnt = 100;
		}
	|	table_def
	|	table_drop
	|	insert_stat
	|	delete_stat
	|	select_stat
	|	frag_stat
	;

frag_stat:
		FRAGMENT '-'HORIZONAL NAME frag_list_h ';'
		{
			frag_type = HOR;
			frag_tb_name = $4;
			cout<<"frag type is " << frag_type <<" HORIZONAL "<<endl;
			cout<<"frag_tb_name is "<<frag_tb_name<<endl;
			cout<<"load_data";
			load_data();
		}
	|	FRAGMENT '-'VERTICAL  NAME frag_list_v ';'
		{
			frag_type = VER;
			frag_tb_name = $4;
			cout<<"frag type is " << frag_type <<" VERTICAL "<<endl;
			cout<<"frag_tb_name is "<<frag_tb_name<<endl;
			load_data();
		}
	|	FRAGMENT '-'MIX		  NAME frag_list_m	';'
	{
			frag_type = M;
			frag_tb_name = $4;
			cout<<"frag type is " << frag_type <<" MIXED"<<endl;
			cout<<"frag_tb_name is "<<frag_tb_name<<endl;
			load_data();
	}
	;
frag_list_m:
	frag_cond '(' attr_list ')' NAME
	{
		frag_list[frag_count].site_name = $5;
		frag_list[frag_count].cond_count = frag_cond_count;
		frag_list[frag_count].attr_count = frag_attr_count;
		cout<<"M:db_name is "<< frag_list[frag_count].site_name <<endl;
		cout<<"frag info"<< frag_list[frag_count].cond_count<<" "<< frag_list[frag_count].attr_count << endl;
		for(int i = 0; i < frag_list[frag_count].cond_count; i++){
			cout<< "cond " << i <<" "<<frag_list[frag_count].CondList[i].col_name <<" op " <<frag_list[frag_count].CondList[i].op <<" "<<frag_list[frag_count].CondList[i].value<<endl;
		}
		for(int i=0; i< frag_list[frag_count].attr_count; i++){
			cout<<frag_list[frag_count].attr_names[i]<<",";
		}
		frag_cond_count = 0;
		frag_attr_count = 0;
		frag_count ++;
	}
;
frag_list_h:
		frag_h
	|	frag_list_h '*' frag_h
	;
frag_h:
		frag_cond NAME
		{
			frag_list[frag_count].site_name = $2;
			frag_list[frag_count].cond_count = frag_cond_count;
			frag_list[frag_count].attr_count = frag_attr_count;
			cout<<"M:db_name is "<< frag_list[frag_count].site_name <<endl;
			cout<<"frag info "<< frag_list[frag_count].cond_count<<" "<< frag_list[frag_count].attr_count << endl;
			for(int i = 0; i < frag_list[frag_count].cond_count; i++){
				cout<< "cond " << i <<" "<<frag_list[frag_count].CondList[i].col_name <<" op " <<frag_list[frag_count].CondList[i].op <<" "<<frag_list[frag_count].CondList[i].value<<endl;
			}
			for(int i=0; i< frag_list[frag_count].attr_count; i++){
				cout<<frag_list[frag_count].attr_names[i]<<",";
			}
			frag_cond_count = 0;
			frag_attr_count = 0;
			frag_count ++;
		}
		;
frag_cond:
		frag_expr
	|	frag_cond AND frag_expr
	;
frag_expr:
		NAME COMPARISION NUMBER
		{
			SaveFragCondition("", $1, $3, I, Operator($2));	
		
		}
	|	NAME COMPARISION STRING
		{
			SaveFragCondition("", $1, $3, C, Operator($2));
		}
	;
frag_list_v:
		frag_v
	|	frag_list_v '*' frag_v
	;
frag_v:
		'(' attr_list ')' NAME
		{
			frag_list[frag_count].site_name = $4;
			frag_list[frag_count].cond_count = frag_cond_count;
			frag_list[frag_count].attr_count = frag_attr_count;
			/*
				print this frag info.
			 */
			cout<<"M:db_name is "<< frag_list[frag_count].site_name <<endl;
			cout<<"frag info"<< frag_list[frag_count].cond_count<<" "<< frag_list[frag_count].attr_count << endl;
			for(int i = 0; i < frag_list[frag_count].cond_count; i++){
				cout<< "cond " << i <<" "<<frag_list[frag_count].CondList[i].col_name <<" op " <<frag_list[frag_count].CondList[i].op <<" "<<frag_list[frag_count].CondList[i].value<<endl;
			}
			for(int i=0; i< frag_list[frag_count].attr_count; i++){
				cout<<frag_list[frag_count].attr_names[i]<<",";
			}
			cout<<endl;
			/*
				initial cout.
			 */
			frag_cond_count = 0;
			frag_attr_count = 0;
			frag_count ++;
		}
	;
attr_list:
		attr_name
	|	attr_list ',' attr_name
	;
attr_name:
		NAME
		{
			frag_list[frag_count].attr_names[frag_attr_count] = (char*)malloc(sizeof($1));
			memcpy(frag_list[frag_count].attr_names[frag_attr_count],$1,sizeof($1));
			frag_attr_count++;
		}
	;

/* create table */
table_def:
		CREATE TABLE table '(' table_attr_list ')' ';'
		{
			cout<<"Create Table "<< tb_name << endl;
			PrintAttrList();
			cout<<"exec_create_stmt"<<endl;
			exec_create_stmt();
			//parser_init();	
		}
	;

table:
		NAME
		{
			tb_name = $1;
			attr_list[attr_count].table_name = $1;
			//printf("tb_name %s \n",tb_name);
		}
	;
table_attr_list:
		column_def
	|	table_attr_list ',' column_def
	;
column_def:
		column data_type
		{
			attr_count++;
			
		}
	;
column:
		NAME
		{
			attr_list[attr_count].attr_name = $1;
		}
	;
data_type:
		CHARACTER '(' NUMBER ')'
		{
			attr_list[attr_count].type = C;
			attr_list[attr_count].used_size = (int)atoi($3);
		}
	|	INTEGER
		{
			attr_list[attr_count].type= I;
			attr_list[attr_count].used_size = 1;
		}
	|	DATE
		{
			attr_list[attr_count].type= D;
			attr_list[attr_count].used_size = 1;
		}
	|
		VARCHAR '(' NUMBER ')'
		{
			attr_list[attr_count].type= V;
			attr_list[attr_count].used_size = (int)atoi($3);
		}
	|
		FLOAT '(' NUMBER ')'
		{
			attr_list[attr_count].type= F;
			attr_list[attr_count].used_size = (int)atoi($3);
		}
	;
/* drop table */
table_drop:
		DROP TABLE table ';'
		{
			cout<<"DROP TABLE"<< tb_name << endl;
			cout<<"exec_drop_table_stmt"<<endl;
			exec_drop_table_stmt();
		}
	;
/* insert statements */
insert_stat:
		INSERT INTO table VALUES '(' insert_list ')' ';'
		{
			cout << "Call Insert Func() here."<<endl;
			cout << "INSERT INTO " << tb_name << " " << recordstr <<endl;
			for(int i = 0; i<insert_count;i++){
				cout<<i<<" "<<insert_record[i]<<endl;
			}			
			//parser_init();
		}
	; 	
insert_list:
		NUMBER
		{
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_LENGTH);
			memcpy(insert_record[insert_count],$1, MAX_INT_LENGTH);
			insert_count++;

			strcpy(recordstr+curPos, $1);
			curPos+=strlen($1);
		}
	|	STRING
		{
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],$1, 256);

			strcpy(recordstr+curPos, $1);
			curPos+=strlen($1);
		}
	|	insert_list ',' NUMBER
		{
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_LENGTH);
			memcpy(insert_record[insert_count],$3, MAX_INT_LENGTH);
			insert_count++;

			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, $3);
			curPos += strlen($3);
		}
	|	insert_list ',' STRING
		{
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],$3,256);
			insert_count++;

			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, $3);
			curPos += strlen($3);
		}
	;
	/* delete statement */
delete_stat:
		DELETE FROM table where_clause ';'
		{
			cout << "DELETE FROM\n"<<endl;
			delete_query->tb_name = tb_name;
			cout << delete_query->tb_name <<endl;
			FillDeleteCond();
			PrintCondList();
			cout << "Call delete() function here."<<endl;
			
		}
	;


/* select statements */
select_stat:
		select_seg ';'
		{
		}
	;
select_seg:
		select_clause FROM fromlist where_clause orderby_clause
		{
			FillSelectCond();
			PrintSelectQuery();
			//query->tb_name = tb_name;
			query->cond_count = cond_count;
			query->sel_count = sel_count;
			query->join_count = join_count;
			query->from_count = from_count;
			//cout<<"query_tb_name"<<query->tb_name<<endl;
			cout<<"cond "<<query->cond_count<<"sel "<<query->sel_count<<"join "<<query->join_count<<"from "<<query->from_count<<endl;
			exec_select_stmt();
			//parser_init();
			
		}
	;
select_clause:
		selectbegin unique sellist
		{
			query->all = 0;
			cout<<"all "<<query->all<<endl;
		}
	|	selectbegin unique '*'
		{
			query->all = 1;
			cout<<"all "<<query->all<<endl;
		}
	;
selectbegin:
		SELECT
		{
			printf("-----one sub selection begin----\n");
		}
	;
unique:
		/* empty */
		{
			query->distinct = 0;
			cout<<"distinct "<<query->distinct<<endl;
		}
	|	ALL
		{
			query->distinct = 0;
			cout<<"distinct "<<query->distinct<<endl;
		}
	|	DISTINCT
		{
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
	|	UNIQUE
		{
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
	;
sellist:
		sel_column
	|	sellist ',' sel_column
	;
sel_column:
		NAME
		{
			SaveSelItem(NULL,$1);
		}
	|	NAME '.' NAME
		{
			SaveSelItem($1,$3);
		}
	;		
fromlist:
		sel_table
	|	fromlist ',' sel_table
	;
sel_table:
		NAME
		{	
			SaveFromItem($1);
			
		}
		/* sub selection */
	|	'(' select_seg ')' /* +empty */			
		{	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
	|	'(' select_seg ')' NAME			
		{	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
		;	
where_clause:
		/* empty */
	|	WHERE condition
	;
condition:
		expr
	|	condition AND expr
	;
expr:
		NAME '.' NAME COMPARISION NAME '.' NAME
		{
			SaveJoin($1, $3, $5, $7, Operator($4));	
		}
	|	NAME COMPARISION NUMBER
		{
			SaveCondition("", $1, $3, I, Operator($2));	
		}
	|	NAME COMPARISION STRING
		{
			SaveCondition("", $1, $3, C, Operator($2));
		}
	|	NAME '.' NAME COMPARISION NUMBER
		{
			SaveCondition($1, $3, $5, I, Operator($4));
		}
	|	NAME '.' NAME COMPARISION STRING
		{
			SaveCondition($1, $3, $5, C, Operator($4));
		}
	;
orderby_clause:
	/*empty*/
	|	ORDER BY orderlist
	;
orderlist:
		NAME
		{
			SaveOrderbyItem($1);
		}
	| 	orderlist ',' NAME
	;
%%

void parser_init()
{
	lex_init();
	tb_name = NULL;
	frag_tb_name = NULL;
	for(int i = 0; i<insert_count;i++)
		memset(insert_record[i],0,MAX_TUPLE_SIZE);
	memset(attr_list,0,sizeof(AttrInfo)*MAX_ATTR_NUM);
	memset(cond_list,0,sizeof(Condition)*MAX_COND_NUM);
	memset(query,0,sizeof(SelectQuery));
	funcRnt = 0;
	//curPos = 0;
	
	cond_count = 0;
	join_count = 0;
	attr_count = 0;
	sel_count = 0;
	from_count = 0;

	frag_count = 0;
	frag_cond_count = 0;
	frag_attr_count = 0;
	frag_tb_name = NULL;
	memset(frag_list,0,sizeof(FragInfo)*MAX_FRAG_NUM);
	for(int i = 0; i<10;i++){
		memset(frag_sql[i],0,sizeof(char)*MAX_SQL_SIZE);
		memset(data_paths[i],0,sizeof(char)*MAX_SQL_SIZE);

	}	
	return;
}

void InitQuery(){
	delete_query = (DeleteQuery*)malloc(sizeof(DeleteQuery));
	query = (SelectQuery*)malloc(sizeof(SelectQuery));
	query->distinct = 0;
	query->all = 0;
}
void DestoryQuery(){
	free(delete_query);
	free(query);
}
int SaveCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op){
	if(cond_count > MAX_COND_NUM){
		return -1;
	}
	cond_list[cond_count].col_name = col_name;
	
	cond_list[cond_count].tb_name = tb_name;
	cond_list[cond_count].value = value;
	
	cond_list[cond_count].value_type = value_type;
	
	cond_list[cond_count].op = op;
	
	cond_count++;
	
	return 0;
}
int SaveFragCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op){
	if(cond_count > MAX_COND_NUM){
		return -1;
	}
	frag_list[frag_count].CondList[frag_cond_count].col_name = col_name;
	frag_list[frag_count].CondList[frag_cond_count].op = op;
	frag_list[frag_count].CondList[frag_cond_count].tb_name = tb_name;
	frag_list[frag_count].CondList[frag_cond_count].value = value;
	frag_list[frag_count].CondList[frag_cond_count].value_type = value_type;

	frag_cond_count++;
	
	return 0;
}
int SaveJoin(char* tb_name1, char* col_name1, char* tb_name2, char* col_name2, OP op){
	if(join_count > MAX_JOIN_NUM){
			return -1;
		}
	query->JoinList[join_count].col_name1 = col_name1;
	query->JoinList[join_count].col_name2 = col_name2;
	query->JoinList[join_count].op = op;
	query->JoinList[join_count].tb_name1 = tb_name1;
	query->JoinList[join_count].tb_name2 = tb_name2;
	join_count++;
	return 0;

}

int SaveSelItem(char* tb_name, char* col_name){
	query->SelList[sel_count].col_name = col_name;
	query->SelList[sel_count].table_name = tb_name;
	sel_count ++;
	return 0;
}
int SaveFromItem(char* tb_name){
	query->FromList[from_count].tb_name = tb_name;
	from_count++;
	return 0;
}
int SaveOrderbyItem(char *col_name){
	query->OrderbyList[orderby_count].col_name = col_name;
	orderby_count ++;
	return 0;
}
int FillSelectCond(){
	memcpy(query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}
int FillDeleteCond(){
	memcpy(delete_query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}


/*
 * attr_list: attributes iostreamfor a table
 */
int PrintAttrList(){
	int i;
	for(i=0;i<attr_count;i++){
			cout<<"attr "<<i<<": "<<attr_list[i].attr_name<<" type "<<attr_list[i].type<<" size "<<attr_list[i].used_size<<endl;
		}
		return 0;
}
int PrintCondList(){
	int i;
	for(i = 0; i < cond_count; i++){
		cout << "AND "<<endl;	
		if(cond_list[i].tb_name != "")
			cout<<"\t"<<cond_list[i].tb_name<<"."<<cond_list[i].col_name<<" op "<<cond_list[i].op<<" "<< cond_list[i].value<<endl;
		else
			cout << " op " << query->CondList[i].op << endl;
			cout<<"\t"<<cond_list[i].col_name<<" op "<<cond_list[i].op<<" "<< cond_list[i].value<<endl;		
	}
}
int PrintSelectQuery(){
	int i = 0;
	if(from_count!=0)
		cout << "SELECT "<< endl;
	if(query->all != 0)
		cout<< "*" << endl;
	if(sel_count!=0){
		cout << "SEL_LIST" <<endl;
		for(i=0; i < sel_count; i++){
			cout<<"\t"<<query->SelList[i].col_name<<endl;
		}
	}	
	cout << "FROMLIST" << endl;
	for(i = 0; i < from_count; i++){
		cout<<"\t"<<query->FromList[i].tb_name<<endl;
	}
	if(cond_count!=0){
		cout <<"WHERECLAUSE"<< endl;
	}
	//PrintTree();
	for(i = 0; i < cond_count; i++){
			
		if(query->CondList[i].tb_name != "")
			cout<<"\t"<<query->CondList[i].tb_name<<"."<<query->CondList[i].col_name<<" op "<<query->CondList[i].op<<" "<< query->CondList[i].value<<endl;
		else
			//cout << " op " << query->CondList[i].op << endl;
			cout<<"\t"<<query->CondList[i].col_name<<" op "<<query->CondList[i].op<<" "<< query->CondList[i].value<<endl;	
		cout << "AND "<<endl;	
	}
	for(i=0;i < join_count; i++){
		cout<<"\t"<<query->JoinList[i].tb_name1<<"."<<query->JoinList[i].col_name1<<" op "<<query->JoinList[i].op<<" "<<query->JoinList[i].tb_name2<<"."<<query->JoinList[i].col_name2<<endl;
		cout << "AND "<<endl;
	}
	if(attr_count != 0)
		cout<<"CREATE TABLE "<<endl;
	for(i=0;i<attr_count;i++){
		cout<<attr_list[i].table_name<<"attr_name "<<attr_list[i].attr_name<<"type "<<attr_list[i].type<<"size "<<attr_list[i].used_size<<endl;
	}
	if(orderby_count!=0)
		cout<<"ORDER BY"<< endl;
	for(i=0;i<orderby_count;i++)
		cout<<query->OrderbyList[i].col_name<<endl;
	
	return 0;
}

bool GetFragInfo(FragInfo *g_frag_list,char* g_tb_name,int g_frag_count,int g_frag_type){
	cout<<"enter GetFragInfo"<<endl;
	cout<<"frag_count"<<frag_count<<endl;
	if(frag_count == 0)
	{
		cout<<"there is no frag info"<<endl;
		return false;
	}
	if(NULL == (g_frag_list = (FragInfo*) malloc(frag_count*sizeof(FragInfo)))){
		cout<<"malloc failure."<<endl;
		return false;
	}
	if(NULL == memcpy(g_frag_list,frag_list,frag_count*sizeof(FragInfo))){
		cout<<"memcpy failure."<<endl;
		return false;
	}
	if(NULL == strcpy(g_tb_name,frag_tb_name)){
		cout<<"strcpy failure."<<endl;
		return false;
	}
	g_frag_count = frag_count;
	g_frag_count = frag_type;
	return true;

}

OP Operator(char* opstr)
{
	OP op;
	if (strcmp(opstr, "=") == 0){
		op = E;
		return op;
	}
	else if (strcmp(opstr, ">=") == 0) {
		op = GE;
		return op;
	}	
	else if (strcmp(opstr, "<=") == 0){
		op = LE;
		return op;
	}
	else if (strcmp(opstr, ">") == 0) {
		op = G;
		return op;
	}
	else if (strcmp(opstr, "<") == 0) {
		op = L;
		return op;
	}
	else if (strcmp(opstr, "<>") == 0) {
		op = NE;
		return op;
	}
	return E;
}

TYPE GetType(char* type_str)
{
	TYPE type;
	if (strcmp(type_str, "INTEGER") == 0){
		type = I;
		return type;
	}
	else if (strcmp(type_str, "CHARACTER") == 0) {
		type = C;
		return type;
	}	
	else if (strcmp(type_str, "VARCHAR") == 0){
		type = V;
		return type;
	}
	else if (strcmp(type_str, "FLOAT") == 0) {
		type = F;
		return type;
	}
	else if (strcmp(type_str, "DATE") == 0) {
		type = D;
		return type;
	}
	return I;
}

