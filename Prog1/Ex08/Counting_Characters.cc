#include <iostream>
#include <string>

int main(){
  std::string str;
  int counter[26]={};

  while(getline(std::cin, str)){

    for(int i=0; i<str.size(); i++){
      if(str[i] >= 'a' &&  str[i] <= 'z') counter[str[i]-'a']++;
      else if(str[i] >= 'A' && 'Z' >= str[i]) counter[str[i]-'A']++;
    }
    break;
  }

  for(int i=0; i<26; i++){
    std::cout << (char)( 'a'+i ) << " : " << counter[i] << std::endl;
  }

  return 0;
}
