#include "FunctionOperation.h"

void FunctionOperation::Execute()
{
    this->foo(this->args);//FIX ME
}

FunctionOperation::FunctionOperation(function foo, void *args)
{
    this->foo = foo;
    this->args = args;
    this->set_priority(normal);
}
