#include "dispather.h"
#include "../QueryTree/query_tree.h"
#include "../MetadataManager/metadatamanager.h"

#include <deque>
#include <fstream>

class MetadataManager;
Dispatcher::Dispatcher()
{
//    if(pmtr == NULL)
//        pmtr = MetadataManager::getInstance();

}

void Dispatcher::set_treevector_from_querytree(struct query_tree& qtree)
{
    int root_pos = qtree.root;
    deque<int> q1,q2;

    q1.push_back(root_pos);
    this->tree_vector.push_back(root_pos);

    do{

        do{
            int i = q1.front();
            q1.pop_front();

            int childsize = qtree.node[i].child[0];
            for(int j =1; j<childsize+1;j++)
            {
                q1.push_back(qtree.node[i].child[j]);
                this->tree_vector.push_back(qtree.node[i].child[j]);
            }


        }while(!q1.empty());

        q1.swap(q2);

    }while(!q1.empty());


    cout<<"Dispather::set_treevector_from_querytree(struct query_tree& qtree)"<<endl;


}

query_tree Dispatcher::get_querytree_fromSQL(string sql)
{

    query_tree original_tree = get_original_tree(sql);
    cout << "Dispatcher::get_querytree_fromSQL(string sql): original tree build complete!"<<endl;
    get_basic_opt_tree(original_tree, 3);//使用前3种优化
    cout << "Dispatcher::get_querytree_fromSQL(string sql): basic optimize tree complete!"<<endl;
    print_tree(original_tree);
    return original_tree;

}

//extern bool RPCExecute(string host_ip, string sql_statement);
//extern string RPCExecuteQuery(string host_ip, string sql_statement);//use for exec sql
//extern int RPCExecuteUpdate(string host_ip, string sql_statement);
//extern bool RPCInsertFileToTable(string host_ip, string sql_file, string table_name);

//need to think about vertical fragment table job how to deal with.
void Dispatcher::exec_SQL_query(string SQL)
{
    tree_vector.clear();
    tree_set.clear();

    MetadataManager* pmgr = MetadataManager::getInstance();

    struct query_tree qtree = get_querytree_fromSQL(SQL);
    set_treevector_from_querytree(qtree);


    while (!tree_vector.empty() )
    {
        int pos = tree_vector.back();
        tree_vector.pop_back();
        int node_type = qtree.node[pos].type;

        switch (node_type) {

        case 0:
        {

            string f_name = qtree.node[pos].str;
            std::string::size_type n = f_name.find(":");
            int site_ID = -1;
            if(n != f_name.npos)
            {
                string s = f_name.substr(0,n);
                string frag = f_name.substr(n+1,n+1);
                site_ID = stoi(frag);
                f_name = s;
                cout<<"the table is:"<<s<<" the fragment is: "<<site_ID<<endl;

            }
                cout<<"table: "<<f_name<<" has no fragment!"<<endl;

                if(site_ID == -1) site_ID =1;
                string IP_address = pmgr->get_IP_by_siteID(site_ID-1);
                string sql_stm = "select * from "+f_name+";" ;
                cout<<"the SQL is: "<<sql_stm<<" to site: "<<site_ID<<" IP is: "<<IP_address<<endl;

                //exec RPC query and save store result in ./tmp/
                string res_str;
                //res_str = RPCExecuteQuery(IP_address, sql_stm);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                ofstream fs_out(get_hash_fromstr(f_name)+".ttb");
                fs_out<<res_str;
                fs_out.close();

                TableMedata tb = pmgr->get_tablemetadata(f_name);
                string create_tmp_table = "create table "+get_hash_fromstr(f_name)+"(";

                for(int i=0;i<tb.table_attr_num;i++)
                {
                    create_tmp_table += tb.Attr[i].attr_name + " " + get_attr_typestring(tb.Attr[i].attr_datatype) + \
                            " " +get_attr_ruletypestring(tb.Attr[i].attr_rulestype);

                    if(i<(tb.table_attr_num-1))
                        create_tmp_table+=",";


                }
                create_tmp_table+=");";
                cout<<"the SQL I made is: "<<create_tmp_table<<endl;
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //RPCExecute(LOCALHOST,create_tmp_table);
                //RPCInsertFileToTable(LOCALHOST,get_hash_fromstr(f_name)+".ttb",get_hash_fromstr(f_name));

                //qtree.node[pos].type = 5;//means the remote data has store in a tmp table with hashed name


        }

            break;

        case 1:
        {


        }

            break;

        case 2:
        {
            string j_name = qtree.node[pos].str;
            int eq_pos = j_name.find("=");
            string l_str = j_name.substr(0,eq_pos);
            string r_str = j_name.substr(eq_pos+1,j_name.length());
            //cout<<"j_name is: "<<j_name<<" l_str is: "<<l_str<<" r_str is: "<<r_str<<endl;
            string l_tb = l_str.substr(0,l_str.find("."));
            string r_tb = r_str.substr(0,r_str.find("."));
            string l_attr = l_str.substr(l_str.find(".")+1,l_str.length());
            string r_attr = r_str.substr(r_str.find(".")+1,r_str.length());

            string sql_stm = "select * from "+get_hash_fromstr(l_tb) + \
                    ","+get_hash_fromstr(r_tb)+" "+"where"+" "+get_hash_fromstr(l_tb)+"."+l_attr+\
                    "="+get_hash_fromstr(r_tb)+"."+r_attr+";";

            string res_str;
            //res_str = RPCExecuteQuery(LOCALHOST, sql_stm);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            ofstream fs_out(get_hash_fromstr(j_name)+".ttb");
            fs_out<<res_str;
            fs_out.close();







        }

            break;

        case 3:
        {


        }

            break;

        case 4:
        {

        }


            break;

        default:
            cout<<"get into the default switch option!"<<endl;
            break;
        }


    }













}

