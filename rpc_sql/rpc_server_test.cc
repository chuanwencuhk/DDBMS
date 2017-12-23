#include <iostream>
#include "rpc_sql.h"
#include <string>
#include "rpc_server.h"

using std::cout;
using std::endl;

int main(){
	startServer();
	cout << "startServer();" << endl;
	return 0;
}