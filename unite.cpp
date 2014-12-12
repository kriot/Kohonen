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
  if(d1 != d2)
  {
    cerr << "Dims bust be the same\n";
    return 0;
  }
  cout << n1+n2 << " " << d1 << "\n";
  for(int i = 0; i < n1; ++i)
  {
    double a;
    for(int j = 0; j < d1; ++j)
    {
      in1 >> a;
      cout << a << " ";
    }
    cout << "\n";
  }
  for(int i = 0; i < n2; ++i)
  {
    double a;
    for(int j = 0; j < d2; ++j)
    {
      in2 >> a;
      cout << a << " ";
    }
    cout << "\n";
  }
}
