#include <iostream>
#include "rpc/client.h"
#include <string>


using std::cout;
using std::endl;
using std::string;

int main() {
    rpc::client client("127.0.0.1", rpc::constants::DEFAULT_PORT);

    cout << "Call getMetaData" << endl;
    auto result = client.call("getMetaData").as<string>();
    cout << result << endl;

    cout << "Call getTableData" << endl;
    auto result2 = client.call("getMetaData").as<string>();
    std::cout << result2 << std::endl;
    
    cout << "Call getBigDataDemo" << endl;
    string result3 = client.call("getBigDataDemo").as<string>();
    cout << "The size of big data is " << result3.size() << endl;

    cout << "Call getFileData" << endl;
    string result4 = client.call("getFileData", string("./greet.txt")).as<string>();
    cout << "File content:" << endl;
    cout << result4 << endl;
    return 0;
}
