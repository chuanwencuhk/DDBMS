#include "zookeeper_metadata_man.h"

namespace zookeeper {




string getAppPath(){
	return "/ourddb";
}

string getSiteIpTablePath(){
	return "/ourddb/siteIpTable";
}

string getSiteServerTablePath(){
	return "/ourddb/siteServerTable";
}

string getTestDataPath(){
	return "/ourddb/testData";
}

string MetaDataManager::getTestData(){
	//todo return rc error code
	zookeeper_->Sync(getTestDataPath());
	return zookeeper_->Get(getTestDataPath(), 0);
}


void MetaDataManager::setTestData(const string& value){
	zookeeper_->Set(getTestDataPath(), value);
}

} //namespace zookeeper
