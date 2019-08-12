#include <iostream>
int main(){
  int x[3000], y[3000];
  int count=0;
  int temp;

  for(int i=0; i<3000; i++){
  std::cin >> x[i] >> y[i];
  if( x[i]==0 && y[i]==0 ) { break; }
  count++;
  }

  for(int i=0; i<count; i++){
    if( x[i] > y[i] ){
      temp = x[i];
      x[i] = y[i];
      y[i] = temp;
    }
  std::cout << x[i] << " " << y[i] << std::endl;
  }
  return 0;
}
