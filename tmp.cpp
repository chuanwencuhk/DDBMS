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
	reutrn true;

}

	