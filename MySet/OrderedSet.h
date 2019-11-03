#pragma once
#include <memory>
#include <iostream>
#include <algorithm>
#include "MySet.h"

using namespace std;

class OrderedSet : public Set {

	size_t m_start;

public:

	OrderedSet();
	OrderedSet(size_t size);
	OrderedSet(const OrderedSet& s);
	OrderedSet(const initializer_list<int>& initlist);

	OrderedSet(const int* values, size_t size);

	int* begin() const override;

	void setSort();

	// gibt eine neue Menge zurueck, die alle Elemente von this enthaelt,
	// die (strikt) kleiner als x sind
	OrderedSet getSmaller(int x) const;
	// gibt eine neue Menge zurueck, die alle Elemente von this enthaelt,
	// die (strikt) groesser als x sind
	OrderedSet getLarger(int x) const;
	void setStart(size_t start) { m_start = start; }
	void setSize(size_t size) { m_size = size; }

	Set merge(const Set& set) const override;
};