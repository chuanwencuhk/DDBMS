#ifndef METADATAMANAGER_H
#define METADATAMANAGER_H

#include "../global.h"
#include "tableMetadataInfo.h"
#include "siteinfo.h"
#include "fragmentinfo.h"
#include "tableMetadataInfo.h"
#include "../QueryTree/query_tree.h"
#include "Dispather/dispather.h"

#include <libconfig.h++>

//extern struct schema sch;
class MetadataManager
{
public:


    void read_config_file(const std::string &filename);
    void initialize_from_config_file(const std::string& str);
    void write_to_config_file(std::string filename);//write the new data into meatadata.cfg

    void initialize_tablemetadata();
    void initialize_siteinfo();
    void initialize_database();
    void initialize_fragment();

    void add_tablename_intolist(std::string str);
    void delete_tablename_formlist(std::string str);
    void load_tablemetadata_fromcfg();

    void add_fragment_name_intolist(std::string str);
    void delete_fragment_name_fromlist(std::string str);
    void load_fragmentmetadata_fromcfg();



    //Interface for ohter Wang Chuanwen///////////////////////////////////////////////////////
    Fragment get_fragment_bystr(std::string str){return fragInfo.get_frag_bystr(str);}
    void set_fargment_info(Fragment &frg);
    void delete_fragmemt_info(std::string str);

    void set_siteinfo(SiteInfo &sti);
    SiteInfo get_siteinfo_byID(int site_ID){return siteinfo[site_ID];}
    std::string get_IP_by_siteID(int site_ID);

    void set_tablemetadata(TableMedata &Tbm);
    TableMedata get_tablemetadata(std::string str){return tableMetadataInfo.get_tablemetadata_bystr(str);}
    void delete_tablemetadata(std::string str);

    void setMetadataVer(std::string str);//set the version of DDB
    std::string get_metadata_version(){return version;}//get the version info

    void execute_SQL(std::string SQL, int version);
    //Interface for Wang Chuanwen///////////////////////////////////////////////////////

    static MetadataManager* getInstance();

    //for Wang Hongyang's schema/////////////////////
    void set_table_metadata_toquerytree();
    void set_fragment_metadata_toquerytree();
    //for Wang Hongyang's schema/////////////////////

private:
    MetadataManager();
   ~MetadataManager();
    MetadataManager(const MetadataManager&);
    MetadataManager& operator=(const MetadataManager&);
    static MetadataManager* pmtr;

    class GarbageCollection //use for garbage collection, embedded class
    {
    public:
        ~GarbageCollection()
        {
            if(MetadataManager::getInstance())
                delete MetadataManager::pmtr;
        }
    };
    static GarbageCollection GC;

    SiteInfo siteinfo[MAX_SITE_NUM];

    TableMetadataInfo tableMetadataInfo;
    FragmentInfo fragInfo;

    std::string database_name;
    std::string version;
    std::string database_path;

    libconfig::Config cfg;

    Dispatcher dpatcher;//for exec sql


};

#endif // METADATAMANAGER_H
