#include <dispatch/dispatch.h>
#include <stdio.h>

static void timer_did_fire(void *context) {
    printf("Strawberry fields...\n");
}

static void write_completion_handler(dispatch_data_t unwritten_data,
                                     int error,
                                     void *context) {
    if (!unwritten_data && error == 0)
       printf("Dispatch I/O wrote everything to stdout. Hurrah.\n");
}

static void read_completion_handler(dispatch_data_t data,
                                    int error,
                                    void *context) {
    int fd = (intptr_t)context;
    close(fd);

    dispatch_write_f_np(STDOUT_FILENO, data, dispatch_get_main_queue(),
                        NULL, write_completion_handler);
}

int do_work(int *data, int i)
{
    return data[i]*i;
}

int main(int argc, const char *argv[]) {
    int arr_size = 10;
    int *data = new int[arr_size];
    int *result = new int[arr_size];
    int i;
    for(int i = 0; i < arr_size; i++) data[i] = i;
    dispatch_apply_f(arr_size, dispatch_get_global_queue(0, 0), (size_t i){
             result[i] = do_work(data, i);
         });
    for(int i = 0; i < arr_size; i++) printf("%d ", result[i]);
    
    delete[] data;
    /*dispatch_source_t timer = dispatch_source_create(
        DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dispatch_get_main_queue());

    dispatch_source_set_event_handler_f(timer, timer_did_fire);
    dispatch_source_set_timer(timer, DISPATCH_TIME_NOW, 1 * NSEC_PER_SEC,
                              0.5 * NSEC_PER_SEC);
    dispatch_resume(timer);

    int fd = open("main.cc", O_RDONLY);

    dispatch_read_f_np(fd, 1024, dispatch_get_main_queue(), (void *)(intptr_t)fd,
                       read_completion_handler);

    dispatch_main();*/
    return 0;
}
