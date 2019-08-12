#include <iostream>
#include <cstring>

int main(){
  int M;
  int H;
  std::string str;
  std::string temp;

  std::cin >> str;
  std::cin >> M;  // number of shuffle

  while(str != "-"){
    for(int i=0; i<M; i++){
      std::cin >> H;
      for(int j=0; j<H; j++){
        temp[j] = str[j];
        str.push_back(temp[j]);
      }
      str.erase(0, H);
    }
    std::cout << str << std::endl;
    std::cin >> str;
  }
  return 0;
}
