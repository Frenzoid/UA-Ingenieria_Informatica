#include <iostream>
#include "tabbcom.h"
#include "tvectorcom.h"
#include <queue>

using namespace std;
// ----------------------------------------------------TNodoABB
// Constructor por defecto IMPLICITO
TNodoABB::TNodoABB(){};

// Constructor de copia
TNodoABB::TNodoABB(const TNodoABB &nodo)
{
  item = nodo.item;
};

// Destructor
TNodoABB::~TNodoABB()
{
  item.~TComplejo();
  iz.~TABBCom();
  de.~TABBCom();
};

// Sobrecarga del operador asignación
TNodoABB &TNodoABB::operator=(const TNodoABB &nodo)
{
  this->item = nodo.item;
  this->iz = nodo.iz;
  this->de = nodo.de;
  return *this;
};

// ----------------------------------------------------TABBCom

// AUXILIAR : Devuelve el recorrido en inorden
void TABBCom::InordenAux(TVectorCom &vect, int &pos) const
{
  if (nodo == NULL)
    return;

  nodo->iz.InordenAux(vect, pos);
  vect[pos++] = nodo->item;
  nodo->de.InordenAux(vect, pos);
};

// AUXILIAR : Devuelve el recorrido en preorden
void TABBCom::PreordenAux(TVectorCom &vect, int &pos) const
{
  if (nodo == NULL)
    return;

  vect[pos++] = nodo->item;
  nodo->iz.PreordenAux(vect, pos);
  nodo->de.PreordenAux(vect, pos);
};

// AUXILIAR : Devuelve el recorrido en postorden
void TABBCom::PostordenAux(TVectorCom &vect, int &pos) const
{
  if (nodo == NULL)
    return;

  nodo->iz.PostordenAux(vect, pos);
  nodo->de.PostordenAux(vect, pos);
  vect[pos++] = nodo->item;
};

// Constructor por defecto
TABBCom::TABBCom()
{
  nodo = NULL;
};

// Constructor de copia
TABBCom::TABBCom(TABBCom &arbol)
{
  Copia(arbol);
};

// Destructor
TABBCom::~TABBCom()
{
  if (nodo != NULL)
  {
    delete nodo;
    nodo = NULL;
  }
};

void TABBCom::Copia(const TABBCom &arbol)
{
  if (arbol.nodo != NULL)
  {
    TNodoABB *tnod = new TNodoABB();
    tnod->item = arbol.nodo->item;
    nodo = tnod;

    nodo->iz.Copia(arbol.nodo->iz);
    nodo->de.Copia(arbol.nodo->de);
  }
  else
    nodo = NULL;
};

// Sobrecarga del operador asignación
TABBCom &TABBCom::operator=(const TABBCom &arbol)
{
  if (this == &arbol)
    return *this;
  else
    this->~TABBCom();

  Copia(arbol);
  return *this;
};

// MÉTODOS
// Sobrecarga del operador igualdad
bool TABBCom::operator==(const TABBCom &arbol) const
{
  return Inorden() == arbol.Inorden();
};

// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TABBCom::EsVacio() const
{
  return this->nodo == NULL ? true : false;
};

// Inserta el elemento en el árbol
bool TABBCom::Insertar(const TComplejo &comp)
{
  if (Buscar(comp))
    return false;

  if (this->nodo == NULL)
  {
    this->nodo = new TNodoABB();

    if (this->nodo == NULL)
    {
      cerr << "No se pudo reservar memoria para crear un TNodoABB en TABBCom:Insertar";
      return false;
    }

    nodo->item = comp;
    return true;
  }
  else
  {
    if (nodo->item < comp)
      return nodo->de.Insertar(comp);
    else if (nodo->item > comp)
      return nodo->iz.Insertar(comp);
  }

  return false;
};

