#include <iostream>
#include "btree.h"

using namespace std;
using namespace DTLib;

int main(int argc, char **argv)
{
    BTree<int> bt;
    BTreeNode<int> *n = NULL;

    bt.insert(1, NULL);

    n = bt.find(1);
    bt.insert(2, n);
    bt.insert(3, n);

    n = bt.find(2);
    bt.insert(4, n);
    bt.insert(5, n);

    n = bt.find(3);
    bt.insert(6, n);
    bt.insert(7, n);

    n = bt.find(4);
    bt.insert(8, n);
    bt.insert(9, n);

    n = bt.find(5);
    bt.insert(10, n);
    
    //n = bt.find(6);
    //bt.insert(11, n, LEFT);

#if 1
    // clone test
    SharedPointer< BTree<int> > btClone = bt.clone();
#endif

#if 0
    // 属性操作测试
    cout << "count : " << bt.count() << endl;
    cout << "height : " << bt.height() << endl;
    cout << "root : " << bt.degree() << endl;
#endif

#if 1
    // remove test
    SharedPointer< Tree<int> > sp = bt.remove(3);
#endif

#if 1
    // 从叶节点开始反向打印
    // int a[] = {8, 9, 10, 11, 7};
    int a[] = {8, 9, 10, 7};
    for(int i = 0; i < 5; i++) {
        //TreeNode<int> *node = bt.find(a[i]);  // insert操作测试
        //TreeNode<int> *node = sp->find(a[i]);   // remove操作测试
        TreeNode<int> *node = btClone->find(a[i]);   // clone操作测试

        while(node) {
            cout << node->value << " ";
            node = node->parent;
        }

        cout << endl;
   
    }
#endif

#if 1
    // 比较操作符测试
    cout << "compare : " << (bt != *btClone) << endl;

#endif


#if 0
    // 层次遍历测试
    cout << endl;

    for (bt.begin(); !bt.end(); bt.next()) {
        cout << bt.current() << " ";
    }

    cout << endl;
#endif

#if 0
    // 二叉树的典型遍历方式
    SharedPointer< Array<int> > sp = NULL;
    
    sp = bt.traversal(PreOrder);
    cout << "PreOrder  : ";
    for(int i = 0; i < (*sp).length(); i++) {
        cout << (*sp)[i] << " ";
    }
    cout << endl;

    sp = bt.traversal(InOrder);
    cout << "InOrder   : ";
    for(int i = 0; i < (*sp).length(); i++) {
        cout << (*sp)[i] << " ";
    }
    cout << endl;

    sp = bt.traversal(PostOrder);
    cout << "PostOrder : ";
    for(int i = 0; i < (*sp).length(); i++) {
        cout << (*sp)[i] << " ";
    }
    cout << endl;
#endif

    return 0;
}