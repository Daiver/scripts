#include <pthread.h>

#include "linkedlist.h"

template <class K, class V, long H(K)>
class HashTable
{
public:
    HashTable()
    {
        this->sizeOfTable = 30000;
        this->_size = 0;
        this->create();
    }

    void set(const K& key, const V& value)
    {
        long index = this->getIndex(key);
        ListItem<K, V> *tmp = this->values[index]->find(key);
        if(NULL == tmp)
        {
            this->_size++;
            this->values[index]->add(key, value);
        }
        else
        {
            tmp->value = value;
        }
    }

    V* get(const K& key)
    {
        long index = this->getIndex(key);
        ListItem<K, V> *tmp = this->values[index]->find(key);
        if(NULL == tmp) return NULL;
        return &tmp->value;
    }

    V getOrDef(const K& key, const V& def)
    {
        V* tmp = this->get(key);
        if(NULL == tmp) return def;
        return *tmp;
    }

    bool erase(const K& key)
    {
        long index = this->getIndex(key);
        bool res = this->values[index]->erase(key);
        if(res)
        {
            this->_size--;
            return true;
        }
        return false;
        //if(NULL == tmp) return false;

    }

    ~HashTable()
    {
        this->clear();
    }

    long size()
    {
        return this->_size;
    }

    void reset()
    {
        this->clear();
        this->create();
    }

private:
    long getIndex(const K& key)
    {
        return H(key) % this->sizeOfTable;
    }

    void clear()
    {
        for(int i = 0; i < this->sizeOfTable; i++)
            delete this->values[i];
        delete[] this->values;
    }

    void create()
    {
        this->values = new LinkedList<K, V> *[sizeOfTable];
        for(int i = 0; i < this->sizeOfTable; i++)
            this->values[i] = new LinkedList<K, V>();
    }


    long sizeOfTable;
    long _size;
    LinkedList<K, V>** values;
    LinkedList<K, V> linked_values;
};
