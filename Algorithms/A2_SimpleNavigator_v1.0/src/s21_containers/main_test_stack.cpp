#include <iostream>
#include <stack>

#include "s21_stack.h"

int main() {
  s21::Stack<int> s;

  s.init();
  // sega:

  // std::cout << "s.peek() after init: " << s.peek() << std::endl;

  s.push(42);
  std::cout << "s.getSize(): " << s.getSize() << std::endl;
  // std::cout << "s.peek() 42: " << s.peek() << std::endl;
  s.push(21);
  std::cout << "s.getSize(): " << s.getSize() << std::endl;
  // std::cout << "s.peek() 21: " << s.peek() << std::endl;
  s.push(12);
  std::cout << "s.getSize(): " << s.getSize() << std::endl;
  // std::cout << "s.peek() 12: " << s.peek() << std::endl;

  // std::cout << "s.getSize(): " << s.getSize() << std::endl;

  while (s.getSize() != 0) {
    std::cout << s.pop() << " ";
    // std::cout << s.pop() << " ";
    // std::cout << s.pop() << " ";
  }
  std::cout << std::endl;

  // sega:

  // s.pop();

  // std::cout << "s.peek() after pop (0): " << s.peek() << std::endl;

  // std::stack<int> st;

  // std::cout << "st.size(): " << st.size() << std::endl;

  // st.push(55);

  // std::cout << "st.top(): " << st.top() << std::endl;

  // st.pop();

  // std::cout << "st.top(): " << st.top() << std::endl;

  while (1) {
  };
}