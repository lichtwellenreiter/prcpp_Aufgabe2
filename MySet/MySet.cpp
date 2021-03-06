#include "MySet.h"
#include <iostream>
#include <memory>
#include <initializer_list>

using namespace std;

Set::Set(size_t size) 
	: m_values(new int[size], default_delete<int[]>()), m_size(0)
{
	cout << "private-ctor " << endl;
}

int* Set::begin() const
{
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
	std::copy_n(begin(), m_size, result.begin());
	result.m_size = m_size;
	// fuege nur jene Elemente von set dazu, die in this noch nicht enthalten sind
	for (size_t i = 0; i < set.m_size; ++i) {
		if (!contains(set[i])) result[result.m_size++] = set[i];
	}
	return result;
}

Set Set::difference(const Set& set) const
{
	Set res(set.m_size);
	for (auto i = 0; i < set.m_size; i++) {
		if (!this->contains(set[i])) res[res.m_size++] = set[i];
	}
	return res;
}

Set Set::difference(Set&& set) const {
	if (set.m_values.use_count() == 1) {
		const size_t startSize = set.m_size;
		set.m_size = 0;
		for (auto i = 0; i < startSize; i++) {
			if (!this->contains(set[i])) {
				set[set.m_size] = set[i];
				set.m_size++;
			}
		}
		return set;
	}
	return difference(set);
}

Set Set::intersection(const Set& set) const
{
	Set res(m_size);
	for (auto i = 0; i < set.m_size; i++) {
		if (this->contains(set[i])) res[res.m_size++] = set[i];
	}
	return res;
}

Set Set::intersection(Set&& set) const 
{
	if (set.m_values.use_count() == 1) {
		const size_t startSize = set.m_size;
		set.m_size = 0;
		for (auto i = 0; i < startSize; i++) {
			if (this->contains(set[i])) {
				set[set.m_size] = set[i];
				set.m_size++;
			}
		}
		return set;
	}
	return intersection(set);
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

Set::Set(const int* values, size_t size)
	:Set(size)
{
	for (auto i = 0; i < size; i++) {
		if (!contains(values[i])) {
			m_values[m_size++] = values[i];			
		}
	}
	cout << "ctor with size" << endl;
}

bool Set::contains(int e) const
{
	for (auto i = 0; i < this->m_size; ++i) {
		if ((*this)[i] == e) return true;
	}
	return false;
}

bool Set::containsAll(const Set& set) const
{
	if (set.isEmpty()) return true;
	for (auto i = 0; i < set.size(); i++) {
		if (!contains(set[i]))
			return false;
	}
	return true;
}

bool Set::isEmpty() const {
	return m_size == 0;
}

size_t Set::size() const
{
	return this->m_size;
}

Set::~Set()
{
	cout << "dtor" << endl;
	m_values.reset();
}