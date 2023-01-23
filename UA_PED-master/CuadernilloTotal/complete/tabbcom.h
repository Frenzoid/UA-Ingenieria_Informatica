#ifndef _tabbCom
#define _tabbCom
#include <iostream>
#include "tcomplejo.h"
#include "tvectorcom.h"
#include "tlistacom.h"

using namespace std;

class TABBCom;
class TNodoABB;

class TABBCom
{
private:
	TNodoABB *nodo;
	void InordenAux(TVectorCom &, int &) const;
	void PreordenAux(TVectorCom &, int &) const;
	void PostordenAux(TVectorCom &, int &) const;
	TComplejo BuscarMayor() const;

public:
	TABBCom();
	TABBCom(const TABBCom &);
	~TABBCom();
	TABBCom &operator=(const TABBCom &);
	bool operator==(const TABBCom &) const;
	bool EsVacio() const;
	bool Insertar(const TComplejo &);
	bool Borrar(const TComplejo &);
	bool Buscar(const TComplejo &) const;
	TComplejo Raiz() const;
	int Altura() const;
	int Nodos() const;
	int NodosHoja() const;
	TVectorCom Inorden() const;
	TVectorCom Preorden() const;
	TVectorCom Postorden() const;
	TVectorCom Niveles() const;
	friend ostream &operator<<(ostream &os, const TABBCom &de);

	//		bool existeCamino(const TListaCom &lista) const;
	//		bool comprobarCamino(const TComplejo &inicio, const TComplejo &fin) const;

	// NUEVOS EJERCICIOS PARA EL EXAMEN PRACTICO.
	// 1. devuelve el numero de hojas que tiene el arbol.
	int getNumHojas() const;

	// 2. devuelve en la lista pasada como parametro las hojas del arbol
	void listarHojas(TListaCom &lp) const;

	// 3. devuelve una lista con los nodos hojas del arbol
	TListaCom listarHojas() const;

	// 4. devuelve un vector de booleanos en el que la posicion i
	// vale cierto si el elemento que ocupa la posicion i de
	// la lista es hoja y falso si no.
	bool *testHojas(const TListaCom &lista) const;

	TNodoABB **soyTuPadre(const TVectorCom &v) const;
	TNodoABB *buscarPadre(const TComplejo &c) const;

	// 5. devuelve un vector.
	int *cuentaHijos(const TListaCom &li) const;

	// 6.
	TListaCom buscaCamino(const TComplejo &inicio, const TComplejo &fin) const;

	// 7.

	// EJERCICIOS EXAMEN PRACTICO.

	// 1- devuelve una lista con los nodos que son hojas en el arbol
	// de los nodos del vector pasado como parametro.
	TListaCom listaHojas(const TVectorCom &up) const;
	bool esHoja(const TComplejo &p) const;

	// 2- Se le pasa una lista y comprueba si los nodos estan en el arbol.
	// Devuelve una lista con las posiciones de forma que si
	// esta pone 1 sino pone 0
	int *marcar(const TListaCom &li) const;

	// 3- devuelve una lista con los hijos del complejo de la lsita
	// pasado
	TListaCom recogeHijos(const TListaCom &lp) const;
	TListaCom hijos(const TComplejo &p) const;

	/*
		// 4- devuelve verdadero si el poro esta en el nivel i del arbol
		// dedicated to matias deambrosiiiiia		
		bool estaEnNivel(const TComplejo &lp, int niv) const;

		// 5- Devuelve un vector con los padres de los elementos
		// en el arbol, si no tiene padre se le pondra 
		// vacio en su posicion.
		TComplejo soyTuPadre(const TComplejo &p) const;
		TVectorCom padresDe(const TListaCom &lp) const;

		// 6- Devuelve una lista la cantidad de nodos que tiene 
		// el subarbol que lo tiene como raiz.
		int *contarNodosSubarbol(const TListaCom &p) const;
		int contarHijosCom(const TComplejo &p) const;

		/// 7- examen cabeceras.
		int *examen(const TListaCom &lp) const;
		int encontrarCaso(const TComplejo &p) const;
*/
	bool existeCamino(const TListaCom &lista) const;

	bool comprobarCamino(const TComplejo &inicio, const TComplejo &fin) const;

	// JULIO 2010
	TVectorCom examen(const TListaCom &l) const;
	TComplejo Simetrico(const TComplejo &c) const;

	int EliminarUltimoNivel();
	int EliminarUltimoNivel(int h, int n);

	// devuelve una lista con los nodos del arbol que tienen dos hijos.
	// la lista se obtendra ordenada de menor a mayor.
	TListaCom DosHijos() const;

	TVectorCom CaminoMasLargo() const;
	void CaminoMasLargo(TVectorCom &v, int i) const;

	//
	int examen(const TABBCom &ab) const;
	void iguales(const TABBCom &ab, bool &estructura, bool &iguales) const;
	int buscarComplejo(const TComplejo &) const;
	int *examen2015(const TListaCom &) const;
	int obtenerMiNumero(const TComplejo &) const;

	friend class TListaNodo;
	friend class TListaPos;
};
class TNodoABB
{
	friend class TABBCom;

private:
	TComplejo item;
	TABBCom iz, de;

public:
	TNodoABB();
	TNodoABB(const TNodoABB &);
	~TNodoABB();
	TNodoABB(const TComplejo &); // no entregar, es mio.
	TNodoABB &operator=(const TNodoABB &);
};

#endif
