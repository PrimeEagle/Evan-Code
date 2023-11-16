/*
 * project2.cpp
 *
 * The implementation file where you will implement your code for Project 2.
 *
 * INSTRUCTOR NOTE: Do not change any of the existing function signatures in
 * this file. You may add helper functions for
 * any function other than Sum in Question 1.
 */

#include "recursive_list.h"
#include "project2.h"

 /** QUESTION 1: SUM AND PRODUCT **/

 // EFFECTS: returns the sum of each element in list, or zero if the list is
 //          empty
 // Your implementation of Sum should NOT be tail recursive and should NOT
 // use a helper function. 
 //
 // PSEUDOCODE:
 // algorithm Sum
 //   Your pseudocode goes here. You do not need to define inputs, outputs, or
 //   side effects, since the requires, modifies, and effects statements are
 //   already provided above.
 //
 // COMMENTS:
 // Add comments here that might help us to understand your thought process,
 // especially if you're unable to finish the pseudocode or code. This can help
 // us award points in the code logic category.
int Sum(RecursiveList list) {
	if (ListIsEmpty(list)) {
		return 0;
	}
	
	return ListFirst(list) + Sum(ListRest(list));
}

// EFFECTS: returns the product of each element in list, or one if the list is
//          empty
//
// PSEUDOCODE:
// algorithm Product
//   Your pseudocode goes here. You do not need to define inputs, outputs, or
//   side effects, since the requires, modifies, and effects statements are
//   already provided above.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
int Product(RecursiveList list) {
	if (ListIsEmpty(list)) {
		return 1;
	}

	return ListFirst(list) * Product(ListRest(list));
}


/** QUESTION 2: TAIL RECURSIVE SUM **/

// EFFECTS: adds the next element in the list to the sum so far
// Your implementation of TailRecursiveSumHelper MUST be tail recursive.
//
// PSEUDOCODE:
// algorithm TailRecursiveSumHelper
//   Your pseudocode goes here. You do not need to define inputs, outputs, or
//   side effects, since the requires, modifies, and effects statements are
//   already provided above.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
int TailRecursiveSumHelper(RecursiveList list, int sum_so_far) {
	if (ListIsEmpty(list)) {
		return sum_so_far;
	}

	return TailRecursiveSumHelper(ListRest(list), sum_so_far + ListFirst(list));
}

// EFFECTS: returns the sum of each element in list, or zero if the list is
//          empty
// 
// THIS FUNCTION IS PROVIDED AS PART OF THE STARTER CODE.
// DO NOT MODIFY THIS FUNCTION.
// 
// PSEUDOCODE:
// algorithm TailRecursiveSum
//   return TailRecursiveSumHelper(list, 0)
int TailRecursiveSum(RecursiveList list) {
	return TailRecursiveSumHelper(list, 0);
}


/** QUESTION 3: FILTER ODD AND FILTER EVEN **/

// EFFECTS: returns a new list containing only the elements of the original list
//          which are odd in value, in the order in which they appeared in list
// For example, FilterOdd(( 4 1 3 0 )) would return the list ( 1 3 )
//
// PSEUDOCODE:
// algorithm FilterOdd
//   Your pseudocode goes here. You do not need to define inputs, outputs, or
//   side effects, since the requires, modifies, and effects statements are
//   already provided above.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
RecursiveList FilterOdd(RecursiveList list) {
	if (ListIsEmpty(list)) {
		return list;
	}

	int first = ListFirst(list);
	if (first % 2 == 0) {
		return FilterOdd(ListRest(list));
	}
	else {
		return MakeList(first, FilterOdd(ListRest(list)));
	}
}

// EFFECTS: returns a new list containing only the elements of the original list
//          which are even in value, in the order in which they appeared in list
// For example, FilterEven(( 4 1 3 0 )) would return the list ( 4 0 )
//
// PSEUDOCODE:
// algorithm FilterEven
//   Your pseudocode goes here. You do not need to define inputs, outputs, or
//   side effects, since the requires, modifies, and effects statements are
//   already provided above.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
RecursiveList FilterEven(RecursiveList list) {
	if (ListIsEmpty(list)) {
		return list;
	}

	int first = ListFirst(list);
	if (first % 2 != 0) {
		return FilterEven(ListRest(list));
	}
	else {
		return MakeList(first, FilterEven(ListRest(list)));
	}
}

