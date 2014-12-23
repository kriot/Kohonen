#include <iostream>
#include <vector>
using namespace std;
class neuron
{
public:
  vector<double> w;
  int c;
};

class Kohonen
{
public:
  int ins, outs;
  void load(istream &in);
  void save(ostream &out);
  vector<double> calc(vector<double> v);
  int res(vector <double> v );
  void teach(istream &in);
  void teach_from_stream(istream &in);
  void teach_from_file(istream &in);
  void set_classes(istream &in);
  void create(istream &in, int _outs);
private:
  vector< neuron > net;
  double scalar(vector<double> v1, vector<double> v2);
  void teach(vector< vector <double> > data, vector<int> types);
};
