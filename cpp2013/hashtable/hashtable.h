#include <pthread.h>

template <class K, class V>
class HashItem
{
public:
    HashItem(const K &key, const V &value)
    {
        this->value = value;
        this->key = key;
    }
private:
    K key;
    V value;
    HashItem<K, V> *next;
};

template <class K, class V, long H(K)>
class HashTable
{
public:
    HashTable()
    {
        this->sizeOfTable = 300;
        this->size = 0;
        this->values = new HashItem<K, V> *[sizeOfTable];
        for(int i = 0; i < this->sizeOfTable; i++)
            this->values[i] = NULL;
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
    HashItem<K, V>** values;
};
