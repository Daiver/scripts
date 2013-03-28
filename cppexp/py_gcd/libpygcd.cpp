#include <stdio.h>
#include <dispatch/dispatch.h>

void work3(void *(*f)(int))
{
    dispatch_queue_t queue = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
    int *r = new int [100];//10000;
    for(int i = 0; i < 100; i++) r[i] = i;

    dispatch_apply(100, queue, ^(size_t i) {
        f(r[i]);
    });
}

void work2(int i, int j)
{
    printf("Hello world %d %d\n", i, j);
}

void work()
{
    dispatch_queue_t queue = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^(void) {
        printf("Hello world2\n");
    });
    dispatch_async(queue, ^(void) {
        printf("Hello world3\n");
    });
    dispatch_async(queue, ^(void) {
        printf("Hello world4\n");
    });
    dispatch_async(queue, ^(void) {
        printf("Hello world5\n");
    });
    
    printf("Hello world\n");
}
