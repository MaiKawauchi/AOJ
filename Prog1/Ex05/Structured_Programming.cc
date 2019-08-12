#include <iostream>

int main(){
  int n, i=1;
  std::cin >> n;

  while(++i<=n){
    int x=i;
    if( x%3 == 0 ){
      std::cout << " " << i;
      continue;
    }
    while(x){
      if( x%10 == 3 ){
        std::cout << " " << i;
        break;
      }
      x/=10;
    }
  }
  std::cout << std::endl;
  return 0;
}
