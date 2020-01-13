// Copyright 2018 Dimontich

#include <gtest/gtest.h>

#include "../include/stack1.h"
#include "../include/stack2.h"

class tests {
 public:
  tests(int x, int y) {
    a = x;
    b = y;
  }
  tests(const tests& tmp) {
    a = tmp.a;
    b = tmp.b;
  }
  int a;
  int b;
};

TEST(Stack_test, Elements) {
  // T data -> int
  int a = 3, b = 4;

  stack<int> mystk;
  mystk.push(a);
  mystk.push(b);

  EXPECT_EQ(mystk.head(), 4);
  mystk.pop();
  EXPECT_EQ(mystk.head(), 3);

  EXPECT_EQ(std::is_move_constructible<stack<int>>::value, true);
  EXPECT_EQ(std::is_move_assignable<stack<int>>::value, true);
  EXPECT_EQ(std::is_copy_constructible<stack<int>>::value, false);
  EXPECT_EQ(std::is_copy_assignable<stack<int>>::value, false);
}
TEST(NoCopyStack, Elements) {
  // T data -> class tests
  int x1 = 1, y1 = 2, x2 = 3, y2 = 4;

  StackTwo<tests> mynocopystk;

  mynocopystk.push(tests(x1, y1));
  mynocopystk.push_emplace(x2, y2);

  EXPECT_EQ(mynocopystk.head().a, x2);
  mynocopystk.pop();
  EXPECT_EQ(mynocopystk.head().b, y1);

  EXPECT_EQ(std::is_move_constructible<StackTwo<int>>::value, true);
  EXPECT_EQ(std::is_move_assignable<StackTwo<int>>::value, true);
  EXPECT_EQ(std::is_copy_constructible<StackTwo<int>>::value, false);
  EXPECT_EQ(std::is_copy_assignable<StackTwo<int>>::value, false);
}
