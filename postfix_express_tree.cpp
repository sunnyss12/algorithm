//根据逆波兰表达式（后缀表达式）构造表达式树
#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
typedef struct TreeNode
{
    int express;
    TreeNode* left;
    TreeNode* right;
    void visit()
    {
        if(left == NULL && right == NULL)
            std::cout<<express;
        else
            std::cout<<(char)express;
    }
}TreeNode;
class peTree  //postfix express tree
{
    public:
        TreeNode* createTree(const char* str); //输入后缀表达式字符串，将其构造为一棵二叉树。注意：操作数是一位整数，只接受+-*/四种操作符
        int cal(TreeNode* root);              //二叉树构造完后，计算表达式树的值
        void preOrderTraver(TreeNode* root);  //前序遍历二叉树
        void inOrderTraver(TreeNode* root);   //中序遍历二叉树
        void postOrderTraver(TreeNode* root); //后序遍历二叉树
    private:
        std::stack<TreeNode*> expressStack; 
};
TreeNode* peTree::createTree(const char* str)
{
    for(int i=0;str[i] != '\0';i++)
    {
        TreeNode* pNode = (TreeNode*)calloc(1,sizeof(TreeNode));
        if(str[i] <= '9' && str[i] >= '0')
        {
            pNode->express = str[i] - '0';
            pNode->left = NULL;
            pNode->right = NULL;
            expressStack.push(pNode);
        }
        else
        {
            pNode->express = str[i];
            pNode->right = expressStack.top();
            expressStack.pop();
            pNode->left = expressStack.top();
            expressStack.pop();
            expressStack.push(pNode);
        }
    }
    return expressStack.top();
}
int peTree::cal(TreeNode* root)
{
    int ret ;
    if(root->left == NULL && root->right == NULL)
        ret=root->express;
    else if(root->express == '+')
    {
        ret = cal(root->left) + cal(root->right);
    } 
    else if(root->express == '-')
    {
        ret = cal(root->left) - cal(root->right);
    }
    else if(root->express == '*')
    {
        ret = cal(root->left) * cal(root->right);
    }
    else if(root->express == '/')
    {
        ret = cal(root->left) / cal(root->right);
    }
    return ret;
}
void peTree::preOrderTraver(TreeNode* root)
{
    if(root)
    {
        root->visit();
        preOrderTraver(root->left);
        preOrderTraver(root->right);
    }
}
void peTree::inOrderTraver(TreeNode* root)
{
    if(root)
    {
        if( root->left != NULL || root->right != NULL)
            std::cout<<"(";
        inOrderTraver(root->left);
        root->visit();
        inOrderTraver(root->right);
        if( root->left != NULL || root->right != NULL)
            std::cout<<")";
    }
}
void peTree::postOrderTraver(TreeNode* root)
{
    if(root)
    {
        postOrderTraver(root->left);
        postOrderTraver(root->right);
        root->visit();
    }
}
int main(int argc,char* argv[])
{
    std::cout<<"postfix express: ";
    std::string str;
    std::cin>>str;
    peTree tree;
    TreeNode* root = tree.createTree(str.c_str());
    std::cout<<"ret= ";
    std::cout<<tree.cal(root);
    std::cout<<std::endl<<"preOrder: ";
    tree.preOrderTraver(root);
    std::cout<<std::endl<<"inOrder: ";
    tree.inOrderTraver(root);
    std::cout<<std::endl<<"postOrder: ";
    tree.postOrderTraver(root);
}
