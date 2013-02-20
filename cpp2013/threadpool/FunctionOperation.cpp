#include "FunctionOperation.h"

void FunctionOperation::Execute()
{
    this->foo();//FIX ME
}

FunctionOperation::FunctionOperation(function foo)
{
    this->foo = foo;
}
