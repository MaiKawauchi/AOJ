#include <iostream>

int main(){
  int sum = 0;
  int n, m;
  std::cin >> n >> m;

  int a[n][m];
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      std::cin >> a[i][j];
    }
  }

  int b[m];
  for(int i=0; i<m; i++){
    std::cin >> b[i];
  }

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      sum += a[i][j] * b[j];
    }
    std::cout << sum << std::endl;
    sum = 0;
  }
  return 0;
}
