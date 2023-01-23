#include <iostream>
#include "tlistacom.h"

using namespace std;

// ----------------------------------------------------------------TLNODO

// Constructor por defecto
TListaNodo::TListaNodo()
{
  e = TComplejo();
  anterior = NULL;
  siguiente = NULL;
};

// Constructor de copia
TListaNodo::TListaNodo(const TListaNodo &tlnodo)
{
  e = TComplejo(tlnodo.e);
};

// Destructor
TListaNodo::~TListaNodo()
{
  e.~TComplejo();
};

// Sobrecarga del operador asignación
TListaNodo &
TListaNodo::operator=(const TListaNodo &tlnodo) // ? (Se iguala la instancia al puntero o solo el tcomplejo?)
{
  e = TComplejo(tlnodo.e);
  return *this;
};

// ----------------------------------------------------------------TLISTAPOS

TListaPos::TListaPos()
{
  pos = NULL;
};

TListaPos::TListaPos(const TListaPos &tlpos)
{
  pos = tlpos.pos;
};

TListaPos::~TListaPos()
{
  pos = NULL;
};

TListaPos &
TListaPos::operator=(const TListaPos &tlpos)
{
  pos = tlpos.pos;
  return *this;
};

bool TListaPos::operator==(const TListaPos &tlpos) const
{
  if (pos == tlpos.pos)
    return true;
  return false;
};

bool TListaPos::operator!=(const TListaPos &tlpos) const
{
  return !(*this == tlpos);
};

TListaPos TListaPos::Siguiente() const
{
  TListaPos tps;
  tps.pos = NULL;

  if ((*pos).siguiente != NULL)
  {
    tps.pos = (*pos).siguiente;
  }

  return tps;
};

TListaPos TListaPos::Anterior() const
{
  TListaPos tps;
  tps.pos = NULL;

  if ((*pos).anterior)
  {
    tps.pos = (*pos).anterior;
  }
  return tps;
};

bool TListaPos::EsVacia() const
{
  if (pos == NULL)
    return true;

  return false;
};

// ----------------------------------------------------------------TLISTACOM

void TListaCom::Copia(const TListaCom &tlcom) //--
{
  if (!tlcom.EsVacia())
  {

    TListaPos tlp;
    tlp.pos = tlcom.ultimo;

    // Comprobabmos Actual -> Insertamos Actual -> Pasamos a Anterior.
    while (!tlp.EsVacia()) // Revisa si la posición actual
    {
      TComplejo comp = tlcom.Obtener(tlp);
      InsCabeza(comp);      // Insertamos la actual.
      tlp = tlp.Anterior(); // Pasamos a la posición anterior
    }
  }
};

// Constructor por defecto
TListaCom::TListaCom() //--
{
  primero = NULL;
  ultimo = NULL;
};

// Constructor de copia
TListaCom::TListaCom(const TListaCom &tlcom) //--
{
  primero = NULL;
  ultimo = NULL;
  Copia(tlcom);
};

// Destructor
TListaCom::~TListaCom() //--
{
  if (Longitud() == 1)
  {
    // Borramos solo el primero porque el primero esta enlazado al segundo.
    delete primero;

    primero = NULL;
    ultimo = NULL;
  }
  else
  {
    TListaPos tlp;
    tlp.pos = primero;

    // Comprobabmos Actual -> Pasamos a Siguiente -> Borramos Anterior .
    while (!tlp.EsVacia())
    {
      if (!tlp.Siguiente().EsVacia())
      {
        tlp = tlp.Siguiente();

        if (tlp.Anterior().pos == primero)
        {
          delete tlp.Anterior().pos;
          primero = NULL;
        }
        else
        {
          delete tlp.Anterior().pos;
        }
      }
      else if (tlp.Siguiente().EsVacia())
      {
        delete ultimo;
        ultimo = NULL;
        tlp.pos = NULL;
      }
    }
  }
};

// Sobrecarga del operador asignación
TListaCom &
TListaCom::operator=(const TListaCom &tlcom) //--
{
  if (this == &tlcom)
    return *this;

  if (!EsVacia())
  {
    (*this).~TListaCom();
  }

  Copia(tlcom);

  return *this;
};
// Sobrecarga del operador igualdad
bool TListaCom::operator==(const TListaCom &tlcom) const //--
{
  TListaPos tlp, tlpg;

  tlp.pos = primero;
  tlpg.pos = tlcom.primero;

  if (Longitud() != tlcom.Longitud())
    return false;

  while (!tlp.EsVacia() && !tlpg.EsVacia())
  {
    if (Obtener(tlp) != tlcom.Obtener(tlpg))
      return false;

    tlp = tlp.Siguiente();
    tlpg = tlpg.Siguiente();
  }

  return true;
};
// Sobrecarga del operador desigualdad
bool TListaCom::operator!=(const TListaCom &tlcom) const //--
{
  return !(this == &tlcom);
};

