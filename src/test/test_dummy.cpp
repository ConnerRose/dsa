#include <cassert>

#include "dummy.hpp"

int main() {
  something some{};
  assert(some.a == 0);
}
