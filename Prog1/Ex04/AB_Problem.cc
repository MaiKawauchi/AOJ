#include <iostream>
#include <cstdio>
int main(){
  int a, b;
  double f;

  std::cin >> a >> b;

  f = 1.0*a/b;
  std::printf("%d %d %.5lf\n", a/b, a%b, f);
  return 0;
}
