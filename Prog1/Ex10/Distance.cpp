#include <iostream>
#include <cmath>
#include <iomanip>

int main(){
  double x1, y1;
  double x2, y2;

  std::cin >> x1 >> y1 >> x2 >> y2;
  std::cout << std::fixed;
  std::cout << std::setprecision(8)
            <<sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1))
            << std::endl;

  return 0;
}
