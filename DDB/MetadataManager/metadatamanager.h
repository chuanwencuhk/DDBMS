#ifndef METADATAMANAGER_H
#define METADATAMANAGER_H

#include "../global.h"
#include "tableMetadataInfo.h"
#include "siteinfo.h"
#include "fragmentinfo.h"
#include "tableMetadataInfo.h"

#include <libconfig.h++>


class MetadataManager
{
public:

    MetadataManager();
    ~MetadataManager();

    //void set_num_of_table(int num){num_of_tables = num;}
    //int get_num_of_table(){return num_of_tables;}

    void read_config_file(const std::string &filename);
    void initialize_from_config_file(const std::string& str);
    void write_to_config_file(std::string filename);//write the new data into meatadata.cfg

    void initialize_tablemetadata();
    void initialize_siteinfo();
    void initialize_database();
    void initialize_fragment();

    //Fragment* get_fragment_info(std::string table_name);//To-do
    //TableMetadata* get_tablemetadata_pointer(){return ptablemetadata;}
    //SiteInfo* get_siteinfo(){return siteinfo;}//get the siteinfo pointer

    //Interface for ohter user///////////////////////////////////////////////////////
    Fragment get_fragment_bystr(std::string str){return fragInfo.get_frag_bystr(str);}
    void set_fargment_info(Fragment &frg);

    void set_siteinfo(SiteInfo &sti);
    SiteInfo get_siteinfo_byID(int site_ID){return siteinfo[site_ID];}

    void set_tablemetadata(TableMedata &Tbm);
    TableMedata get_tablemetadata(std::string str){return tableMetadataInfo.get_tablemetadata_bystr(str);}

    void setMetadataVer(std::string str);//set the version of DDB
    std::string get_metadata_version(){return version;}//get the version info
    //Interface for ohter user///////////////////////////////////////////////////////
private:

    SiteInfo siteinfo[MAX_SITE_NUM];

    //TableMetadata tablemetadata[MAX_TABLE_NUM];
    //TableMetadata* ptablemetadata;
    TableMetadataInfo tableMetadataInfo;
    FragmentInfo fragInfo;

    //int num_of_tables;
    //database info
    std::string database_name;
    std::string version;
    std::string database_path;

    libconfig::Config cfg;


};

#endif // METADATAMANAGER_H
