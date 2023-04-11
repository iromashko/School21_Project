#ifdef S21_STACK_H

template <typename T>
s21::Stack<T>::Stack() : size_(0), head_(nullptr) {}

template <typename T>
s21::Stack<T> &s21::Stack<T>::operator=(const Stack &rhs) {
  this->Clear();
  s21::Stack<T>::Copy(rhs);
  return (*this);
}

template <typename T>
s21::Stack<T>::Stack(const Stack &src) : Stack() {
  *this = src;
}

template <typename T>
s21::Stack<T> &s21::Stack<T>::operator=(Stack &&ss) {
  // if (this == &ss)
  // 	return (*this);
  // std::cout << "hello from  operator=" << std::endl;
  this->Clear();
  s21::Stack<T>::Copy(ss);
  ss->Clear();
  return (*this);
}

template <typename T>
s21::Stack<T>::Stack(Stack &&ss) : Stack() {
  // std::cout << "hello from  &&ss" << std::endl;
  *this = ss;
}

template <typename T>
s21::Stack<T>::Stack(std::initializer_list<T> const &init) : Stack() {
  for (auto it = init.begin(); it != init.end(); it++) {
    push(*it);
  }
}

template <typename T>
s21::Stack<T>::~Stack() {
  this->Clear();

}

template <typename T>
void s21::Stack<T>::init() {
  head_ = nullptr;
  size_ = 0;
}

template <typename T>
void s21::Stack<T>::push(T const &elem) {
  StackItem *s = new StackItem();

  s->value = elem;
  s->next = NULL;

  s->next = head_;
  head_ = s;

  size_++;
}

template <typename T>
T &s21::Stack<T>::pop() {
  StackItem *ret = head_;
  // создание указателя на значение, без указателя - лики:
  T *val = &(ret->value);
  delete ret;

  if (head_ == nullptr) {
    s21::exitError("Error: stack is empty");
  }
  head_ = head_->next;
  size_--;
  // return (ret->value);
  return (*val);
}

template <typename T>
T &s21::Stack<T>::peek() {
  if (head_ == nullptr) {
    s21::exitError("Error: stack is empty");
  }
  return (head_->value);
}

template <typename T>
unsigned int s21::Stack<T>::getSize() {
  return (size_);
}

template <typename T>
void s21::Stack<T>::Copy(Stack &rhs) {
  StackItem *begin = rhs.head_;
  StackItem *ptr;

  size_ = rhs.size_;
  while (begin != nullptr) {
    StackItem *tmp = new StackItem();
    tmp->value = begin->value;
    tmp->next = nullptr;
    if (head_ == nullptr) {
      head_ = ptr = tmp;
    } else {
      ptr->next = tmp;
      ptr = tmp;
    }
    begin = begin->next;
  }
}

template <typename T>
void s21::Stack<T>::Clear() {
  while (head_ != nullptr) {
    pop();
  }
  size_ = 0;
  if (head_)
    delete head_;
}

#endif