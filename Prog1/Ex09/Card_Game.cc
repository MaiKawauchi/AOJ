#include <iostream>
#include <string>

#define MAX 101
#define WIN 3
#define DROW 1

using namespace std;

int main(){
  int N;
  cin >> N;

  string T; // Taro
  string H; // Hanako
  int T_point = 0;
  int H_point = 0;

  for(int i=0; i<N; ++i){
    cin >> T >> H;

    if(T.compare(H) == 0){ // same
      T_point += DROW;
      H_point += DROW;
    }
    else if(T.compare(H) > 0){
      T_point += WIN;
    }
    else H_point += WIN;
  }

  cout << T_point << " " << H_point << endl;
  return 0;
}
