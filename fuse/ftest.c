#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

#include "log.h"
#include "fswork.h"

int main(int argc, char **argv)
{
    printf("Start....\n");
    struct filestruct *nodes = getNodes();
    int i;
    for(i = 0; i < 3; i++)
        printf("path %s %ld \n", nodes[i].path, nodes[i].parentdir);
    printf("Finish\n");
    return 0;
}
