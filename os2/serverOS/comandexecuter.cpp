#include "comandexecuter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ComandExecuter::PrintVec(std::vector<std::string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        printf("%d:%s", i, vec[i].c_str());
    }
}

std::vector<std::string> InnerExecute(std::string cmd)
{
    std::vector<std::string> res;
    char buf[512];
    strcpy(buf, cmd.c_str());//ta-dadam!
    FILE* ptr = popen(buf, "r");

    if (ptr != NULL)
    {
        while (fgets(buf, BUFSIZ, ptr) != NULL)
            res.push_back(buf);
            //(void) printf("~>%s", buf);
        (void) pclose(ptr);
    }
    return res;
}

std::vector<std::string> ComandExecuter::Execute(std::string cmd)
{
    std::vector<std::string> res;
    if (cmd.size() > 0)
    {
        res = InnerExecute(cmd);
    }
    return res;
}

ComandExecuter::ComandExecuter()
{

}
