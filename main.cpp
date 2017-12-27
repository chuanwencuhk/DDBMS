#include <string.h>
#include <iostream>
#include "yacc.tab.h"
#include "parser.h"
#include "rpc_sql/rpc_sql.h"
using namespace std;

int main(){
	cout<<"frag_data test."<<endl;
	InitQuery();
	while(1) {
	    parser_init();
	    int rnt = yyparse();
	    if(rnt==-1)
	    	break;
	    cout<<"finished yyparse."<<endl;
	    //spliceCreateStmt();
	    /*
	    load_data should at the very begining of db initialization.
	     */
	  //  load_data();
	    // test();
	}
	DestoryQuery();
	return 0;
}

// int main(){
// 	string sqlstmt;
// 	char first_char;
// 	while(1){
// 		cout<<"Please enter your sql statement."<<endl;
// 		cin>>sqlstmt;
// 		first_char = sqlstmt[0];
// 		switch(first_char){
// 			case 'C':
// 			case 'c':
// 				exec_create_stmt(sqlstmt);
// 			case 'F':
// 			case 'f':
// 				int rnt = yyparse();
// 				if(rnt==-1)
// 	    			break;

// 		}
// 	}
// }