// Borra el elemento en el árbol
bool TABBCom::Borrar(const TComplejo &comp)
{
  bool borrado;
  TNodoABB *aux;
  TComplejo mayorIzq;

  if (nodo == NULL)
    borrado = false;
  else
  {
    // Una vez encontrado el elemento...
    if (comp == nodo->item)
    {
      borrado = true;

      // comprobamos, y si sus ramas son vacias, borramos.
      if (nodo->iz.EsVacio() && nodo->de.EsVacio())
      {
        delete nodo;
        nodo = NULL;
      }
      else
      {
        // SI iz es vacio, reajustamos en la de
        if (nodo->iz.EsVacio())
        {
          aux = nodo;
          nodo = nodo->de.nodo;
          aux->de.nodo = NULL;
          delete aux;
          aux = NULL;
        } // Si derecha es vacio, reajustamos en la iz
        else if (nodo->de.EsVacio())
        {
          aux = nodo;
          nodo = nodo->iz.nodo;
          aux->iz.nodo = NULL;
          delete aux;
          aux = NULL;
        }
        else
        { // si ambos estan populados, buscamos el mayor de la iz para reajustar.
          mayorIzq = nodo->iz.Extremo();
          nodo->iz.Borrar(mayorIzq);
          nodo->item = mayorIzq;
        }
      }
    } // si no es el que estamos buscando, comparamos, y ejecutamos la funcion
    // recursiva en la rama respectiva.
    else
    {
      if (comp > nodo->item)
        borrado = nodo->de.Borrar(comp);
      else
        borrado = nodo->iz.Borrar(comp);
    }
  }
  return borrado;
};

TComplejo TABBCom::Extremo() const
{
  TComplejo aux;
  if (nodo->de.EsVacio())
    aux = nodo->item;
  else
    aux = nodo->de.Extremo();
  return aux;
}

// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TABBCom::Buscar(const TComplejo &comp) const
{
  if (nodo == NULL)
    return false;

  if (comp == nodo->item)
    return true;

  if (nodo->iz.Buscar(comp) || nodo->de.Buscar(comp))
    return true;

  return false;
};

// Devuelve el elemento en la raíz del árbol
TComplejo TABBCom::Raiz() const
{
  if (nodo == NULL)
    return TComplejo();
  else
    return nodo->item;
};

// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TABBCom::Altura() const
{
  int a1, a2;
  if (nodo != NULL)
  {
    a1 = nodo->iz.Altura();
    a2 = nodo->de.Altura();
    return (1 + (a1 < a2 ? a2 : a1));
  }
  else
    return 0;
};

// Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
int TABBCom::Nodos() const
{
  int nodos = 0;
  if (nodo != NULL)
    nodos = 1 + nodo->iz.Nodos() + nodo->de.Nodos();

  return nodos;
};

// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TABBCom::NodosHoja() const
{
  if (nodo == NULL)
    return 0;
  else if (nodo->iz.nodo == NULL && nodo->de.nodo == NULL)
    return 1;
  else
    return nodo->iz.NodosHoja() + nodo->de.NodosHoja();

  return 0;
};

// Devuelve el recorrido en inorden
TVectorCom TABBCom::Inorden() const
{
  // Posición en el vector que almacena el recorrido
  int posicion = 1;

  // Vector del tamaño adecuado para almacenar todos los nodos
  TVectorCom v(Nodos());
  InordenAux(v, posicion);
  return v;
};

// Devuelve el recorrido en preorden
TVectorCom TABBCom::Preorden() const
{
  // Posición en el vector que almacena el recorrido
  int posicion = 1;

  // Vector del tamaño adecuado para almacenar todos los nodos
  TVectorCom v(Nodos());
  PreordenAux(v, posicion);
  return v;
};

// Devuelve el recorrido en postorden
TVectorCom TABBCom::Postorden() const
{
  // Posición en el vector que almacena el recorrido
  int posicion = 1;

  // Vector del tamaño adecuado para almacenar todos los nodos
  TVectorCom v(Nodos());
  PostordenAux(v, posicion);
  return v;
};

// Devuelve el recorrido en niveles
TVectorCom TABBCom::Niveles() const
{
  TVectorCom tvec(Nodos());

  queue<TNodoABB *> cola;
  TNodoABB *aux;
  int i = 1;
  cola.push(nodo);

  while (!cola.empty())
  {
    aux = cola.front();
    cola.pop();

    if (aux != NULL)
    {
      tvec[i++] = aux->item;
      cola.push(aux->iz.nodo);
      cola.push(aux->de.nodo);
    }
  }

  return tvec;
};

// Sobrecarga del operador salida
ostream &operator<<(ostream &ost, const TABBCom &arbol)
{
  ost << arbol.Niveles();
  return ost;
};