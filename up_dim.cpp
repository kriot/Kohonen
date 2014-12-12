#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
  ifstream in1(argv[1]);
  ifstream in2(argv[2]);
  int d1,d2, n1, n2;
  in1 >> n1 >> d1;
  in2 >> n2 >> d2;
  int n = n1 < n2 ? n1 : n2;
  cout << n << " " << d1+d2 << "\n";
  for(int i = 0; i < n; ++i)
  {
    double a;
    for(int j = 0; j < d1; ++j)
    {
      in1 >> a;
      cout << a << " ";
    }
    for(int j = 0; j < d2; ++j)
    {
      in2 >> a;
      cout << a << " ";
    }
    cout << "\n";
  }
}
