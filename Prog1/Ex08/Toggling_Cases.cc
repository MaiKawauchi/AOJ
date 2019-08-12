#include <iostream>
#include <string>

int main(){
  std::string ch;

  std::getline(std::cin, ch);

  for(int i=0; i<ch.size(); i++){
    if(ch[i] >= 'a' && 'z' >= ch[i]){ch[i] -= 32;}
    else if(ch[i] >= 'A' && 'Z' >= ch[i]){ch[i] += 32;}
  }
  std::cout << ch << std::endl;

  return 0;
}
