// Elvi Mihai Sabau Sabau - 51254875L

#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <unistd.h>
#include <iostream>

using namespace std;

int _STEPS_;

// T(n) = 2 T(n-1) - lineal
unsigned long pow2_1(unsigned n)
{
  unsigned long recurVal = 0;
  _STEPS_++;

  if (n == 0)
    return 1;

  if (n > 0)
    recurVal = 2 * pow2_1(n - 1);

  return recurVal;
}

// T(n) = T(n/2) * T(n/2) - lineal
unsigned long pow2_2(unsigned n)
{
  unsigned long recurVal = 0;
  _STEPS_++;

  if (n == 0)
    return 1;

  if ((n % 2) == 0)
    recurVal = pow2_2(n / 2) * pow2_2(n / 2);
  else if ((n % 2) != 0)
    recurVal = 2 * pow2_2(n / 2) * pow2_2(n / 2);

  return recurVal;
}

// T(n) = T(n/2)^2 - logaritmica
unsigned long pow2_3(unsigned n)
{
  unsigned long recurVal = 0;
  _STEPS_++;

  if (n == 0)
    return 1;

  recurVal = pow2_3(n / 2);
  if ((n % 2) == 0)
  {
    recurVal = recurVal * recurVal;
  }
  else if ((n % 2) != 0)
  {
    recurVal = 2 * recurVal * recurVal;
  }

  return recurVal;
}

int main(void)
{

  const int maxIters = 60;

  cout << "Steps done by each implementation per each iteration"
       << endl;
  cout << "----------------------------------------------------"
       << endl;
  cout << "iter\t\tPow2_1\t\tPow2_2\t\tPow2_3"
       << endl;
  cout << "----------------------------------------------------"
       << endl;

  for (unsigned int i = 1; i <= maxIters; i++)
  {
    cout << i << "\t\t    ";

    _STEPS_ = 0;
    if (pow2_1(i) != pow(2, i))
    {
      cout << pow2_1(i) << " != " << pow(2, i);
    }
    cout << _STEPS_ << "\t\t    ";

    _STEPS_ = 0;
    if (pow2_2(i) != pow(2, i))
    {
      cout << pow2_2(i) << " != " << pow(2, i);
    }
    cout << _STEPS_ << "\t\t    ";

    _STEPS_ = 0;
    if (pow2_3(i) != pow(2, i))
    {
      cout << pow2_3(i) << " != " << pow(2, i);
    }
    cout << _STEPS_ << endl;
  }
}