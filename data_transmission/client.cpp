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
    result = client.call("getMetaData").as<string>();
    std::cout << result << std::endl;

    return 0;
}
