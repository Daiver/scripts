#include "Operation.h"

typedef void (*function)(void);

class FunctionOperation : public Operation
{
public:
    void Execute();
    FunctionOperation(function foo);
private:
    function foo;
};
