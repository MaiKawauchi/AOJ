#include <iostream>
int main(){
  int a, b, c;
  int count=0;
  int x[10000];

  std::cin >> a >> b >> c;
  for(int i=a; i<=b; i++) {
    if( c % i == 0 ) {
      count++;
    }
  }
  std::cout << count << std::endl;
  return 0;
}
