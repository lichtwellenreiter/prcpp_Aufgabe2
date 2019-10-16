#include <iostream>
#include "../MySet/MySet.h"
using namespace std;
int main() {
	Set s1;
	Set s11(s1);
	Set s2({ 1,2,3 }); // Initializer List
	Set s21(s2);
	Set s22 = s2;
	
	return 0;
}