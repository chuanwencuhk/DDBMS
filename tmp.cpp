for (int i = 0; i < frag_count; ++i)
	{
		if(frag_type == HORIZONAL){

			tmp_frag.condition_slice[i].isValid = true;
			tmp_frag.condition_slice[i].con_H1.isValid = true;
			tmp_frag.condition_slice[i].con_H1.attr_name = frag_list[i].CondList[0].col_name;
			tmp_frag.condition_slice[i].con_H1.attr_condition = GetTypeString(frag_list[i].CondList[0].op);
			tmp_frag.condition_slice[i].con_H1.attr_value = frag_list[i].CondList[0].value;

			tmp_frag.condition_slice[i].con_H2.isValid = true;
			tmp_frag.condition_slice[i].con_H2.attr_name = frag_list[i].CondList[1].col_name;
			tmp_frag.condition_slice[i].con_H2.attr_condition = GetTypeString(frag_list[i].CondList[1].op);
			tmp_frag.condition_slice[i].con_H2.attr_value = frag_list[i].CondList[1].value;
			tmp_frag.condition_slice[i].con_V1.attr_num = 0;
			tmp_frag.condition_slice[i].con_V1.isValid = false;
		}
		tmp_frag.condition_slice[i].con_V1.attr_num
		for (int j = 0; j < attr_num; ++j)
			{
				tmp_frag.condition_slice[i].con_V1.attr_frag_strlist[i]
			}
		
	}


bool isTableExists(string table_name){
	TableMedata tmp_tb_meta;
	tmp_tb_meta = mt.get_tablemetadata(&table_name);
	
	if(tmp_tb_meta.table_name == "")
		return false;
	return true;
}


TARGET = main

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++
CFLAGS = -g -Wall -I${DIR_INC} -I/usr/include/mysql/ -lmysqlclient -lrpc_sql -pthread -lrpc -lmysqlcppconn -libconfig++


yacc.tab.c  yacc.tab.h: yacc.y
	$(YACC) -d yacc.y

lex.yy.c: lex.l
	$(LEX) lex.l

${BIN_TARGET}: ${OBJ}
    $(CC) $(OBJ)  -o $@
 

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
    $(CC) $(CFLAGS) -c  $< -o $@


.PHONY:clean
clean:
    find ${DIR_OBJ} -name *.o -exec rm -rf {}








/*
#DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
#DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.cpp)
DIR = $(notdir ${SRC})
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))

ALL:
	@echo $(SRC)
	@echo $(DIR)
	@echo $(OBJ)
*/




CC=g++
OBJECT=metadata

$(OBJECT): attribution.o tablemetadata.o metadatamanager.o main.o
	$(CC)  attribution.o tablemetadata.o metadatamanager.o main.o -lconfig++ -o $(OBJECT)

main.o: global.h metadatamanager.h
	$(CC) -c main.cpp
tablemetadata.o: tableMetadata.h attribution.h
	$(CC) -c tablemetadata.cpp
metadatamanager.o: tableMetadata.h metadatamanager.h global.h
	$(CC) -c metadatamanager.cpp
attribution.o: attribution.cpp attribution.h global.h
	$(CC) -c attribution.cpp

.PHONY: clean
clean:
	@rm -f $(OBJECT)  *.o

extern "C"{
	extern int yylex(void);
	extern int lex_init();
	//extern void parser_init();
	extern int yyerror(char *s);
}


LEX=flex
YACC=bison
CC=g++
OBJECT=parser			

$(OBJECT): lex.yy.o  yacc.tab.o parser.o conn_mysql.o main.o
	$(CC)  lex.yy.o yacc.tab.o parser.o conn_mysql.o main.o \
	-I/usr/include/mysql/ -lmysqlclient -lrpc_sql -pthread -lrpc -lmysqlcppconn -o $(OBJECT)

main.o: yacc.tab.h main.cpp
	$(CC) -c main.cpp

conn_mysql.o: parser.h parser.cpp lex.yy.c yacc.tab.c  yacc.tab.h conn_mysql.cpp
	$(CC) -c conn_mysql.cpp 

parser.o: parser.h parser.cpp lex.yy.c yacc.tab.c  yacc.tab.h
	$(CC) -c  parser.cpp

lex.yy.o: lex.yy.c  yacc.tab.h  parser.h
	$(CC) -c  lex.yy.c

yacc.tab.o: yacc.tab.c  parser.h
	$(CC) -c  yacc.tab.c
yacc.tab.c  yacc.tab.h: yacc.y
	$(YACC) -d yacc.y

lex.yy.c: lex.l
	$(LEX) lex.l

