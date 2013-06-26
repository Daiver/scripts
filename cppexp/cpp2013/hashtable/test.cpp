#include "test.h"

#include <stdio.h>
#include <string>
#include <sstream>

#include "hashtable.h"
#include "linkedlist.h"

void printList(LinkedList<int, int> *list)
{
    for(auto it = list->begin(); it != list->end(); it++)
        printf("%d ", (*it));
    printf("\n");
}

bool testLinkedListAdd(LinkedList<int, int> *list)
{
    list->add(1, 1);
    list->add(2, 2);
    list->add(3, 3);
    if(list->size() != 3) return false;
    if(list->find(900) != NULL) return false;
    if(list->find(1)->value != 1) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(1)->value != 1) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(2)->value != 2) return false;
    printList(list);
    return true;
}

bool testLinkedListFind(LinkedList<int, int> *list)
{
    list->add(5, 5);
    if(list->size() != 4) return false;
    if(list->find(5)->value != 5) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(1)->value != 1) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(6) != NULL) return false;
    printList(list);
    return true; 
}

bool testLinkedListErase(LinkedList<int, int> *list)
{
    list->erase(1);
    if(list->size() != 3) return false;
    if(list->find(5)->value != 5) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(1) != NULL) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(6) != NULL) return false;
    if(list->find(1) != NULL) return false;
    list->erase(5);
    if(list->size() != 2) return false;
    if(list->find(5) != NULL) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(1) != NULL) return false;
    if(list->find(3)->value != 3) return false;
    if(list->find(2)->value != 2) return false;
    if(list->find(6) != NULL) return false;
    if(list->find(1) != NULL) return false;
    list->erase(3);
    printList(list);
    if(list->size() != 1) return false;
    if(list->find(3) != NULL) return false;
    if(list->find(2)->value != 2) return false;
    return true; 
}

bool testLinkedListErase2(LinkedList<int, int> *list)
{
    list->erase(2);
    if(list->size() != 0) return false;
    if(list->find(5) != NULL) return false;
    if(list->find(2) != NULL) return false;
    if(list->find(1) != NULL) return false;
    if(list->find(6) != NULL) return false;
    if(list->find(1) != NULL) return false;
    return true;
}

void printTestRes(bool res, std::string test_name)
{
    printf(">Test %s ", test_name.c_str());
    if(res) printf("PASSED\n");
    else printf("FAILED\n");
}

void testLinkedList()
{
    LinkedList<int, int> *list = new LinkedList<int, int>();
    printTestRes(testLinkedListAdd(list), "LinkedList add test");
    printTestRes(testLinkedListFind(list), "LinkedList find test");
    printTestRes(testLinkedListErase(list), "LinkedList erase test");
    printTestRes(testLinkedListErase2(list), "LinkedList erase2 test");
    printTestRes(testLinkedListAdd(list), "2 LinkedList add test");
    printTestRes(testLinkedListFind(list), "2 LinkedList find test");
    printTestRes(testLinkedListErase(list), "2 LinkedList erase test");
    printTestRes(testLinkedListErase2(list), "2 LinkedList erase2 test");
    printTestRes(testLinkedListAdd(list), "3 LinkedList add test");
    printTestRes(testLinkedListFind(list), "3 LinkedList find test");
    printTestRes(testLinkedListErase(list), "3 LinkedList erase test");
    printTestRes(testLinkedListErase2(list), "3 LinkedList erase2 test");
    delete list;
}


long strHash(std::string string)
{
    size_t len = string.size();
    long hash = 0;
    for(size_t i = 0; i < len; ++i) 
        hash = 65599 * hash + string[i];
    return hash ^ (hash >> 16);
}

void printTable(HashTable<std::string, int> *table)
{
    for(auto it = table->begin(); it != table->end(); it++) printf("%s:%d ",it.Key().c_str(), (*it));
    printf("\n");
}

bool testHashTableAddFindAndDelete(HashTable<std::string, int> *table)
{
    table->set("A", 12);
    if(table->size() != 1) return false;
    if(table->getOrDef("A", 0) != 12) return false;
    table->set("A", 10);
    if(table->size() != 1) return false;
    if(table->getOrDef("A", 0) != 10) return false;
    table->set("daiver", 128);
    printTable(table);
    if(table->size() != 2) return false;
    if(table->getOrDef("daiver", 0) != 128) return false;
    table->erase("daiver");
    printTable(table);
    if(table->size() != 1) return false;
    if(table->getOrDef("daiver", 0) != 0) return false;
    table->erase("A");
    if(table->size() != 0) return false;
    if(table->getOrDef("A", 0) != 0) return false;
    if(table->getOrDef("daiver", 0) != 0) return false;
    return true;
}

long big_size = 1000000;
bool testHashTableBigData1(HashTable<std::string, int> *table)
{
    for(int i = 0; i < big_size; i++)
    {
        std::stringstream ss;
        ss << i;
        std::string tmp_key;
        ss >> tmp_key;
        //printf("%s\n", tmp_key.c_str());
        table->set(tmp_key, i);
        if(table->size() != i + 1) return false;
        if(table->getOrDef(tmp_key, -1) != i) return false;
    }
    return true;
}

bool testHashTableBigData2(HashTable<std::string, int> *table)
{
    for(int i = 0; i < big_size; i++)
    {
        std::stringstream ss;
        ss << i;
        std::string tmp_key;
        ss >> tmp_key;
        //printf("%s\n", tmp_key.c_str());
        table->set(tmp_key, i*10);
        if(table->size() != big_size) return false;
        if(table->getOrDef(tmp_key, -1) != i*10) return false;
    }
    return true;
}

bool testHashTableBigData3(HashTable<std::string, int> *table)
{
    int j = 0;
    for(int i = 0; i < big_size; i += 2)
    {
        std::stringstream ss;
        ss << i;
        std::string tmp_key;
        ss >> tmp_key;
        table->erase(tmp_key);
        j++;
        //table->set(tmp_key, i*10);
        if(table->size() != big_size - j) return false;
        if(table->getOrDef(tmp_key, -1) != -1) return false;
    }
    for(int i = 1; i < big_size; i += 2)
    {
        std::stringstream ss;
        ss << i;
        std::string tmp_key;
        ss >> tmp_key;
        if(table->getOrDef(tmp_key, -1) != i*10) return false;
    }
    printf("%ld\n", table->size());
    return true;
}

bool testHashTableManual(HashTable<std::string, int> *table)
{
    table->set("me", 0);
    auto st = table->begin();
    auto fin = table->end();
    //printf("after create\n");
    HashTable<std::string, int> table2(st, fin);
    printf("show orig:\n");
    printTable(table);
    printf("show copy:\n");
    printTable(&table2);

    return true;
}

void testHashTable()
{
    //printf("before test\n");
    HashTable<std::string, int> table;
    printTestRes(testHashTableManual(&table), "test HashTable manual");
    table.reset();
    printTestRes(testHashTableAddFindAndDelete(&table), "test HashTable Add");
    printTestRes(testHashTableBigData1(&table), "test HashTable big data1");
    printTestRes(testHashTableBigData2(&table), "test HashTable big data2");
    table.reset();
    printTestRes(testHashTableBigData1(&table), "test HashTable big data1");
    printTestRes(testHashTableBigData2(&table), "test HashTable big data2");
    table.reset();
}

void runAllTests()
{
    printf("Testing linkedlist...\n");
    testLinkedList();
    printf("Testing hashtable...\n");
    testHashTable();
}
