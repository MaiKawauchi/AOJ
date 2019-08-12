#include <iostream>

int main() {
  int S;
  int h, m, s;

  std::cin >> S;
  h = S/3600;
  m = (S%3600)/60;
  s = (S%3600)%60;
  std::cout << h << ":" << m << ":" << s << std::endl;
  return 0;
}
