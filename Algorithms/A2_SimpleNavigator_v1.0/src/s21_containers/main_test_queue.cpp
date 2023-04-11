#include <iostream>
#include <queue>

#include "s21_queue.h"

int main() {
  s21::Queue<int> s;

  s.init();
  // sega:
  // std::cout << "s.peek() after init: " << s.peek() << std::endl;
  s.push(42);
  std::cout << "s.peek() 42: " << s.peek() << std::endl;
  s.push(21);
  std::cout << "s.peek() 42: " << s.peek() << std::endl;
  s.push(12);
  std::cout << "s.peek() 42: " << s.peek() << std::endl;
  // конструктор копирования
  s21::Queue<int> s1(s);
  std::cout << "s1.peek() 42: " << s1.peek() << std::endl;

  s.pop();
  std::cout << "s.peek() after pop (21): " << s.peek() << std::endl;
  s.pop();
  std::cout << "s.peek() after pop (12): " << s.peek() << std::endl;

  std::cout << "s1.peek() 42: " << s1.peek() << std::endl;

  s1.pop();

  std::cout << "s1.peek() after pop (21): " << s1.peek() << std::endl;

  // конструктор перемещения
  s21::Queue<int> s2 = std::move(s1);
  std::cout << "s2.peek() after pop (21): " << s2.peek() << std::endl;

  // s.pop();
  // std::cout << "s.peek() after pop (sega): " << s.peek() << std::endl;

  // while (1) {};

  // std::queue<int>	st;

  // std::cout << "st.size(): " << st.size() << std::endl;
  // st.push(55);
  // std::cout << "st.front(): " << st.front() << std::endl;
  // st.pop();
  // //sega:
  // //std::cout << "st.front(): " << st.front() << std::endl;
}