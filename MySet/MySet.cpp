#include "MySet.h"
#include <iostream>
#include <memory>
#include <initializer_list>

using namespace std;

Set::Set(size_t size) 
	: m_values(new int[size]), m_size(0) 
{
	cout << "private-ctor " << endl;
}

int* Set::begin() const
{
	if (this->m_size == 0) {
		return nullptr;
	}
	return m_values.get();
}
int Set::operator[](size_t i) const
{
	return *(begin()+i);
}

int& Set::operator[](size_t i)
{
	return *(begin() + i);
}

Set Set::merge(const Set& set) const
{
	// erstelle eine neue Menge mit allen Elementen von this
	Set result(m_size + set.m_size);
	copy_n(begin(), m_size, result.begin());
	result.m_size = m_size;
	// fuege nur jene Elemente von set dazu, die in this noch nicht enthalten sind
	for (size_t i = 0; i < set.m_size; ++i) {
		if (!contains(set[i])) result[result.m_size++] = set[i];
	}
	return result;
}

Set Set::difference(const Set& set) const
{
	Set res(size() + set.size());
	for (auto i = 0; i < set.m_size; i++) {
		if (!contains(set[i])) res[res.m_size++] = set[i];
	}
	return res;
}

Set Set::intersection(const Set& set) const
{
	Set res(size() + set.size());
	for (auto i = 0; i < set.m_size; i++) {
		if (contains(set[i])) res[res.m_size++] = set[i];
	}
	return res;
}

Set::Set()
	: m_size(0)
{
}

Set::Set(const Set& s)
	: m_values(s.m_values), m_size(s.m_size)
{
	cout << "copy constructor" << endl;
}

Set::Set(const initializer_list<int> &initlist)
	: Set(initlist.size())
{
	cout << "type conversion constructor" << endl;

	for (auto ptr = initlist.begin(); ptr != initlist.end(); ptr++) {
		if(!contains(*ptr)) (*this)[m_size++] = *ptr;
	}
}

bool Set::contains(int e) const
{
	for (size_t i = 0; i < this->m_size; ++i) {
		if (begin()[i] == e) return true;
	}
	return false;
}

bool Set::containsAll(const Set& set) const
{
	if (set.isEmpty()) return true;
	bool res = false;
	for (auto i = 0; i < set.size(); i++) {
		res = contains(set[i]);
	}
	return res;
}

bool Set::isEmpty() const {
	return m_size == 0;
}

size_t Set::size() const
{
	return this->m_size;
}



//

/*
Set::~Set()
{
	cout << "free" << endl;
	delete[] &m_values;
}
*/





