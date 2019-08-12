#include <iostream>

int main(){

  int n;
  std::cin >> n;

  int cards[4][13] = {{}};

  char mark;
  int num;

  for(int i=0; i<n; i++){
    std::cin >> mark >> num;

    switch(mark){
    case 'S':
      cards[0][num-1] = 1;
      break;
    case 'H':
      cards[1][num-1] = 1;
      break;
    case 'C':
      cards[2][num-1] = 1;
      break;
    case 'D':
      cards[3][num-1] = 1;
      break;
    }
  }

  for(int i=0; i<52; i++){
     switch(i/13){
    case 0:
      if(cards[0][i%13] == 0){ std::cout << "S "  << i+1 << std::endl; }
      break;
    case 1:
      if(cards[1][i%13] == 0){ std::cout << "H "  << i%13+1 << std::endl; }
      break;
    case 2:
      if(cards[2][i%13] == 0){ std::cout << "C "  << i%13+1 << std::endl; }
      break;
    case 3:
      if(cards[3][i%13] == 0){ std::cout << "D "  << i%13+1 << std::endl; }
      break;
    }
  }
  return 0;
}
