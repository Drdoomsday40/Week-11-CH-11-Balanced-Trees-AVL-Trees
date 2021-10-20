// Written by: Michael Main (main@colorado.edu) - Nov 4, 1997
// Non-interactive test program for the PriorityQueue class.
//
// DESCRIPTION:
// Each function of this program tests part of the
// PriorityQueue class, returning
// some number of points to indicate how much of the test was passed.
// A description and result of each test is printed to cout.
// Maximum number of points awarded by this program is determined by the
// constants POINTS[1], POINTS[2]...
//
// Note: At the moment, there is just one test function, test1( ) which
// tests all the member functions. Additional tests could be added in the
// future.

#include <iostream>   // Provides cout.
#include <cstdlib>    // Provides size_t and qsort.
#include "pqueue2.h"  // Provides the PriorityQueue class with int items
using namespace std;  // and unsigned ints for priorities. 

// Descriptions and points for each of the tests:
const size_t MANY_TESTS = 1;
const int POINTS[MANY_TESTS+1] = {
    25,  // Total points for all tests.
    25  // Test 1 points.
};
const char DESCRIPTION[MANY_TESTS+1][256] = {
    "tests for the Priority Queue",
    "Testing all the member functions"
};


// **************************************************************************
// bool correct(PriorityQueue& test, size_t n, int items[])
//   This function determines if the PriorityQueue (test) is "correct"
//   according to these requirements:
//   a. it has exactly n items.
//   b. the items (as obtained by get_front) are equal to
//      int[0] ... int[n-1]
// The function returns true if these requirements are met, otherwise the
// function returns false.
// NOTE: All items are removed from the list during a successful test.
// **************************************************************************
bool correct(PriorityQueue& test, size_t n, int items[])
{
    size_t i;
    bool answer = true;
    if (test.size( ) != n)
        answer = false;
    else if (test.is_empty( ) != (n == 0))
        answer = false;
    else
        for (i = 0; answer && (i < n); i++)
	{
            if (items[i] != test.get_front( ))
                answer = false;
        }
    cout << (answer ? "Test passed.\n" : "Test failed.\n") << endl;
    return answer;
}

int compar(const void* ptr1, const void* ptr2)
// Precondition: Neither ptr1 nor ptr2 is NULL.
// Postcondition: The function returns (*ptr2) - (*ptr1), which is useful
// for the quicksort used in test1.
{
    return (*static_cast<const int*>(ptr2)) - (*static_cast<const int*>(ptr1));
}

int test1( )
// Postcondition: A handful of simple tests have been run on the 
// PriorityQueue data type. If all tests are passed, then the function
// returns 100. Otherwise the function returns zero.
{
    const size_t TESTSIZE = 3000;
    
    PriorityQueue test;
    int items[8] = { 100, 200, 3, 4, 5, 6, 8, 7 };
    int rand_items[TESTSIZE];
    char test_letter = 'A';
    int i;

    cout << test_letter++ << ". ";
    cout << "Testing size and is_empty for an empty priority queue.";
    cout << endl;
    if (!correct(test, 0, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Adding one item to the queue, and then testing\n";
    cout << "   is_empty, size, and get_front.";
    cout << endl;
    test.insert(100, 1);
    if (!correct(test, 1, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting two items (first has higher priority).\n";
    cout << "   Then checking that both items come out correctly.";
    cout << endl;
    test.insert(100, 10);
    test.insert(200, 5);
    if (!correct(test, 2, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting two items (second has higher priority).\n";
    cout << "   Then checking that both items come out correctly.";
    cout << endl;
    test.insert(200, 5);
    test.insert(100, 10);
    if (!correct(test, 2, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting eight items with priorities of\n";
    cout << "   8, 10, 4, 3, 7, 6, 9, 5 (in that order)\n";
    cout << "   Then checking that all items come out correctly.";
    cout << endl;
    test.insert(3, 8);
    test.insert(100, 10);
    test.insert(8, 4);
    test.insert(7, 3);
    test.insert(4, 7);
    test.insert(5, 6);
    test.insert(200, 9);
    test.insert(6, 5);
    if (!correct(test, 8, items)) return 0;

    cout << test_letter++ << ". ";
    cout << "Inserting " << TESTSIZE << " random items with random\n";
    cout << "   priorities, and checking that all items come out right.";
    cout << endl;
    for (i = 0; i < (int) TESTSIZE; i++)
    {
        // Insert a bunch of random items, using items themselves as priorities
        rand_items[i] = rand( ) % 100;
        test.insert(rand_items[i], unsigned(rand_items[i]));
    }
    qsort(rand_items, TESTSIZE, sizeof(int), compar); // Sorts from high-low
    if (!correct(test, TESTSIZE, rand_items)) return 0;

    return POINTS[1];
}


int run_a_test(int number, const char message[], int test_function( ), int max)
{
    int result;
    
    cout << endl << "START OF TEST " << number << ":" << endl;
    cout << message << " (" << max << " points)." << endl;
    result = test_function( );
    if (result > 0)
    {
	cout << "Test " << number << " got " << result << " points";
	cout << " out of a possible " << max << "." << endl;
    }
    else
	cout << "Test " << number << " failed." << endl;
    cout << "END OF TEST " << number << "." << endl << endl;
    
    return result;
}


// **************************************************************************
// int main( )
//   The main program calls all tests and prints the sum of all points
//   earned from the tests.
// **************************************************************************
int main( )
{
    int sum = 0;
    
    cout << "Running " << DESCRIPTION[0] << endl;

    sum += run_a_test(1, DESCRIPTION[1], test1, POINTS[1]);

    cout << "If you submit this List to Dora now, you will have\n";
    cout << sum << " points out of the " << POINTS[0];
    cout << " points from this test program.\n";
    
    return EXIT_SUCCESS;

}
