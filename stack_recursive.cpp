//用两种方法将一个递归函数使用堆栈转换为非递归，第一种方法为nonrec::replace1，第二种方法为nonrec::replace2。两种方法其实本质一样，只是第二种方法用循环代替了第一种方法的各种goto
#include <stack>
#include <stdio.h>
//转换的递归函数为：
int exmp(int n)
{
    if(n<2)
        return n+1;
    else
    {
        return exmp(n/2)*exmp(n/4);
    }
}
//注意我们转换的函数是没有返回值的，所以如果函数有返回值，需要首先把函数转换为返回值能用形参传出去的形式。像下面这样：
void exmp(int n,int& f)
{
    int u1,u2;
    if(n<2)
        f = n+1;
    else
    {
        exmp((int)(n/2),u1);
        exmp((int)(n/4),u2);
        f = u1*u2;
    }
}
typedef struct elem
{
    int rd;        //返回语句的标号，如果递归函数内调用了t个递归子函数，那么rd=t+2，rd=1~t代表调用的第rd个子函数的标号。rd=0表示递归出口的语句，也是递归函数第一个可执行语句。rd=t+1表示当递归子函数调用结束返回前需要处理的语句。
    int pn,pf;     //函数形参,pn表示参数n,pf表示参数f
    int q1,q2;     //局部变量,q1表示u1,q2表示u2
}ELEM;
class nonrec
{
    private:
        std::stack<ELEM> S;
    public:
        nonrec(void){}
        void replace1(int n,int& f);
        void replace2(int n,int& f);
};
void nonrec::replace1(int n,int& f)
{
    ELEM x,tmp;
    x.rd=3;    //3=t+1,压到栈底作监视哨
    x.pn=n;
    S.push(x); //调用最开始函数,递归的总入口
label0:
       if( (x = S.top()).pn < 2)        //处理递归出口,所有递归出口处需要增加语句goto label t+1。也是递归语句第一条可执行语句
       { 
            S.pop();
            x.pf = x.pn + 1;
            S.push(x);
            goto label3;      //因为递归出口语句执行完后需要执行函数返回,而lable t+1用来处理函数返回需要做的工作的，所以需要goto lable3
       }

       x.rd = 1;        //调用第一个递归函数,位于label0的后面，所以如果不满足递归出口会调用这里
       x.pn = (int)(x.pn/2);
       S.push(x);      //一次调用使用一个堆栈数据
       goto label0;
       //调用后开始执行函数，由于函数的第一条执行语句位于lable0，所以需要goto label0

label1: tmp = S.top();    //当第一个递归函数调用返回时需要进行的处理，通常是把自己计算结果放到调用者所属的数据内
        S.pop();       //tmp=S.top()，tmp.pf代表第一个递归函数计算的结果
        x = S.top();
        S.pop();
        x.q1 = tmp.pf;  //获取第一个递归函数计算的结果，赋值给该函数调用者的q1
        S.push(x);

        x.rd = 2;       //调用第二个递归函数
        x.pn = (int)(x.pn/4); 
        S.push(x);
        goto label0;

label2: tmp = S.top();    //从第二个递归函数中退出
        S.pop();
        x = S.top();
        S.pop();
        x.q2 = tmp.pf;
        x.pf = x.q1 * x.q2;
        S.push(x);
label3:                 //设在函数体结束处，当函数返回时会调用这里，处理函数返回前需要做哪些工作。它的写法是固定的：根据递归返回地址跳转到相应的label。label0 即递归出口结束后会调用这里
        switch((x=S.top()).rd)
        {
            case 1:
            goto label1;
            break;
            case 2:
            goto label2;
            break;
            case 3:          //t+1处的label：表示整个函数结束
            tmp = S.top();
            S.pop();
            f = tmp.pf;    //计算结果
            break;
            default:
            break;
        }
}

void nonrec::replace2(int n,int& f)
{
    ELEM x,tmp;
    x.rd = 3;
    x.pn = n;
    S.push(x);
    do
    {
        while((x=S.top()).pn >= 2)    //深度搜索一个递归函数，直到满足出口条件。只有新调用一个递归函数才能从这里开始
        {
            x.rd = 1;
            x.pn = (int)(x.pn/2);
            S.push(x);
        }

        x = S.top();                 //满足出口条件，该函数调用结束了
        S.pop();
        x.pf = x.pn + 1;             //计算值保存在pf中，以让它的上层调用者使用。它的调用者是它的数据的上一层
        S.push(x);

        while( (x = S.top()).rd == 2)  //满足出口条件后，需要回溯到父亲节点。需要分两种情况考虑：如果它是父亲的最后一个节点，即rd==2，那父亲节点也执行完了，需要继续回溯到它的祖父节点。如果它不是父亲的最后一个节点，那么需要调用它的兄弟节点。为什么先考虑rd==2再考虑rd==1，因为父亲节点不是祖父的最后一个节点，那需要执行父亲节点的兄弟节点，这个操作恰好就是后面代码干的事情
        {
            tmp = S.top();
            S.pop();
            x = S.top();
            S.pop();
            x.q2 = tmp.pf;
            x.pf = x.q1 * x.q2;
            S.push(x);
        }

        if((x = S.top()).rd == 1) //满足出口条件后，需要回溯到父亲节点。如果该节点不是父亲节点的最后一个节点，那么把兄弟节点加到堆栈里
        {                         //rd = 1和rd == 2最大的不同是：rd == 1新节点的回溯节点没变，新节点的回溯点依然是父节点，不需要做向上回溯操作。而rd == 2由于rd==2节点的完成导致父节点的操作也完成了，父节点需要出栈，即回溯点变了，需要找到正确的回溯节点。 
            tmp = S.top();
            S.pop();
            x = S.top();
            S.pop();
            x.q1 = tmp.pf;
            S.push(x);
            tmp.rd = 2;
            tmp.pn = (int)(x.pn/4);
            S.push(tmp);
        }
    }while( (x = S.top()).rd !=3);
    x = S.top();
    S.pop();
    f = x.pf;


//递归转非递归四个步骤：
//压栈第一个节点
//（1）向左遍历，直到满足递归出口条件
//（2）处理递归出口
//（3）判断递归出口节点是不是父节点的最后一个节点，如果是,不断回溯找到祖先不是最后一个节点的那个祖先节点
//（4）判断递归出口节点或者（3）回溯的节点是第几个节点，把该节点设置为它的下一个节点，回溯点不变不用回溯
//判断do while是不是第一个节点，如果是退出
    
}
int main()
{
    nonrec t;
    int f;
    t.replace2(10,f);
    printf("f=%d",f);


}
