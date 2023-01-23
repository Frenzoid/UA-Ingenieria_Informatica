#include "tcomplejo.h"
#include "tvectorcom.h"

#ifndef _TABBCOM_
#define _TABBCOM_

#include <ostream>
using namespace std;

class TNodoABB;
class TABBCom
{
private:
  // Puntero al nodo
  TNodoABB *nodo;
  // AUXILIAR : Devuelve el recorrido en inorden
  void InordenAux(TVectorCom &, int &) const;
  // AUXILIAR : Devuelve el recorrido en preorden
  void PreordenAux(TVectorCom &, int &) const;
  // AUXILIAR : Devuelve el recorrido en postorden
  void PostordenAux(TVectorCom &, int &) const;

  void Copia(const TABBCom &);
  TComplejo Extremo() const;

public:
  // Constructor por defecto
  TABBCom();
  // Constructor de copia
  TABBCom(TABBCom &);
  // Destructor
  ~TABBCom();
  // Sobrecarga del operador asignación
  TABBCom &operator=(const TABBCom &);

  // MÉTODOS
  // Sobrecarga del operador igualdad
  bool operator==(const TABBCom &) const;
  // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
  bool EsVacio() const;
  // Inserta el elemento en el árbol
  bool Insertar(const TComplejo &);
  // Borra el elemento en el árbol
  bool Borrar(const TComplejo &);
  // Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
  bool Buscar(const TComplejo &) const;
  // Devuelve el elemento en la raíz del árbol
  TComplejo Raiz() const;
  // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
  int Altura() const;
  // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
  int Nodos() const;
  // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
  int NodosHoja() const;
  // Devuelve el recorrido en inorden
  TVectorCom Inorden() const;
  // Devuelve el recorrido en preorden
  TVectorCom Preorden() const;
  // Devuelve el recorrido en postorden
  TVectorCom Postorden() const;
  // Devuelve el recorrido en niveles
  TVectorCom Niveles() const;
  // Sobrecarga del operador salida
  friend ostream &operator<<(ostream &, const TABBCom &);

  friend class TNodoABB;
};

class TNodoABB
{
  // El elemento del nodo
  TComplejo item;
  // Subárbol izquierdo y derecho
  TABBCom iz, de;

public:
  // Constructor por defecto
  TNodoABB();
  // Constructor de copia
  TNodoABB(const TNodoABB &);
  // Destructor
  ~TNodoABB();
  // Sobrecarga del operador asignación
  TNodoABB &operator=(const TNodoABB &);

  friend class TABBCom;
};

#endif
