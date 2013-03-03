#include <dispatch/dispatch.h>
#include <stdio.h>

#include "Operation.h"
#include "FunctionOperation.h"
#include "ThreadPool.h"


void foo(void (^block)(void))
{
    void (^f)(void);
    f = block;
    f();
}

void foo2(void *data)
{
    printf("foo2 %d\n", *(int *)data);
}

void foo3(void *data)
{
    printf("foo3\n");
}

void tmpfoo()
{

    dispatch_queue_t queue = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^(void) {
        printf("So...\n");
    });
    dispatch_release(queue);
}
int main(int argc, char** argv)
{
    ThreadPool pool(3);
    int tst = 100;
    FunctionOperation op2(foo2, &tst);
    FunctionOperation op(foo3, NULL);
    op.set_priority(low);
    pool.async(&op2);
    pool.async(&op2);
    pool.async(&op);
    pool.async(&op2);
    //run_Operation_async(queue, &op2);
    //dispatch_group_t group = dispatch_group_create()
    //foo(^(void){ printf("!!!!!!\n");});
    sleep(1);
    printf("THE END");
    return 0;
}
