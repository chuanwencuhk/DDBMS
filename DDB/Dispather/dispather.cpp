#include "dispather.h"

Dispather::Dispather()
{
    if(pmtr == NULL)
        pmtr = MetadataManager::getInstance();

}

void Dispather::set_treevector_from_querytree(struct query_tree& qtree)
{
    int root_pos = qtree.root;



}
