#include <iostream>

int main (){
  int H, W;
  std::cin >> H >> W;

  while( H!=0 && W!=0 ){
 //************************************//
    for(int i=0; i<W; i++){
      std::cout << "#";
    }
    std:: cout << std::endl;
 //************************************//
    for(int i=0; i<H-2; i++){
       std::cout << "#" ;
      for(int j=0; j<W-2; j++){
        std::cout << "." ;
      }
      std::cout << "#" << std::endl;
    }
 //************************************//
     for(int i=0; i<W; i++){
      std::cout << "#";
    }
    std:: cout << std::endl;
 //************************************//
    std::cout << std::endl;
    std::cin >> H >> W;
  }

  return 0;
}
