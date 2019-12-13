#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  int n;
  std::cin >> n;

  double x[101], y[101];
  for(int i=0; i<n; ++i){
    std::cin >> x[i];
  }
  for(int i=0; i<n; ++i){
    std::cin >> y[i];
  }

  double dist = 0;
  /*----------------- Manhattan distance -------------------*/
  // p = 1
  for(int i=0; i<n; ++i){
    dist += abs(x[i]-y[i]);
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(6) << dist << std::endl;


  dist = 0;
  /*----------------- Euclidean distance -------------------*/
  // p = 2
  for(int i=0; i<n; ++i){
  dist += abs(x[i]-y[i])*abs(x[i]-y[i]);
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(6) << sqrt(dist) << std::endl;


  dist = 0;
  /*----------------- Minkowski distance -------------------*/
  // p = 3
  for(int i=0; i<n; ++i){
    dist += abs(x[i]-y[i])*abs(x[i]-y[i])*abs(x[i]-y[i]);
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(6) << pow(dist, 1.0/3.0) << std::endl;


  dist = 0;
  /*----------------- Chebyshev distance -------------------*/
  // p = ∞
  for(int i=0; i<n; ++i){
    dist = max(dist, abs(x[i]-y[i]));
  }

  std::cout << std::fixed;
  std::cout << std::setprecision(6) << dist << std::endl;;


  return 0;
}
