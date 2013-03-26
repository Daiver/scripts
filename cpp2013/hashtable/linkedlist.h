#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

template <class K, class V>
class ListItem
{
public:
    ListItem(const K &key, const V &value)
    {
        this->value = value;
        this->key = key;
        this->next = NULL;
    }
    ~ListItem()
    {
        //delete this->next;
    }

    ListItem<K, V> *next;
    K key;
    V value;
};

template <class K, class V>
class LinkedList
{
public:
    LinkedList()
    {
        this->tail = NULL;
        this->_size = 0;
    }
    ~LinkedList()
    {
        ListItem<K, V> *tmp = this->tail;
        while(tmp != NULL)
        {
            ListItem<K, V> *tmp2 = tmp;
            tmp = tmp->next;
            delete tmp2;
        }
    }

    ListItem<K, V> *find(const K& key)
    {
        ListItem<K, V> *tmp = this->tail;
        while((tmp != NULL) && (tmp->key != key))
            tmp = tmp->next;
        return tmp;
    }

    bool erase(const K& key)
    {
        if(this->tail == NULL) return false;
        if(this->tail->key == key)
        {
            ListItem<K, V> *tmp = this->tail;
            this->tail = this->tail->next;
            delete tmp;
            this->_size--;
            return true;
        }
        ListItem<K, V> *old = this->tail;
        ListItem<K, V> *tmp = this->tail->next;
        while((tmp != NULL) && (tmp->key != key))
        {
            old = tmp;
            tmp = tmp->next;
        }
        if (NULL == tmp) return false;
        old->next = tmp->next;
        delete tmp;
        this->_size--;
        return true;
    }

    void add(const K& key, const V& value)
    {
        ListItem<K, V> *tmp = new ListItem<K, V>(key, value);
        tmp->next = this->tail;
        this->tail = tmp;
        this->_size++;
    }

    long size()
    {
        return this->_size;
    }

private:
    ListItem<K, V> *tail;
    long _size;
};


template<class T>
class Iterator
{
public:
   typedef T value_type;
   typedef T* pointer;
   typedef T& reference;
   typedef std::forward_iterator_tag iterator_category;
   typedef ptrdiff_t difference_type;
   
   Iterator(T* curr):current(curr)
   {
   }
   Iterator& operator =(const Iterator& other)
   {
       if (this != &other)
       {
           current = other.current;
       }
       return *this;
   }
   Iterator& operator ++()
   {
       ++current;
       return *this;
   }
   Iterator operator ++(int i)
   {
       Iterator tmp(current);
       ++current;
       return tmp;
   }
   T& operator *()
   {
      return *current;
   }
   T* operator ->()
   {
      return current;
   }
   bool operator ==(const Iterator& other)
   {
      return current == other.current;
   }
   bool operator !=(const Iterator& other)
   {
      return !(*this == other);
   }
private:
   T* current;
};
 

#endif
