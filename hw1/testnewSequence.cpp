#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void printDat(Sequence s) {
	for (int i = 0; i < s.size(); i++) {
		ItemType element;
		s.get(i, element);
		cout << element << ", ";
	}
	cout << endl;
}

int main() {

	Sequence a(1000);   // a can hold at most 1000 items
	Sequence b(5);      // b can hold at most 5 items
	Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
	ItemType v = 1;

	// No failures inserting 5 items into b
	for (int k = 0; k < 5; k++)
		assert(b.insert(k, v));
	printDat(b);


	// Failure if we try to insert a sixth item into b
	assert(!b.insert(5, v));
	cout << "Failure if we try to insert a sixth item into b" << endl;

	assert(!a.insert(1000, v));

	// When two Sequences' contents are swapped, their capacities are
	// swapped as well:
	a.swap(b);
	assert(!a.insert(5, v));
	for (int k = 0; k < 1000; k++)
		assert(b.insert(k, v));
	cout << "swapping test passed" << endl;




	Sequence s;
	Sequence s2(7);

	/*
	ItemType testArray[7] = {"HAHA", "lmao", "xd", "xd2", "yo", "HeHe", "vince" };
	load(testArray, 7, s);
	printDat(s);
	cout << "sequence size: " << s.size() << endl;
	*/


	//const func test: empty, size, get, find
	/*
	assert(s.empty());
	assert(s.find("xd") == -1);
	ItemType testArray[7] = { "HAHA", "lmao", "xd", "xd2", "yo", "HeHe", "vince" };
	load(testArray, 7, s);
	assert(s.size() == 7 && s.find("lmao") == 1);
	ItemType test;
	s.get(3, test);
	assert(test == "xd2");
	assert(s.find("yo") == 4);

	cout << "Passed all const" << endl;
	*/



	//non-const func test: erase, remove, swap
	ItemType testArray[2] = { 1,2 };
	for (int i = 0; i < 2; i++) {
		s.insert(testArray[i]);
	}
	//load(testArray, 2, s);
	ItemType testArray2[7] = { 5, 3, 1, 7, 6, 2, 4 };
	//load(testArray2, 7, s2);
	for (int i = 0; i < 7; i++) {
		s2.insert(testArray2[i]);
	}
	printDat(s2);
	s2.erase(1);
	printDat(s2);
	cout << "removed: " << s2.remove(7) << endl;
	printDat(s2);


	cout << "swap test" << endl;
	//swap test
	s.swap(s2);
	cout << "s:" << endl;
	printDat(s);
	cout << "s2:" << endl;
	printDat(s2);

}