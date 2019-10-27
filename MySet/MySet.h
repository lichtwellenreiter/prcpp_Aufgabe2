#pragma once
#include <memory>
#include <iostream>

using namespace std;

class Set {
protected:
	// protected Datenstruktur (erlaubt Vererbung)
	size_t m_size;
	shared_ptr<int[]> m_values;
	explicit Set(size_t size);
	
	// geschützte Instanzmethoden
	int* begin() const; // gibt einen Zeiger auf das erste Element
						// der Menge zurueck (nullptr falls leer)
	int operator[](size_t i) const; // gibt das i-te Element des Mengen-Arrays
	int& operator[](size_t i);
	// zurueck

	Set merge(const Set& set) const; // gibt als neue Menge die Vereinigungs-
	// menge dieser Menge mit set zurueck
	Set difference(const Set& set) const; // gibt als neue Menge die Differenzmenge
	Set difference(Set&& set) const;
	// zwischen set und dieser Menge
	// (set \ this) zurueck
	Set intersection(const Set& set) const; // gibt als neue Menge die Schnittmenge
	Set intersection(Set&& set) const;
	// dieser Menge mit set zurueck
	
public:
	// öffentliche Methoden

	// Kostruktoren und Destruktor
	Set();
	Set(const Set& s);
	Set(const initializer_list<int>& initlist);
	~Set();
	
	// Instanzmethoden
	bool contains(int e) const; // testet, ob die Menge e enthaelt
	// testet, ob diese Menge alle Elemente der
	// anderen Menge enthaelt (und somit
	// dessen Supermenge ist)
	bool containsAll(const Set& set) const;
	bool isEmpty() const; // testet, ob die Menge leer ist
	size_t size() const; // gibt Anzahl Elemente in der Menge zurueck
	// Gleichheitsoperator ('equals' in Java)
	// (Inline - Implementation schon gegeben)
	bool operator==(const Set& set) const
	{
		return size() == set.size() && containsAll(set) && set.containsAll(*this);
	}
	
	// Ausgabe-Operator für Output-Streams (Inline-Implementation schon gegeben)
	friend ostream& operator<<(ostream& os, const Set& s) {
		const int* const vptr = s.begin();
		os << "{";
		if (!s.isEmpty()) os << vptr[0];
		for (size_t i = 1; i < s.m_size; ++i) { os << ", " << vptr[i]; }
		os << "}";
		return os;
	}
	

	// Klassen-Methoden
	// Vereinigungsmenge (die Bezeichnung union ist nicht möglich)
	static Set merge(const Set& set1, const Set& set2) { return set1.merge(set2); }
	// Differenzmenge set1\set2
	static Set difference(const Set& set1, const Set& set2)
	{
		return set2.difference(set1);
	}
	// Schnittmenge
	static Set intersection(const Set& set1, const Set& set2)
	{
		return set1.intersection(set2);
	}

	// Differenzmenge set1\set2
	static Set difference(Set&& set1, const Set& set2)
	{
		return set2.difference(move(set1));
	}
	static Set difference(Set&& set1, Set&& set2)
	{
		return set2.difference(move(set1));
	}
	// Schnittmenge
	static Set intersection(const Set& set1, Set&& set2)
	{
		return set1.intersection(move(set2));
	}
	static Set intersection(Set&& set1, const Set& set2)
	{
		return set2.intersection(move(set1));
	}
	static Set intersection(Set&& set1, Set&& set2)
	{
		return set1.intersection(move(set2));
	}
	
};