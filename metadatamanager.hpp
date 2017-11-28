#include <string>
#include <vector>

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

	}
	static string getSiteIpTablePath(){

	}

	static string getSiteServerTablePath(){

	}
};

class MetaDataManager {
public:
	int getSiteIpTable(SiteIpList& siteIpList);
	int setSiteIpTable(SiteIpList& siteIpList);
	int getSiteServerTable(SiteServerList& siteServerList);
	int setSiteServerTable(SiteServerList& siteServerList);
private:

};
