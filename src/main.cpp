/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: wcw
 *	
 */
#include <string.h>
#include <iostream>
#include "../include/yacc.tab.h"
#include "../include/parser.h"
#include "../include/metadatamanager.h"
#include "../rpc_sql/rpc_sql.h"
using namespace std;

int main(){
	cout<<"---------------A SIMPLE TEST VERSION.---------------"<<endl;
	InitQuery();
	MetadataManager* p = MetadataManager::getInstance();
	string IP = "192.168.8.13";
	string site = "site";
    for(int i=0;i<4;i++)
    {
      SiteInfo st;
      st.set_site_ID(i);
      st.set_site_ip(IP+to_string(i+3));
      st.set_site_name(site+to_string(i));
      p->set_siteinfo(st);
    }
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
