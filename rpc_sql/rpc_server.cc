#include "rpc_server.h"

void startServer(){
    rpc::server srv("0.0.0.0", rpc::constants::DEFAULT_PORT);
    cout << "rpc::server srv(\"0.0.0.0\", rpc::constants::DEFAULT_PORT);" << endl;
    srv.bind("localExecute", &localExecute);
    cout << "srv.bind(\"localExecute\", &localExecute);" << endl;
    srv.bind("localExecuteQuery", &localExecuteQuery);
    srv.bind("localExecuteUpdate", &localExecuteUpdate);
    srv.bind("localInsertFileToTable", &localInsertFileToTable);
  
    srv.suppress_exceptions(true);
    srv.run();
    cout << "srv.run();" << endl;
}