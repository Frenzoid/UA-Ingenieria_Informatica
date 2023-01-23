#ifndef _TCOMPLEJO_
#define _TCOMPLEJO_

#include <ostream>
using namespace std;

class TComplejo
{
private:
    double re; // PARTE REAL
    double im; // PARTE IMAGINARIA
    void Copia(const TComplejo &);

public:
    //Constructor por defecto : PARTE REAL e IMAGINARIA inicializadas a 0
    TComplejo(double = 0, double = 0);

    //Constructor copia
    TComplejo(const TComplejo &);

    //Destructor
    ~TComplejo();

    // Sobrecarga del operador asignación
    TComplejo &operator=(const TComplejo &);

    // SOBRECARGA DE OPERADORES ARITMÉTICOS;
    TComplejo operator+(const TComplejo &) const;
    TComplejo operator-(const TComplejo &) const;
    TComplejo operator*(const TComplejo &)const;
    TComplejo operator+(const double) const;
    TComplejo operator-(const double) const;
    TComplejo operator*(const double)const;

    // OTROS OPERADORES
    bool operator==(const TComplejo &) const; // IGUALDAD de números complejos
    bool operator!=(const TComplejo &) const; // DESIGUALDAD de números complejos
    double Re() const;                        // Devuelve PARTE REAL
    double Im() const;                        // Devuelve PARTE IMAGINARIA
    bool Empty() const;                       // Devuelve si está vacio o no
    void Re(const double);                    // Modifica PARTE REAL
    void Im(const double);                    // Modifica PARTE IMAGINARIA
    double Arg(void) const;                   // Calcula el Argumento (en Radianes)
    double Mod(void) const;                   // Calcula el Módulo

    // Sobrecarga del operador SALIDA
    friend std::ostream &operator<<(ostream &, const TComplejo &);
    friend TComplejo operator+(const double, const TComplejo &);
    friend TComplejo operator-(const double, const TComplejo &);
    friend TComplejo operator*(const double, const TComplejo &);
};

#endif // !_TCOMPLEJO_
