/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: wcw
 *	
 */
#include <string.h>
#include <iostream>
#include "yacc.tab.h"
#include "parser.h"
#include "rpc_sql/rpc_sql.h"
using namespace std;

int main(){
	cout<<"---------------A SIMPLE TEST VERSION.---------------"<<endl;
	InitQuery();
	while(1) {
		cout<<"---------------Please Input SQL.--------------------"<<endl;
	    parser_init();
	    int rnt = yyparse();
	    if(rnt==-1)
	    	break;
	    cout<<"---------------Finished.----------------------------"<<endl;
	}
	DestoryQuery();
	return 0;
}
