#include <stdio.h>
#include "Operation.h"

void Operation::set_priority(Operation_Priority priority)
{
    this->priority = priority;
}

Operation_Priority Operation::get_priority()
{
    return this->priority;
}
