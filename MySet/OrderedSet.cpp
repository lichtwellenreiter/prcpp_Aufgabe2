#include "OrderedSet.h"
#include <iostream>
#include <memory>
#include <initializer_list>
#include <algorithm>

using namespace std;


OrderedSet::OrderedSet()
	: Set::Set(), m_start(0)
{
	cout << "std ctor" << endl;
}

OrderedSet::OrderedSet(size_t size) 
	: Set(size), m_start(0)
{

}

OrderedSet::OrderedSet(const OrderedSet& s)
	: Set::Set(s), m_start(0)
{
	setSort();
	cout << "copy ctor" << endl;
}

OrderedSet::OrderedSet(const initializer_list<int>& initlist)
	: Set::Set(initlist), m_start(0)
{
	setSort();
}

OrderedSet::OrderedSet(const int* values, size_t size) 
	: Set(values, size), m_start(0) 
{ 
	setSort(); 
}

int* OrderedSet::begin() const
{
	return m_values.get() + m_start;
}

void OrderedSet::setSort() {
	int* beg = begin(); 
	std::sort(beg, beg + m_size);
}

OrderedSet OrderedSet::getSmaller(int x) const
{
	for (size_t i = 0; i < m_size; i++) {
		if ((*this)[i] >= x) {
			return OrderedSet(begin(), i);
		}
	}
	return *this;
}


OrderedSet OrderedSet::getLarger(int x) const
{
	for (size_t i = 0; i < m_size; i++) {
		if ((*this)[i] > x) {
			return OrderedSet(begin() + i, m_size - i);
		}
	}

	return OrderedSet();
}

Set OrderedSet::merge(const Set& set) const
{
	const auto *s = dynamic_cast<const OrderedSet*>(&set);
	if (s == nullptr) {
		return Set::merge(set);
	}
	if (set.size() == 0) {
		return *this;
	}
	if (this->size() == 0) {
		return set;
	}
	OrderedSet set1 = (*s), result(size() + set1.size());
	int* pt = begin(), * ps = set1.begin();
	size_t i = 0, j = 0;
	size_t tS = size(), sS = set1.size();
	while (i < tS || j < sS) {
		int iVal = pt[i], jVal = ps[j], val;
		if (i < tS && j < sS) {
			if (iVal <= jVal) { 
				val = iVal; i++; 
			}
			if (iVal >= jVal) { 
				val = jVal; j++; 
			}
		}
		else if (j < sS) {
			val = jVal; j++;
		} 
		else if (i < tS) {
			val = iVal; i++;
		}

		result[result.m_size++] = val;
	} 
	
	return result;

}


