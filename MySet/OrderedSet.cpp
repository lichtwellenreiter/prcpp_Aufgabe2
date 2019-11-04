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
	cout << "ctor with size" << endl;
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
	sort(beg, beg + m_size);
}

OrderedSet OrderedSet::getSmaller(int x) const
{
	for (auto i = 0; i < m_size; i++) {
		if ((*this)[i] >= x) {
			return OrderedSet(begin(), i);
		}
	}
	return *this;
}

OrderedSet OrderedSet::getLarger(int x) const
{
	for (auto i = 0; i < m_size; i++) {
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

	OrderedSet set1 = (*s);
	size_t i = 0;
	size_t j = 0;
	size_t thisSize = size();
	size_t setSize = set1.size();
	OrderedSet res(thisSize + setSize);

	int* pt = begin(); 
	int* ps = set1.begin();
	int value;
	int iValue;
	int jValue;

	while (i < thisSize || j < setSize) {
		iValue = pt[i];
		jValue = ps[j];
		if (i < thisSize && j < setSize) {
			if (iValue <= jValue) {
				value = iValue;
				i++; 
			}

			if (iValue >= jValue) {
				value = jValue;
				j++; 
			}
		}

		else if (j < setSize) {
			value = jValue; j++;
		} 

		else if (i < thisSize) {
			value = iValue; i++;
		}

		res[res.m_size++] = value;
	} 
	return res;
}