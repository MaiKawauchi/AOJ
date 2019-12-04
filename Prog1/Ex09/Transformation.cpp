#include <iostream>
#include <string>

using namespace std;

int main ()
{
  string str;
  string r_str;
  int N;
  int a, b;

  cin >> str;
  cin >> N;

  string order[N];
  for(int i=0; i<N; ++i){
    cin >> order[i];
    cin >> a >> b;

    /*-------------------------------------*/
    if(order[i] == "replace"){
      cin >> r_str;
      if(b-a+1 == r_str.length()){
        int k=0;
        for(int j=a; j<=b; ++j){
          str[j] = r_str[k];
          k++;
        }
      }
    }

    /*-------------------------------------*/
    else if(order[i] == "reverse"){
      while(a < b){
        swap(str[a++], str[b--]);
      }
    }

    /*-------------------------------------*/
    else if(order[i] == "print"){
      for(int j=a; j<=b; ++j){
        cout << str[j];
      }
      cout << endl;
    }

  }

  return 0;
}
