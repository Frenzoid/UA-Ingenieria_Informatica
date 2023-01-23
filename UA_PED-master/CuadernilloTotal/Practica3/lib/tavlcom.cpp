#include <iostream>
#include "tavlcom.h"
#include "tvectorcom.h"
#include <queue>

using namespace std;
// ----------------------------------------------------TNodoAVL
// Constructor por defecto IMPLICITO
TNodoAVL::TNodoAVL()
{
  fe = 1;
};

// Constructor de copia
TNodoAVL::TNodoAVL(const TNodoAVL &nodo)
{
  item = nodo.item;
  fe = nodo.fe;
};

// Destructor
TNodoAVL::~TNodoAVL()
{
  item.~TComplejo();
  iz.~TAVLCom();
  de.~TAVLCom();
};

// Sobrecarga del operador asignación
TNodoAVL &TNodoAVL::operator=(const TNodoAVL &nodo)
{
  this->item = nodo.item;
  this->iz = nodo.iz;
  this->de = nodo.de;
  return *this;
};

// ----------------------------------------------------TAVLCom

// AUXILIAR : Devuelve el recorrido en inorden
void TAVLCom::InordenAux(TVectorCom &vect, int &pos) const
{
  if (nodo == NULL)
    return;

  nodo->iz.InordenAux(vect, pos);
  vect[pos++] = nodo->item;
  nodo->de.InordenAux(vect, pos);
};

// AUXILIAR : Devuelve el recorrido en preorden
void TAVLCom::PreordenAux(TVectorCom &vect, int &pos) const
{
  if (nodo == NULL)
    return;

  vect[pos++] = nodo->item;
  nodo->iz.PreordenAux(vect, pos);
  nodo->de.PreordenAux(vect, pos);
};

// AUXILIAR : Devuelve el recorrido en postorden
void TAVLCom::PostordenAux(TVectorCom &vect, int &pos) const
{
  if (nodo == NULL)
    return;

  nodo->iz.PostordenAux(vect, pos);
  nodo->de.PostordenAux(vect, pos);
  vect[pos++] = nodo->item;
};

// Constructor por defecto
TAVLCom::TAVLCom()
{
  nodo = NULL;
};

// Constructor de copia
TAVLCom::TAVLCom(TAVLCom &arbol)
{
  Copia(arbol);
};

// Destructor
TAVLCom::~TAVLCom()
{
  if (nodo != NULL)
  {
    delete nodo;
    nodo = NULL;
  }
};

void TAVLCom::Copia(const TAVLCom &arbol)
{
  if (arbol.nodo != NULL)
  {
    TNodoAVL *tnod = new TNodoAVL();
    if (tnod == NULL)
    {
      cerr << "No se pudo reservar memoria para crear un TNodoABB en TABBCom:Copia";
    }

    tnod->item = arbol.nodo->item;
    nodo = tnod;

    nodo->iz.Copia(arbol.nodo->iz);
    nodo->de.Copia(arbol.nodo->de);
  }
  else
    nodo = NULL;
};

// Sobrecarga del operador asignación
TAVLCom &TAVLCom::operator=(const TAVLCom &arbol)
{
  if (this == &arbol)
    return *this;
  else
    this->~TAVLCom();

  Copia(arbol);
  return *this;
};

// MÉTODOS
// Sobrecarga del operador igualdad
bool TAVLCom::operator==(const TAVLCom &arbol) const
{
  return Inorden() == arbol.Inorden();
};

// Sobrecarga del operador desigualdad
bool TAVLCom::operator!=(const TAVLCom &arbol) const
{
  return !(*this == arbol);
};

// Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
bool TAVLCom::EsVacio() const
{
  return this->nodo == NULL ? true : false;
};

// ---------------------------------------- INSERTAR ------------------------------------------

// Inserta el elemento en el árbol
bool TAVLCom::Insertar(const TComplejo &comp)
{
  bool crece;
  return InsertarAux(comp, crece);
}

