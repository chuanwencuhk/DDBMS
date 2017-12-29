#ifndef METADATAMANAGER_H
#define METADATAMANAGER_H

#include "../include/global.h"
#include "../include/tableMetadataInfo.h"
#include "../include/siteinfo.h"
#include "../include/fragmentinfo.h"
#include "../include/tableMetadataInfo.h"

#include <libconfig.h++>

class MetadataManager
{
public:
    static MetadataManager* GetInstance(){
        if(mtManager == NULL){
            mtManager = new MetadataManager;
        }
        return mtManager;
    }
    void read_config_file(const std::string &filename);
    void initialize_from_config_file(const std::string& str);
    void write_to_config_file(std::string filename);//write the new data into meatadata.cfg

    void initialize_tablemetadata();
    void initialize_siteinfo();
    void initialize_database();
    void initialize_fragment();

    Fragment get_fragment_bystr(std::string str){return fragInfo.get_frag_bystr(str);}
    void set_fargment_info(Fragment &frg);
    bool delete_fragment_info(std::string str);

    void set_siteinfo(SiteInfo &sti);
    SiteInfo get_siteinfo_byID(int site_ID){return siteinfo[site_ID];}

    void set_tablemetadata(TableMedata &Tbm);
    TableMedata get_tablemetadata(std::string str){return tableMetadataInfo.get_tablemetadata_bystr(str);}

    bool delete_tablemetadata(std::string str);
    void setMetadataVer(std::string str);//set the version of DDB
    std::string get_metadata_version(){return version;}//get the version info
private:
    
    MetadataManager();
    ~MetadataManager();
    MetadataManager(const MetadataManager&);
    MetadataManager& operator=(const MetadataManager&);
    static MetadataManager* mtManager;

    SiteInfo siteinfo[MAX_SITE_NUM];

    TableMetadataInfo tableMetadataInfo;
    FragmentInfo fragInfo;

    std::string database_name;
    std::string version;
    std::string database_path;

    libconfig::Config cfg;


};

#endif // METADATAMANAGER_H