// Sobrecarga del operador suma
TListaCom TListaCom::operator+(const TListaCom &tlcom) const //--
{
  TListaCom nls = tlcom;

  if (tlcom.EsVacia())
  {
    return *this;
  }

  TListaPos tpl;
  tpl.pos = ultimo;

  while (!tpl.EsVacia())
  {
    nls.InsCabeza(Obtener(tpl));
    tpl = tpl.Anterior();
  }

  return nls;
};

// Sobrecarga del operador resta
TListaCom TListaCom::operator-(const TListaCom &tlcom) const //--
{
  TListaCom nls;
  nls = *this;

  if (tlcom.EsVacia() || nls.EsVacia())
  {
    return nls;
  }

  TListaPos tlp, tlpg;

  tlp.pos = nls.primero;
  tlpg.pos = tlcom.primero;

  while (!tlpg.EsVacia())
  {
    while (!tlp.EsVacia())
    {
      if (nls.Obtener(tlp) == tlcom.Obtener(tlpg))
      {
        // [NL]|[P0]|[S0] <-> [A1]|[P1]|[S1] <-> [A2]|[P2]|[NL]
        // [NL]|[P0]|[S0] <-> [A2]|[P2]|[NL] / [A0]|[P1]|[S2]

        // Nos guardamos la instancia a borrar
        TListaNodo *borrar = tlp.pos;

        // Des-enlazamos la instancia a borrar de los vecinos, pero no los vecinos de la instancia, no todavia.
        if (!tlp.Siguiente().EsVacia() && !tlp.Anterior().EsVacia())
        { // Caso en el que el nodo esta en medio
          (*tlp.Siguiente().pos).anterior = tlp.Anterior().pos;
          (*tlp.Anterior().pos).siguiente = tlp.Siguiente().pos;
        }
        else if (!tlp.Anterior().EsVacia() && tlp.Siguiente().EsVacia())
        { // Caso en el que el nodo esta en el extremo derecho
          (*tlp.Anterior().pos).siguiente = NULL;
          nls.ultimo = tlp.Anterior().pos;
        }
        else if (!tlp.Siguiente().EsVacia() && tlp.Anterior().EsVacia())
        { // Caso en el que el nodo esta en el extremo izquierda
          (*tlp.Siguiente().pos).anterior = NULL;
          nls.primero = tlp.Siguiente().pos;
        }
        else if (tlp.Siguiente().EsVacia() && tlp.Anterior().EsVacia())
        { // Caso en el que es el unico elemento de la lista
          nls.primero = NULL;
          nls.ultimo = NULL;
        }

        // Actualizamos a la posición siguiente antes de borrar la instancia.
        tlp = tlp.Siguiente();

        // Borramos la istancia.
        delete borrar;
        borrar = NULL;
      }
      else
      {
        tlp = tlp.Siguiente();
      }
    }

    tlp.pos = nls.primero;
    tlpg = tlpg.Siguiente();
  }

  return nls;
};

// Devuelve true si la lista está vacía, false en caso contrario
bool TListaCom::EsVacia() const //--
{
  if (primero == NULL && ultimo == NULL)
    return true;
  return false;
};

// Inserta el elemento en la cabeza de la lista
bool TListaCom::InsCabeza(const TComplejo &tcomp) //--
{
  TListaNodo *nodcab = new TListaNodo();

  if (nodcab == NULL)
  {
    cerr << "No se pudo reservar memoria para crear un TListaNodo en TListaCom:InsCab:nodcab";
    return false;
  }

  (*nodcab).e = tcomp;

  if (EsVacia())
  {
    primero = nodcab;
    ultimo = nodcab;
  }
  else
  {
    (*primero).anterior = nodcab;
    (*nodcab).siguiente = primero;
    primero = nodcab;
  }

  return true;
};
// Inserta el elemento a la izquierda de la posición indicada
bool TListaCom::InsertarI(const TComplejo &tcomp, const TListaPos &tlpos) //--
{
  if (tlpos.EsVacia())
    return false;

  TListaNodo *tln = new TListaNodo();
  if (tln == NULL)
  {
    cerr << "No se pudo reservar memoria para crear un TListaNodo en TListaCom:InsertarI:tln";
    return false;
  }

  // Enlazamos el nodo anterior a la posicion actual
  // Si anterior es Vacia, significa que estamos insertando en cabeza.
  if (!tlpos.Anterior().EsVacia())
  {
    (*tlpos.Anterior().pos).siguiente = tln;
    (*tln).anterior = tlpos.Anterior().pos;
  }
  else if (tlpos.Anterior().EsVacia())
    primero = tln;

  // Enlazamos el nodo siguiente a la posición actual
  (*tlpos.pos).anterior = tln;
  (*tln).siguiente = tlpos.pos;

  (*tln).e = tcomp;

  return true;
};

