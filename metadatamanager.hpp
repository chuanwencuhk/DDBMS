#ifndef METADATAMANAGER_H_
#define METADATAMANAGER_H_

#include <string>
#include <vector>
#include "zookeeper.hpp"


//#define SERVER_MAX_COUNT_OF_SITE 5

/*
一个site只对应一个ip;
一个site可对应多个server;
比如：

site1:127.0.0.1;site2:127.0.0.2;

site1:server1,server2;

需求：
读或者修改（全部改）


*/

using std::string;
using std::vector;




struct SiteIpList {
	vector<string> siteName;
	vector<string> ipName;
};

struct SiteServerKV {
	string siteName;
	vector<string> serverNameList;
};


struct SiteServerList {
	vector<SiteServerKV*> list;
	SiteServerList(int cnt){
		while (cnt--){
			SiteServerKV* kv = new SiteServerKV;
			list.push_back(kv);
		}
	}
	~SiteServerList(){
		for (int i=0;i<list.size();++i){
			delete list[i];
			//list[i] = NULL;
		}
		//list.clear();
	}
};



class MetaDataDirManager {
private:	
	static string appPath = "/ourddb"
	static string siteIpTablePath = "/siteIpTable";
	static string siteServerTablePath = "/siteServerTable";
public:
	static string getAppPath(){
		return appPath;
	}
	static string getSiteIpTablePath(){
		return appPath + siteIpTablePath;
	}

	static string getSiteServerTablePath(){
		return appPath + siteServerTable;
	}
};



class MetaDataManager {
public:
	int getSiteIpTable(SiteIpList& siteIpList);
	int setSiteIpTable(SiteIpList& siteIpList);
	int getSiteServerTable(SiteServerList& siteServerList);
	int setSiteServerTable(SiteServerList& siteServerList);
	string getMetaData(const string& path, bool watch = false);
	void setMetaData(const string& path, string& value);

	MetaDataDirManager(const std::string& server_hosts,
            ZooWatcher* global_watcher = nullptr,
            int timeout_ms = 5 * 1000)
	: global_watcher_(global_watcher){
		zookeeper_ = new Zookeeper(server_hosts, global_watcher, timeout_ms);
	}

	~MetaDataDirManager(){
		delete zookeeper_;
	}
private:
	Zookeeper zookeeper_;
	zhandle_t* zoo_handle_ = nullptr;
  	ZooWatcher* global_watcher_ = nullptr;

};


#endif