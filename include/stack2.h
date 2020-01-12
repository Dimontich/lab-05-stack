#pragma once
#include <utility>

template <typename T>
struct NoCopyNode {
  T data;
  NoCopyNode<T>* prev;
};

template <typename T>
class StackTwo {
 private:
  NoCopyNode<T>* top = nullptr;

 public:
  StackTwo() = default;
  StackTwo(const StackTwo&) = delete;  //
  StackTwo(StackTwo&&) = default;      //
  auto operator=(StackTwo&&) noexcept
  -> class StackTwo& = default;  // перемещаемый при присваивании

  template <typename... Args>
  void push_emplace(
      Args&&... value);  // аналог emplace_back, передаем как конструктору
  void push(T&& value);
  const T& head() const;
  T pop();
};

template <typename T>
template <typename... Args>
inline void StackTwo<T>::push_emplace(Args&&... data) {
  auto* curr = top;  // перемещаем
  top = new NoCopyNode<T>{
      {std::forward<Args>(data)...},
      curr};  // рекурсивно вызываем функцию с распакованным пакетом параметров
  // функции ((data)...)(f(args..))  для "идеальной передачи" с
  // forward(std::forward<Args>(data)...})  в конструктор структуры
  // Node (std::forward<Args>(data)...}, curr )
  // идеальная передача позволяет передавать аргументы в функцию внутри
  // функции-обертки. Для этого нам и дан forward/
}

template <typename T>
inline void StackTwo<T>::push(T&& data) {
  auto* curr = top;
  top = new NoCopyNode<T>{std::forward<T>(data),
                          curr};  // все то же самое, но без рекурсии
}

template <typename T>
inline const T& StackTwo<T>::head() const {
  return top->data;
}

template <typename T>
inline T StackTwo<T>::pop() {
  T data = top->data;
  top = top->prev;

  return data;
}