void Dispatcher::exec_SQL_query_poor_optimal(string SQL)
{
    tree_vector.clear();
    tree_set.clear();
    cplmnt_set.clear();

    MetadataManager* pmgr = MetadataManager::getInstance();

    struct query_tree qtree = get_querytree_fromSQL(SQL);
    set_treevector_from_querytree(qtree);


    while (!tree_vector.empty() )
    {
        int pos = tree_vector.back();
        tree_vector.pop_back();
        int node_type = qtree.node[pos].type;

        switch (node_type) {

        case 0:
        {

            string f_name = qtree.node[pos].str;
            std::string::size_type n = f_name.find(":");
            int site_ID = -1;
            if(n != f_name.npos)
            {
                string s = f_name.substr(0,n);
                string frag = f_name.substr(n+1,n+1);
                site_ID = stoi(frag);
                f_name = s;
                cout<<"the table is:"<<s<<" the fragment is: "<<site_ID<<endl;

            }else cout<<"table: "<<f_name<<" has no fragment!"<<endl;


            Fragment frg = pmgr->get_fragment_bystr(f_name);
            bool V_frag = false;
            for(int i=0;i<MAX_FRAGMENT_NUM;i++)
                V_frag = frg.condtion_slice[i].con_V1.isValid;
            if(V_frag)//if V_frag==true means the table has vertical frangment
            {
                if(site_ID == -1) site_ID =1;
                string IP_address = pmgr->get_IP_by_siteID(site_ID-1);
                string sql_stm = "select * from "+f_name+";" ;
                cout<<"the SQL is: "<<sql_stm<<" to site: "<<site_ID<<" IP is: "<<IP_address<<endl;

                //exec RPC query and save store result in ./tmp/
                string res_str;
                //res_str = RPCExecuteQuery(IP_address, sql_stm);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                ofstream fs_out(get_hash_fromstr(f_name)+".ttb");
                fs_out<<res_str;
                fs_out.close();

                TableMedata tb = pmgr->get_tablemetadata(f_name);
                string create_tmp_table = "create table "+get_hash_fromstr(f_name)+"(";

                tree_set.clear();
                for(int j=0;j<frg.condtion_slice[site_ID-1].con_V1.attr_num;j++)
                    tree_set.insert(frg.condtion_slice[site_ID-1].con_V1.attr_frag_strlist[j]);
                int comma_num = tree_set.size();
                for(int i=0;i<tb.table_attr_num;i++)
                {
                    if(tree_set.count(tb.Attr[i].attr_name)==0)
                    {
                        continue;
                    }
                    else
                    {
                        create_tmp_table += tb.Attr[i].attr_name + " " + get_attr_typestring(tb.Attr[i].attr_datatype) + \
                            " " +get_attr_ruletypestring(tb.Attr[i].attr_rulestype);
                    }

                    if(comma_num-1)
                    {
                        create_tmp_table+=",";
                        comma_num--;
                    }

                }
                create_tmp_table+=");";
                cout<<"the SQL I made is: "<<create_tmp_table<<endl;
                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //RPCExecute(LOCALHOST,create_tmp_table);
                //RPCInsertFileToTable(LOCALHOST,get_hash_fromstr(f_name)+".ttb",get_hash_fromstr(f_name));

                //qtree.node[pos].type = 5;//means the remote data has store in a tmp table with hashed name

                SQL = replace_SQL_tablename_byhash(SQL,f_name,get_hash_fromstr(f_name));
                cout<<SQL<<endl;
                cout<<endl;

                bool hasselectall = false;
                bool hasdifferent_frag_attr = false;
                //int complement_frag_num;
                int complemnt_siteID;
                for(int k=0;k<MAX_FRAGMENT_NUM;k++)
                {
                    if(hasdifferent_frag_attr) break;
                    if(k==(site_ID-1)) continue;
                    if(frg.condtion_slice[site_ID-1].con_H1.attr_condition == frg.condtion_slice[k].con_H1.attr_condition)
                    {
                        complemnt_siteID = k;
                        for(int q=1;q<frg.condtion_slice[k].con_V1.attr_num;q++)
                        {
                            int frg_attr_pos = SQL.find(frg.condtion_slice[k].con_V1.attr_frag_strlist[q]);
                            if(frg_attr_pos != SQL.npos)
                            {
                                hasdifferent_frag_attr = true;
                                break;
                            }

                        }
                    }
                }

                if(SQL.find("*") != SQL.npos) hasselectall = true;
//to create complement table with vertical fragment
                if(hasdifferent_frag_attr || hasselectall)
                {
                    string IP_address = pmgr->get_IP_by_siteID(complemnt_siteID);
                    string sql_stm = "select * from "+f_name+";" ;
                    cout<<"the SQL is: "<<sql_stm<<" to site: "<<site_ID<<" IP is: "<<IP_address<<endl;

                    //exec RPC query and save store result in ./tmp/
                    string res_str;
                    //res_str = RPCExecuteQuery(IP_address, sql_stm);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    ofstream fs_out(get_hash_fromstr(f_name+"_L")+".ttb");
                    fs_out<<res_str;
                    fs_out.close();

                    TableMedata tb = pmgr->get_tablemetadata(f_name);
                    string create_tmp_table = "create table "+get_hash_fromstr(f_name+"_L")+"(";

                    //cplmnt_set.insert(get_hash_fromstr(f_name)+"_L");
                    cplmnt_set.insert(f_name);

                    tree_set.clear();
                    for(int j=0;j<frg.condtion_slice[complemnt_siteID].con_V1.attr_num;j++)
                        tree_set.insert(frg.condtion_slice[complemnt_siteID].con_V1.attr_frag_strlist[j]);
                    int comma_num = tree_set.size();
                    for(int i=0;i<tb.table_attr_num;i++)
                    {
                        if(tree_set.count(tb.Attr[i].attr_name)==0)
                        {
                            continue;
                        }
                        else
                        {
                            create_tmp_table += tb.Attr[i].attr_name + " " + get_attr_typestring(tb.Attr[i].attr_datatype) + \
                                " " +get_attr_ruletypestring(tb.Attr[i].attr_rulestype);
                        }

                        if(comma_num-1)
                        {
                            create_tmp_table+=",";
                            comma_num--;
                        }

                    }
                    create_tmp_table+=");";
                    cout<<"the SQL I made is: "<<create_tmp_table<<endl;
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    //RPCExecute(LOCALHOST,create_tmp_table);
                    //RPCInsertFileToTable(LOCALHOST,get_hash_fromstr(f_name+"_L")+".ttb",get_hash_fromstr(f_name+"_L"));





                }

            }
            else//no vertical fragment condition
            {
                if(site_ID == -1) site_ID =1;
                string IP_address = pmgr->get_IP_by_siteID(site_ID-1);
                string sql_stm = "select * from "+f_name+";" ;
                cout<<"the SQL is: "<<sql_stm<<" to site: "<<site_ID<<" IP is: "<<IP_address<<endl;

                //exec RPC query and save store result in ./tmp/
                string res_str;
                //res_str = RPCExecuteQuery(IP_address, sql_stm);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                ofstream fs_out(get_hash_fromstr(f_name)+".ttb");
                fs_out<<res_str;
                fs_out.close();

                TableMedata tb = pmgr->get_tablemetadata(f_name);
                string create_tmp_table = "create table "+get_hash_fromstr(f_name)+"(";

                for(int i=0;i<tb.table_attr_num;i++)
                {
                    create_tmp_table += tb.Attr[i].attr_name + " " + get_attr_typestring(tb.Attr[i].attr_datatype) + \
                            " " +get_attr_ruletypestring(tb.Attr[i].attr_rulestype);

                    if(i<(tb.table_attr_num-1))
                        create_tmp_table+=",";


                }
                create_tmp_table+=");";
                cout<<"the SQL I made is: "<<create_tmp_table<<endl;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //RPCExecute(LOCALHOST,create_tmp_table);
                //RPCInsertFileToTable(LOCALHOST,get_hash_fromstr(f_name)+".ttb",get_hash_fromstr(f_name));

                //qtree.node[pos].type = 5;//means the remote data has store in a tmp table with hashed name

                SQL = replace_SQL_tablename_byhash(SQL,f_name,get_hash_fromstr(f_name));
                cout<<SQL<<endl;
                cout<<endl;
            }

                break;

        }



        case 1:
        {
            break;


        }



        case 2:
        {
            break;


        }
        case 3:
        {
            break;


        }
        case 4:

        {
            break;


        }

        default:
        {
            cout<<"get into the default switch option!"<<endl;
            break;
        }
       }


    }

    if(!cplmnt_set.empty())
    {
        MetadataManager* pmgr = MetadataManager::getInstance();
        auto cpl_set_it = cplmnt_set.cbegin();

        while(cpl_set_it!= cplmnt_set.cend())
        {
            string cpl_str = *cpl_set_it;
            TableMedata tb = pmgr->get_tablemetadata(cpl_str);
            string p_key = tb.Attr[0].attr_name;

            string new_sql_A = SQL.substr(0,SQL.find("from")+4);
            string new_sql_B ="";
            string new_sql_C ="";

            string::size_type n = SQL.find("where");
            if(n != SQL.npos)
            {
            new_sql_A = new_sql_A + " "+get_hash_fromstr(cpl_str+"_L")+",";
            new_sql_B = SQL.substr(SQL.find("from")+5,SQL.find("where")+6-(SQL.find("from")+5));
            new_sql_B = new_sql_B  + get_hash_fromstr(cpl_str)+"."+p_key+"=" + \
                    get_hash_fromstr(cpl_str+"_L")+"."+p_key + " " +"and"+" ";
            new_sql_C = SQL.substr(SQL.find("where")+6,SQL.find(SQL.length()));
            SQL = new_sql_A + new_sql_B + new_sql_C;
            }
            else
            {
            new_sql_A = new_sql_A + " "+get_hash_fromstr(cpl_str+"_L")+",";
            new_sql_B = SQL.substr(SQL.find("from")+5,SQL.length());
            new_sql_C =new_sql_C + " " + "where" + " " + get_hash_fromstr(cpl_str)+"."+p_key+"="+get_hash_fromstr(cpl_str+"_L")+"."+p_key;
            SQL = new_sql_A + new_sql_B + new_sql_C;


            }
            cpl_set_it++;

        }

    }
    string final_res;
    //final_res = RPCExecuteQuery(LOCALHOST, SQL);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    cout<<"The final SQL query is:"<<SQL<<endl;
    cout<<final_res<<endl;



}

string Dispatcher::get_hash_fromstr(string str)
{
    //return str+"_tmp";
    unsigned long hash_value = (unsigned long)hash_function(str);
    string s = to_string(hash_value);
    cout<<"the hash_value is: "<<s<<endl;
    return s;


}

string Dispatcher::get_attr_ruletypestring(int rule_type)
{
    switch (rule_type) {
    case 0:
        return string("primary key");
        break;

    default:
        return string("not null");
        break;
    }

}

string Dispatcher::get_attr_typestring(int type)
{
    // I=1,C,V,F,D
    switch (type) {
    case 1:
        return string("int");
        break;
    case 2:
        return string("char(20)");
        break;
    case 3:
        return string("varchar(20)");
        break;
    case 4:
        return string("float");
        break;
    case 5:
        return string("date");
    default:
        return string("");
        break;
    }
}

string&  Dispatcher::replace_SQL_tablename_byhash(string&   str,const   string&   old_value,const   string&   new_value)
{
    while(1)
    {
        string::size_type pos(0);
        if((pos=str.find(old_value))!=string::npos)
            str.replace(pos,old_value.length(),new_value);
        else break;
    }
    return str;
}
