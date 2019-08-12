#include <iostream>

int main(){
  int n;
  std::cin >> n;

  int i;
  int num[100];
  for(i=0; i<n; i++){
    std::cin >> num[i];
  }

  for(i=n-1; i>0; i--){
    std::cout << num[i] << " " ;
  }
  if(i==0){ std::cout << num[i]; }
  std::cout << std::endl;

  return 0;
}
