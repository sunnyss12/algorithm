//二叉查找树
#include<iostream>
#include<stdexcept>
#include<cstdlib>
#include<stack>
template <typename Comparable>
class BinarySearchTree
{
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree& rhs);
        ~BinarySearchTree();

        const Comparable& findMin()const;          //查找最小值,如果树空抛runtime_error异常
        const Comparable& findMax()const;          //查找最大值,如果树空抛runtime_error异常
        bool contains(const Comparable & x)const;  //判断二叉查找树是否包含值x
        bool isEmpty()const;                       //判断二叉查找树是否为空
        void preOrderTraver()const;                //先序遍历
        void inOrderTraver()const;                 //中序遍历
        void postOrderTraver()const;               //后序遍历
        void preOrderTraverStack()const;           //使用栈不使用递归实现先序遍历
        void inOrderTraverStack()const;            //使用栈不使用递归实现中序遍历
        void postOrderTraverStack()const;          //使用栈不使用递归实现后序遍历

        void makeEmpty();                          //清空二叉查找树
        void insert(const Comparable& x);          //插入值x
        void remove(const Comparable& x);          //删除值x

        const BinarySearchTree& operator=(const BinarySearchTree& ths);  //重载赋值操作符


    private:
        struct BinaryNode
        {
            Comparable element;
            BinaryNode* left;
            BinaryNode* right;
            BinaryNode():left(NULL),right(NULL)
            {
            }

            BinaryNode(const Comparable& theElement,BinaryNode* lt,BinaryNode* rt):element(theElement),left(lt),right(rt)
            { 
            }
            void visit()
            {
                std::cout<<element<<std::endl;
            }
        };
  
        BinaryNode* root;
        void insert(const Comparable& x,BinaryNode*& t);
        void remove(const Comparable& x,BinaryNode*& t);
        Comparable removeMin(BinaryNode*& t);
        BinaryNode* findMin(BinaryNode* t)const;
        BinaryNode* findMax(BinaryNode* t)const;
        bool contains(const Comparable& x,BinaryNode* t)const;
        void makeEmpty(BinaryNode*& t);
        void preOrderTraver(BinaryNode* t)const;
        void inOrderTraver(BinaryNode* t)const;
        void postOrderTraver(BinaryNode* t)const;
        void preOrderTraverStack(BinaryNode* t)const; 
        void inOrderTraverStack(BinaryNode* t)const;
        void postOrderTraverStack(BinaryNode* t)const;
        BinaryNode* clone(BinaryNode* t);
    public:
        typedef BinaryNode _BinaryNode;
};


    template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree()
{
    root=NULL;
}
    template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree& rhs)
{
    root = clone(rhs.root);
}

    template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
    makeEmpty();
}

template<typename Comparable>
const Comparable& BinarySearchTree<Comparable>::findMin()const
{
    BinaryNode* pNode = findMin(root);
    if(pNode == NULL)
        throw std::runtime_error("null point");
    return pNode->element;
}

