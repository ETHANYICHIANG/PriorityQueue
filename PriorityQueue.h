//Programmer: Ethan Yi Chiang
//Programmer ID: 1538719

#ifndef ProrityQueue_H
#define ProrityQueue_H

#include <algorithm>

template<typename V>
class priorityQueue
{
  V* values;
  int CAP;
  int siz;
  void capacity(int);

  public:
  priorityQueue(int=2);
  // dynamic 3 
  priorityQueue(const priorityQueue<V>&);
  ~priorityQueue() {delete [ ] values;}
  priorityQueue<V>& operator=(const priorityQueue<V>&);

  void push(const V&);
  void pop();
  const V& top() {return values[0];} 
  int size() {return siz;}
  bool empty() {return siz == 0 ? true : false;}
  void clear() {siz = 0;}
};

template<typename V>
priorityQueue<V>::priorityQueue(int CAP)
{
  this->CAP = CAP;
  siz = 0;

  values = new V[CAP];
  for(int i = 0; i < CAP; i++)
    values[i] = V();
}

template<typename V>
priorityQueue<V>::priorityQueue(const priorityQueue<V>& original)
{
  this->CAP = original.CAP;
  this->siz = original.siz;
  values = new V[CAP];
  for(int i = 0; i < CAP; i++)
    values[i] = original.values[i];
}

template <typename V>
priorityQueue<V>& priorityQueue<V>::operator=(const priorityQueue<V>& original)
{
  if (this != &original) // of it's not a self copy...
  {
    // do what the destructor does
    delete [ ] values;

    // do what the copy constructor does
    CAP = original.CAP; // still just a copy 
    siz = original.siz;
    values = new V[CAP]; // not a copy -- new object gets its own array
    for (int i = 0; i < CAP; i++) // copy the contents of the array from the original...
      values[i] = original.values[i]; // ...to the copy
  }
  return *this; // return a self reference
}

template <typename V>
void priorityQueue<V>::capacity(int CAP)
{
  V* temp = new V[CAP];
  int limit = min(CAP, this->CAP); 

  for (int i = 0; i < limit; i++)
    temp[i] = values[i];

  for (int i = limit; i < CAP; i++)
    temp[i] = V();

  delete [ ] values; 
  values = temp;
  this->CAP = CAP;
}

template <typename V>
void priorityQueue<V>::push(const V& data)
{
  // increase if no space
  if(siz >= CAP) 
    capacity(CAP * 2);

  // add new value to end of queue
  values[siz] = data;
  
  // get indexes 
  int index = siz;
  int pIndex = (index + 1) / 2 - 1;

  // chechking priority
  while(!(pIndex < 0 || values[index] < values[pIndex]))
  {
    swap(values[index], values[pIndex]);
    index = pIndex;
    pIndex = (index + 1) / 2 - 1;
  }
  siz++;
}

template <typename V>
void priorityQueue<V>::pop()
{
  siz--;
  int index = 0;
  
  while(true)
  {
    int lIndex = 2 * index + 1;
    int rIndex = 2 * index + 2;

    if(rIndex < siz) // both L and R
    {
      if(values[lIndex] < values[siz] && values[rIndex] < values[siz])
        break;
      else if(values[siz] < values[lIndex] && values[rIndex] < values[lIndex])
      {
        values[index] = values[lIndex];
        index = lIndex;
      }
      else 
      {
        values[index] = values[rIndex];
        index = rIndex;
      }
    }
    else if(lIndex < siz) // only L
    {
      if(values[lIndex] < values[siz])
        break;
      else 
      {
        values[index] = values[lIndex];
        index = lIndex;
      }
    }
    else break;
  }

  values[index] = values[siz];
}

#endif