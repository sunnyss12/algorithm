#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20 
void insert_sort(int arr[N],int len)//将数据分为有序区和无序区，将序区的第一个元素直接插入到有序区中以形成一个更大的有序区
{
    int i,j;
    int key;
    for(i = 1;i < len;i++)
    {
        key = arr[i]; //这一句不可省略
        for(j = i-1;j>=0;j--)
        {
            if(arr[j]>key)
            {
                arr[j+1] = arr[j];
            }
            else
            {
                break;
            }
        }
        arr[j+1] = key;
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
    insert_sort(arr,N);
    printf("after sort:\n");
    for(index=0;index<N;index++)
    {
        printf("%3d",arr[index]);
    }
    printf("\n");

}
