#include <cstddef>
#include <cstdlib>
#include <iostream>

template <typename T>
class pooled_list {
  class node {
    T val{};
    node* next{};
    node* prev{};

    node(const T& val, node* next, node* prev)
        : val(val), next(next), prev(prev) {}

    friend class pooled_list;
  };

  node* data{};
  node** available{};
  size_t _cap{};
  size_t _size{};
  node* _front{};
  node* _back{};

 public:
  ~pooled_list() {
    for (node* curr = _front; curr != nullptr; curr = curr->next) {
      curr->val.~T();
    }
    free(data);
    free(available);
  }

  T& front() { return _front->val; }

  T& back() { return _back->val; }

  bool empty() { return _size == 0; }

  size_t size() { return _size; }

  size_t capacity() { return _cap; }

  void reserve(size_t new_cap) {
    if (new_cap <= _cap) {
      return;
    }
    data = data == nullptr
               ? static_cast<node*>(malloc(sizeof(node) * new_cap))
               : static_cast<node*>(realloc(data, sizeof(node) * new_cap));
    available =
        available == nullptr
            ? static_cast<node**>(malloc(sizeof(node*) * new_cap))
            : static_cast<node**>(realloc(available, sizeof(node*) * new_cap));
    for (size_t i = _cap; i < new_cap; ++i) {
      available[i - _cap] = data + i;
    }
    _cap = new_cap;
  }

  void clear() {}

  void push_back(const T& value) {
    if (_cap == _size++) {
      reserve(_cap == 0 ? 1 : 2 * _cap);
    }
    *available[_cap - _size] = node{value, _back, nullptr};
    if (_back != nullptr) {
      _back->next = available[_cap - _size];
    }
    _back = available[_cap - _size];
    if (_size == 1) {
      _front = _back;
    }
  }

  void pop_back() {
    node* prev = _back;
    if (_back != nullptr) {
      _back = _back->prev;
    }
    if (_back != nullptr) {
      _back->next = nullptr;
    }
    if (prev != nullptr) {
      prev->val.~T();
    }
    if (--_size == 0) {
      _front = _back = nullptr;
    }
  }

  void push_front(const T& value) {
    if (_cap == _size++) {
      reserve(_cap == 0 ? 1 : 2 * _cap);
    }
    *available[_cap - _size] = node{value, nullptr, _front};
    if (_front != nullptr) {
      _front->next = available[_cap - _size];
    }
    _front = available[_cap - _size];
    if (_size == 1) {
      _back = _front;
    }
  }

  void pop_front() {
    node* prev = _front;
    _front = _front == nullptr ? nullptr : _front->next;
    if (_front != nullptr) {
      _front->prev = nullptr;
    }
    if (prev != nullptr) {
      prev->val.~T();
    }
    if (--_size == 0) {
      _front = _back = nullptr;
    }
  }
};
