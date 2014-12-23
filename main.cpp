#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "kohonen.hpp"

int main(int argc, char* argv[])
{
  Kohonen k;
  if(argc > 1)
  {
    ifstream net(argv[1]);
    k.load(net);
    int dat_ins;
    cin >> dat_ins;
    vector<double> v(k.ins);
    for(int i = 0; i < k.ins; ++i)
      cin >> v[i];
    cout << k.res(v);
    return 0;
  }
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
    if(c == 'n')
    {
      string f;
      int outs;
      cin >> f >> outs;
      ifstream in(f.c_str());
      k.create(in, outs);
    }
    if(c == 't')
    {
      string f;
      cin >> f;
      ifstream in(f.c_str());
      k.teach(in);
    }
    if(c == 'f')
    {
      string f;
      cin >> f;
      ifstream in(f.c_str());
      k.teach_from_file(in);
    }
    if(c == 'u')
    {
      string f;
      cin >> f;
      ifstream in(f.c_str());
      k.set_classes(in);
      cout << "OK\n";
    }
  }
}
