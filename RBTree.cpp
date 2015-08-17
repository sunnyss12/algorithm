//红黑树
#include <iostream>
template<class KEY>
class RBTree
{
    public:
        RBTree();
        ~RBTree();
        bool IsEmpty();         //判断是否为空
        bool Insert(const KEY& key);  //插入值key
        bool Delete(const KEY& key);  //删除值key
        void PreOrderTraver();
        void InOrderTraver();   //中序遍历红黑树
        void MakeEmpty();       //清空红黑树
        bool find(const KEY& key);    //查找key，如果存在返回true，否则返回false
        bool findMin(KEY& key); //如果是空树，返回false，否则返回true，并且把最小值存到key值中

    private:
        enum COLOR{RED,BLACK};
        struct RBNode
        {
            COLOR color;
            RBNode* left;
            RBNode* right;
            RBNode* parent;
            KEY key;
            RBNode()
            {
                left = NULL;
                right = NULL;
                parent = NULL;
            }
            void visit()
            {
                if(this == parent->left)
                    std::cout<<"left:"<<key<<"parent:"<<parent->key<<"color:"<<color;
                else
                    std::cout<<"right:"<<key<<"parent:"<<parent->key<<"color:"<<color;
                std::cout<<std::endl;
            }
        };

        RBNode* m_root;
        RBNode* m_null;

        bool RotateLeft(RBNode* pNode);
        bool RotateRight(RBNode* pNode);
        void InsertFixUp(RBNode* pNode);
        void DeleteFixUp(RBNode* pNode);
        void PreOrderTraver(RBNode* pNode);
        void InOrderTraver(RBNode* pNode);
        void MakeEmpty(RBNode* pNode);
        RBNode* find(RBNode* pNode,const KEY& key);
        RBNode* findMin(RBNode* pNode);
};

    template<class KEY>
RBTree<KEY>::RBTree()
{
    m_null = new RBNode;
    m_root = m_null;
    m_null->color = BLACK;
}

    template<class KEY>
RBTree<KEY>::~RBTree()
{
    MakeEmpty();
}

    template<class KEY>
void RBTree<KEY>::MakeEmpty()
{
    MakeEmpty(m_root);
    delete m_null;
}
    template<class KEY>
bool RBTree<KEY>::IsEmpty()
{
    return m_root == m_null;
}

    template<class KEY>
bool RBTree<KEY>::find(const KEY& key)
{
    RBNode* pIndex = find(m_root,key);
    if(pIndex == m_null)
        return false;
    else 
        return true;
}

    template<class KEY>
bool RBTree<KEY>::findMin(KEY& key)
{
    RBNode* pIndex = findMin(m_root);
    if(pIndex == m_null)
        return false;

    key = pIndex->key;
    return true;
}

    template<class KEY>
bool RBTree<KEY>::Insert(const KEY& key)
{
    RBNode* pPrev = m_null;
    RBNode* pIndex = m_root;
    while(pIndex != m_null)
    {
        pPrev = pIndex;
        if(key < pIndex->key)
            pIndex = pIndex->left;
        else if(key > pIndex->key)
            pIndex = pIndex->right;
        else
            return false;
    }

    RBNode* pNode = new RBNode;
    pNode->left = m_null;
    pNode->right = m_null;
    pNode->parent = pPrev;
    pNode->key = key;
    pNode->color = RED;

    if(pPrev == m_null)
        m_root = pNode;
    else if(key < pPrev->key)
        pPrev->left = pNode;
    else 
        pPrev->right = pNode;

    InsertFixUp(pNode);

}

    template<class KEY>
