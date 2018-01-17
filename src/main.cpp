/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: wcw
 *	
 */
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#include "../include/yacc.tab.h"
#include "../include/parser.h"
#include "../include/metadatamanager.h"
#include "../rpc_sql/rpc_sql.h"
using namespace std;
vector<string> ip_vec_m = {"10.48.139.126","10.48.224.134","10.77.30.189","10.77.30.189"};

int main(){
	cout<<"---------------A SIMPLE TEST VERSION.---------------"<<endl;
	InitQuery();
	MetadataManager* p = MetadataManager::getInstance();
	
	string site = "site";
    for(int i=0;i<4;i++)
    {
      SiteInfo st;
      st.set_site_ID(i);
      st.set_site_ip(ip_vec_m[i]);
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

