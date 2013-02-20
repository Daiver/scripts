#include <dispatch/dispatch.h>
#include <stdio.h>

#include "Operation.h"

int main(int argc, char** argv)
{
    dispatch_queue_t queue = dispatch_get_global_queue(0, 0);
    dispatch_async(queue, ^(void) {
        printf("So...\n");
    });
    sleep(1);
    printf("THE END");
    dispatch_release(queue);
    return 0;
}
