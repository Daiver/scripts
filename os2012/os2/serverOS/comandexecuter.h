#ifndef COMANDEXECUTER_H
#define COMANDEXECUTER_H
#include <vector>
#include <string>

class ComandExecuter
{
protected:
    std::vector<std::string> history;
public:
    void PrintVec(std::vector<std::string>);
    std::vector<std::string> Execute(std::string cmd);
    ComandExecuter();
};

#endif // COMANDEXECUTER_H