bool TAVLCom::InsertarAux(const TComplejo &comp, bool &crece)
{
  bool insertado = false;

  if (this->Buscar(comp))
    return false;

  if (EsVacio())
  {
    nodo = new TNodoAVL;
    if (this->nodo == NULL)
    {
      cerr << "No se pudo reservar memoria para crear un TNodoABB en TABBCom:InsertarAux";
    }

    nodo->item = comp;
    nodo->fe = 0;

    crece = true;
    insertado = true;
  }
  else if (nodo->item.Mod() != comp.Mod())
  {
    bool creceIz = false;
    bool creceDe = false;

    if (comp.Mod() < nodo->item.Mod())
    {
      insertado = nodo->iz.InsertarAux(comp, creceIz);
    }
    else
    {
      insertado = nodo->de.InsertarAux(comp, creceDe);
    }
    if (creceIz)
    {
      nodo->fe--;
      TNodoAVL *auxNodo, *auxNodIz, *auxNodDe;

      if (nodo->fe == 0)
        crece = false;
      else if (nodo->fe == -1)
        crece = true;
      else if (nodo->fe == -2)
      {
        crece = false;

        if (nodo->iz.nodo->fe == -1)
        {
          auxNodo = nodo;

          nodo = auxNodo->iz.nodo;
          auxNodo->iz.nodo = nodo->de.nodo;

          nodo->de.nodo = auxNodo;

          if (nodo->fe == 0)
          {
            nodo->fe = 1;
            nodo->de.nodo->fe = -1;
          }
          else
          {
            nodo->fe = 0;
            nodo->de.nodo->fe = 0;
          }
        }
        else if (nodo->iz.nodo->fe == 1)
        {

          auxNodo = nodo;

          nodo = nodo->iz.nodo->de.nodo;
          auxNodIz = nodo->iz.nodo;
          auxNodDe = nodo->de.nodo;

          nodo->iz.nodo = auxNodo->iz.nodo;
          nodo->de.nodo = auxNodo;
          auxNodo->iz.nodo = auxNodDe;

          nodo->iz.nodo->de.nodo = auxNodIz;

          if (nodo->fe == 0)
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
            nodo->de.nodo->fe = 0;
          }
          else if (nodo->fe == -1)
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
            nodo->de.nodo->fe = 1;
          }
          else
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = -1;
            nodo->de.nodo->fe = 0;
          }
        }
      }
    }
    else if (creceDe)
    {
      nodo->fe++;

      if (nodo->fe == 0)
        crece = false;
      else if (nodo->fe == 1)
        crece = true;
      else if (nodo->fe == 2)
      {
        crece = false;
        TNodoAVL *auxNodo, *auxNodIz, *auxNodDe;

        if (nodo->de.nodo->fe == -1)
        {
          auxNodo = nodo;

          nodo = nodo->de.nodo->iz.nodo;
          auxNodIz = nodo->iz.nodo;
          auxNodDe = nodo->de.nodo;

          nodo->de.nodo = auxNodo->de.nodo;
          nodo->iz.nodo = auxNodo;
          auxNodo->de.nodo = auxNodIz;

          nodo->de.nodo->iz.nodo = auxNodDe;

          if (nodo->fe == 0)
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
            nodo->de.nodo->fe = 0;
          }
          else if (nodo->fe == -1)
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
            nodo->de.nodo->fe = 1;
          }
          else
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = -1;
            nodo->de.nodo->fe = 0;
          }
        }
        else if (nodo->de.nodo->fe == 1)
        {
          auxNodo = nodo;

          nodo = auxNodo->de.nodo;
          auxNodo->de.nodo = nodo->iz.nodo;

          nodo->iz.nodo = auxNodo;

          if (nodo->fe == 0)
          {
            nodo->iz.nodo->fe = 1;
            nodo->fe = -1;
          }
          else
          {
            nodo->iz.nodo->fe = 0;
            nodo->fe = 0;
          }
        }
      }
    }
  }
  else
  {
    insertado = false;
    crece = false;
  }

  return insertado;
}

// ---------------------------------------- BORRAR ------------------------------------------

// Borra el elemento en el árbol
bool TAVLCom::Borrar(const TComplejo &comp)
{
  bool decrece;
  return BorrarAux(comp, decrece);
}