template<typename Comparable>
const Comparable& BinarySearchTree<Comparable>::findMax()const
{
    BinaryNode* pNode = findMax(root);
    if(pNode == NULL)
        throw std::runtime_error("null point");
    return pNode->element; 
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& x)const
{
    return contains(x,root);
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty()const
{
    return root==NULL;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::preOrderTraver()const
{
    preOrderTraver(root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::inOrderTraver()const
{
    inOrderTraver(root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::postOrderTraver()const
{
    postOrderTraver(root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::preOrderTraverStack()const
{
    preOrderTraverStack(root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::inOrderTraverStack()const
{
    inOrderTraverStack(root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::postOrderTraverStack()const
{
    postOrderTraverStack(root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}

    template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x)
{
    insert(x,root);
}

    template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x)
{
    remove(x,root);
}

    template<typename Comparable>
const BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree& ths)
{
    if(this == &ths)
        return *this;
    makeEmpty();
    root = clone(ths.root);
    return *this;
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::findMin(BinaryNode* t)const
{
    if(t == NULL)
        return NULL;
    else if(t->left == NULL)
        return t;
    else return findMin(t->left);

}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::findMax(BinaryNode* t)const
{
    if(t == NULL)
        return NULL;
    else
    {
        BinaryNode* pNode = t;
        while(pNode->right != NULL)
        {
            pNode = pNode->right;
        }
        return pNode;
    }
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& x,BinaryNode* t)const
{
    if(t == NULL)
        return false;
    else if(x == t->element)
        return true;
    else if(x < t->element)
        return contains(x,t->left);
    else 
        return contains(x,t->right);
}

    template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x,BinaryNode*& t)
{
    if(t == NULL)
        t = new BinaryNode(x,NULL,NULL);
    else if(x == t->element)
        return;
    else if(x < t->element)
        insert(x,t->left);
    else
        insert(x,t->right);
}

    template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x,BinaryNode*& t)
{
    if(t == NULL)
        return;
    else if(x < t->element)
        remove(x,t->left);
    else if(x > t->element)
        remove(x,t->right);
    else
    {
        if(t->left == NULL || t->right==NULL)
        {
            BinaryNode* pNode = t;
            t = t->left == NULL ? t->right:t->left;
            delete pNode;
        }
        else
        {
            Comparable val = removeMin(t->right);
            t->element = val;
        }
    }
}

    template<typename Comparable>
Comparable BinarySearchTree<Comparable>::removeMin(BinaryNode*& t)
{
    if(t == NULL)
        return 0;
    else if(t->left == NULL)
    {
        Comparable val = t->element;
        delete t;
        t = NULL;
        return val;
    }
    else 
    {
        return removeMin(t->left);
    }

}

    template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode*& t)
{
    if(t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t=NULL;
    }
}

template<typename Comparable>
void BinarySearchTree<Comparable>::preOrderTraver(BinaryNode* t)const
{
    if(t != NULL)
    {
        t->visit();
        preOrderTraver(t->left);
        preOrderTraver(t->right);
    }
}//T(n)=O(1)+T(a)+T(n-a-1)=O(n)

template<typename Comparable>
void BinarySearchTree<Comparable>::inOrderTraver(BinaryNode* t)const
{
    if(t != NULL)
    {
        inOrderTraver(t->left);
        t->visit();
        inOrderTraver(t->right);
    }
}

template<typename Comparable>
void BinarySearchTree<Comparable>::postOrderTraver(BinaryNode* t)const
{
    if(t != NULL)
    {
        postOrderTraver(t->left);
        postOrderTraver(t->right);
        t->visit();
    }
}

template<typename Comparable>
void BinarySearchTree<Comparable>::preOrderTraverStack(BinaryNode* t)const
{
    std::stack<BinaryNode*> s;    //辅助栈
    s.push(t);
    BinaryNode* p = NULL;
    while(!s.empty())        //不断遍历左节点，直到空（空为遍历出口）
    {
        while( (p = s.top()) != NULL)              
        {
            p->visit();           //访问当前节点
            s.push(p->left);     //右孩子（右子树）入栈（将来逆序出栈）
        }
        s.pop();                 //空节点不需要做任何事情 
        if(!s.empty())       //由于s进行了pop操作，而如果之前仅有一个节点，这个节点一个是NULL节点，那么stack就会空。因为该节点不是NULL，那么不断遍历左节点时，一定会添加节点,节点个数一定大于1
        {
            p = s.top();  //这三条语句可以这样考虑：因为p已经执行了visit，它的左节点为空已经pop掉了，而且左节点也通过回溯知道了右节点，那么p p的左节点 p的右节点组成的三个节点的价值和p的右节点一个节点的价值一样了，可以把p pop掉，这样右节点就相当了占用了它的父节点p的位置，只有尾递归可以这样做。
            s.pop();
            s.push(p->right);   
        }
    }                              
}
template<typename Comparable>
void BinarySearchTree<Comparable>::inOrderTraverStack(BinaryNode* t)const
{
    std::stack<BinaryNode*> s;
    s.push(t);
    BinaryNode* p = NULL;
    while(!s.empty())
    {
        while( (p = s.top()) != NULL)
        {
            s.push(p->left);
        }
        s.pop();
        if(!s.empty())
        {
            p = s.top();
            p->visit();
            s.pop();
            s.push(p->right);
        }
    }
}

enum Tags{ROOT,LEFT,RIGHT};
template<typename Comparable>
class ELEM
{
public:
    typename BinarySearchTree<Comparable>::_BinaryNode* point;
    Tags tag;
};

template<typename Comparable>
void BinarySearchTree<Comparable>::postOrderTraverStack(BinaryNode* t)const
{

    std::stack<ELEM<Comparable> > s;
    ELEM<Comparable> element,tmp;
    tmp.point = t;
    tmp.tag = ROOT;
    s.push(tmp);
    do
    {
        while( (element = s.top()).point != NULL)   //深搜直到找到出口条件
        {
            tmp.point = element.point->left;
            tmp.tag = LEFT;
            s.push(tmp);
        }

        while( (element = s.top()).tag == RIGHT)   //如果是父节点最后一个节点则上溯
        {
            s.pop();
            element = s.top();
            (element.point)->visit();
        }

        if( (element = s.top()).tag == LEFT)    //如果是父节点其他节点则pop自己将下一个兄弟节点放进来。上溯的过程可能引起tag==LEFT的节点
        {
            s.pop();
            element = s.top();
            tmp.point = element.point->right;
            tmp.tag = RIGHT;
            s.push(tmp);
        }
    }while( (element = s.top()).tag != ROOT); //上溯的过程可能到达根节点。会是最右的那个节点导致上溯到根节点
    s.pop();

}
    template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::clone(BinaryNode* t)
{
    if(t == NULL)
        return NULL;
    BinaryNode* pNode = new BinaryNode;
    pNode->element = t->element;
    pNode->left = clone(t->left);
    pNode->right = clone(t->right);
    return pNode;
}

int main(int argc,char* argv[])
{
    int array[10]={83,86,77,15,93,35,86,92,49,21};
    BinarySearchTree<int> tree;
    for(int i=0;i<10;i++)
    {
        int val = array[i];
        tree.insert(val);
    }

    std::cout<<"inOrderTraver:"<<std::endl;
    tree.inOrderTraver();
    std::cout<<"preOrderTraver:"<<std::endl;
    tree.preOrderTraver();
    std::cout<<"postOrderTraver:"<<std::endl;
    tree.postOrderTraver();
    std::cout<<"inOrderTraverStack:"<<std::endl;
    tree.inOrderTraverStack();
    std::cout<<"preOrderTraverStack:"<<std::endl;
    tree.preOrderTraverStack();
    std::cout<<"postTraverStack:"<<std::endl;
    tree.postOrderTraverStack();

    std::cout<<"Min:"<<tree.findMin()<<std::endl;
    std::cout<<"Max:"<<tree.findMax()<<std::endl;

    if(tree.contains(35))
        std::cout<<"15 exist"<<std::endl;
    else
        std::cout<<"15 not exist"<<std::endl;
    if(tree.contains(34))
        std::cout<<"34 exist"<<std::endl;
    else
        std::cout<<"34 not exist"<<std::endl;
    
     std::cout<<"operator=,inOrderTraver:"<<std::endl;
     BinarySearchTree<int> other;
     other=tree;
     other.inOrderTraver();

     std::cout<<"copy construct,inOrderTraver:"<<std::endl;
     BinarySearchTree<int> another(other);
     another.inOrderTraver();

     std::cout<<"remove 35,inOrderTraver:"<<std::endl;
     tree.remove(35);
     tree.inOrderTraver();

     std::cout<<"makeEmpty,inOrderTraver:"<<std::endl;
     tree.makeEmpty();
     tree.inOrderTraver();

}
