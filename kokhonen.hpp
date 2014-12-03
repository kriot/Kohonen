#include <iostream>
#include <vector>
using namespace std;
class Kokhonen
{
public:
  int ins, outs;
  void load(istream &in);
  void save(ostream &out);
  vector<double> calc(vector<double> v);
  int res(vector <double> v );
  void teach(vector< vector<double> > dat, int outs);
private:
  vector< vector<double> > net;
  double scalar(vector<double> v1, vector<double> v2);
};
