#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

int main()
{
  double round;
  cin >> round;
  double range;
  cin >> range;
  int n;
  cin >> n;
  cout << n << " "<< 1 << "\n";
  for(int i = 0; i < n; ++i)
  {
    double p = round + range * (((double)rand())/RAND_MAX - 0.5) * 2;
    cout << p << "\n";
  }
}
