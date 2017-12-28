extern "C"{
	extern int yylex(void);
	extern int lex_init();
	//extern void parser_init();
	extern int yyerror(char *s);
}




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

	