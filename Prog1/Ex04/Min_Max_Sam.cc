#include <iostream>

int main(){
  int n, num;
  int MIN, MAX;
  long long SUM=0;

  std::cin >> n;

  for(int i=0; i<n; i++){
    std::cin >> num;
     SUM = SUM + num;
    if( i==0 ){
      MIN = num;
      MAX = num;
    }
    if(MIN > num){ MIN = num; }
    if(MAX < num){ MAX = num; }
  }

    std::cout << MIN << " " << MAX << " " << SUM <<std::endl;

  return 0;
}
