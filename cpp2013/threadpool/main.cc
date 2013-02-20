#include <dispatch/dispatch.h>
#include <stdio.h>

#include "Operation.h"
#include "BlockOperation.h"
#include "FunctionOperation.h"

void run_Operation_async(dispatch_queue_t queue, Operation *op)
{
    dispatch_async(queue, ^(void) {
        op->Execute();
    });
}

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

class MyOperation : public Operation
{
    void Execute()
    {
        printf("Make!\n");
    }
};

int main(int argc, char** argv)
{
    dispatch_queue_t queue = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);//dispatch_get_global_queue(0, 0);
    MyOperation op;
    FunctionOperation op2(foo2);
    run_Operation_async(queue, &op);
    run_Operation_async(queue, &op2);
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
