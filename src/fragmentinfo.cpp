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
    string str = frg.frag_table_name;
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

    frag_array[i].frag_table_name = str;
    for(int j = 0; j<MAX_FRAGMENT_NUM;j++)
    {
        //cout<<i<<endl;
        //if(!frg.condition_slice[j].isValid)
            //continue;

        frag_array[i].condition_slice[j].isValid = frg.condition_slice[j].isValid;

        //if(frg.condition_slice[j].con_H1.isValid)
        {
            frag_array[i].condition_slice[j].con_H1.isValid = frg.condition_slice[j].con_H1.isValid;
            frag_array[i].condition_slice[j].con_H1.attr_condition = frg.condition_slice[j].con_H1.attr_condition;
            frag_array[i].condition_slice[j].con_H1.attr_name = frg.condition_slice[j].con_H1.attr_name;
            frag_array[i].condition_slice[j].con_H1.attr_value = frg.condition_slice[j].con_H1.attr_value;

        }

        //if(frg.condition_slice[j].con_H2.isValid)
        {
            frag_array[i].condition_slice[j].con_H2.isValid = frg.condition_slice[j].con_H2.isValid;
            frag_array[i].condition_slice[j].con_H2.attr_condition = frg.condition_slice[j].con_H2.attr_condition;
            frag_array[i].condition_slice[j].con_H2.attr_name = frg.condition_slice[j].con_H2.attr_name;
            frag_array[i].condition_slice[j].con_H2.attr_value = frg.condition_slice[j].con_H2.attr_value;

        }

        {
            frag_array[i].condition_slice[j].con_V1.isValid = frg.condition_slice[j].con_V1.isValid;
            frag_array[i].condition_slice[j].con_V1.attr_num = frg.condition_slice[j].con_V1.attr_num;
            frag_array[i].condition_slice[j].con_V1.attr_prikey = frg.condition_slice[j].con_V1.attr_prikey;
            //frag_array[i].condition_slice[j].con_V1.attr_frag_strlist
            for(int k=0;k<frg.condition_slice[j].con_V1.attr_num;k++)
                frag_array[i].condition_slice[j].con_V1.attr_frag_strlist[k] = frg.condition_slice[j].con_V1.attr_frag_strlist[k];
        }

//        {
//            frag_array[i].condition_slice[j].con_V2.isValid = frg.condition_slice[j].con_V2.isValid;
//            frag_array[i].condition_slice[j].con_V2.attr_num = frg.condition_slice[j].con_V2.attr_num;
//            frag_array[i].condition_slice[j].con_V2.attr_prikey = frg.condition_slice[j].con_V2.attr_prikey;
//            //frag_array[i].condition_slice[j].con_V2.attr_frag_strlist
//            for(int q=0;q<frg.condition_slice[j].con_V2.attr_num;q++)
//                frag_array[i].condition_slice[j].con_V2.attr_frag_strlist[q] = frg.condition_slice[j].con_V2.attr_frag_strlist[q];
//        }

    }








}


//random alloc a pos to store fragment info.
int FragmentInfo::get_availble_fragarray_pos()
{
    int i;
    while(1)
    {
        i = (rand()%(MAX_TABLE_NUM-1))+1;
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


//2017-12-30 addby yfchai
void FragmentInfo::delete_fragment_inmap(string str)
{
    if(map_tablename_to_pos.count(str)== 0)
        {
            cout<<"delete_fragment_inmap: "<<"table fragment "<<str<<"not exist!"<<endl;
            return;
        }
    int pos = map_tablename_to_pos[str];
    fragarray_bitmap[pos] = true;
        if(map_tablename_to_pos.erase(str))
        {
            cout<<"delete_fragment_inmap: "<<"table fragment "<<str<<"deleted!"<<endl;
        }

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
