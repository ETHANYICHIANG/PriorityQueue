//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <iostream> // for cout, ios, and endl
#include <string> // for string
using namespace std;

#include <cassert> // for assert
#include <cmath> // for log and pow
#include <cstdlib> // for srand and rand
#include <ctime> // for clock(), clock_t, time, and CLOCKS_PER_SEC

#include "PriorityQueue.h"

int main()
{
  srand(time(0)); rand(); // seed the random number generator (in case you need it)

  // programmer customization go here
  int n = 1000000; // THE STARTING PROBLEM SIZE (MAX 250 MILLION)
  const int reps = n / 100; // one percent of starting n

  cout.setf(ios::fixed);
  cout.precision(4);
  double elapsedSecondsNorm = 0;
  for(int cycle = 0; cycle < 4; cycle++, n*= 2)
  {
    // problem setup goes here -- create a data structure of size n
    priorityQueue<int> testQueue(n * 2);
    for(int i = 0; i < n; i++)
      testQueue.push(i);

    // comfirmation 
    assert(testQueue.size() == n);
    priorityQueue<int> tempQueue = testQueue;
    while(!tempQueue.empty())
    {
      int temp = tempQueue.top(); 
      tempQueue.pop();
      assert(temp >= tempQueue.top());
    }

    // start the timer, do something, and stop the timer
    clock_t startTime = clock();
    for(int rep = 0; rep < reps; rep++)
    {
      testQueue.push(rand() % n);
    }
    clock_t endTime = clock(); 

    // validation block -- assure that process worked if applicable
    assert(testQueue.size() == n + reps);
    tempQueue = testQueue;
    while(!tempQueue.empty())
    {
      int temp = tempQueue.top(); 
      tempQueue.pop();
      assert(temp >= tempQueue.top());
    }

    // compute timing results
    double elapsedSeconds = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    double factor = pow(2.0, double(cycle));
    if(cycle == 0) elapsedSecondsNorm = elapsedSeconds;
    double expectedSecondsLog = log(double(n)) / log(n / factor) * elapsedSecondsNorm;

    // reporting block
    cout << elapsedSeconds;
    if(cycle == 0) cout << " (expected)";
    else cout << " (expected " << elapsedSecondsNorm << " to " << expectedSecondsLog << ')';
    cout << " for n=" << n << endl;
  }
  return 0;
}