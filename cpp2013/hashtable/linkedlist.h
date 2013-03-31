#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>
#include "listitem.h"

template <class K, class V>
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    ListItemIterator<K, V> begin();
    ListItemIterator<K, V> end();
    bool erase(const K& key);
    ListItem<K, V> *find(const K& key);
    ListItem<K, V> *add(const K& key, const V& value);
    ListItem<K, V> *add(ListItem<K, V> *tmp);
    long size();

private:
    ListItem<K, V> *tail;
    long _size;
};

template<class K, class V>
LinkedList<K, V>::LinkedList()
{
    this->tail = NULL;
    this->_size = 0;
}

template<class K, class V>
LinkedList<K, V>::~LinkedList()
{
    ListItem<K, V> *tmp = this->tail;
    while(tmp != NULL)
    {
        ListItem<K, V> *tmp2 = tmp;
        tmp = tmp->next;
        delete tmp2;
    }
}

template<class K, class V>
ListItemIterator<K, V> LinkedList<K, V>::begin()
{
    return ListItemIterator<K, V>(this->tail);
}

template<class K, class V>
ListItemIterator<K, V> LinkedList<K, V>::end()
{
    return ListItemIterator<K, V>(NULL);
}

template<class K, class V>
ListItem<K, V> *LinkedList<K, V>::find(const K& key)
{
    ListItem<K, V> *tmp = this->tail;
    while((tmp != NULL) && (tmp->key != key))
        tmp = tmp->next;
    return tmp;
}

template<class K, class V>
bool LinkedList<K, V>::erase(const K& key)
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

template<class K, class V>
long LinkedList<K, V>::size()
{
    return this->_size;
}

template<class K, class V>
ListItem<K, V> *LinkedList<K, V>::add(ListItem<K, V> *tmp)
{
    tmp->next = this->tail;
    this->tail = tmp;
    this->_size++;
    return tmp;
}

template<class K, class V>
ListItem<K, V> *LinkedList<K, V>::add(const K& key, const V& value)
{
    ListItem<K, V> *tmp = new ListItem<K, V>(key, value);
    return this->add(tmp);
}

#endif
