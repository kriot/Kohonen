#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "kokhonen.hpp"

int main()
{
  Kokhonen k;
  char c;
  while(true)
  {
    cout << '$';
    cin >> c;
    if(c == 'q')
      break;
    if(c == 'l')
    {
      string f;
      cin >> f;
      ifstream in(f.c_str());
      k.load(in);
    }
    if(c == 's')
    {
      string f;
      cin >> f;
      ofstream out(f.c_str());
      k.save(out);
    }
    if(c == 'c')
    {
      vector<double> v(k.ins);
      for(int i = 0; i < k.ins; ++i)
        cin >> v[i];
      vector<double> res = k.calc(v);
      for(int i = 0; i < res.size(); ++i)
        cout << res[i] << "\n";
    }
  }
}
