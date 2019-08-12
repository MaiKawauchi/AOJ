#include <iostream>
#define Max 10001

int main(){
  int data[Max];
  int count;

  for(int i=1; i<Max; i++){
    std::cin >> data[i];
    if(data[i]==0){ break; }
    count++;
  }
  for(int i=1; i<count+1; i++){
    std::cout << "Case " << i << ": " << data[i] << std::endl;
  }
  return 0;
}
