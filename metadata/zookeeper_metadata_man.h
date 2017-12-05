#pragma once

#include <string>
#include <vector>

#include "Zookeeper.h"


using std::string;
using std::vector;

namespace zookeeper {



static string getSiteIpTablePath();
static string getSiteServerTablePath();
static string getTestDataPath();



class MetaDataManager {
public:
	//int getSiteIpTable(SiteIpList& siteIpList);
	//int setSiteIpTable(SiteIpList& siteIpList);
	//int getSiteServerTable(SiteServerList& siteServerList);
	//int setSiteServerTable(SiteServerList& siteServerList);
	//string getMetaData(const string& path, bool watch = false);
	//void setMetaData(const string& path, string& value);

	string getTestData();
	void setTestData(const string& value);

	//eg hostPort 127.0.0.1:2181
	MetaDataManager(const string& hostPort) 
	: zookeeper_(new ZooKeeper(hostPort, nullptr, 5 * 1000))
	{
		//zookeeper_ = new Zookeeper(hostPort);
	}

	~MetaDataManager(){
		delete zookeeper_;
	}

private:
	ZooKeeper* zookeeper_;
};

} //namespace zookeeper









