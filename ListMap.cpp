/**
   Plik do modyfikacji w ramach cwiczenia z AISDI.
   Zawiera niekompletne implementacje metod klasy ListMap,
   oraz mape podobna koncepcyjnie do tej z cwicznia 1 (SmallMap)
   zaimplementowana w jescze bardziej szczatkowy sposob.
   Jest tez prosta funkcja testujaca (void test()), ktora
   jest wolana w funkcji main. Mozna w niej zaimplementowac
   wlasne testy.
   NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY LISTMAP.

   COPYRIGHT:
   Copyright (c) 2015 Instytut Informatyki, Politechnika Warszawska
   ALL RIGHTS RESERVED
*******************************************************************************/

#include <algorithm>
#include <iostream>

#ifndef AISDI_LOCAL
#include "ListMap.h"
#else
#include "ListMap.h"
#endif

ListMap::ListMap()
{
	last = first = NULL;
	last = new Node(std::make_pair(0, ""), NULL, NULL);
	first = last;
	if(last == NULL){
		std::string s = "Nie udalo sie przydzielic pamieci dla listy.";
		throw s;
	}
}

ListMap::ListMap(const ListMap& m)
{
	last = new Node(std::make_pair(0, ""), NULL, NULL);
	first = last;
	if(last == NULL){
		std::string s = "Nie udalo sie przydzielic pamieci dla listy.";
		throw s;
	}
	for(const_iterator it = m.begin(); it != m.end(); it++){
		this->unsafe_insert(*it);
	}
}

ListMap::~ListMap()
{
  clear();
  first = last = NULL;
}

std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
	iterator i = find(entry.first);
	if(i != end())
		return std::make_pair(i, false);
	return std::make_pair(unsafe_insert(entry), true);
}

ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
	if(first == last){
		first = new Node(entry, last, NULL);
		if(first == NULL){
			std::string s = "Nie udalo sie przydzielic pamieci dla nowego wezla.";
			throw s;
		}
		last->prev = first;
		return iterator(first, this);
	}
	last->prev->next = new Node(entry, last, last->prev);
	last->prev = last->prev->next;
	return iterator(last->prev, this);
}

ListMap::iterator ListMap::find(const Key& k)
{
	for(iterator it = begin(); it != end(); it++)
		if(it->first == k)
			return it;
	return end();
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
	for(const_iterator it = begin(); it != end(); it++)
		if(it->first == k)
			return it;
	return end();
}

ListMap::Val& ListMap::operator[](const Key& k)
{
	iterator i = find(k);
	if(i == end())
	{
		std::pair<int , std::string> tmp;
		tmp.first = k;
		tmp.second = "";
		i = unsafe_insert(tmp);
	}
	return i.node->data.second;
}

bool ListMap::empty() const
{
  return first == last;
}

ListMap::size_type ListMap::size() const
{
	size_type n = 0;
	for(const_iterator it = this->begin(); it != this->end(); it++)
		n++;
	return n;
}

ListMap::size_type ListMap::count(const Key& _Key) const
{
	if(find(_Key) == end())
		return 0;
	return 1;
}

ListMap::iterator ListMap::erase(ListMap::iterator i)
{
	Node *tmpnext;
	Node *tmpprev;
	if(i == end())
		return i;
	if(i == begin()){
		tmpnext = first->next;
		first->data.first = 0;
		first->data.second = "";
		delete first;
		first = tmpnext;
		first->prev = NULL;
		return ++i;
	}
	else{
		tmpprev = i.node->prev;
		tmpnext = i.node->next;
		tmpprev->next = tmpnext;
		tmpnext->prev = tmpprev;
		i.node->data.first = 0;
		i.node->data.second = "";
		delete i.node;
	}
	return iterator(tmpnext, this);

}

ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
  return end();
}

ListMap::size_type ListMap::erase(const Key& key)
{
	iterator it = find(key);
	if(it == end())
		return 0;
	erase(it);
	return 1;
}

void ListMap::clear( )
{
	Node *tmp = first;
	while(last != first){
		tmp = tmp->next;
		first->data.first = 0;
		first->data.second = "";
		delete first;
		first = tmp;
	}
	delete last;
	first = last = NULL;
}

bool ListMap::struct_eq(const ListMap& another) const
{
	const_iterator it2 = this->begin();
	const_iterator it1;
	for(it1 = another.begin(); it1 != another.end() && it2 != this->end(); it1++, it2++)
		if(*it1 != *it2)
			return false;
	if(it2 != this->end() || it1 != another.end())
		return false;
	return true;
}

bool ListMap::info_eq(const ListMap& another) const
{
	for(const_iterator it = another.begin(); it != another.end(); it++)
		if(this->find(it.node->data.first) == this->end())
			return false;
	for(const_iterator it = this->begin(); it != this->end(); it++)
		if(another.find(it.node->data.first) == another.end())
			return false;
	return true;
}

// pre
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
	if(node->next != NULL){
		node = node->next;
		return *this;
	}
	return *this;
}

// post
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
	if(node->next != NULL){
		node = node->next;
		return *this;
	}
	return *this;
}

// pre
ListMap::const_iterator& ListMap::const_iterator::operator--()
{
	if(node->prev != NULL){
		node = node->prev;
		return *this;
	}
	return *this;
}

// post
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
	if(node->prev != NULL){
		node = node->prev;
		return *this;
	}
	return *this;
}

ListMap::iterator ListMap::begin()
{
  return iterator(first, this);
}

ListMap::const_iterator ListMap::begin() const
{
	return iterator(first, nullptr);
}

ListMap::iterator ListMap::end()
{
  return iterator(last, this);
}

ListMap::const_iterator ListMap::end() const
{
	return iterator(last, nullptr);
}
