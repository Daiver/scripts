#ifndef __FUNCTIONOPERATION_H__
#define __FUNCTIONOPERATION_H__
#include "Operation.h"

typedef void (*function)(void *);

class FunctionOperation : public Operation
{
public:
    void Execute();
    FunctionOperation(function foo, void *args);
private:
    function foo;
    void *args;
};
#else
#endif
