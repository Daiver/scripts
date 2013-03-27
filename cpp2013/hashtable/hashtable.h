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
            this->values[i] = new LinkedList<K, V>();
    }

    void set(const K& key, const V& value)
    {
        long index = this->getIndex(key);
        ListItem<K, V> *tmp = this->values[index]->find(key);
        if(NULL == tmp)
        {
            this->values[index]->add(key, value);
        }
        else
        {
            tmp->value = value;
        }
    }

    V get(const K& key)
    {
        long index = this->getIndex(key);
        ListItem<K, V> *tmp = this->values[index]->find(key);
        return tmp->value;
    }

    ~HashTable()
    {
        for(int i = 0; i < this->sizeOfTable; i++)
            delete this->values[i];
        delete[] this->values;
    }

private:
    long getIndex(const K& key)
    {
        return H(key) % this->sizeOfTable;
    }

    long sizeOfTable;
    long size;
    LinkedList<K, V>** values;
};