// Inserta el elemento a la derecha de la posición indicada
bool TListaCom::InsertarD(const TComplejo &tcomp, const TListaPos &tlpos) //--
{
  if (tlpos.EsVacia())
    return false;

  TListaNodo *tln = new TListaNodo();
  if (tln == NULL)
  {
    cerr << "No se pudo reservar memoria para crear un TListaNodo en TListaCom:InsertarI:tln";
    return false;
  }

  // Enlazamos los vecinos
  if (!tlpos.Siguiente().EsVacia())
  {
    (*tlpos.Siguiente().pos).anterior = tln;
    (*tln).siguiente = tlpos.Siguiente().pos;
  }
  else if (tlpos.Siguiente().EsVacia())
    ultimo = tln;

  (*tlpos.pos).siguiente = tln;
  (*tln).anterior = tlpos.pos;

  (*tln).e = tcomp;

  return true;
};

// Busca y borra la primera ocurrencia del elemento
bool TListaCom::Borrar(const TComplejo &tcomp) //--
{
  TListaPos tlp;
  tlp.pos = primero;

  while (!tlp.EsVacia())
  {
    if (Obtener(tlp) == tcomp)
    {
      Borrar(tlp);
      return true;
    }

    tlp = tlp.Siguiente();
  }

  return false;
};

// Busca y borra todas las ocurrencias del elemento
bool TListaCom::BorrarTodos(const TComplejo &tcomp)
{
  TListaPos tlp;
  tlp.pos = primero;

  bool borrado = false;

  while (!tlp.EsVacia())
  {
    if (Obtener(tlp) == tcomp)
    {
      borrado = true;
      TListaPos borrar;
      if (!tlp.Siguiente().EsVacia())
      {
        tlp = tlp.Siguiente();
        borrar = tlp.Anterior();
      }
      else
        borrar = tlp;

      Borrar(borrar);
    }
    else
    {
      tlp = tlp.Siguiente();
    }
  }

  return borrado;
};

// Borra el elemento que ocupa la posición indicada
bool TListaCom::Borrar(const TListaPos &tlpos)
{
  TListaPos tlp = tlpos;

  if (tlpos.EsVacia())
    return false;

  if (!tlp.Siguiente().EsVacia() && !tlp.Anterior().EsVacia())
  { // Caso en el que el nodo esta en medio
    (*tlp.Siguiente().pos).anterior = tlp.Anterior().pos;
    (*tlp.Anterior().pos).siguiente = tlp.Siguiente().pos;
  }
  else if (!tlp.Anterior().EsVacia() && tlp.Siguiente().EsVacia())
  { // Caso en el que el nodo esta en el extremo derecho
    (*tlp.Anterior().pos).siguiente = NULL;
    ultimo = tlp.Anterior().pos;
  }
  else if (!tlp.Siguiente().EsVacia() && tlp.Anterior().EsVacia())
  { // Caso en el que el nodo esta en el extremo izquierda
    (*tlp.Siguiente().pos).anterior = NULL;
    primero = tlp.Siguiente().pos;
  }
  else if (tlp.Siguiente().EsVacia() && tlp.Anterior().EsVacia())
  { // Caso en el que es el unico elemento de la lista
    primero = NULL;
    ultimo = NULL;
  }

  delete tlp.pos;
  tlp.pos = NULL;

  return true;
};

// Obtiene el elemento que ocupa la posición indicada
TComplejo TListaCom::Obtener(const TListaPos &tlpos) const //--
{
  TComplejo vacio = TComplejo();
  if (tlpos.EsVacia())
    return vacio;

  return (*tlpos.pos).e;
};

// Devuelve true si el elemento está en la lista, false en caso contrario
bool TListaCom::Buscar(const TComplejo &tcomp) const //--
{
  TListaPos tlp;
  tlp.pos = primero;

  while (!tlp.EsVacia())
  {
    if (Obtener(tlp) == tcomp)
    {
      return true;
    }

    tlp = tlp.Siguiente();
  }

  return false;
};
// Devuelve la longitud de la lista
int TListaCom::Longitud() const //--
{
  int contador = 0;
  TListaPos tps = Primera();

  while (!tps.EsVacia())
  {
    contador++;
    tps = tps.Siguiente();
  }

  return contador;
};
// Devuelve la primera posición en la lista
TListaPos TListaCom::Primera() const //-
{
  TListaPos tps;
  tps.pos = primero;
  return tps;
};
// Devuelve la última posición en la lista
TListaPos TListaCom::Ultima() const //-
{
  TListaPos tps;
  tps.pos = ultimo;
  return tps;
};

// Sobrecarga del operador salida
ostream &operator<<(ostream &ost, TListaCom &tlcom)
{
  TListaPos tlp = tlcom.Primera();

  ost << "{";

  while (!tlp.EsVacia())
  {
    if (!tlp.Siguiente().EsVacia())
      ost << tlcom.Obtener(tlp) << " ";
    else
      ost << tlcom.Obtener(tlp);

    tlp = tlp.Siguiente();
  }

  ost << "}";

  return ost;
};