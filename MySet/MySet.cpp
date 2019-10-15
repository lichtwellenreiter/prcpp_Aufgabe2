#include "MySet.h"
#include <iostream>
#include <memory>
#include <initializer_list>

using namespace std;

explicit Set::Set(size_t size) 
	: m_values(make_unique<int[]>(size)), m_size(0) {
	cout << "private-ctor " << endl;
}

Set::Set()
{
}

Set::Set(const Set& s)
	: m_values(s.m_values) ,m_size(0)
{
	cout << "copy constructor" << endl;
}

Set::Set(initializer_list<int> i)
{

}

Set::~Set()
{
	cout << "free" << endl;
}


