#include "BlockOperation.h"

void BlockOperation::Execute()
{
    this->operation_block();//FIX ME
}

void BlockOperation::set_block(void (^blck)(void))
{
    this->operation_block = blck;
}
