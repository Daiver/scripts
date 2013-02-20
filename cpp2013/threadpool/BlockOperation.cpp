#include "BlockOperation.h"

void BlockOperation::Execute()
{
    //this->operation_block();//FIX ME
}

BlockOperation::BlockOperation(RequestCompletionBlock blck)
{
    this->operation_block = blck;
}
