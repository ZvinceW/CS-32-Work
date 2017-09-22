#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
	ScoreList a;
	ScoreList b;
	ScoreList c;

	assert(!a.add(-1) && !a.add(101));
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		a.add(1);
	}
	assert(!a.add(1) && (a.size() == DEFAULT_MAX_ITEMS));
	assert(b.minimum() == NO_SCORE);
	assert(b.maximum() == NO_SCORE);

	unsigned long array[10] = { 10,9,8,7,1,2,3,4,5,6 };
	for (int i = 0; i < 10; i++) {
		c.add(array[i]);
	}

	unsigned long ten = 10;
	unsigned long one = 1;
	unsigned long eleven = 11;

	assert(c.maximum() == ten);
	assert(c.minimum() == one);

	assert(!c.remove(eleven));

	cout << "all test passed" << endl;

}