#include "zookeeper_metadata_man.h"

namespace zookeeper {




string getAppPath(){
	return "/ourddb";
}

string getSiteIpTablePath(){
	return "/ourddb/siteIpTable";
}

string getSiteServerTablePath(){
	return "/ouddb/siteServerTable";
}

string getTestDataPath(){
	return "/ouddb/testData";
}

string MetaDataManager::getTestData(){
	return zookeeper_->Get(getTestDataPath(), 0);
}


void MetaDataManager::setTestData(const string& value){
	zookeeper_->Set(getTestDataPath(), value);
}

} //namespace zookeeper