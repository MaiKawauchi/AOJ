#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
  double a, b, c;
  double area, length, height;

  std::cin >> a >> b >> c;

  double C = c * (M_PI/180);


  area = 0.5 * a * b * sin(C);
  length = sqrt((a*a) + (b*b) - (2 * a * b * cos(C))) + a + b;
  height = b * sin(C);

  std::cout << std::fixed;
  std::cout << std::setprecision(8) << area << std::endl;
  std::cout << std::setprecision(8) << length << std::endl;
  std::cout << std::setprecision(8) << height<< std::endl;
  return 0;
}
