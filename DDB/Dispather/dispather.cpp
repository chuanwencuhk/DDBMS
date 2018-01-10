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

string Dispatcher::get_hash_fromstr(string str)
{
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
