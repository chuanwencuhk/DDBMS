#include "../include/fragmentinfo.h"

#include <stdlib.h>
using namespace std;
FragmentInfo::FragmentInfo()
{
    for(int i=0;i<100;i++)
        fragarray_bitmap[i] = true;

}

void FragmentInfo:: set_fragment_info(Fragment &frg)
{
    string str = frg.frag_talbe_name;
    int i;
    //int j =0;
    if(map_tablename_to_pos.count(str) == 0)
    {
        i = get_availble_fragarray_pos();
        map_tablename_to_pos.insert({str,i});
        //fragarray_bitmap[i] = false;
        this->frag_table_num++;

    }
    else
    {
        i = map_tablename_to_pos[str];
    }

    frag_array[i].frag_talbe_name = str;
    for(int j = 0; j<MAX_FRAGMENT_NUM;j++)
    {
        cout<<i<<endl;
        if(!frg.condtion_slice[j].isValid)
            continue;

        frag_array[i].condtion_slice[j].isValid = frg.condtion_slice[j].isValid;

        if(frg.condtion_slice[j].con_A.isValid)
        {
            frag_array[i].condtion_slice[j].con_A.isValid = frg.condtion_slice[j].con_A.isValid;
            frag_array[i].condtion_slice[j].con_A.attr_condition = frg.condtion_slice[j].con_A.attr_condition;
            frag_array[i].condtion_slice[j].con_A.attr_name = frg.condtion_slice[j].con_A.attr_name;
            frag_array[i].condtion_slice[j].con_A.attr_value = frg.condtion_slice[j].con_A.attr_value;

        }

        if(frg.condtion_slice[j].con_B.isValid)
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
        i = (rand()%(MAX_FRAGMENT_NUM-1))+1;
        cout<<"i is: "<<i<<endl;
        if(fragarray_bitmap[i] == true)
        {
            fragarray_bitmap[i] = false;
            cout<<"the get_availble_fragarray_pos is "<<i<<endl;
            return i;
        }


    }



}

int FragmentInfo::get_fragment_pos(string str)
{
    if(map_tablename_to_pos.count(str)==0)
        return 0;

    return (int)map_tablename_to_pos[str];
}

Fragment FragmentInfo::get_frag_bystr(string str)
{
    int pos = get_fragment_pos(str);
    if(pos == 0)
    {
        cout<<"frag not exist!\n"<<endl;
        return frag_array[0];
    }

    return frag_array[pos];


}
