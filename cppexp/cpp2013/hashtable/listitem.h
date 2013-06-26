#ifndef __LISTITEM_H__
#define __LISTITEM_H__

template <class K, class V>
class ListItem
{
public:
    ListItem(const K &key, const V &value);

    ListItem<K, V> *next;
    K key;
    V value;
};

template<class K, class V>
ListItem<K, V>::ListItem(const K &key, const V &value)
{
    this->value = value;
    this->key = key;
    this->next = NULL;
}

template <class K, class V>
class ListItemIterator
{
public:
    ListItemIterator(ListItem<K, V>* item);

    ListItemIterator& operator++ (int);
    V& operator *();
    ListItemIterator& operator++ ();
    bool operator==(const ListItemIterator<K, V>& o) const;
    bool operator!=(const ListItemIterator<K, V>& o) const;
    ListItem<K, V> *getInner();

protected:
    ListItem<K, V> *inner_item;
};

template<class K, class V>
ListItem<K, V> *ListItemIterator<K, V>::getInner()
{
    return this->inner_item;
}

template<class K, class V>
ListItemIterator<K, V>::ListItemIterator(ListItem<K, V>* item)
{
    inner_item = item;
}

template<class K, class V>
ListItemIterator<K, V>& ListItemIterator<K, V>::operator++ (int)
{
    ListItemIterator<K, V> tmp(*this);
    if(NULL != this->inner_item)
        this->inner_item = this->inner_item->next;
    return tmp;
}

template<class K, class V>
V& ListItemIterator<K, V>::operator *()
{
    return this->inner_item->value;
}

template<class K, class V>
ListItemIterator<K, V>& ListItemIterator<K, V>::operator++ ()
{
    if(NULL != this->inner_item)
        this->inner_item = this->inner_item->next;
    return *this;
}

template<class K, class V>
bool ListItemIterator<K, V>::operator==(const ListItemIterator<K, V>& o) const 
{
    return this->inner_item == o.inner_item;
}

template<class K, class V>
bool ListItemIterator<K, V>::operator!=(const ListItemIterator<K, V>& o) const 
{ 
    return !(*this == o); 
}

#endif