void RBTree<KEY>::InsertFixUp(RBNode* pNode)
{
    while(pNode->parent->color == RED)  //如果p[z]==RED,那么p[z]不是根节点，所以p[p[z]一定存在。
    {
        if(pNode->parent == pNode->parent->parent->left)
        {
            RBNode* pUncle = pNode->parent->parent->right;
            if(pUncle->color == RED)
            {
                pNode->parent->color = BLACK;
                pUncle->color = BLACK;
                pNode->parent->parent->color = RED;
                pNode = pNode->parent->parent;
            }
            else
            {
                if(pNode == pNode->parent->right)
                {
                    pNode = pNode->parent;
                    RotateLeft(pNode);
                }
                pNode->parent->color=BLACK;
                pNode->parent->parent->color=RED;
                RotateRight(pNode->parent->parent);
            }
        }
        else
        {
            RBNode* pUncle = pNode->parent->parent->left;
            if(pUncle->color == RED)
            {
                pNode->parent->color = BLACK;
                pUncle->color = BLACK;
                pNode->parent->parent->color = RED;
                pNode = pNode->parent->parent;
            }
            else
            {
                if(pNode == pNode->parent->left)
                {
                    pNode = pNode->parent;
                    RotateRight(pNode);
                }
                pNode->parent->color=BLACK;
                pNode->parent->parent->color=RED;
                RotateLeft(pNode->parent->parent);
            }
        }

    }

    m_root->color=BLACK;

}

    template<class KEY>
bool RBTree<KEY>::Delete(const KEY& key)
{
    RBNode* pDelete = find(m_root,key);
    if(pDelete == m_null)
        return false;

    RBNode* pSuccessor;
    if(pDelete->left == m_null )
        pSuccessor = pDelete->right;
    else if(pDelete->right == m_null)
        pSuccessor = pDelete->left;
    else
    {
        RBNode* pMin = findMin(pDelete->right);
        pDelete->key = pMin->key;
        pDelete = pMin;
        pSuccessor = pMin->right;
    }

    pSuccessor->parent = pDelete->parent;
    if(pDelete == m_root)
        m_root = pSuccessor;
    else
    {
        if(pDelete == pDelete->parent->left)
            pDelete->parent->left = pSuccessor;
        else
            pDelete->parent->right = pSuccessor;
    }

    if(pDelete->color == BLACK)
    {
        DeleteFixUp(pSuccessor);
    }

    delete pDelete;
    return true;

}

    template<class KEY>
void RBTree<KEY>::DeleteFixUp(RBNode* pNode)
{
    while(pNode != m_root && pNode->color == BLACK)
    {
        if(pNode == pNode->parent->left)
        {
            RBNode* pBrother = pNode->parent->right;
            if(pBrother->color == RED)
            {
                pBrother->color = BLACK;
                pNode->parent->color = RED;
                RotateLeft(pNode->parent);
                pBrother = pNode->parent->right;
            }
            if(pBrother->left->color == BLACK && pBrother->right->color == BLACK)
            {
                pBrother->color = RED;
                pNode = pNode->parent;
            }
            else
            {
                if(pBrother->right->color == BLACK)
                {
                    pBrother->left->color = BLACK;
                    pBrother->color = RED;
                    RotateRight(pBrother);
                    pBrother = pNode->parent->right;
                }

                pBrother->color = pNode->parent->color;
                pNode->parent->color = BLACK;
                pBrother->right->color = BLACK;
                RotateLeft(pNode->parent);
                pNode = m_root;
            }

        }
        else
        {
            RBNode* pBrother = pNode->parent->left;
            if(pBrother->color == RED)
            {
                pBrother->color = BLACK;
                pNode->parent->color = RED;
                RotateRight(pNode->parent);
                pBrother = pNode->parent->left;
            }
            if(pBrother->left->color == BLACK && pBrother->right->color == BLACK)
            {
                pBrother->color = RED;
                pNode = pNode->parent;
            }
            else
            {
                if(pBrother->left->color == BLACK)
                {
                    pBrother->right->color = BLACK;
                    pBrother->color = RED;
                    RotateLeft(pBrother);
                    pBrother = pNode->parent->left;
                }

                pBrother->color = pNode->parent->color;
                pNode->parent->color = BLACK;
                pBrother->left->color = BLACK;
                RotateRight(pNode->parent);
                pNode = m_root;
            }

        }

    }

    pNode->color = BLACK;
}

