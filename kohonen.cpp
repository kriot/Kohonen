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
    net[i].w.resize(ins);
    in >> net[i].c;
    for(int j = 0; j < ins; ++j)
    {
      in >> net[i].w[j];
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
    out << net[i].c << " ";
    for(int j = 0; j < net[i].w.size(); ++j)
    {
      out << net[i].w[j] << " ";
    }
    out << "\n";
  }
}

vector<double> Kohonen::calc(vector<double> v)
{
  vector<double> res(net.size());
  for(int i = 0; i < net.size(); ++i)
    res[i] = scalar(net[i].w, v) * 2 - scalar(net[i].w, net[i].w);
  return res;
}

int Kohonen::res(vector<double> v)
{
  vector<double> dat = calc(v);
  int imax = 0;
  for(int i = 0; i < dat.size(); ++i)
    if(dat[i] >= dat[imax])
      imax = i;
  return net[imax].c;  
}

void Kohonen::create(istream &dat, int _outs)
{
  outs = _outs;
  int ldat;
  string type;
  dat >> type;
  if(type == "stream")
  {
    dat >> ldat >> ins;
    vector<double> field(ins);
    for(int i = 0; i < ins; i++)
      dat >> field[i];
    net.clear();
    net.resize(outs);
    for(int i = 0; i < outs; ++i)
    {
      net[i].w.resize(ins);
      net[i].c = -1;
      for(int j = 0; j < ins; ++j)
      {
        net[i].w[j] = (rand()*field[j])/RAND_MAX;
      }
    }
  }
  else if(type == "file")
  {
    dat >> ldat >> ins;
    double field;
    dat >> field;
    net.clear();
    net.resize(outs);
    for(int i = 0; i < outs; ++i)
    {
      net[i].w.resize(ins);
      net[i].c = -1;
      for(int j = 0; j < ins; ++j)
      {
        net[i].w[j] = (rand()*field)/RAND_MAX;
      }
    }
  }
  else
  {
    cerr << type << " is not type of theacher\n";
  }
}

void Kohonen::teach(vector< vector <double> > data, vector<int> types)
{
  double step;
  double cov = 0.5;
  vector<neuron> newnet = net;
  vector<double> a(outs);
  vector<double> dist(outs);

  ofstream logger("out.log");
  
  for(int k = 0; k < 10000; ++k)
  {
    step = 1.0/(pow(k+10, 0.6)+10);
    cov = 0.003 + 1.0/(k+1);
    logger <<"step = "<< step << "\n";
    for(int i = 0; i < data.size(); ++i)
    {
      for(int j = 0; j < outs; ++j)
      {
        dist[j] = 0;
        for(int l = 0; l < ins; ++l)
          dist[j] += pow((net[j].w[l] - data[i][l]),2);
      }

      int closest = 0;
      for(int j = 0; j < outs; ++j)
        if(dist[j] < dist[closest]) closest = j;

      for(int j = 0; j < outs; ++j)
      {
        a[j] = (net[j].c == types[i] ? 1 : -1.0/outs) * step * cov / (cov + dist[j] - dist[closest]) ;
        logger << types[i] << " " << net[j].c << "; a[" << j << "] = " << a[j] << "\n";
      }

      for(int j = 0; j < outs; ++j)
        for(int l = 0; l < ins; ++l)
          newnet[j].w[l] += a[j]*(data[i][l] - net[j].w[l]); 
    }
    net = newnet;
  }

  logger.close();
}

void Kohonen::teach_from_file(istream &dat)
{
  int dsize;
  int dins;
  dat >> dsize >> dins;
  if(dins != ins) 
  {
    cerr << "Data ins and network ins must be the same\n";
    return;
  }

  {
    double tmp;
    dat >> tmp;
  }
  vector<vector< double> > data(dsize);
  vector<int> types(dsize);
  for(int i = 0; i < data.size(); ++i)
  {
    data[i].resize(ins);
    dat >> types[i];
    string source;
    dat >> source;
    ifstream s(source.c_str());
    int size_of_s;
    s >> size_of_s;
    for(int j = 0; j < ins; ++j)
    {
      s >> data[i][j];
    }
    s.close();
  }
  teach(data, types);
}

void Kohonen::teach(istream &dat)
{
  string type;
  dat >> type;
  if(type == "file")
  {
    teach_from_file(dat);
  }
  else if(type == "stream") 
  {
    teach_from_stream(dat);
  }
  else
  {
    cerr << type << " is not type of theacher\n";
  }
}

void Kohonen::teach_from_stream(istream &dat)
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
  vector<int> types(dsize);
  for(int i = 0; i < data.size(); ++i)
  {
    data[i].resize(ins);
    dat >> types[i];
    for(int j = 0; j < ins; ++j)
    {
      dat >> data[i][j];
    }
  }
  teach(data, types);
}

void Kohonen::set_classes(istream& dat)
{
  string type;
  int dsize;
  int dins;
  dat >> type;
  dat >> dsize >> dins;

  vector<vector< double> > data(dsize);
  vector<int> types(dsize);

  if(dins != ins) 
  {
    cerr << "Data ins and network ins must be the same\n";
    return;
  }
  if(type == "stream")
  {
    for(int j = 0; j < ins; ++j)
    {
      double tmp;
      dat >> tmp;
    }
    for(int i = 0; i < data.size(); ++i)
    {
      data[i].resize(ins);
      dat >> types[i];
      for(int j = 0; j < ins; ++j)
      {
        dat >> data[i][j];
      }
    }
  }
  else if(type == "file")
  {
    {
      double tmp;
      dat >> tmp;
    }
    for(int i = 0; i < data.size(); ++i)
    {
      data[i].resize(ins);
      dat >> types[i];
      string source;
      dat >> source;
      ifstream s(source.c_str());
      int size_of_s;
      s >> size_of_s;
      for(int j = 0; j < ins; ++j)
      {
        s >> data[i][j];
      }
      s.close();
    }
    
  }
  else
  {
    cerr << type << " is not type of theacher\n";
    return;
  }

  for(int j = 0; j < outs; ++j)
  {
    int closest = -1;
    double dist = 1e100;
    for(int i = 0; i < dsize; ++i)
    {
      double d = 0;
      for(int l = 0; l < ins; ++l)
        d += pow((net[j].w[l] - data[i][l]),2);
      if( d <= dist )
      {
        closest = i;
        dist = d;
      }
    }
    net[j].c = types[closest];
  }
}
