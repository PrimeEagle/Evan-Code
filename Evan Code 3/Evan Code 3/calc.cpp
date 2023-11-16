// Run in repl.it:
// g++ -pthread -std=c++17 -o calc calc.cpp; 
//./calc < calc_test1.in
// Run in zeus:
// g++ -pthread -o calc calc.cpp; 
//./calc < calc_test1.in

#include <cstdlib>
#include <iostream>
#include <string>

#include "dlist.h"

/*
  operations: + add
              - subtract
              * multiply 
              / divide
              n negate top item
              d duplicate top item
              r reverse top two items
              p print top item
              c clear entire stack
              a print all items
              q quit
*/

class divZero {};
class badInput {};

/**** INSTRUCTOR NOTE: DO NOT MODIFY ABOVE THIS LINE ****/

/*******************************************************
 * INSTRUCTOR NOTE: Implement the functions below.     *
 * You may throw exception classes emptyList, divZero, *
 * or badInput from these functions as needed.         *
 ******************************************************/

// EFFECTS: performs + operation

/*PSEDUOCODE:

    double one
    double two

    one = stack.RemoveFront()

    try
    {
        two = stack.RemoveFront()
    }
    catch (emptyList)
    {
        stack.InsertFront(one);
        emptyList();
    }

    if (one != NULL && two != NULL)
    {
        stack.InsertFront(one + two)
    }
    else
    {
        stack.InsertFront(two)
        stack.InsertFront(one)
    }

*
*/

void DoAdd(Dlist<double>& stack) {
    // Implement this function.
    double num_one;
    double num_two;

    num_one = stack.RemoveFront();

    try
    {
        num_two = stack.RemoveFront();
    }
    catch (emptyList e)
    {
        stack.InsertFront(num_one);
        throw emptyList();
    }

    stack.InsertFront(num_two + num_one);
}

// EFFECTS: performs - operation

/*PSEDUOCODE:

    double one
    double two

    one = stack.RemoveFront()
    two = stack.RemoveFront()
    if (one != NULL && two != NULL)
    {
        stack.InsertFront(two - one)
    }
    else
    {
        stack.InsertFront(two)
        stack.InsertFront(one)
    }

*
*/
void DoSub(Dlist<double> &stack) {
  // Implement this function.
    double num_one;
    double num_two;

    num_one = stack.RemoveFront();

    try
    {
        num_two = stack.RemoveFront();
    }
    catch(emptyList e)
    {
        stack.InsertFront(num_one);
        throw emptyList();
    }

    stack.InsertFront(num_two - num_one);

    //check if stack has atleast two value?
}

// EFFECTS: performs * operation

/*PSEDUOCODE:

    double one
    double two

    one = stack.RemoveFront()
    two = stack.RemoveFront()
    if (one != NULL && two != NULL)
    {
        stack.InsertFront(two * one)
    }
    else
    {
        stack.InsertFront(two)
        stack.InsertFront(one)
    }

*
*/
void DoMult(Dlist<double> &stack) {
  // Implement this function.
    double num_one;
    double num_two;

    num_one = stack.RemoveFront();

    try
    {
        num_two = stack.RemoveFront();
    }
    catch (emptyList e)
    {
        stack.InsertFront(num_one);
        throw emptyList();
    }

    stack.InsertFront(num_two * num_one);
}

// EFFECTS: performs / operation

/*PSEDUOCODE:

    double one
    double two

    one = stack.RemoveFront()
    two = stack.RemoveFront()
    if (one != NULL && two != NULL)
    {
        stack.InsertFront(two / one)
    }
    else
    {
        stack.InsertFront(two)
        stack.InsertFront(one)
    }

*
*/
void DoDiv(Dlist<double> &stack) {
  // Implement this function.
    double num_one;
    double num_two;

    num_one = stack.RemoveFront();

    try
    {
        num_two = stack.RemoveFront();
    }
    catch (emptyList e)
    {
        stack.InsertFront(num_one);
        throw emptyList();
    }

    stack.InsertFront(num_two / num_one);
}

// EFFECTS: performs n operation

/*PSEDUOCODE:

    double one
    if (!stack.IsEmpty)
    {
        one = stack.RemoveFront()
        stack.InsertFront(one * -1)
    }

*
*/

void DoNeg(Dlist<double>& stack) {
    // Implement this function.
    double num_one;
    if (!stack.IsEmpty())
    {
        num_one = stack.RemoveFront();
        stack.InsertFront(num_one * -1);
    }
}

// EFFECTS: performs d operation

