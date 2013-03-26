#include <pthread.h>

#include "linkedlist.h"

template <class K, class V, long H(K)>
class HashTable
{
public:
    HashTable()
    {
        this->sizeOfTable = 300;
        this->size = 0;
        this->values = new LinkedList<K, V> *[sizeOfTable];
        for(int i = 0; i < this->sizeOfTable; i++)
            this->values[i] = NULL;
    }

    void add(const V& value, const K& key)
    {
        
    }

    ~HashTable()
    {
        for(int i = 0; i < this->sizeOfTable; i++)
            delete this->values[i];
        delete[] this->values;
    }

private:
    long sizeOfTable;
    long size;
    LinkedList<K, V>** values;
};
