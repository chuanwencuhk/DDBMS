#include "zookeeper_metadata_man.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using zookeeper::MetaDataManager;

int main(){
	string hostPort("127.0.0.1:3181");
	MetaDataManager mdm(hostPort);
	cout << "Connect to " << hostPort << endl;
	string testData("Distribute system lesson");
	mdm.setTestData(testData);
	cout << "Set testData as " << testData << endl; 
	return 0;
}