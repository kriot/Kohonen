#include <iostream>
#include <vector>
#include <stdlib.h>
#include "kohonen.hpp"
using namespace std;

double Kohonen::scalar(vector<double> v1, vector<double> v2)
{
  if(v1.size() != v2.size())
  {
    cerr << "Vectors must be the same size";
    exit(0);
  }
  double res = 0;
  for(int i = 0; i < v1.size(); ++i)
    res += v1[i] * v2[i];
  return res;
}

void Kohonen::load(istream &in)
{
  in >> outs >> ins;
  net.resize(outs);
  for(int i = 0; i < outs; ++i)
  {
    net[i].resize(ins);
    for(int j = 0; j < ins; ++j)
    {
      in >> net[i][j];
    }
  }
}

void Kohonen::save(ostream &out)
{
  out.precision(10);
  out << outs << " ";
  out << ins << "\n";
  for(int i = 0; i < outs; ++i)
  {
    for(int j = 0; j < net[i].size(); ++j)
    {
      out << net[i][j] << " ";
    }
    out << "\n";
  }
}

vector<double> Kohonen::calc(vector<double> v)
{
  vector<double> res(net.size());
  for(int i = 0; i < net.size(); ++i)
    res[i] = scalar(net[i], v) * 2 - scalar(net[i], net[i]);
  return res;
}

int Kohonen::res(vector<double> v)
{
  vector<double> dat = calc(v);
  int imax = 0;
  for(int i = 0; i < dat.size(); ++i)
    if(dat[i] >= dat[imax])
      imax = i;
  return imax;  
}

void Kohonen::create(istream &dat, int _outs)
{
  outs = _outs;
  int ldat;
  vector<double> field;
  dat >> ldat >> ins;
  for(int i = 0; i < ins; i++)
    dat >> field[i];
  net.clear();
  net.resize(outs);
  for(int i = 0; i < outs; ++i)
  {
    for(int j = 0; j < ins; ++j)
    {
      net[i][j] = (rand()*field[j])/RAND_MAX;
    }
  }
}

void Kohonen::teach(istream &dat)
{
}
