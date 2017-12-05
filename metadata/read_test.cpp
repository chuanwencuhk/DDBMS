#include "zookeeper_metadata_man.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using zookeeper::MetaDataManager;


int main(){
	string hostPort("127.0.0.1:3182");
	MetaDataManager mdm(hostPort);
	cout << "Connect to " << hostPort << endl;
	string testData;
	mdm.getTestData();
	cout << "The value of testData is " << testData << endl; 
	return 0;
}