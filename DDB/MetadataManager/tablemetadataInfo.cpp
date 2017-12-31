#include "tableMetadataInfo.h"

#include <stdlib.h>
using namespace std;

//TableMetadata::TableMetadata()
//{
//    table_name = "";
//    table_attr_num = 0;
//    pAttr = Attr;
//    table_path = "";


//}

TableMetadataInfo::TableMetadataInfo()
{
    this->table_num = 0;
    for(int i =0; i<MAX_TABLE_NUM;i++)
        tableMetaArray_bitmap[i] = true;

}

void TableMetadataInfo::set_table_metadata(TableMedata &Tbm)
{
    string str = Tbm.table_name;
    int i ;
    if(map_str_topos.count(str) == 0)
    {
        i = get_available_array_pos();
        map_str_topos.insert({str,i});
        this->table_num++;

    }
    else
    {
        i = map_str_topos[str];

    }

    tableMetaArray[i].table_name = str;
    tableMetaArray[i].table_attr_num = Tbm.table_attr_num;
    tableMetaArray[i].table_path = Tbm.table_path;

    for(int j = 0; j<tableMetaArray[i].table_attr_num;j++)
    {
        tableMetaArray[i].Attr[j].attr_name = Tbm.Attr[j].attr_name;
        tableMetaArray[i].Attr[j].attr_datatype = Tbm.Attr[j].attr_datatype;
        tableMetaArray[i].Attr[j].attr_length = Tbm.Attr[j].attr_length;
        tableMetaArray[i].Attr[j].attr_rulestype = Tbm.Attr[j].attr_rulestype;

    }
}

int TableMetadataInfo::get_available_array_pos()
{
    int i;
    while(1)
    {
        i = (rand()%(MAX_TABLE_NUM)-1)+1;
        cout<<"TableMetadataInfo::get_available_array_pos i is: "<<i<<endl;
        if(tableMetaArray_bitmap[i] == true)
        {
            tableMetaArray_bitmap[i] = false;
            cout<<"the get_availble_fragarray_pos is "<<i<<endl;
            return i;
        }


    }

}

int TableMetadataInfo::get_tablemetadata_pos_bystr(string str)
{
    if(map_str_topos.count(str) == 0)
        return 0;

    return map_str_topos[str];

}

TableMedata TableMetadataInfo::get_tablemetadata_bystr(string str)
{
    int pos = get_tablemetadata_pos_bystr(str) ;
    if(pos == 0)
    {
        cout<<"tablemetadata not exist!"<<endl;
        return tableMetaArray[0];
    }

    return tableMetaArray[pos];

}
//2017-12-30 add by yfchai
void TableMetadataInfo::delete_tablemetadata_inmap(string str)
{
    if(map_str_topos.count(str)== 0)
    {
        cout<<"delete_tablemetadata_inmap: "<<"table "<<str<<"not exist!"<<endl;
        return;
    }

    int pos = map_str_topos[str];
    tableMetaArray_bitmap[pos] = true;
    if(map_str_topos.erase(str))
    {
        cout<<"delete_tablemetadata_inmap: "<<"table "<<str<<"deleted!"<<endl;
    }


}
