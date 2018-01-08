#include "dispather.h"
#include "../QueryTree/query_tree.h"
#include <deque>

Dispather::Dispather()
{
//    if(pmtr == NULL)
//        pmtr = MetadataManager::getInstance();

}

void Dispather::set_treevector_from_querytree(struct query_tree& qtree)
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
