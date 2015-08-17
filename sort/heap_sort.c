#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 20
int tmp;
#define swap(left,right) do{\
                            tmp = left;\
                            left = right;\
                            right = tmp;\
                           }while(0)

void adjust_down(int arr[N],int index,int end) //将arr[index]为根的树调整为最大堆,end为arr堆最后一个元素的下标
{
    int key = arr[index];
    int index_child = index*2+1;
    while(index_child <= end)
    {
        if(index_child +1 <= end && arr[index_child+1] > arr[index_child])
        {
            index_child = index_child+1;            
        }
        if(arr[index_child] <= key)
        {
            break;
        }
        arr[index] = arr[index_child];
        index = index_child;
        index_child = 2*index+1;       
    }
    arr[index]=key;
}
void heap_sort(int arr[N],int len)
{
    int index;
    for(index = len/2-1;index >= 0;index--)//将无序的arr变成最大堆
    {
        adjust_down(arr,index,len-1);        
    }
    for(index = len-1;index >= 1;index--)//最大堆的arr[0]为最大的数值，将arr[0]和最后一个元素arr[k]置换，然后将arr[0]~arr[k-1]再次调整为最大堆。目的：每次在最后一个元素存放最大值
    {
        swap(arr[0],arr[index]);
        adjust_down(arr,0,index-1);
    }
}
int main(int argc,char* argv[])
{
    int arr[N]={0};
    int index;
    srand(time(NULL));
    printf("befor sort:\n");
    for(index=0;index<N;index++)
    {
        arr[index]=rand()%100;
        printf("%4d",arr[index]);        
    }
    printf("\n");
    printf("after sort:\n");
    heap_sort(arr,N);
    for(index=0;index<N;index++)
    {
        printf("%4d",arr[index]);
    }
    printf("\n");
    return 0;
}
