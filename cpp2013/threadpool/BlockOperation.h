#include "Operation.h"

typedef void (^RequestCompletionBlock)(void);

class BlockOperation : public Operation
{
public:
    void Execute();
    void set_block(void (^block)(void));
private:
    void (^operation_block)(void);
};
