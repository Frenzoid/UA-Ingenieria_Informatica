#include "tcomplejo.h"
#include "tvectorcom.h"

#ifndef _TAVLCOM_
#define _TAVLCOM_

#include <ostream>
using namespace std;

class TNodoAVL;
class TAVLCom
{
private:
  // Puntero al nodo
  TNodoAVL *nodo;

  // AUXILIAR : Devuelve el recorrido en inorden
  void InordenAux(TVectorCom &, int &) const;
  // AUXILIAR : Devuelve el recorrido en preorden
  void PreordenAux(TVectorCom &, int &) const;
  // AUXILIAR : Devuelve el recorrido en postorden
  void PostordenAux(TVectorCom &, int &) const;

  TComplejo Extremo() const;

  bool BorrarAux(const TComplejo &, bool &);
  bool InsertarAux(const TComplejo &, bool &);

  void Copia(const TAVLCom &);

public:
  // Constructor por defecto
  TAVLCom();
  // Constructor de copia
  TAVLCom(TAVLCom &);
  // Destructor
  ~TAVLCom();
  // Sobrecarga del operador asignación
  TAVLCom &operator=(const TAVLCom &);

  // MÉTODOS
  // Sobrecarga del operador igualdad
  bool operator==(const TAVLCom &) const;
  // Sobrecarga del operador desigualdad
  bool operator!=(const TAVLCom &) const;
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
  friend ostream &operator<<(ostream &, const TAVLCom &);

  friend class TNodoAVL;
};

class TNodoAVL
{
  // El elemento del nodo
  TComplejo item;
  // Subárbol izquierdo y derecho
  TAVLCom iz, de;
  // Factor de equilibrio
  int fe;

public:
  // Constructor por defecto
  TNodoAVL();
  // Constructor de copia
  TNodoAVL(const TNodoAVL &);
  // Destructor
  ~TNodoAVL();
  // Sobrecarga del operador asignación
  TNodoAVL &operator=(const TNodoAVL &);

  friend class TAVLCom;
};

#endif
