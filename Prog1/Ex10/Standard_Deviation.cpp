#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    int sum = 0;
    int sum2 = 0;
    int avg = 0;
    double dev = 0;

  while(1){
    int n;
    std::cin >> n;

    if(n == 0) break;

    /*-----------------------------*/
    int s[n];

    for(int i=0; i<n; ++i){
      std::cin >> s[i];
      sum += s[i];
      sum2 += s[i] * s[i];
    }
    avg = sum/n;
    for(int i=0; i<n; ++i)
    dev +=((sum/n)-s[i])*((sum/n)-s[i])/n;;
  }

  std::cout << std::fixed;
  std::cout << std::setprecision(8) << dev << std::endl;

  return 0;
}
