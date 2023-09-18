#ifndef INTVECTOR_H_
#define INTVECTOR_H_

#include <cstddef> // for size_t

class IntVector {
public:
  // Default constructor
  IntVector(size_t cap) {
    _array = new int[cap];
    _capacity = cap;
    _used = 0;
  }
  IntVector(const IntVector &other) {
    _array = new int[other._capacity];
    _capacity = other._capacity;
    _used = other._used;
    for (size_t i = 0; i < _used; i++) {
      _array[i] = other._array[i];
    }
  }
  IntVector &operator=(const IntVector &other) {
    if (this != &other) {
      delete[] _array;
      _array = new int[other._capacity];
      _capacity = other._capacity;
      _used = other._used;
      for (size_t i = 0; i < _used; i++) {
        _array[i] = other._array[i];
      }
    }
    return *this;
  }
  ~IntVector() { delete[] _array; }
  size_t capacity() const { return _capacity; }
  void push_back(int value) {
    if (_used == _capacity) {
      int *new_array = new int[_capacity * 2];
      for (size_t i = 0; i < _used; i++) {
        new_array[i] = _array[i];
      }
      delete[] _array;
      _array = new_array;
      _capacity *= 2;
    }
    _array[_used++] = value;
  }
  size_t size() const { return _used; }
  int get(size_t index) const { return _array[index]; }

private:
  int *_array;
  size_t _capacity;
  size_t _used;
};

#endif