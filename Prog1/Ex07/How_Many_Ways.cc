#include <iostream>

int main(){
  int n, x;

  while(std::cin >> n >> x){
    if(n==0 && x ==0)break;
    int count=0;
    for(int i=1; i<=n; i++){
      for(int j=i+1; j<=n; j++){
        for(int k=j+1; k<=n; k++){
          if(i+j+k == x) count++;
        }
      }
    }
    std::cout << count << std::endl;
  }
  //  std::cout << count << std::endl;
  return 0;
}
