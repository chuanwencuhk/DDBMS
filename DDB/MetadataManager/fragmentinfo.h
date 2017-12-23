#ifndef FRAGMENTINFO_H
#define FRAGMENTINFO_H
#include "global.h"

#include <map>
#include<set>

typedef struct _Condition
{
    std::string attr_name = "";
    std::string attr_condition = "";
    std::string attr_value = "";
    bool isValid = false;
}Conditon;

typedef struct _ConditionAB
{
    Conditon con_A;
    Conditon con_B;
    bool isValid = false;
//A and B ,2 condition can produce 4 slice
}ConditonAB;

typedef struct _Fragment
{
     std::string frag_talbe_name = "";
     //int slice_num =0;
     ConditonAB condtion_slice[MAX_FRAGMENT_NUM];
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

    int get_fragment_pos(std::string str){return (int)map_tablename_to_pos[str];}

    Fragment get_frag_bypos(int i){return frag_array[i];}
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