bool TAVLCom::BorrarAux(const TComplejo &comp, bool &decrece)
{
  bool borrado = false;
  bool decreceIz = false;
  bool decreceDe = false;

  TComplejo mayorIz;
  TNodoAVL *nodoBorrar, *nodoAux;

  if (!this->Buscar(comp))
    return false;

  if (!nodo)
  {
    decrece = false;
    borrado = false;
  }
  else if (comp.Mod() < nodo->item.Mod())
  {
    borrado = nodo->iz.BorrarAux(comp, decreceIz);
  }
  else if (comp.Mod() > nodo->item.Mod())
  {
    borrado = nodo->de.BorrarAux(comp, decreceDe);
  }
  else if (nodo->item == comp)
  { // nodo hoja
    if (nodo->iz.EsVacio() && nodo->de.EsVacio())
    {
      delete nodo;
      nodo = NULL;

      borrado = true;
      decrece = true;
    } // 1 hijo izq
    else if (!nodo->iz.EsVacio() && nodo->de.EsVacio())
    {
      nodoBorrar = nodo;
      nodo = nodo->iz.nodo;

      nodoBorrar->iz.nodo = NULL;
      nodoBorrar->de.nodo = NULL;
      delete nodoBorrar;

      borrado = true;
      decrece = true;
    } // 1 hijo der
    else if (nodo->iz.EsVacio() && !nodo->de.EsVacio())
    {
      nodoBorrar = nodo;
      nodo = nodo->de.nodo;

      nodoBorrar->iz.nodo = NULL;
      nodoBorrar->de.nodo = NULL;
      delete nodoBorrar;

      borrado = true;
      decrece = true;
    }
    else // 2 hujos
    {
      mayorIz = nodo->iz.Extremo();
      nodoAux = nodo;
      borrado = BorrarAux(mayorIz, decrece);
      nodoAux->item = mayorIz;
    }
  }

  if (borrado)
  {
    if (decreceIz)
    {
      nodo->fe++;
      TNodoAVL *auxNodo, *auxNodIz, *auxNodDe;

      if (nodo->fe == 0)
        decrece = true;
      else if (nodo->fe == 1)
        decrece = false;
      else if (nodo->fe == 2)
      {

        if (nodo->de.nodo->fe == -1)
        {
          auxNodo = nodo;

          nodo = nodo->de.nodo->iz.nodo;
          auxNodIz = nodo->iz.nodo;
          auxNodDe = nodo->de.nodo;

          nodo->de.nodo = auxNodo->de.nodo;
          nodo->iz.nodo = auxNodo;
          auxNodo->de.nodo = auxNodIz;

          nodo->de.nodo->iz.nodo = auxNodDe;

          if (nodo->fe == 0)
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
            nodo->de.nodo->fe = 0;
          }
          else if (nodo->fe == -1)
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
            nodo->de.nodo->fe = 1;
          }
          else
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = -1;
            nodo->de.nodo->fe = 0;
          }

          decrece = true;
        }
        else if (nodo->de.nodo->fe == 0)
        {
          auxNodo = nodo;

          nodo = auxNodo->de.nodo;
          auxNodo->de.nodo = nodo->iz.nodo;

          nodo->iz.nodo = auxNodo;
          if (nodo->fe == 0)
          {
            nodo->fe = -1;
            nodo->iz.nodo->fe = 1;
          }
          else
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
          }

          decrece = false;
        }
        else if (nodo->de.nodo->fe == 1)
        {
          auxNodo = nodo;

          nodo = auxNodo->de.nodo;
          auxNodo->de.nodo = nodo->iz.nodo;

          nodo->iz.nodo = auxNodo;

          if (nodo->fe == 0)
          {
            nodo->fe = -1;
            nodo->iz.nodo->fe = 1;
          }
          else
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
          }
          decrece = true;
        }
      }
    }
    else if (decreceDe)
    {
      nodo->fe--;
      TNodoAVL *auxNodo, *auxNodIz, *auxNodDe;

      if (nodo->fe == 0)
        decrece = true;
      else if (nodo->fe == 1)
        decrece = false;
      else if (nodo->fe == -2)
      {
        if (nodo->iz.nodo->fe == -1)
        {
          auxNodo = nodo;

          nodo = auxNodo->iz.nodo;
          auxNodo->iz.nodo = nodo->de.nodo;

          nodo->de.nodo = auxNodo;

          if (nodo->fe == 0)
          {
            nodo->fe = 1;
            nodo->de.nodo->fe = -1;
          }
          else
          {
            nodo->fe = 0;
            nodo->de.nodo->fe = 0;
          }
          decrece = true;
        }
        else if (nodo->iz.nodo->fe == 0)
        {
          auxNodo = nodo;

          nodo = auxNodo->iz.nodo;
          auxNodo->iz.nodo = nodo->de.nodo;

          nodo->de.nodo = auxNodo;

          if (nodo->fe == 0)
          {
            nodo->fe = 1;
            nodo->de.nodo->fe = -1;
          }
          else
          {
            nodo->fe = 0;
            nodo->de.nodo->fe = 0;
          }

          decrece = false;
        }
        else if (nodo->iz.nodo->fe == 1)
        {
          auxNodo = nodo;

          nodo = nodo->iz.nodo->de.nodo;
          auxNodIz = nodo->iz.nodo;
          auxNodDe = nodo->de.nodo;

          nodo->iz.nodo = auxNodo->iz.nodo;
          nodo->de.nodo = auxNodo;
          auxNodo->iz.nodo = auxNodDe;

          nodo->iz.nodo->de.nodo = auxNodIz;

          if (nodo->fe == 0)
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
            nodo->de.nodo->fe = 0;
          }
          else if (nodo->fe == -1)
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = 0;
            nodo->de.nodo->fe = 1;
          }
          else
          {
            nodo->fe = 0;
            nodo->iz.nodo->fe = -1;
            nodo->de.nodo->fe = 0;
          }

          decrece = true;
        }
      }
    }
  }
  return borrado;
}

