#ifndef __LAMBDAOPERATION_H__
#define __LAMBDAOPERATION_H___H__
#include "Operation.h"

class LambdaOperation : public Operation
{
public:
    void Execute();
    LambdaOperation(void *args);
private:
    function foo;
    void *args;
};
#else
#endif
