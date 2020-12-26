#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#define N 10

void *MyOwnMalloc(size_t size)
{
    void *t = sbrk(0); // t as a temp variable
    void *req_size = sbrk(size);
    if(req_size == (void *)-1)
    {
        return NULL;
    } 
    else
    {
        assert(t == req_size);
        return t;
    }
}

int main()
{
    int i,*array;
    printf("\n Enter n numbers: ");
    array = MyOwnMalloc(sizeof(int)*N);
    for(i=0;i<N;i++)
    {
        scanf("%d",&array[i]);
    }
    printf("\n The numbers are :\n");
    for(i=0;i<N;i++)
    {
        printf("%d ",array[i]);
    }

    return 0;
}
