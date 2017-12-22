#include "fragmentinfo.h"

#include <stdlib.h>
using namespace std;
FragmentInfo::FragmentInfo()
{

}

void FragmentInfo:: set_fragment_info(Fragment &frg)
{
    string str = frg.frag_talbe_name;
    int i = get_availble_fragarray_pos();
    if(map_tablename_to_pos.count(str) == 0)
    {
        map_tablename_to_pos.insert({str,i});
        fragarray_bitmap[i] = false;
        this->frag_table_num++;

    }
    else
    {
        i = map_tablename_to_pos[str];
    }

    for(int j = 0; i<MAX_FRAGMENT_NUM;j++)
    {
        if(frg.condtion_slice[j].isValid == false)
            continue;

        if(frg.condtion_slice[j].con_A.isValid == true)
        {
            frag_array[i].condtion_slice[j].con_A.isValid = frg.condtion_slice[j].con_A.isValid;
            frag_array[i].condtion_slice[j].con_A.attr_condition = frg.condtion_slice[j].con_A.attr_condition;
            frag_array[i].condtion_slice[j].con_A.attr_name = frg.condtion_slice[j].con_A.attr_name;
            frag_array[i].condtion_slice[j].con_A.attr_value = frg.condtion_slice[j].con_A.attr_value;

        }

        if(frg.condtion_slice[j].con_B.isValid == true)
        {
            frag_array[i].condtion_slice[j].con_B.isValid = frg.condtion_slice[j].con_B.isValid;
            frag_array[i].condtion_slice[j].con_B.attr_condition = frg.condtion_slice[j].con_B.attr_condition;
            frag_array[i].condtion_slice[j].con_B.attr_name = frg.condtion_slice[j].con_B.attr_name;
            frag_array[i].condtion_slice[j].con_B.attr_value = frg.condtion_slice[j].con_B.attr_value;

        }

    }








}


//random alloc a pos to store fragment info.
int FragmentInfo::get_availble_fragarray_pos()
{
    int i;
    while(1)
    {
        i = rand()%100;
        if(fragarray_bitmap[i] == true)
        {
            fragarray_bitmap[i] = false;
            return i;
        }


    }



}
