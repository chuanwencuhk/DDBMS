#ifndef FRAGMENTINFO_H
#define FRAGMENTINFO_H
#include "global.h"

#include <map>
#include<set>

typedef struct _HCondition
{
    bool isValid = false;
    std::string attr_name = "";
    std::string attr_condition = "";
    std::string attr_value = "";

}HConditon;

typedef struct _VCondition
{
    bool isValid = false;
    int attr_num = 0;
    std::string attr_frag_strlist[MAX_VERTICAL_FRAGMENT_NUM];
    std::string attr_prikey = "";


}VCondition;

typedef struct _ConditionHV
{
    bool isValid = false;
    HConditon con_H1;
    HConditon con_H2;

    VCondition con_V1;
    //VCondition con_V2;//no need to use con_V2 at now

}ConditonHV;

typedef struct _Fragment
{
     std::string frag_talbe_name = "";
     //int slice_num =0;
     ConditonHV condtion_slice[MAX_FRAGMENT_NUM];
     //condition_slice[i] means DB[i]'s fragment

}Fragment;


class FragmentInfo
{
public:
    FragmentInfo();

    void set_frag_table_num(int num){this->frag_table_num = num;}
    int get_frag_table_num(){return this->frag_table_num;}

    void set_fragment_info(Fragment &frg);

    int get_availble_fragarray_pos();

    int get_fragment_pos(std::string str);

    void delete_fragment_inmap(std::string str);

    //Fragment get_frag_bypos(int i){return frag_array[i];}

    Fragment get_frag_bystr(std::string str);
private:
    std::map<std::string , int> map_tablename_to_pos;
    //set<std::string> mapset_tablename_has;
    //map<std::string,Fragment> map_tablename_to_frag;
    //set<std::string> set_contain_talbename;
    bool fragarray_bitmap[MAX_TABLE_NUM];
    int frag_table_num;
    Fragment frag_array[MAX_TABLE_NUM];




};

#endif // FRAGMENTINFO_H