TComplejo TAVLCom::Extremo() const
{
  TComplejo aux;
  if (nodo->de.EsVacio())
    aux = nodo->item;
  else
    aux = nodo->de.Extremo();
  return aux;
}

// Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
bool TAVLCom::Buscar(const TComplejo &comp) const
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
TComplejo TAVLCom::Raiz() const
{
  if (nodo == NULL)
    return TComplejo();
  else
    return nodo->item;
};

// Devuelve la altura del árbol (la altura de un árbol vacío es 0)
int TAVLCom::Altura() const
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
int TAVLCom::Nodos() const
{
  int nodos = 0;
  if (nodo != NULL)
    nodos = 1 + nodo->iz.Nodos() + nodo->de.Nodos();

  return nodos;
};

// Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
int TAVLCom::NodosHoja() const
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
TVectorCom TAVLCom::Inorden() const
{
  // Posición en el vector que almacena el recorrido
  int posicion = 1;

  // Vector del tamaño adecuado para almacenar todos los nodos
  TVectorCom v(Nodos());
  InordenAux(v, posicion);
  return v;
};

// Devuelve el recorrido en preorden
TVectorCom TAVLCom::Preorden() const
{
  // Posición en el vector que almacena el recorrido
  int posicion = 1;

  // Vector del tamaño adecuado para almacenar todos los nodos
  TVectorCom v(Nodos());
  PreordenAux(v, posicion);
  return v;
};

// Devuelve el recorrido en postorden
TVectorCom TAVLCom::Postorden() const
{
  // Posición en el vector que almacena el recorrido
  int posicion = 1;

  // Vector del tamaño adecuado para almacenar todos los nodos
  TVectorCom v(Nodos());
  PostordenAux(v, posicion);
  return v;
};

// Devuelve el recorrido en niveles
TVectorCom TAVLCom::Niveles() const
{
  TVectorCom tvec(Nodos());

  queue<TNodoAVL *> cola;
  TNodoAVL *aux;
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
ostream &operator<<(ostream &ost, const TAVLCom &arbol)
{
  ost << arbol.Niveles();
  return ost;
};
