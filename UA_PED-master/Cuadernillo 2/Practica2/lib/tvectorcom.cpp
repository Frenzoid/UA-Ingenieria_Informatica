#include <iostream>
#include "tvectorcom.h"

using namespace std;

// Constructor a partir de un tamaño
TVectorCom::TVectorCom(const int tam)
{
  error = TComplejo(0, 0);

  if (tam <= 0)
  {
    tamano = 0;
    c = NULL;
  }
  else
  {
    tamano = tam;
    c = new TComplejo[tamano];
    if (c == NULL)
      cerr << "No se pudo reservar memoria para crear un TComplejo en TVectorCom:TVectorCom:c";
  }
};

// Constructor de copia
TVectorCom::TVectorCom(const TVectorCom &tvcom)
{
  Copia(tvcom);
};

// Destructor
TVectorCom::~TVectorCom()
{
  tamano = 0;

  if (c != NULL)
  {
    delete[] c;
    c = NULL;
  }
};

// Sobrecarga del operador asignación
TVectorCom &
TVectorCom::operator=(const TVectorCom &tvcom)
{
  if (this == &tvcom)
    return *this;

  this->~TVectorCom();

  Copia(tvcom);

  return *this;
};

void TVectorCom::Copia(const TVectorCom &cop)
{
  tamano = cop.tamano;
  c = new TComplejo[tamano];
  if (c == NULL)
    cerr << "No se pudo reservar memoria para crear un TComplejo en TVectorCom:Copia:c";

  for (int i = 1; i <= tamano; i++)
  {
    c[i - 1] = cop[i];
  }
}

// Sobrecarga del operador igualdad
bool TVectorCom::operator==(const TVectorCom &tvcom) const
{
  if (this == &tvcom)
    return true;

  if (tamano != tvcom.Tamano())
    return false;

  for (int i = 0; i < tamano; i++)
  {
    if (c[i] != tvcom[i + 1])
      return false;
  }

  return true;
};

// Sobrecarga del operador desigualdad
bool TVectorCom::operator!=(const TVectorCom &tvcom) const
{
  return !(*this == tvcom);
};

// Sobrecarga del operador corchete (parte IZQUIERDA)
TComplejo &TVectorCom::operator[](const int index)
{
  if (index < 1 || index > tamano)
    return error;

  return c[index - 1];
};

// Sobrecarga del operador corchete (parte DERECHA)
TComplejo TVectorCom::operator[](const int index) const
{
  if (index < 1 || index > tamano)
  {
    TComplejo temp = TComplejo();
    return temp;
  }

  return c[index - 1];
};

// Tamaño del vector (posiciones TOTALES)
int TVectorCom::Tamano() const
{
  return tamano;
};

// Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
int TVectorCom::Ocupadas() const
{
  int ocupadas = 0;
  if (c == NULL)
    return tamano;

  for (int i = 0; i < tamano; i++)
  {
    if (!c[i].Empty())
      ocupadas++;
  }

  return ocupadas;
};

// Devuelve TRUE si existe el TComplejo en el vector
bool TVectorCom::ExisteCom(const TComplejo &tcom) const
{
  for (int i = 0; i < tamano; i++)
  {
    if (c[i] == tcom)
      return true;
  }

  return false;
};

// Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL IGUAL O POSTERIOR al argumento
void TVectorCom::MostrarComplejos(double value) const
{
  // Buscamos los datos
  TComplejo *temp = new TComplejo[tamano];
  if (temp == NULL)
    cerr << "No se pudo reservar memoria para crear un TComplejo en TVectorCom:MostrarComplejos:temp";

  int items = 0;

  for (int i = 0; i < tamano; i++)
  {
    if (c[i].Re() >= value)
    {
      temp[items] = c[i];
      items++;
    }
  }

  // Mostramos los datos.
  cout << "[";

  for (int i = 0; i < items - 1; i++)
  {
    cout << temp[i] << ", ";
  }

  if (items > 0)
    cout << temp[items - 1] << "]";
  else
    cout << "]";

  delete[] temp;
  temp = NULL;
};

// REDIMENSIONAR el vector de TComplejo
bool TVectorCom::Redimensionar(int newTamano)
{
  if (newTamano <= 0 || newTamano == tamano)
    return false;

  TVectorCom temp = TVectorCom(newTamano);
  for (int i = 0; i < newTamano && i < tamano; i++)
  {
    temp[i + 1] = c[i];
  }

  this->~TVectorCom();
  this->tamano = temp.tamano;
  c = new TComplejo[tamano];
  if (c == NULL)
    cerr << "No se pudo reservar memoria para crear un TComplejo en TVectorCom:TVectorCom:c";

  for (int i = 1; i <= newTamano; i++)
  {
    c[i - 1] = temp[i];
  }

  return true;
};

// Sobrecarga del operador salida
ostream &operator<<(ostream &ost, const TVectorCom &tvcom)
{
  ost << "[";

  for (int i = 0; i < tvcom.Tamano() - 1; i++)
  {
    ost << "(" << i + 1 << ") " << tvcom[i + 1] << ", ";
  }

  if (tvcom.Tamano() > 0)
    ost << "(" << tvcom.Tamano() << ") " << tvcom[tvcom.Tamano()] << "]";
  else if (tvcom.Tamano() == 0)
    ost << "]";
  return ost;
};