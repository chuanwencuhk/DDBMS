/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: gpadmin
 */
#include <malloc.h>
#include <iostream>
#include "parser.h"
#include "parser.tab.h"
using namespace std;

int main(){
	InitQuery();	
	parser_init();
	yyparse();
	//PrintQuery();
	return 0;

}
