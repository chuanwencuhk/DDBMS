#include "dispather.h"
#include "../QueryTree/query_tree.h"
#include <deque>

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

void Dispatcher::exec_SQL_query(string SQL)
{
    tree_vector.clear();
    tree_set.clear();

    struct query_tree qtree = get_querytree_fromSQL(SQL);
    set_treevector_from_querytree(qtree);










}
