#ifndef __BLOCKOPERATION_H__
#define __BLOCKOPERATION_H__
#include "Operation.h"

typedef void (^RequestCompletionBlock)(void);

class BlockOperation : public Operation
{
public:
    BlockOperation(void (^work)(void));
    void Execute();
private:
    void* operation_block;
};
#else
#endif
