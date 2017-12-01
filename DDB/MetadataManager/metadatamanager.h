#ifndef METADATAMANAGER_H
#define METADATAMANAGER_H

#include "global.h"
#include "tableMetadata.h"
#include <libconfig.h++>


class MetadataManager
{
public:

    MetadataManager();
    ~MetadataManager();

    void set_num_of_table(int num){num_of_tables = num;}
    int get_num_of_table(){return num_of_tables;}

    TableMetadata* get_tablemetadata_pointer(){return ptablemetadata;}

    void read_config_file(const std::string &filename);

    void initialize_from_config_file(const std::string& str);

    void initialize_tablemetadata();

    void setMetadataVer(std::string str);

private:

    TableMetadata tablemetadata[MAX_TABLE_NUM];
    TableMetadata* ptablemetadata;

    int num_of_tables;
    //database info
    std::string database_name;
    std::string version;
    std::string database_path;

    libconfig::Config cfg;


};

#endif // METADATAMANAGER_H
