#include "Filter.h"

Filter::Filter(int _dim)
{
  divisor = 1;
  dim = _dim;
  data = new int[dim * dim];

  RDIM0 = 0;
  RDIM1 = 0;
  RDIM2 = 0;
}

int Filter::get(int r, int c)
{
  return data[ r * dim + c ];
}

void Filter::setRDIM(int r)
{
    RDIM0 = dim*r;
    RDIM1 = dim*(r+1);
    RDIM2 = dim*(r+2);
}

void Filter::setRDIM0(int r)
{
    RDIM0 = dim*r;
}

int Filter::get0(int c)
{
    return data[RDIM0 +c];
}

int Filter::get1(int c)
{
    return data[RDIM1 +c];
}

int Filter::get2(int c)
{
    return data[RDIM2 +c];
}

void Filter::set(int r, int c, int value)
{
  data[ r * dim + c ] = value;
}

void Filter::set0(int c, int value)
{
    data[RDIM0 + c] = value;
}

int Filter::getDivisor()
{
  return divisor;
}

void Filter::setDivisor(int value)
{
  divisor = value;
}

int Filter::getSize()
{
  return dim;
}
