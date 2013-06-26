#ifndef __FUNCTIONOPERATION_H__
#define __FUNCTIONOPERATION_H__
#include "Operation.h"

typedef void (*function)(void *);

class FunctionOperation : public Operation
{
public:
    void Execute();
    FunctionOperation(function foo, void *args);
    FunctionOperation(const FunctionOperation &op):Operation(op)
    {
        this->foo = op.foo;
        this->args = op.args;
        //this->dependency = op.dependency;
        //this->id = this->get_new_ID();
    }
private:
    function foo;
    void *args;
};
#else
#endif
