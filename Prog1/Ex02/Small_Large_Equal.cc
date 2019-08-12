#include <iostream>

int main() {
  int a, b;
  std::cin >> a >> b;

  if(a<b){
    std::cout << "a < b" << std::endl;
  }
  if(b<a){
    std::cout << "a > b" << std::endl;
  }
  if(a==b){
    std::cout << "a == b" << std::endl;
  }
  return 0;
}
