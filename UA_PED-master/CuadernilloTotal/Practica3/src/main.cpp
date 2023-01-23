#include <iostream>

using namespace std;

#include "tcomplejo.h"
#include "tvectorcom.h"
#include "tabbcom.h"
#include "tlistacom.h"

int main(int argc, char const *argv[])
{

  TABBCom a;
  TListaCom L;

  L.InsCabeza(26);
  L.InsCabeza(83);
  L.InsCabeza(74);
  L.InsCabeza(68);
  L.InsCabeza(25);
  L.InsCabeza(42);
  L.InsCabeza(75);
  L.InsCabeza(23);
  L.InsCabeza(50);

  TComplejo *x;

  x = a.MostrarNiveles(L);

  if (x == NULL)
    cout << "Correcto" << endl;
  else
    cout << "Falla" << endl;

  return 0;
}