.PHONY:prepare
clean:
	rm -rf yacc.tab.* lex.yy.*
	@rm -f $(OBJECT)  *.o
prepare:
	cd /home/wcw/ddb_parser/rpc_sql
	g++ -c local_sql.cc rpc_server.cc rpc_sql.cc
	ar -crv librpc_sql.a local_sql.o rpc_server.o rpc_sql.o
	sudo cp librpc_sql.a /usr/local/lib/
	g++ -o myserver rpc_server_test.cc -lrpc_sql -pthread -lrpc -lmysqlcppconn


extern "C"{
	int yyerror(char *s);
	int yylex(void);
	int yywrap(void);
	int lex_init();
}
int main(){
	cout<<"begin"<<endl;
	InitQuery();
	while(1)
    {
       parser_init();
       int rnt = yyparse();
       if(rnt==-1)
            break;
    }
	DestoryQuery();
	return 0;
}

/*
frag stmt.
 */
char frag_sql[10][MAX_SQL_SIZE];
char data_paths[10][MAX_SQL_SIZE];
int frag_count = 0;
int frag_cond_count = 0;
int frag_attr_count = 0;
FRAG_TYPE frag_type;
FragInfo frag_list[MAX_FRAG_NUM];

struct FragInfo{
	char* site_name;
	int cond_count;
	int attr_count;
	Condition CondList[MAX_COND_NUM];
	char* attr_names[MAX_ATTR_NAME_LENGTH];
};

bool GetFragInfo(FragInfo *g_frag_list,char* g_tb_name,int g_frag_count,int g_frag_type){
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

// if(query->cond_count!=0){
		// 	tmp_stmt.append(" WHERE ");
		// 	tmp_stmt.append(query->CondList[0].col_name);
		// 	tmp_stmt.append(" ");
		// 	string type_string = string(" ");
		// 	type_string = GetTypeString(query->CondList[0].op);
		// 	tmp_stmt.append(type_string);
		// 	tmp_stmt.append(query->CondList[0].value);
		// }
		// //cout<<tmp_stmt<<endl;
		// for(int i=1;i< query->cond_count;i++){
		// 	tmp_stmt.append(" AND ");
		// 	tmp_stmt.append(query->CondList[i].col_name);
		// 	tmp_stmt.append(" ");
		// 	string type_string = string(" ");
		// 	type_string = GetTypeString(query->CondList[i].op);
		// 	tmp_stmt.append(type_string);
		// 	tmp_stmt.append(query->CondList[i].value);
		// }
		//cout<<tmp_stmt<<endl;


			// tmp_stmt.append(" WHERE ");
			// if(frag_list[i].cond_count != 0){
			// 	tmp_stmt.append(frag_list[i].CondList[0].col_name);
			// 	string type_string = string(" ");
			// 	type_string = GetTypeString(frag_list[i].CondList[0].op);
			// 	tmp_stmt.append(type_string);
			// 	tmp_stmt.append(frag_list[i].CondList[0].value);

			// }
			// for(int j = 1; j < frag_list[i].cond_count; j++){
			// 	tmp_stmt.append(" AND ");
			// 	tmp_stmt.append(frag_list[i].CondList[j].col_name);
			// 	string type_string = string(" ");
			// 	type_string = GetTypeString(frag_list[i].CondList[j].op);
			// 	tmp_stmt.append(type_string);
			// 	tmp_stmt.append(frag_list[i].CondList[j].value);			
			// }
// if(delete_query->cond_count != 0){
	// 	tmp_stmt.append("WHERE ");
	// 	tmp_stmt.append(delete_query->CondList[0].col_name);
	// 	tmp_stmt.append(" ");
	// 	string type_string = GetTypeString(delete_query->CondList[0].op);
	// 	tmp_stmt.append(type_string);
	// 	tmp_stmt.append(delete_query->CondList[0].value);
	// }
	// for(int i=1;i< query->cond_count;i++){
	// 	tmp_stmt.append(" AND ");
	// 	tmp_stmt.append(delete_query->CondList[i].col_name);
	// 	tmp_stmt.append(" ");
	// 	string type_string = GetTypeString(delete_query->CondList[i].op);
	// 	tmp_stmt.append(type_string);
	// 	tmp_stmt.append(delete_query->CondList[i].value);
	// }

///var/lib/mysql-files/data.csv
// "SELECT * INTO OUTFILE '/var/lib/mysql-files/data.csv' FIELDS TERMINATED BY ',' FROM EMP;",
// strlen("SELECT * INTO OUTFILE '/var/lib/mysql-files/data.csv' FIELDS TERMINATED BY ',' FROM EMP;"

	