#ifndef STATIC_LINK_LIST_H
#define STATIC_LINK_LIST_H

#include "link_list.h"

namespace DTLib {

template<typename T, int N>
class StaticLinkList : public LinkList<T> {
protected:

    typedef typename LinkList<T>::Node Node;

    // 用来调用Node中value的构造函数
    struct SNode : public Node {
        void *operator new(size_t size, void *loc)
        {
            (void*)size;
            return loc;
        }
    };

    unsigned char m_space[sizeof(SNode) *N];
    int m_used[N];

    Node *create()
    {
        SNode *ret = NULL;

        for(int i = 0; i < N; i++) {
            if(!m_used[i]) {
                ret = reinterpret_cast<SNode*>(m_space) + i;
                ret = new(ret)SNode(); // 调用构造函数, 括号中的ret指定想要在哪一个内存空间中调用构造函数
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }

    void destroy(Node *pn)
    {
        SNode *space = reinterpret_cast<SNode*>(m_space);
        SNode *psn = dynamic_cast<SNode*>(pn);

        std::cout << "StaticLinkList::destroy()" << std::endl;

        for (int i = 0; i < N; i++) {
            if (pn == (space + i)) {
                m_used[i] = 0;
                psn->~SNode();
                break;
            }
        }

    }

public:
    StaticLinkList()
    {
        for(int i = 0; i < N; i++) {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }

    ~StaticLinkList()
    {
        std::cout << "~StaticLinkList()" << std::endl;
        this->clear();
    }
};


}


#endif