#include <iostream>
#include "rpc/server.h"
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

string getTableData(){
    return "table data is ...";
}

string getMetaData(){
    return "meta data is ...";
}

string getBigDataDemo(){
    string res(1<<28, '1');
    return res;
}

string getFileData(string name){
    //cout << "name is " << name << endl;
    ifstream ifile(name, std::ios::in);
    char tmp[100];
    string ret;
    while (ifile.getline(tmp, 100)){
        ret.append(tmp);
        ret.append("\n");
    }
    //cout << "ret is " << ret << endl;
    return ret;
}



int main() {
    // Create a server that listens on port 8080, or whatever the user selected
    rpc::server srv("0.0.0.0", rpc::constants::DEFAULT_PORT);

    // Binding the name "foo" to free function foo.
    // note: the signature is automatically captured
    srv.bind("getTableData", &getTableData);

    // Binding a lambda function to the name "add".
    srv.bind("getMetaData", &getMetaData);

    srv.bind("getBigDataDemo", &getBigDataDemo);

    srv.bind("getFileData", &getFileData);
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
