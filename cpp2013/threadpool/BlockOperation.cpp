#include "BlockOperation.h"

BlockOperation::BlockOperation(RequestCompletionBlock block)
{
    this->operation_block = block;
}
