#include <iostream>
#include <cstring>

int Role(int *label, std::string dir)
{
  std::string tmp;
  for(int i=0; i<dir.length(); ++i){
    if( dir[i] == 'E' ){
      tmp = label[1];
      label[1] = label[4];
      label[4] = label[6];
      label[6] = label[3];
      label[3] = tmp[0];
    }else if( dir[i] == 'N' ){
      tmp = label[1];
      label[1] = label[2];
      label[2] = label[6];
      label[6] = label[5];
      label[5] = tmp[0];
    }else if( dir[i] == 'S' ){
      tmp = label[1];
      label[1] = label[5];
      label[5] = label[6];
      label[6] = label[2];
      label[2] = tmp[0];
    }else if( dir[i] == 'W' ){
      tmp = label[1];
      label[1] = label[3];
      label[3] = label[6];
      label[6] = label[4];
      label[4] = tmp[0];
    }
  }
  return label[1];
}


int main()
{
  int label[7];
  for(int i=1; i<=6; ++i){ std::cin >> label[i]; }

  std::string dir;
  std::cin >> dir;

  int ans = 0;
  ans = Role(label, dir);
  std::cout << ans << std::endl;

  return 0;
}
