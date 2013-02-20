#include "Operation.h"

typedef void (^RequestCompletionBlock)(void *data);

class BlockOperation : public Operation
{
public:
    BlockOperation(RequestCompletionBlock opblock);
private:
    RequestCompletionBlock operation_block;
};
