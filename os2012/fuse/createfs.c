#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "fswork.h"

int main(int argc, char** argv)
{
    initFileSystem();
    printf("FS in %s was created!\n", FS_FILE_PATH);
    return 0;
}
