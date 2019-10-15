#pragma once
#include <memory>

using namespace std;

class Set {
protected:
	// protected Datenstruktur (erlaubt Vererbung)
	size_t m_size;
	shared_ptr<int[]> m_values;
	explicit Set(size_t size);
	
public:
	// öffentliche Methoden
	Set();
	Set(const Set& s);
	Set(initializer_list<int>);
	~Set();
};