%{
extern int yylex();
extern int yyerror();
extern int lex_init();
#include <stdio.h>
#include <string.h>

char* tbname;
static unsigned int attrcnt;


static int funcRnt;

static int curPos;
static char recordstr[4096];

int condcnt;

static char errmsg[4096];

static int SelCnt;
int optrans(char* opstr);
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
%left	 AND
%left COMPARISION /* < <= > >= <> = */
%left '+' '-'
%left '*' '/'

	/* reserved keywords */
%token SELECT FROM WHERE ORDER BY ASC DESC
%token ALL UNIQUE DISTINCT
%token CREATE TABLE DROP INDEX
%token INSERT INTO VALUES DELETE
%token CHARACTER VARCHAR INTEGER DATE
%token SHOW TABLES
%token EXIT

%%

sql_start:
		sql_func
		{
			/*(funcRnt == 0)
				printf("> Success.\n");
			else if(funcRnt < 0)
			{
				printf("> Failure:%d> %s\n",funcRnt,errmsg);
			}*/
			printf("> Success.\n");
			return 0;
		}
	|	EXIT
		{
			printf("EXIT.\n");
			return 0;
		}
	;
sql_func:
		';'
		{
			printf(";\n");
		}
	|	table_def
	|	table_drop
	|	insert_stat
	|	delete_stat
	|	select_stat
	;
/* create table */
table_def:
		CREATE TABLE table '(' table_attr_list ')' ';'
		{	
			printf(">CreateTable fuc. (%s,%d,%s)\n",tbname,attrcnt,errmsg);
		}
	;

table:
		NAME
		{
			tbname = $1;
			printf("tbname %s \n",tbname);
		}
	;
table_attr_list:
		column_def
	|	table_attr_list ',' column_def
	;
column_def:
		column data_type
		{
			attrcnt++;
			printf("attrcnt %d \n", attrcnt);
		}
	;
column:
		NAME
		{
			//attrs[attrcnt].name = $1;
			printf("attr %s \n",$1);
			printf("column name %s \n",$1);
			//cond[condcnt].columnName = $1;
		}
	;
data_type:
		CHARACTER '(' NUMBER ')'
		{
			printf("attrs type is CHAR\n");
			printf("attrs used is %d",atoi($3));
		}
	|
		VARCHAR '(' NUMBER ')'
		{
			printf("attrs type is VARCHAR\n");
			printf("attrs used is %d",atoi($3));
		}
	|	INTEGER
		{
			printf("attrs type is INT.\n");
			printf("attrs used is %d",1);
		}
	|	DATE
		{
			printf("attts type is DATE.\n");
			printf("attrs used is %d",1);
		}
	;
/* drop table */
table_drop:
		DROP TABLE table ';'
		{
			printf(">DropTable fuc (%s,%s).\n",tbname,errmsg);
		}
	;
/**************************************
**About Records operations Statements
**************************************/
/* insert statements */
insert_stat:
		INSERT INTO table VALUES '(' insert_list ')' ';'
		{
			printf("InsertRecord func(newdb,%s,%s,%s)\n",tbname,recordstr,errmsg);
		}
	; 	
insert_list:
		NUMBER
		{
			strcpy(recordstr+curPos, $1);
			curPos+=strlen($1);
			printf("insert_list NUMBER %d, curPos = %d \n",atoi($1),curPos);
		}
	|	STRING
		{
			strcpy(recordstr+curPos, $1);
			curPos+=strlen($1);
			printf("insert_list STRING %s, curPos = %d \n",$1,curPos);
		}
	|	insert_list ',' NUMBER
		{
			strcpy(recordstr+curPos, ",");
			curPos++;
			printf("insert_list NUMBER %s, curPos = %d \n",",",curPos);
			strcpy(recordstr+curPos, $3);
			curPos += strlen($3);
			printf("insert_list NUMBER %s, curPos = %d \n",$3,curPos);
		}
	|	insert_list ',' STRING
		{
			strcpy(recordstr+curPos, ",");
			curPos++;
			printf("insert_list STRING %s, curPos = %d \n",",",curPos);
			strcpy(recordstr+curPos, $3);
			curPos += strlen($3);
			printf("insert_list STRING %s, curPos = %d \n",$3,curPos);
		}
	;
	/* delete statement */
delete_stat:
		DELETE FROM table where_clause ';'
		{
			printf("DeleteRecord func(%s,condsm,%s).\n",tbname,errmsg);
		}
	;


/* select statements */
select_stat:
		select_seg ';'
		{
			printf("Finish\n");
		}
	;
select_seg:
		select_clause FROM fromlist where_clause
		{
			char* tmptbname = (char*)malloc(7);		//set a tmp tbname for the catch table of selection results.
			sprintf(tmptbname,"%s%d","TMPTB_",SelCnt);
			
			printf("select_seg\n");			
			printf("-----one sub selection end----\n");
		}
	;
select_clause:
		selectbegin unique sellist
		{
			printf("select begin unique sellist.\n");
			
		}
	|	selectbegin unique '*'
		{
			printf("select begin unique *.\n");
			
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
			printf("unique empty.\n");
		
		}
	|	ALL
		{
			printf("unique all.\n");
			
		}
	|	DISTINCT
		{
			printf("unique distinct.\n");
		}
	|	UNIQUE
		{
			printf("unique unique.\n");
			
		}
	;
sellist:
		sel_column
	|	sellist ',' sel_column
	;
sel_column:
		NAME
		{
			printf("sel_column NAME %s.\n",$1);
			
		}
	|	NAME '.' NAME
		{
			printf("sel_column NAME.NAME %s.%s \n",$1,$3);
		}
	;		
fromlist:
		sel_table
	|	fromlist ',' sel_table
	;
sel_table:
		NAME
		{	
			
			printf("AddSelTB NAME %s",$1);
			
		}
		/* sub selection */
	|	'(' select_seg ')' /* +empty */			
		{	
			char* tmptbname = (char*)malloc(8);		//set a tmp tbname for the catch table of selection results.
			sprintf(tmptbname,"%s%d","TMPTB_",SelCnt++);
			printf("AddSelTB NAME %s %s",tmptbname,tmptbname);
		}
	|	'(' select_seg ')' NAME			
		{	
			char* tmptbname = (char*)malloc(7);		//set a tmp tbname for the catch table of selection results.
			sprintf(tmptbname,"%s%d","TMPTB_",SelCnt++);
			printf("AddSelTB NAME %s %s",tmptbname,$4);
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
			printf("Join %s.%s compare%d %s.%s \n",$1,$3,optrans($4),$5,$7);
			
		}
	|	NAME COMPARISION NUMBER
		{
			printf("SelConditions %s compare%d %s \n",$1,optrans($2),$3);
		}
	|	NAME COMPARISION STRING
		{
			printf("SelConditions %s compare%d %s \n",$1,optrans($2),$3);
		}
	|	NAME '.' NAME COMPARISION NUMBER
		{
			printf("SelConditions %s.%s compare%d %s \n",$1,$3,optrans($4),$5);
		}
	|	NAME '.' NAME COMPARISION STRING
		{
			printf("SelConditions %s.%s compare%d %s \n",$1,$3,optrans($4),$5);
		}
	;
%%


void parser_init()
{
	lex_init();
	attrcnt = 0;
	tbname = NULL;
	funcRnt = 0;
	curPos = 0;
	condcnt = 0;
	SelCnt = 0;
	return;
}
int optrans(char* opstr)
{
	if (strcmp(opstr, "=") == 0) 
		return 0;
		//return EQ;
	else if (strcmp(opstr, ">=") == 0) 
		return 1;
		//return GE;
	else if (strcmp(opstr, "<=") == 0) 
		return 2;
		//return LE;
	else if (strcmp(opstr, ">") == 0) 
		return 3;
		//return GT;
	else if (strcmp(opstr, "<") == 0)
		return 5;
		//return LT;
	else if (strcmp(opstr, "<>") == 0)
		return 6;
		//return NE;
	return -1;
}
