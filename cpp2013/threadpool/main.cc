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

int tmp_data1 = 0;
int tmp_data2 = 0;

void foo(void *data)
{
    tmp_data2 = *(int*)data;
    printf("foo! %d\n", tmp_data2);
    //std::cout<<"foo2"<<std::endl<<std::cout.flush();
}

void foo2(void *data)
{
    tmp_data1 += 10;
    printf("foo2! %d\n", tmp_data1);

}

void foo3(void *data)
{
    tmp_data1 *= 3;
    printf("foo3 %d\n", tmp_data1);
}

void foo4(void *data)
{
    printf("foo4 %d\n", tmp_data1);
}

void foo5(void *data)
{
    tmp_data1 *= tmp_data2;
    printf("foo5 %d\n", tmp_data1);
}


int main(int argc, char** argv)
{
    ThreadPool pool(3);
    int tst = 100;
    FunctionOperation op1(foo, &tst);
    FunctionOperation op2(foo2, NULL);
    FunctionOperation op3(foo3, NULL);
    FunctionOperation op4(foo4, NULL);
    FunctionOperation op5(foo5, NULL);
    std::cout<<"op1 "<< op1.get_ID()<<std::endl;
    std::cout<<"op2 "<< op2.get_ID()<<std::endl;
    std::cout<<"op3 "<< op3.get_ID()<<std::endl;
    std::cout<<"op1 "<< op1.get_ID()<<std::endl;
    //op4.set_priority(low);
    //pool.async(&op2);
    //pool.async(&op2);
    //pool.async(&op1);
    //pool.async(&op2);
    op3.add_dependency(&op4);
    op3.add_dependency(&op2);
    op3.add_dependency(&op1);
    op3.add_dependency(&op4);
    op3.add_dependency(&op4);
    op3.add_dependency(&op4);
    op5.add_dependency(&op3);
    pool.async(&op5);

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