/*PSEDUOCODE:

    double one
    if (!stack.IsEmpty)
    {
        one = stack.RemoveFront()

        stack.InsertFront(one)
        stack.InsertFront(one)
    }

*
*/
void DoDup(Dlist<double> &stack) {
  // Implement this function.
    double num_one;
    if(!stack.IsEmpty())
    {
        num_one = stack.RemoveFront();

        stack.InsertFront(num_one);
        stack.InsertFront(num_one);
    }
}

// EFFECTS: performs r operation

/*PSEDUOCODE:

    double one
    double two
    one = stack.RemoveFront()
    two = stack.RemoveFront()
    if (one != NULL && two != NULL)
    {
        stack.InsertFront(one)
        stack.InsertFront(two)
    }
    else
    {
        stack.InsertFront(two)
        stack.InsertFront(one)
    }

*
*/
void DoRev(Dlist<double> &stack) {
  // Implement this function.
    double num_one;
    double num_two;

    num_one = stack.RemoveFront();

    try
    {
        num_two = stack.RemoveFront();
    }
    catch (emptyList e)
    {
        stack.InsertFront(num_one);
        throw emptyList();
    }

    stack.InsertFront(num_two);
    stack.InsertFront(num_one);
}

// EFFECTS: performs p operation

/*PSEDUOCODE:

    double one

    one = stack.RemoveFront()
    stack.InsertFront(one)

    cout << one << endl;

*
*/

void DoPrint(Dlist<double> &stack) {
  // Implement this function.
    double num_one;
    
    num_one = stack.RemoveFront();
    stack.InsertFront(num_one);

    std::cout << num_one << std::endl;
}

// EFFECTS: performs c operation

/*PSEDUOCODE:

    while(!stack.IsEmpty)
    {
        stack.RemoveFront()
    }

*
*/
void DoClear(Dlist<double> &stack) {
  // Implement this function.
    while(!stack.IsEmpty())
    {
        stack.RemoveFront();
    }
}

// EFFECTS: performs a operation

/*PSEDUOCODE:

    Dlist<double> tempstack;
    while(!stack.IsEmpty)
    {
         double one = stack.RemoveFront()
         cout << num_one << " " <<
         tempstack.InsertFront(one);
    }
    cout << endl;
    stack = tempstack;

*
*/
void DoPrintAll(Dlist<double> &stack) {
  // Implement this function.
    
    
    Dlist<double> temp_stack;
    while (!stack.IsEmpty())
    {
        double num_one = stack.RemoveFront();
        std::cout << num_one << " ";

        temp_stack.InsertBack(num_one);
    }

    std::cout << std::endl;
    stack = temp_stack;
}

/**** INSTRUCTOR NOTE: DO NOT MODIFY BELOW THIS LINE ****/

bool DoOne(Dlist<double> &stack) {
  std::string s;
  double d;

  std::cin >> s;
  switch (s[0]) {
  case '+':
    DoAdd(stack);
    break;
  case '-':
    DoSub(stack);
    break;
  case '*':
    DoMult(stack);
    break;
  case '/':
    DoDiv(stack);
    break;
  case 'n':
    DoNeg(stack);
    break;
  case 'd':
	  DoDup(stack);
	  break;
  case 'r':
	  DoRev(stack);
	  break;
  case 'p':
	  DoPrint(stack);
	  break;
  case 'c':
	  DoClear(stack);
	  break;
  case 'a':
	  DoPrintAll(stack);
	  break;
  case 'q':
	  return true;
	  break;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
	  d = std::atof(s.c_str());
    stack.InsertFront(d);
	  break;
  default:
	  badInput e;
	  throw e;
	  break;
  }
  return false;
}

int main() {
  Dlist<double> stack;

    //stack.InsertFront('2');
    //stack.InsertFront('3');
    //stack.InsertFront('4');
    //stack.InsertFront('+');
    //stack.InsertFront('*');
    //stack.InsertFront('p');
    //stack.InsertFront('+');
    //stack.InsertFront('d');
    //stack.InsertFront('+');
    //stack.InsertFront('p');
    //stack.InsertFront('2');
    //stack.InsertFront('-');
    //stack.InsertFront('p');
    //stack.InsertFront('q');

  bool done = false;
  while (!done) {
    try {
      done = DoOne(stack);
    } catch (emptyList e) {
      std::cout << "Not enough operands\n";
    } catch (divZero e) {
      std::cout << "Divide by zero\n";
    } catch (badInput e) {
      std::cout << "Bad input\n";
    }
  }
}
