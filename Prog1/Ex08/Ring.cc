#include <iostream>
#include <cstring>

int main(){
  std::string str;
  std::string comp;

  std::cin >> str;
  std::cin >> comp;

  str = str + str;
  if ( str.find(comp) == -1) std::cout << "No" << std::endl;
  else std::cout << "Yes" << std::endl;

  return 0;
}
