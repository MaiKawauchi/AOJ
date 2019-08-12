#include <iostream>

int main(){
  int H, W;
  std::cin >> H >> W;

  while( H!=0 ){
    for(int i=0; i<H; i++){
      for(int j=0; j<W; j++){
        std::cout << "#" ;
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cin >> H >> W;
  }
  return 0;
}
