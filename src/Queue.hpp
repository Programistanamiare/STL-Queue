#pragma once

template<class DATA, unsigned int CAPACITY>
class SlowQueue
{
public:
  SlowQueue() : head{0u}, rear{0u}, size{0u} {}

  bool isFull() const
  {
    return size == CAPACITY;
  }

  bool isEmpty() const
  {
    return size == 0;
  }

  void clear()
  {
    head = 0;
    rear = 0;
    size = 0;
  }

  bool enqueue(const DATA& inValue)
  {
    if (isFull()) return false;
    ++size;
    buffer[rear] = inValue;
    rear = (rear + 1) % CAPACITY;
    return true;
  }

  bool dequeue(DATA& outValue)
  {
    if (isEmpty()) return false;
    --size;
    outValue = buffer[head];
    head = (head + 1) % CAPACITY;  
    return true;
  }

  bool peek(DATA& outValue)
  {
    if (isEmpty()) return false;
    outValue = buffer[head];
    return true;
  }

  constexpr unsigned int getCapacity() const
  {
    return CAPACITY;
  }

  unsigned int getSize() const
  {
    return size;
  }

private:
  unsigned int head;
  unsigned int rear;
  unsigned int size;
  DATA buffer[CAPACITY];

};


template<class DATA, unsigned int CAPACITY>
class FastQueue
{
public:
  
  FastQueue() {}

  bool isFull() const
  {
    return size == CAPACITY;
  }

  bool isEmpty() const
  {
    return size == 0u;
  }

  template<class CONTEXT>
  bool enqueue(void (*set)(DATA*, CONTEXT*), CONTEXT* context)
  {
    if (isFull()) return false;
    set(&buffer[rear], context);
    rear = (rear + 1) % CAPACITY;
    ++size;
    return true;
  }

  bool enqueue(void (*set)(DATA*, void*), void* context)
  {
    return enqueue<void>(set, context);
  }

  bool enqueue(void (*set)(DATA*))
  {
    if (isFull()) return false;
    set(&buffer[rear]);
    rear = (rear + 1) % CAPACITY;
    ++size;
    return true;
  }

  bool dequeue(DATA* const outDataPtr)
  {
    if (isEmpty()) return false;
    outDataPtr = &buffer[head];
    head = (head + 1) % CAPACITY;  
    --size;
    return true;
  }

  bool dequeue(void)
  {
    if (isEmpty()) return false;
    head = (head + 1) % CAPACITY;
    --size;
    return true;
  }

  bool peek(DATA* const outDataPtr)
  {
    if (isEmpty()) return false;
    outDataPtr = buffer + head;
    return true;
  }

  constexpr unsigned int getCapacity() const
  {
    return CAPACITY;
  }

  unsigned int getSize() const
  {
    return size;
  }

private:
  unsigned int head;
  unsigned int rear;
  unsigned int size;
  DATA buffer[CAPACITY];
};
