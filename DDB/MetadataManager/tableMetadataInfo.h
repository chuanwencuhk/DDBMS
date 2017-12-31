#ifndef TABLEMETADATA_H
#define TABLEMETADATA_H

#include "../global.h"
#include <map>

//#include "attribution.h" //not use it anymore


typedef struct _Attribution
{
      std::string attr_name ="";
      //enum TYPE attr_datatype = I;
      int attr_datatype = 1;
      int attr_length = 0;
      //RulesType attr_rulestype = NOT_NULL;
      int attr_rulestype = 1;

}Attribution;

//change TableMetadata form class to struct
typedef struct _TableMetata
{
    Attribution Attr[MAX_ATTRIBUTION_NUM];
    //Attribution* pAttr;

    std::string table_name = "";
    int table_attr_num = 0;
    std::string table_path = "";

}TableMedata;


class TableMetadataInfo
{
public:
    TableMetadataInfo();

    void set_table_num(int num){table_num = num;}
    int get_table_num(){return table_num;}

    void set_table_metadata(TableMedata& Tbm);

    int get_available_array_pos();
    int get_tablemetadata_pos_bystr(std::string str);

    TableMedata get_tablemetadata_bystr(std::string str);
    void delete_tablemetadata_inmap(std::string str);

    //TableMedata get_tablemetadata_bypos(int i){return tableMetaArray[i];}


private:

    TableMedata tableMetaArray[MAX_TABLE_NUM];
    std::map<std::string, int> map_str_topos;
    bool tableMetaArray_bitmap[MAX_TABLE_NUM];
    int table_num;
    std::string DB_name;


};
//class TableMetadata
//{
//public:
//    TableMetadata();
//    void set_table_name(std::string name){table_name = name;}
//    std::string get_table_name(){return table_name;}

//    Attribution* get_attr_pointer(){return pAttr;}

//    void set_table_attr_num(int num){table_attr_num = num;}
//    int get_table_attr_num(){return table_attr_num;}

//    void set_table_path(std::string path){table_path = path;}
//    std::string get_table_path(){return table_path;}

//private:
//    Attribution Attr[MAX_ATTRIBUTION_NUM];
//    Attribution* pAttr;

//    std::string table_name;
//    int table_attr_num;
//    std::string table_path;



//};

#endif // TABLEMETADATA_H
