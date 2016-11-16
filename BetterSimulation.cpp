//Programmer: Ethan Chiang
//Programmer ID: 1538719

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

#include <cmath>
#include <cstdlib>

#include "PriorityQueue.h"
#include "DynamicArray.h"

struct Customer
{
  char id;
  int arrivalTime;
};

struct serverInfo
{
  Customer customer;
  bool status;
};

struct serviceEvent
{
  int serverNum;
  int endTime;
};

// prototype(s)
int getRandomNumberOfArrivals(double);
int getServiceTime(const int, const int);
char assignName();

// for priorityQueue
bool operator<(const serviceEvent& a, const serviceEvent& b)
{
  return a.endTime < b.endTime ? false : true;
}

int main()
{
  cout << "Programmer: Ethan Yi Chiang\n"
       << "Programmer ID: 1538719\n"
       << "File: " << __FILE__ << endl;

  ifstream fin;
  fin.open("simulation.txt");
  if(!fin.good()) throw "I/O error!";
  srand(time(0)); rand();

  // read the input values from a text file, one per line, in the order specified above.
  string buf;
  getline(fin,buf);
  int serversNum = atoi(buf.c_str());
  getline(fin,buf);
  double rate = atof(buf.c_str());
  getline(fin,buf);
  int waitLength = atoi(buf.c_str());
  getline(fin,buf);
  int minTime = atoi(buf.c_str());
  getline(fin,buf);
  int maxTime = atoi(buf.c_str());
  getline(fin,buf);
  int totalTime = atoi(buf.c_str());

  cout << "Number of servers: " << serversNum << endl;
  cout << "Customer arrival rate: " << rate << " per mintue, for "
       << totalTime << " mintues\n";
  cout << "Maximun queue length: " << waitLength << endl;
  cout << "Minimun service time: " << minTime << " mintues\n";
  cout << "Maximun service time: " << maxTime << " mintues\n\n";

  // declare and create and assign arrays and queues to be used in the solution
  queue<Customer> waitLine;
  //DynamicArray<Customer> serving;
  //DynamicArray<bool> serverStatus;
  DynamicArray<serverInfo> servers;
  priorityQueue<serviceEvent> eventList;

  // the clock time loop
  for (int time = 0;; time++) // the clock time
  {
    // handle all services scheduled to complete at this clock time
    while(!eventList.empty() && eventList.top().endTime == time)
    {
      servers[eventList.top().serverNum].status = false;
      eventList.pop();
    }

    // handle new arrivals -- can be turned away if wait queue is at maximum length!
    if(time < totalTime)
    {
      int arrivalNum = getRandomNumberOfArrivals(rate);
      for(int i = 0; i < arrivalNum; i++)
      {
        if(waitLine.size() < waitLength)
        {
          Customer c;
          c.id = assignName();
          c.arrivalTime = time;
          waitLine.push(c);
        }
      }
     }

    // for idle servers, move customer from wait queue and begin service
    for(int i = 0; i < serversNum; i++)
    {
      if(!servers[i].status && !waitLine.empty())
      {
        servers[i].customer = waitLine.front(); // assign first customer to server
        waitLine.pop(); // remove customer from waut line
        servers[i].status = true; // mark that server as busy

        serviceEvent temp;
        temp.serverNum = i;
        temp.endTime = time + getServiceTime(minTime, maxTime);
        eventList.push(temp);
      }
    }

    // output event list
    cout << "server | time for end-of-service\n"
         << "------ + -----------------------\n";
    for(priorityQueue<serviceEvent> temp = eventList; !temp.empty(); temp.pop())
    {
      cout.width(4);
      cout << temp.top().serverNum << "   |";
      cout.width(12);
      cout << temp.top().endTime << endl;
    }

    // output the servers summary
    cout << "\nTime: " << time << endl;
    cout << "----------------------------\n"
         << "server now serving wait line\n"
         << "------ ----------- ---------\n";
    for(int i = 0; i < serversNum; i++)
    {
      // output server #
      cout << "  " << i ;
      if(servers[i].status)
      {
        cout.width(10);
        cout << servers[i].customer.id;
        if(i == 0 && !waitLine.empty()) // output wait line on server 0
        {
          cout << "      ";
          queue<Customer> temp = waitLine;
          while(temp.size() != 0)
          {
            cout << temp.front().id;
            temp.pop();
          }
        }
      }
      cout << endl;
    }

    // if the end of the simulation has been reached, break
    bool end = false;
    if(waitLine.empty() && time >= totalTime) // reach time and no waitings
    {
      for(int i = 0; i < serversNum; i++) // all servers idle
      {
        if(servers[i].status) break;
        if(i == serversNum - 1) end = true;
      }
      if(end)
      {
        cout << "\nSimulation end!\n";
        break;
      }
    }
    
    // pause for the user to press ENTER
    cout << "Press enter to continue....\n";
    //cin.get();
  }

  return 0;
}

// possion function
int getRandomNumberOfArrivals(double averageArrivalRate)
{
  int arrivals = 0;
  double probOfnArrivals = exp(-averageArrivalRate);
  for(double randomValue = (double)rand( ) / RAND_MAX;
    (randomValue -= probOfnArrivals) > 0.0;
    probOfnArrivals *= averageArrivalRate / static_cast<double>(++arrivals));
  return arrivals;
}

// function(s)
int getServiceTime(const int min, const int max)
{
  return min + (rand() % max);
}

char assignName()
{
  static int name = 65;

  if(name == 91) name = 65;

  char id = name;
  name++;

  return id;
}
