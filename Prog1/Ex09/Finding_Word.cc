#include <iostream>
#include <cstring>

int main(){
  std::string text;
  std::string str;
  int count=0;

  std::cin >> str;

  for(int i=0; i<str.size(); i++){
    if('A' <= str[i] && str[i] <= 'Z') str[i] += 'a'-'A';
  }

  std::cin >> text;

  while(text != "END_OF_TEXT"){
    for(int i=0; i<text.size(); i++){
      if('A' <= text[i] && text[i] <= 'Z') text[i] += 'a'-'A';
    }
    if(text.find(str) != -1) count++;
    std::cin >> text;
  }

  std::cout << count << std::endl;

  return 0;
}
