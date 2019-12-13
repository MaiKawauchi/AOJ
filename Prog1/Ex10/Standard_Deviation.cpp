#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    double ans;

    int n;

    std::cin >> n;

  while( n != 0 ){
    double dev = 0;
    double sum = 0;
    double avg = 0;
    int s[1000];

    for(int i=0; i<n; ++i){
      std::cin >> s[i];
      sum += s[i];
    }

    avg = sum/n;
    for(int i=0; i<n; ++i){
      dev += (s[i]-avg)*(s[i]-avg);
    }
     std::cout << std::fixed;
     std::cout << std::setprecision(8) << sqrt(dev/n) << std::endl;
     std::cin >> n;
  }

  return 0;
}
