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
/*
int* Set::begin() const
{
	if (m_size == 0) {
		return nullptr;
	}
	return shared_ptr<int>(m_values);
}
*/
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
	: Set(static_cast<int>(initlist.size()))
{
	cout << "type conversion constructor" << endl;
	int count = 0;
	for (auto& element : initlist)
	{
		m_values[count] = element;
		++count;
	}
	/*
	for (auto ptr = initlist.begin(); ptr < initlist.end(); ptr++) {
		m_values[m_size++] = *ptr;
	}*/
}
/*
Set::~Set()
{
	cout << "free" << endl;
	delete[] &m_values;
}
*/



