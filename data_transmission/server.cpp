#include <iostream>
#include "rpc/server.h"
#include <string>

using std::string;


string getTableData(){
    return "table data is ...";
}

string getMetaData(){
    return "meta data is ...";
}


int main() {
    // Create a server that listens on port 8080, or whatever the user selected
    rpc::server srv("0.0.0.0", rpc::constants::DEFAULT_PORT);

    // Binding the name "foo" to free function foo.
    // note: the signature is automatically captured
    srv.bind("getTableData", &getTableData);

    // Binding a lambda function to the name "add".
    srv.bind("getMetaData", &getMetaData);

    // Throwing an exception will cause the server to write
    // an error response. This call will make it also
    // suppress the exception (note that this is not default
    // because this behavior might hide errors in the
    // code).
    srv.suppress_exceptions(true);

    // Run the server loop.
    srv.run();

    return 0;
}
