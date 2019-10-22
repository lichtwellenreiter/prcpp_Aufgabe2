#include <iostream>
#include "../MySet/MySet.h"
using namespace std;
int main() {
	/*
	Set s1;
	Set s11(s1);
	Set s2({ 1,2,3 }); // Initializer List
	Set s21(s2);
	Set s22 = s2;
	Set s3({ 1,2,3,3,2,1,2,3,4 });
	size_t groesse = s2.size();
	cout << groesse << endl;
	cout << s2 << endl;
	cout << s21 << endl;
	cout << s3 << endl;
	bool res1 = s2.containsAll(s1);
	bool res = s2.contains(4);
	cout << res1 << endl;
	cout << res << endl;
	*/
	Set s; // bewusst in 2 Schritten
	s = Set::difference(Set({ 1,2,3 }), Set({ 2,3,4 }));
	cout << s << endl;

	return 0;
}