#ifndef GTREE_NODE_H
#define GTREE_NODE_H

#include "tree.h"
#include "link_list.h"

namespace DTLib {

template <typename T>
class GTreeNode : public TreeNode<T> {
public:
    LinkList<GTreeNode<T> *> child;


};


}

#endif