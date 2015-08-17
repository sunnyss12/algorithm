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

int partion(int arr[N],int left,int right) //从left+1 ~ right中寻找小于arr[left]的数，并紧挨着left放到arr[left]后面，然后将arr[left]和小于arr[left]的最后一个数置换。目的：使arr形成三部分：arr[left]~arr[k-1]放着小于arr[k]的值,arr[k+1]~arr[right]放置大于arr[k]的值。使用方法：快慢指针
{
    int i,j;
    for(i = left,j = left+1;j <= right;j++)
    {
        if(arr[j] < arr[left])
        {
            swap(arr[i+1],arr[j]);
            i++;
        }
    }
    swap(arr[left],arr[i]);
    return i;
}
void quick_sort(int arr[N],int left,int right)
{
    int k;
    if(left < right)
    {
        k = partion(arr,left,right);
        quick_sort(arr,left,k-1);
        quick_sort(arr,k+1,right);
    }
}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    int arr[N] = {0};
    int index;
    printf("before sort:\n");
    for(index = 0;index < N;index++)
    {
        arr[index] = rand() % 100;
        printf("%4d",arr[index]);
    }
    printf("\n");
    quick_sort(arr,0,N-1);
    printf("after sort:\n");
    for(index = 0;index < N;index++)
    {
        printf("%4d",arr[index]);
    }
    printf("\n");

}