template<class KEY>
void RBTree<KEY>::PreOrderTraver()
{
    PreOrderTraver(m_root);
}
    template<class KEY>
void RBTree<KEY>::InOrderTraver()
{
    InOrderTraver(m_root);
}

template<class KEY>
void RBTree<KEY>::PreOrderTraver(RBNode* pNode)
{
    if(pNode != m_null)
    {
        pNode->visit();
        PreOrderTraver(pNode->left);
        PreOrderTraver(pNode->right);
    }

}

    template<class KEY>
void RBTree<KEY>::InOrderTraver(RBNode* pNode)
{
    if(pNode != m_null)
    {
        InOrderTraver(pNode->left);
        pNode->visit();
        InOrderTraver(pNode->right);
    }
}
    template<class KEY>
typename RBTree<KEY>::RBNode* RBTree<KEY>::find(RBNode* pNode,const KEY& key)
{
    RBNode* pIndex = pNode;
    while(pIndex != m_null)
    {
        if(key == pIndex->key)
            break;
        else if(key < pIndex->key)
            pIndex = pIndex->left;
        else
            pIndex = pIndex->right;
    }
    return pIndex;
}

    template<class KEY>
typename RBTree<KEY>::RBNode* RBTree<KEY>::findMin(RBNode* pNode)
{
    RBNode* pIndex = pNode;
    if(m_root == m_null)
        return m_null;

    while(pIndex->left != m_null)
        pIndex = pIndex->left;
    return pIndex;
}

    template<class KEY>
bool RBTree<KEY>::RotateLeft(RBNode* pNode)
{
    if(pNode == m_null || pNode->right == m_null)
        return false;    //canot rotate

    RBNode* pRight = pNode->right;

    pNode->right = pRight->left;
    if(pRight->left != m_null)
        pRight->left->parent = pNode;

    pRight->parent = pNode->parent;
    if(pNode->parent == m_null)
        m_root = pRight;
    else
    {
        if(pNode == pNode->parent->left)
            pNode->parent->left = pRight;
        else
            pNode->parent->right = pRight;
    }

    pRight->left = pNode;
    pNode->parent = pRight;

    return true;

}

    template<class KEY>
bool RBTree<KEY>::RotateRight(RBNode* pNode)
{
    if(pNode == m_null || pNode->left == m_null)
        return false;

    RBNode* pLeft = pNode->left;

    pNode->left = pLeft->right;
    if(pLeft->right != m_null)
        pLeft->right->parent = pNode;

    pLeft->parent = pNode->parent;
    if(pNode->parent == m_null)
        m_root = pLeft;
    else
    {
        if(pNode == pNode->parent->left)
            pNode->parent->left = pLeft;
        else
            pNode->parent->right = pLeft;
    }

    pNode->parent = pLeft;
    pLeft->right = pNode;

    return true;

}

    template<class KEY>
void RBTree<KEY>::MakeEmpty(RBNode* pNode)
{
    if(pNode != m_null)
    {
        MakeEmpty(pNode->left);
        MakeEmpty(pNode->right);
        delete pNode;
    }
}

int main(int argc,char* argv[])
{
    RBTree<int> tree;
    int array[] = {12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17};
    for(int i=0;i<sizeof(array)/sizeof(array[0]);i++)
        tree.Insert(array[i]);
    std::cout<<"preOrder:"<<std::endl;
    tree.PreOrderTraver();
    std::cout<<"delete 6 num,preOrder:"<<std::endl;
    tree.Delete(12);
    tree.Delete(1);
    tree.Delete(9);
    tree.Delete(2);
    tree.Delete(0);
    tree.Delete(11);
    tree.PreOrderTraver();
}

