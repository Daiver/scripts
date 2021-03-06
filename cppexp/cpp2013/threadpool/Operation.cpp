#include <stdio.h>
#include "Operation.h"

void Operation::set_priority(Operation_Priority priority)
{
    this->id = Operation::get_new_ID();
    this->priority = priority;
}

Operation_Priority Operation::get_priority()
{
    return this->priority;
}

void Operation::add_dependency(Operation *op)
{
    this->dependency.push_back(op);
}

std::vector<Operation*> Operation::get_dependences()
{
    return this->dependency;
}

long Operation::get_ID() 
{
    return this->id;
}
