#include <dispatch/dispatch.h>
#include <iostream>
#include <stdio.h> //temporary

#include "Operation.h"
#include "FunctionOperation.h"
#include "ThreadPool.h"


void exec_block(void (^block)(void))//del it
{
    void (^f)(void);
    f = block;
    f();
}

int tmp_data = 0;

void foo(void *data)
{
    printf("foo! %d\n", (*(int*)data));
    //std::cout<<"foo2"<<std::endl<<std::cout.flush();
}

void foo2(void *data)
{
    printf("foo2!\n");
}

void foo3(void *data)
{
    printf("foo3\n");
}

void foo4(void *data)
{
    printf("foo4\n");
}

int main(int argc, char** argv)
{
    ThreadPool pool(3);
    int tst = 100;
    FunctionOperation op1(foo, &tst);
    FunctionOperation op2(foo2, NULL);
    FunctionOperation op3(foo3, NULL);
    FunctionOperation op4(foo4, NULL);
    op1.set_priority(low);
    //pool.async(&op2);
    //pool.async(&op2);
    //pool.async(&op1);
    //pool.async(&op2);
    op4.add_dependency(&op1);
    op3.add_dependency(&op2);
    op4.add_dependency(&op3);
    pool.async(&op4);

    //run_Operation_async(queue, &op2);
    //dispatch_group_t group = dispatch_group_create()
    //foo(^(void){ printf("!!!!!!\n");});
    sleep(1);
    //tmpfoo();
    std::cout<<"THE END";
    return 0;
}

void tmpfoo()
{

    dispatch_queue_t queue = dispatch_queue_create("com.mydomain.myapp.longrunningfunction", DISPATCH_QUEUE_CONCURRENT);
    dispatch_async(queue, ^(void) {
    });
    dispatch_group_t gr = dispatch_group_create();
    dispatch_group_async(gr, queue, ^(void) {
        printf("Wait me\n");
    });
    dispatch_group_async(gr, queue, ^(void) {
        printf("Wait me 2\n");
    });
    dispatch_group_async(gr, queue, ^(void) {
        printf("Wait me 3\n");
    });
    dispatch_group_wait(gr,  DISPATCH_TIME_FOREVER);
    dispatch_release(queue);
    printf("End tmp foo\n");
}
