#include "tcomplejo.h"
#include "tvectorcom.h"

#ifndef _TLCOM_
#define _TLCOM_
class TListaNodo
{
private:
  // El elemento del nodo
  TComplejo e;

public:
  // El nodo anterior
  TListaNodo *anterior;
  // El nodo siguiente
  TListaNodo *siguiente;

  // Constructor por defecto
  TListaNodo();
  // Constructor de copia
  TListaNodo(const TListaNodo &);
  // Destructor
  ~TListaNodo();
  // Sobrecarga del operador asignación
  TListaNodo &operator=(const TListaNodo &);

  friend class TListaPos;
  friend class TListaCom;
};

class TListaPos
{
private:
  // Puntero a un nodo de la lista
  TListaNodo *pos;

public:
  // Constructor por defecto
  TListaPos();
  // Constructor de copia
  TListaPos(const TListaPos &);
  // Destructor
  ~TListaPos();
  // Sobrecarga del operador asignación
  TListaPos &operator=(const TListaPos &);

  // Sobrecarga del operador igualdad
  bool operator==(const TListaPos &) const;
  // Sobrecarga del operador desigualdad
  bool operator!=(const TListaPos &) const;
  // Devuelve la posición anterior
  TListaPos Anterior() const;
  // Devuelve la posición siguiente
  TListaPos Siguiente() const;
  // Devuelve TRUE si la posición no apunta a una lista, FALSE en caso contrario
  bool EsVacia() const;

  friend class TListaNodo;
  friend class TListaCom;
};

class TListaCom
{
private:
  // Primer elemento de la lista
  TListaNodo *primero;
  // Ultimo elemento de la lista
  TListaNodo *ultimo;
  void Copia(const TListaCom &);

public:
  // Constructor por defecto
  TListaCom();
  // Constructor de copia
  TListaCom(const TListaCom &);
  // Destructor
  ~TListaCom();

  // Sobrecarga del operador asignación
  TListaCom &operator=(const TListaCom &);
  // Sobrecarga del operador igualdad
  bool operator==(const TListaCom &) const;
  // Sobrecarga del operador desigualdad
  bool operator!=(const TListaCom &) const;

  // Sobrecarga del operador suma
  TListaCom operator+(const TListaCom &) const;
  // Sobrecarga del operador resta
  TListaCom operator-(const TListaCom &) const;

  // Devuelve true si la lista está vacía, false en caso contrario
  bool EsVacia() const;
  // Inserta el elemento en la cabeza de la lista
  bool InsCabeza(const TComplejo &);
  // Inserta el elemento a la izquierda de la posición indicada
  bool InsertarI(const TComplejo &, const TListaPos &);
  // Inserta el elemento a la derecha de la posición indicada
  bool InsertarD(const TComplejo &, const TListaPos &);
  // Busca y borra la primera ocurrencia del elemento
  bool Borrar(const TComplejo &);
  // Busca y borra todas las ocurrencias del elemento
  bool BorrarTodos(const TComplejo &);
  // Borra el elemento que ocupa la posición indicada
  bool Borrar(const TListaPos &);
  // Obtiene el elemento que ocupa la posición indicada
  TComplejo Obtener(const TListaPos &) const;
  // Devuelve true si el elemento está en la lista, false en caso contrario
  bool Buscar(const TComplejo &) const;
  // Devuelve la longitud de la lista
  int Longitud() const;
  // Devuelve la primera posición en la lista
  TListaPos Primera() const;
  // Devuelve la última posición en la lista
  TListaPos Ultima() const;

  // Sobrecarga del operador salida
  friend ostream &
  operator<<(ostream &, TListaCom &);

  friend class TListaNodo;
  friend class TListaPos;
};

#endif
