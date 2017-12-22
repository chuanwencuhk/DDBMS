#include "rpc_server.h"

void startServer(){
    rpc::server srv("0.0.0.0", rpc::constants::DEFAULT_PORT);
    srv.bind("localExecute", &localExecute);
    srv.bind("localExecuteQuery", &localExecuteQuery);
    srv.bind("localExecuteUpdate", &localExecuteUpdate);
    srv.bind("localInsertFileToTable", &localInsertFileToTable);
  
    srv.suppress_exceptions(true);
    srv.run();
}