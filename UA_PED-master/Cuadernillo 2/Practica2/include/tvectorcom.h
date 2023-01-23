#include "tcomplejo.h"
#include <string>

#ifndef _TVECTORCOM_
#define _TVECTORCOM_

class TVectorCom
{
private:
  TComplejo *c;
  TComplejo error;
  int tamano;

  void Copia(const TVectorCom &);

public:
  // Constructor a partir de un tamaño
  TVectorCom(const int = 0);

  // Constructor de copia
  TVectorCom(const TVectorCom &);

  // Destructor
  ~TVectorCom();

  // Sobrecarga del operador asignación
  TVectorCom &operator=(const TVectorCom &);

  // Sobrecarga del operador igualdad
  bool operator==(const TVectorCom &) const;

  // Sobrecarga del operador desigualdad
  bool operator!=(const TVectorCom &) const;

  // Sobrecarga del operador corchete (parte IZQUIERDA)
  TComplejo &operator[](const int);

  // Sobrecarga del operador corchete (parte DERECHA)
  TComplejo operator[](const int) const;

  // Tamaño del vector (posiciones TOTALES)
  int Tamano() const;

  // Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
  int Ocupadas() const;

  // Devuelve TRUE si existe el TComplejo en el vector
  bool ExisteCom(const TComplejo &) const;

  // Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL IGUAL O POSTERIOR al argumento
  void MostrarComplejos(double) const;

  // REDIMENSIONAR el vector de TComplejo
  bool Redimensionar(int);

  // Sobrecarga del operador salida
  friend ostream &
  operator<<(ostream &, const TVectorCom &);
};

#endif // !_TVCOMPLEJO_
