#include <iostream>
#include <math.h>
#include <time.h>
#include <cstdlib>
using namespace std;

int main()
{
  srand(time(NULL));
  double round;
  cin >> round;
  double range;
  cin >> range;
  int n;
  cin >> n;
  cout << n << " "<< 1 << "\n";
  for(int i = 0; i < n; ++i)
  {
    double k = (((double)rand())/RAND_MAX - 0.5) * 2;
    k = k * (pow(fabs(k)+1, 0.3)-1) / fabs(k);
    double p = round + range * k;
    cout << p << "\n";
  }
}
