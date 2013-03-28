#include <stdio.h>
#include <dispatch/dispatch.h>

void work()
{
    dispatch_queue_t queue = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^(void) {
        printf("Hello world2\n");
    });
    printf("Hello world\n");
}
