#include <pthread.h>

template <class K, class V, long H(K)>
class HashTable
{
public:
    HashTable()
    {
        this->sizeOfTable = 300;
        this->size = 0;
        this->values = new V[sizeOfTable];
    }
    ~HashTable()
    {
        delete[] this->values;
    }

private:
    long sizeOfTable;
    long size;
    V* values;
};
