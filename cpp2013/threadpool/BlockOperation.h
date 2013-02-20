#include "Operation.h"

typedef void (^RequestCompletionBlock)(void *data);

class BlockOperation : public Operation
{
public:
    
private:
    RequestCompletionBlock operation_block;
};
