#ifndef S21_STACK_H
#define S21_STACK_H

// #include <strings.h>

#include "s21_utils.h"

namespace s21 {
template <class T>

class Stack {
 public:
  Stack();
  Stack &operator=(const Stack &);
  Stack(const Stack &);
  Stack &operator=(Stack &&);
  Stack(Stack &&);
  Stack(std::initializer_list<T> const &);
  ~Stack();
  void init();
  void push(T const &);
  T &pop();
  T &peek();
  unsigned int getSize();

 private:
  void Copy(Stack &);
  void Clear();
  struct StackItem {
    T value;
    StackItem *next;
  };
  unsigned int size_;
  StackItem *head_;
};
}  // namespace s21

#include "s21_stack.tpp"

#endif