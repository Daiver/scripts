#include <dispatch/dispatch.h>
#include <stdio.h>

#include "Operation.h"
#include "BlockOperation.h"
#include "FunctionOperation.h"
#include "ThreadPool.h"


void foo(void (^block)(void))
{
    void (^f)(void);
    f = block;
    f();
}

void foo2()
{
    printf("foo2\n");
}

int main(int argc, char** argv)
{
    ThreadPool pool;
    dispatch_queue_t queue = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
    FunctionOperation op2(foo2);
    pool.async(&op2);
    //run_Operation_async(queue, &op2);
    //dispatch_group_t group = dispatch_group_create()
    //foo(^(void){ printf("!!!!!!\n");});
    dispatch_async(queue, ^(void) {
        printf("So...\n");
    });
    sleep(1);
    printf("THE END");
    dispatch_release(queue);
    return 0;
}
