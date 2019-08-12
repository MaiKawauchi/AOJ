#include <iostream>

int main() {
  int x, y, z;
  int temp;

  std::cin >> x >> y >> z;

  if(y<x){
    temp = x;
    x = y;
    y = temp;
  }
  if(z<y){
    temp = y;
    y = z;
    z = temp;
  }
  if(y<x){
    temp = x;
    x = y;
    y = temp;
  }
  std::cout << x << " " << y << " " << z << std::endl;
  return 0;
}
