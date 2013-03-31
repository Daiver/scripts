#ifndef __LISTITEM_H__
#define __LISTITEM_H__

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
class ListItemIterator
{
public:
    ListItemIterator(ListItem<K, V>* item)
    {
        inner_item = item;
    }

    ListItemIterator& operator++ (int)
    {
        ListItemIterator<K, V> tmp(*this);
        if(NULL != this->inner_item)
            this->inner_item = this->inner_item->next;
        return tmp;

    }
    
    V& operator *()
    {
        return this->inner_item->value;
    }

    ListItemIterator& operator++ ()
    {
        if(NULL != this->inner_item)
            this->inner_item = this->inner_item->next;
        return *this;
    }

    bool operator==(const ListItemIterator<K, V>& o) const
    {
        return this->inner_item == o.inner_item;
    }
    bool operator!=(const ListItemIterator<K, V>& o) const { return !(*this == o); }


protected:
    ListItem<K, V> *inner_item;
};


#endif

