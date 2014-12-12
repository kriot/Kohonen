#include <iostream>
#include <fstream>
#include <vector>
#include "gnuplot_i.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  Gnuplot g;
  g.showonscreen();
  for(int k = 1; k < argc; ++k )
  {
    ifstream in(argv[k]);
    int n, dim;
    in >> n >> dim;
    vector< vector<double> > dat(dim);
    for(int i = 0; i < dim; ++i)
      dat[i].resize(n);
    for(int i = 0; i < n; ++i)
    {
      for(int j = 0; j < dim; ++j)
      {
        in >> dat[j][i];
      }
    }
    if(dim == 1)
    {
      vector<double> zero(n,0);
      g.plot_xy(dat[0], zero);
    }
    else if(dim == 2)
      g.plot_xy(dat[0],dat[1]);
    else if(dim == 3)
      g.plot_xyz(dat[0], dat[1], dat[2]);
    else
      cerr << "Unsupported dim: "<< dim << "\n";
  }
  int x;
  cin >> x;
}
