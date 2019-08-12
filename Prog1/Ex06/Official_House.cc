#include <iostream>

int main(){
  int n;
  std::cin >> n;

  int b, f, r, v;
  int room[4][3][10] = {{{}}};

  for(int i=0; i<n; i++){
    std::cin >> b >> f >> r >> v;
    room[b-1][f-1][r+-1] += v;
  }

  for(int i=0; i<4; i++){
    for(int j=0; j<3; j++){
      for(int k =0; k<10; k++){
        std::cout <<  " " << room[i][j][k];
      }
      std::cout << std::endl;
    }
    if( i<3 ){
      std::cout << "####################" << std::endl;
    }
  }
  return 0;
}
