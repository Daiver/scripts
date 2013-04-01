#include <stdio.h>

/*class MyCls
{
public:
MyCls()
{this->value = new int[100];}
~MyCls()
{delete this->value;}

int* value;
};

MyCls getContainer()
{
MyCls res;
return res;
}
*/

template<class K, class V> 
class Mytmp
{
public:
    K key;
    V value;
    V get(V v);
    void some()
    {
        printf("less\n");
    }
};

template<class K, class V>
V Mytmp<K, V>::get(V v)
{
    this->some();
    return v;
}

template<class K>
class Mytmp<K, int> : public Mytmp<K, int>
{
public:
    int get(int v)
    {
        this->some();
        printf("Hi!");
        return v;
    }
};

int main()
{
    /*MyCls res;
    res = getContainer();
    res.value[0] = 90;*/
    Mytmp<int, int> mt;
    mt.get(100);
    return 0;
}
