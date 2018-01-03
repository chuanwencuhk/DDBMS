#ifndef TABLEMETADATA_H
#define TABLEMETADATA_H

#include "global.h"
#include "attribution.h"

class TableMetadata
{
public:
    TableMetadata();
    void set_table_name(std::string name){table_name = name;}
    std::string get_table_name(){return table_name;}

    Attribution* get_attr_pointer(){return pAttr;}

    void set_table_attr_num(int num){table_attr_num = num;}
    int get_table_attr_num(){return table_attr_num;}

    void set_table_path(std::string path){table_path = path;}
    std::string get_table_path(){return table_path;}

private:
    Attribution Attr[MAX_ATTRIBUTION_NUM];
    Attribution* pAttr;

    std::string table_name;
    int table_attr_num;
    std::string table_path;



};

#endif // TABLEMETADATA_H
