#include <dispatch/dispatch.h>
#include <stdio.h>

#include "Operation.h"
#include "BlockOperation.h"

void run_Operation_async(dispatch_queue_t queue, Operation *op)
{
    dispatch_async(queue, ^(void) {
        op->Execute();
    });
}

int main(int argc, char** argv)
{
    dispatch_queue_t queue = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);//dispatch_get_global_queue(0, 0);
    //Operation op;
    //run_Operation_async(queue, &op);
    //dispatch_group_t group = dispatch_group_create()
    dispatch_async(queue, ^(void) {
        printf("So...\n");
    });
    sleep(1);
    printf("THE END");
    dispatch_release(queue);
    return 0;
}
