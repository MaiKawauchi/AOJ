#include<iostream>

int main(){
  int n, m, l;
  std::cin >> n >> m >> l;
  int A[100][100], B[100][100];
  long long C[100][100];

  /*imput A*/
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      std::cin >> A[i][j];
    }
  }
  /*imput B*/
  for(int j=0; j<m; j++){
    for(int k=0; k<l; k++){
      std::cin >> B[j][k];
    }
  }
  /*imput C*/
  for(int i=0; i<n; i++){
    for(int k=0; k<l; k++){
      C[i][k]=0;
      for(int j=0; j<m; j++){
        C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
  /*output*/
  for(int i=0; i<n; i++){
    for(int k=0; k<l; k++){
      if(k<l-1){
        std::cout << C[i][k] <<" ";
      }else{
        std::cout << C[i][k];
      }
    }
    std::cout << std::endl;
  }
  return 0;
}
