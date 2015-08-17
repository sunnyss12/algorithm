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
void select_sort(int arr[N],int len)//从无序区中选择一个最小的元素放到无序区中的最一个位置
{
    int i,j;
    int index_min;
    for(i = 0;i < len-1;i++)
    {
        index_min = i;
        for(j = i+1;j < len;j++)
        {
            if(arr[j] < arr[index_min])
                index_min = j;
        }
        if(i != index_min)
        {
            swap(arr[i],arr[index_min]);         
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
    select_sort(arr,N);
    printf("after sort:\n");
    for(index=0;index<N;index++)
    {
        printf("%3d",arr[index]);
    }
    printf("\n");

}
