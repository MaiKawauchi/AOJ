#include <iostream>
#include <string>

int main(){

  std::string number;
  std::cin >> number;

  while(number[0] != '0'){
    int sum=0;

    for(int i=0; i<number.size(); i++){
      sum += number[i]-'0';
    }
    std::cout << sum << std::endl;
    std::cin >> number;
  }
  return 0;
}
