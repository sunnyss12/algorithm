#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
int tmp;
#define swap(left,right) do{\
                            tmp = left;\
                            left = right;\
                            right = tmp;\
                           }while(0)
void buble_sort(int arr[N],int len)
{
    int i,j;
    for(i = 0;i < len;i++)//使用冒泡法，每次在arr[len-i]处放置arr[0]~arr[len-i]中最大的数值
    {
        for(j = 1 ;j<len - i;j++)
        {
            if(arr[j]<arr[j-1])
                swap(arr[j],arr[j-1]);
        }
    }
    
}
int main(int argc,char* argv[])
{
    int arr[N] = {0};
    srand(time(NULL));
    int index;
    printf("before sort:\n");
    for(index=0;index<N;index++)
    {
        arr[index] = rand()%100;
        printf("%3d",arr[index]);
    }
    printf("\n");
    buble_sort(arr,N);
    printf("after sort:\n");
    for(index=0;index<N;index++)
    {
        printf("%3d",arr[index]);
    }
    printf("\n");

}
