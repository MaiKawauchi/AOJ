#include <iostream>

int main(){
  int r,c;
  std::cin >> r >> c;
  int num[101][101];
  int rsum[101], csum[101], sum=0;


  /*imput*/
  for(int i=0; i<r; i++){
    for(int j=0; j<c; j++){
      std::cin >> num[i][j];
      rsum[i] += num[i][j];
    }
  }

  /*output*/
  for(int i=0; i<r; i++){
    for(int j=0; j<c; j++){
      std::cout  << num[i][j] << " ";
    }
    std::cout << rsum[i] << std::endl;
  }

  /*output*/
  for(int i=0; i<c; i++){
    for(int j=0; j<r; j++){
    csum[i] += num[j][i];
    }
    sum += csum[i];
    std::cout << csum[i] << " ";
  }
  std::cout << sum << std::endl;

  return 0;
}
