#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <strings.h>

#include <initializer_list>
// #include <iostream>

#include "s21_utils.h"

namespace s21 {
template <class T>

class Queue {
 public:
  Queue();  // конструктор по умолчанию
  Queue &operator=(Queue const &);
  Queue(const Queue &);  // конструктор копирования
  Queue &operator=(Queue &&);
  Queue(Queue &&);  // конструктор перемещения
  Queue(std::initializer_list<T> const &init);
  ~Queue();
  T &peek();
  T &pop();
  unsigned int getSize();
  void init();
  void push(T const &);

 private:
  struct QueueItem {
    QueueItem *next;
    T value;
  };
  QueueItem *head_;
  QueueItem *tail_;
  unsigned int size_;
  void Clear();
  void Copy(const Queue &);

};  // class Queue
}  // namespace s21

#include "s21_queue.tpp"

#endif