//-*-c++-*-
#ifndef _Filter_h_
#define _Filter_h_

using namespace std;

class Filter {
  int divisor;
  int dim;
  int *data;

  int RDIM0;
  int RDIM1;
  int RDIM2;

public:
  Filter(int _dim);
  int get(int r, int c);
  void setRDIM(int r);
  void setRDIM0(int r);

  int get0(int c);
  int get1(int c);
  int get2(int c);

  void set(int r, int c, int value);
  void set0(int c, int value);

  int getDivisor();
  void setDivisor(int value);

  int getSize();
};

#endif
