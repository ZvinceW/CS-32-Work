#include <iostream>
using namespace std;

bool somePredicate(double x)
{
	return x > 0;
}



// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
	//stoping condition
	if (n == 1)
	{
		return somePredicate(a[0]);
	}
	
	
	//recursion
	bool B1 = allTrue(a, n / 2);
	//delete a1;  //no memory leak pls
	bool B2 = allTrue(a + n / 2, n - n / 2);
	//delete a2;  //no memory leak pls

	return (B1 && B2);  // if either B1 or B2 is false, the statement will return false
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
	if (n == 1)  //stopping condition
	{
		if (!somePredicate(a[0]))
		{
			return 1;
		}
		else 
		{
			return 0;
		}
	}
	
	//recursion
	int I1 = countFalse(a, n / 2);
	//delete a1;  //no memory leak pls
	int I2 = countFalse(a + n/2, n - n / 2);
	//delete a2;  //no memory leak pls

	return (I1 + I2);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
	if (n == 1)
	{
		if (!somePredicate(a[0]))
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		//recursion
		int I1 = firstFalse(a, n / 2);
		//delete a1;  //no memory leaks
		int I2 = firstFalse(a + n/2, n - n / 2);
		//delete a2; //no memory leaks
		if (I1 == -1 && I2 == -1) //a false doesnt exist
		{
			return -1;  //return -1
		}
		else if (I1 == -1)  //first half is all true -> the false is in second half
		{
			return n / 2 + I2; //return index of false in second half + length of first half = index of false in the full array
		}
		else if (I2 == -1) //second half is all true -> the false is in first half
		{
			return I1; //return the index of false in first half
		}
		else //false exist in both halves
		{
			return I1; //return the false in first half b/c thats always gonna come before the false in the second half
		}
	}
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
	if (n == 0) //empty list
	{
		return -1;
	}
	else if (n == 1) //the smallest value in an 1-item array is that 1-item
	{
		return 0;
	}
	else if (n == 2) //what happens when u only have 2 items? -> only two possible cases
	{
		if (a[0] <= a[1]) //first item is smaller or two items are equal -> return index of 0
		{
			return 0;
		}
		else //second item is smaller -> return index of 1
		{
			return 1;
		}
	}
	else if (n >= 3)
	{
		//recursion
		int I1 = indexOfMin(a, n / 2);
		//delete a1;
		int I2 = indexOfMin(a + n / 2, n - n / 2);
		//delete a2;
		if (a[I1] <= a[n / 2 + I2]) //compare the result from both halves and find the index that represent the smaller value
		{
			return I1; //result from first half is smaller -> return that index
		}
		else 
		{
			return n / 2 + I2;  //result from second half is smaller -> return that value + the length of first half = the actual location of the value in the full array
		}
	}
	return -1;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 == 0)
	{
		return false;
	}
	else if (n2 > n1)
	{
		return false;
	}
	else if (n1 == 0)
	{
		return false;
	}
	else
	{
		bool gotIt;
		if (a2[0] == a1[0])
		{
			if (n2 == 1)
			{
				return true;
			}
			gotIt = includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
		}
		else
		{
			gotIt = includes(a1 + 1, n1 - 1, a2, n2);
		}
		return gotIt;
	}
}


int main()
{
	double a1[5] = { 5, -2, 6, 2, -1 };
	int n1 = 5;
	double a2[2] = { 2, -1 };
	int n2 = 2;
	cout << allTrue(a1, 5) << endl; //0
	cout << countFalse(a1, 5) << endl; //2 
	cout << indexOfMin(a1, 5) << endl; //1
	cout << firstFalse(a1, 5) << endl; //1
	cout << includes(a1, n1, a2, n2) << endl; //1
}