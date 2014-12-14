#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>
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
  dat >> ldat >> ins;
  vector<double> field(ins);
  for(int i = 0; i < ins; i++)
    dat >> field[i];
  net.clear();
  net.resize(outs);
  for(int i = 0; i < outs; ++i)
  {
    net[i].resize(ins);
    for(int j = 0; j < ins; ++j)
    {
      net[i][j] = (rand()*field[j])/RAND_MAX;
    }
  }
}

void Kohonen::teach(istream &dat)
{
  int dsize;
  int dins;
  dat >> dsize >> dins;
  if(dins != ins) 
  {
    cerr << "Data ins and network ins must be the same\n";
    return;
  }
  for(int j = 0; j < ins; ++j)
  {
    double tmp;
    dat >> tmp;
  }
  vector<vector< double> > data(dsize);
  for(int i = 0; i < data.size(); ++i)
  {
    data[i].resize(ins);
    for(int j = 0; j < ins; ++j)
    {
      dat >> data[i][j];
    }
  }

  double step;
  double cov = 0.5;
  vector<vector <double> > newnet = net;
  vector<double> a(outs);
  vector<double> dist(outs);

  ofstream logger("out.log");
  
  for(int k = 0; k < 100000; ++k)
  {
    step = 1.0/(pow(k+10, 0.6)+10);
    cov = 0.003 + 1.0/(k+1);
    logger <<"step = "<< step << "\n";
    for(int i = 0; i < dsize; ++i)
    {
      for(int j = 0; j < outs; ++j)
      {
        dist[j] = 0;
        for(int l = 0; l < ins; ++l)
          dist[j] += pow((net[j][l] - data[i][l]),2);
      }

      int closest = 0;
      for(int j = 0; j < outs; ++j)
        if(dist[j] < dist[closest]) closest = j;

      for(int j = 0; j < outs; ++j)
        a[j] = step * cov / (cov + dist[j] - dist[closest]) ;

      for(int j = 0; j < outs; ++j)
        for(int l = 0; l < ins; ++l)
          newnet[j][l] += a[j]*(data[i][l] - net[j][l]); 
    }
    net = newnet;
  }

  logger.close();
}