int ListSize(RecursiveList list, int n = 0) {
	if (ListIsEmpty(list)) {
		return n;
	}

	ListSize(ListRest(list), n + 1);
}

int ListLast(RecursiveList list) {
	int n = ListSize(list);

	if (n == 1) {
		return ListFirst(list);
	}
	else {
		return ListLast(ListRest(list));
	}
}



/** QUESTION 4: REVERSE **/

// EFFECTS: returns the reverse of list
// For example, the reverse of ( 3 2 1 ) is ( 1 2 3 )
//
// PSEUDOCODE:
// algorithm Reverse
//   Your pseudocode goes here. You do not need to define inputs, outputs, or
//   side effects, since the requires, modifies, and effects statements are
//   already provided above.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
RecursiveList Reverse(RecursiveList list) {
	int n = ListSize(list);

	if (n < 2) {
		return list;
	}
	int first = ListFirst(list);
	RecursiveList rest = ListRest(list);
	RecursiveList empty_list = MakeList();


	return Append(Reverse(rest), MakeList(first, empty_list));
}


/** QUESTION 5: APPEND **/

// EFFECTS: returns the list (first_list second_list)
// For example, if first_list is ( 1 2 3 ) and second_list is ( 4 5 6 ), then
// returns ( 1 2 3 4 5 6 )
//
// PSEUDOCODE:
// algorithm Append
//   Your pseudocode goes here. You do not need to define inputs, outputs, or
//   side effects, since the requires, modifies, and effects statements are
//   already provided above.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
RecursiveList Append(RecursiveList first_list, RecursiveList second_list) {
	if (ListIsEmpty(first_list)) {
		return second_list;
	}
	
	RecursiveList rev_first_list = Reverse(first_list);
	int first_list_last_elem = ListFirst(rev_first_list);
	RecursiveList new_second_list = MakeList(first_list_last_elem, second_list);
	
	return Append(Reverse(ListRest(rev_first_list)), new_second_list);
}


/** QUESTION 6: CHOP **/

// REQUIRES: list has at least n elements
// EFFECTS: returns the list equal to list without its last n elements
//
// PSEUDOCODE:
// algorithm Chop
//   Your pseudocode goes here. You do not need to define inputs, outputs, or
//   side effects, since the requires, modifies, and effects statements are
//   already provided above.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
RecursiveList Chop(RecursiveList list, unsigned int n) {
	if (n < 1) {
		return list;
	}

	RecursiveList rev_list = Reverse(list);
	RecursiveList new_list = ListRest(rev_list);

	return Chop(Reverse(new_list), n - 1);
}


/** QUESTION 7: ROTATE **/

// EFFECTS: returns a list equal to the original list with the
//          first element moved to the end of the list n times.
// For example, Rotate(( 1 2 3 4 5 ), 2) yields ( 3 4 5 1 2 )
//
// PSEUDOCODE:
// algorithm Rotate
//   Your pseudocode goes here. You do not need to define inputs, outputs, or
//   side effects, since the requires, modifies, and effects statements are
//   already provided above.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
RecursiveList Rotate(RecursiveList list, unsigned int n) {
	if (n == 0) {
		return list;
	}

	int first = ListFirst(list);
	RecursiveList empty_list = MakeList();
	RecursiveList new_list = Append(ListRest(list), MakeList(first, empty_list));
	
	return Rotate(new_list, n - 1);
}


/** QUESTION 8: INSERT LIST **/

// REQUIRES: n <= the number of elements in first_list
// EFFECTS: returns a list comprising the first n elements of first_list,
//          followed by all elements of second_list, followed by any remaining
//          elements of "first_list"
// For example, InsertList (( 1 2 3 ), ( 4 5 6 ), 2) returns ( 1 2 4 5 6 3 )
//
// PSEUDOCODE:
// algorithm InsertList
//   Your pseudocode goes here. You do not need to define inputs, outputs, or
//   side effects, since the requires, modifies, and effects statements are
//   already provided above.
//
// COMMENTS:
// Add comments here that might help us to understand your thought process,
// especially if you're unable to finish the pseudocode or code. This can help
// us award points in the code logic category.
RecursiveList InsertList(RecursiveList first_list, RecursiveList second_list,
	unsigned int n) {
	
	if (n == 0) {
		return Append(second_list, first_list);
	}

	int first_element = ListFirst(first_list);

	return MakeList(first_element, InsertList(ListRest(first_list), second_list, n - 1));
}