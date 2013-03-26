#include <stdio.h>
#include <string>

#include "hashtable.h"

long someFunc(int i)
{
    return i;
}

bool testLinkedListAdd(LinkedList<int, int> *list)
{
    list->add(1, 1);
    list->add(2, 2);
    list->add(3, 3);
    if(list->find(900) != NULL) return false;
    if(list->find(1)->value != 1) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(1)->value != 1) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(2)->value != 2) return false;
    return true;
}

bool testLinkedListFind(LinkedList<int, int> *list)
{
    list->add(5, 5);
    if(list->find(5)->value != 5) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(1)->value != 1) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(6) != NULL) return false;
    return true; 
}

bool testLinkedListErase(LinkedList<int, int> *list)
{
    list->erase(1);
    if(list->find(5)->value != 5) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(1) != NULL) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(6) != NULL) return false;
    if(list->find(1) != NULL) return false;
    list->erase(5);
    if(list->find(5) != NULL) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(1) != NULL) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(6) != NULL) return false;
    if(list->find(1) != NULL) return false;
    list->erase(3);
    if(list->find(3) != NULL) return false;
    if(list->find(2)->value != 2) return false;
    return true; 
}


void printTestRes(bool res, std::string test_name)
{
    printf("Test %s ", test_name.c_str());
    if(res) printf("PASSED\n");
    else printf("FAILED\n");
}

void runAllTests()
{
    LinkedList<int, int> *list = new LinkedList<int, int>();
    printTestRes(testLinkedListAdd(list), "LinkedList add test");
    printTestRes(testLinkedListFind(list), "LinkedList find test");
    printTestRes(testLinkedListErase(list), "LinkedList erase test");
    delete list;
}

int main(int argc, char** argv)
{
    HashTable<int, int, someFunc> ht;
    printf("and so on\n");
    runAllTests();
    return 0;
}
