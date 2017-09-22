
#include "Sequence.h"
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

void load(ItemType load[], int loadSize, Sequence& s) {
	ItemType last = load[loadSize - 1];
	s.insert(last);
	for (int j = loadSize - 2; j >= 0; j--) {
		s.insert(0, load[j]);
	}
}

int main()
{
	Sequence s;
	Sequence s2;

	/*
	ItemType testArray[7] = {"HAHA", "lmao", "xd", "xd2", "yo", "HeHe", "vince" };
	load(testArray, 7, s);
	printDat(s);
	cout << "sequence size: " << s.size() << endl;
	*/


	//const func test: empty, size, get, find

	assert(s.empty());
	assert(s.find(3) == -1);
	ItemType testArray[7] = { 34, 5436, 4356, 890, 23, 43, 6 };
	load(testArray, 7, s);
	assert(s.size() == 7 && s.find(5436) == 1);
	ItemType test;
	s.get(3, test);
	assert(test == 890);
	assert(s.find(23) == 4);

	cout << "Passed all const" << endl;




	//non-const func test: erase, remove, swap
	//ItemType testArray[2] = { "one", "two" };
	//load(testArray, 2, s);
	ItemType testArray2[7] = { 5, 3, 1, 7, 6, 2, 4 };
	//load(testArray2, 7, s2);
	for (int i = 0; i < 7; i++) {
		s2.insert(testArray2[i]);
	}
	//s2.erase(1);
	//printDat(s2);
	//cout << "removed: " << s2.remove("xd") << endl;
	printDat(s2);


	//swap test
	s.swap(s2);
	cout << "s:" << endl;
	printDat(s);
	cout << "s2:" << endl;
	printDat(s2);


}

