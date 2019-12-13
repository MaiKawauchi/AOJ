#include <iostream>

struct Dice
{
  int label[7];
  void Roll(std::string dir)
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
      }else if( dir[i] == 'R' ){
        tmp = label[2];
        label[2] = label[3];
        label[3] = label[5];
        label[5] = label[4];
        label[4] = tmp[0];
      }
    }
  }
  int top(){
    return label[1];
  }
  int front(){
    return label[2];
  }
  int right(){
    return label[3];
  }
  int left(){
    return label[4];
  }
  int back(){
    return label[5];
  }
  int bottom(){
    return label[6];
  }
};


int main()
{
  Dice d;
  for(int i=1; i<=6; ++i){ std::cin >> d.label[i]; }

  int n;
  std::cin >> n;

  while( n-- ){
    int top, front;
    std::cin >> top >> front;

    if(d.left() == top) d.Roll("E");
    if(d.right() == top) d.Roll("W");
    while(d.top() !=  top) d.Roll("N");
    while(d.front() != front) d.Roll("R");

    std::cout << d.right() << std::endl;
  }


  return 0;
}
