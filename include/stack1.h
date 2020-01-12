#pragma once

template <typename T>
struct Node {
  T data;
  Node<T>* prev;
};

template <typename T>
class stack {
 private:
  Node<T>* top = nullptr;

 public:
  stack() = default;
  stack(const stack&) = delete;  // некопируемый шаблон класса
  stack(stack&& stack) = default;  // is_move_constructible
  auto operator=(stack&& stack) noexcept
      -> class stack& = default;  // is_move_assignable

  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
};

template <typename T>
inline void stack<T>::push(
    T&& value)  // type&& - аргумент может быть только rvalue, при этом внутри
// вызова можно его изменять и вообще, работаете как с обычной
// переменной (как только rvalue внутри функции обретает имя,
// оно "автоматом" становится lvalue :-)). Чтобы обычную
// переменную превратить в rvalue, нужно её "переместить", т.е.
// по сути, отдать владение в вызываемую функцию:
{
  if (top) {
    Node<T>* temp = new Node<T>;
    temp->data = top->data;
    temp->prev = top->prev;
    top->data = value;
    top->prev = temp;
  } else {
    top = new Node<T>;
    top->data = value;
    top->prev = nullptr;
  }
}

template <typename T>
inline void stack<T>::push(
    const T& value)  // const type& - аргумент может быть как lvalue (при этом
// даёте гарантию, что он там не поменяется) или rvalue,
// тогда его время жизни продлевается на время вызова:
{
  if (top) {
    Node<T>* temp = new Node<T>;
    temp->data = top->data;
    temp->prev = top->prev;
    top->data = value;
    top->prev = temp;
  } else {
    top = new Node<T>;
    top->data = value;
    top->prev = nullptr;
  }
}

template <typename T>
inline void stack<T>::pop() {
  top = top->prev;
}

template <typename T>
inline const T& stack<T>::head() const {
  return top->data;
}