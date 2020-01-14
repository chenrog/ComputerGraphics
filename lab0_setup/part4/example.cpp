#include <iostream>
#include <string>

int main() {
  int my_arr[10];
  for (int i = 0; i < 10; ++i) {
    my_arr[i] = i;
    std::cout << i << " ";
  }

  std::string hello = "hello";
  for(char c : hello) {
    std::cout << c;
  }
}