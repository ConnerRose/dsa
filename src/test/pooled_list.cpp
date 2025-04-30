#include <cassert>
#include <iostream>

#include "pooled_list.hpp"

int main() {
  pooled_list<int> list;
  list.push_back(0);
  assert(list.front() == 0);
  assert(list.back() == 0);
  assert(list.size() == 1);
  assert(list.capacity() == 1);

  list.pop_back();
  assert(list.size() == 0);
  assert(list.capacity() == 1);

  list.push_front(1);
  assert(list.front() == 1);
  assert(list.back() == 1);
  assert(list.size() == 1);
  assert(list.capacity() == 1);

  list.pop_back();
  assert(list.size() == 0);
  assert(list.capacity() == 1);
  return 0;
}
