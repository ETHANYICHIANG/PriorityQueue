//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <algorithm>
#include <iostream>
using namespace std;

#include <cassert>

#include "PriorityQueue.h"
#include "PriorityQueue.h"

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer ID: 1538719\n"
       << "File: " << __FILE__ << endl;

  // default con 
  cout << "\nPriorityQueue test\n"
       << "------------------------\n"
       << "Testing priorityQueue::priorityQueue & size\n";
  
  priorityQueue<double> a;
  assert(a.size() == 0);
  cout << "Pass!\n\n";

  cout << "Testing priorityQueue::push & top\n";
  a.push(2.1);
  a.push(2.2);
  a.push(2.3);
  assert(a.top() == 2.3);
  assert(a.size() == 3);
  cout << "Pass!\n\n";

  cout << "Testing priorityQueue::pop\n";
  a.pop();
  assert(a.top() == 2.2);
  assert(a.size() == 2);
  cout << "Pass!\n\n";

  cout << "Testing copy constructor\n";
  priorityQueue<double> b = a;
  assert(b.size() == a.size());
  assert(a.top() == b.top());
  a.pop(); b.pop();
  assert(a.top() == b.top());
  cout << "Pass!\n\n";

  cout << "Testing priorityQueue::clear & empty\n";
  a.clear();
  assert(a.empty());
  cout << "Pass!\n\n";

  cout << "Testing assignment operator\n";
  for(int i = 0; i < 10; i++)
  	a.push(i);
  priorityQueue<double> c;
  c = a;
  assert(c.size() == a.size());
  for(int i = 0;!c.empty();c.pop(), a.pop(), i++)
  	assert(c.top() == a.top());
  cout << "Pass!\n\n";

  return 0;
}