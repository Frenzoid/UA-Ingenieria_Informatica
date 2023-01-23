#include "tcomplejo.h"
#include <cmath>
#include <complex>
#include <iostream>

using namespace std;

// Constructor a partir de la PARTE REAL e IMAGINARIA
TComplejo::TComplejo(double reIn, double imIn)
{
    re = reIn;
    im = imIn;
};

// Constructor copia
TComplejo::TComplejo(const TComplejo &tcom)
{
    Copia(tcom);
};

// Destructor
TComplejo::~TComplejo()
{
    this->re = 0;
    this->im = 0;
};

// Sobrecarga del operador asignación
TComplejo &
TComplejo::operator=(const TComplejo &tcomp)
{
    if (*this == tcomp)
        return *this;

    this->~TComplejo();

    Copia(tcomp);

    return *this;
};

void TComplejo::Copia(const TComplejo &tcom)
{
    im = tcom.Im();
    re = tcom.Re();
}

// SOBRECARGA DE OPERADORES ARITMÉTICOS;
TComplejo TComplejo::operator+(const TComplejo &tcomp) const
{
    TComplejo tcom(re + tcomp.re, im + tcomp.im);
    return tcom;
};

TComplejo TComplejo::operator-(const TComplejo &tcomp) const
{
    TComplejo tcom(re - tcomp.re, im - tcomp.im);
    return tcom;
};

TComplejo TComplejo::operator*(const TComplejo &tcomp) const
{
    // ac - bd, ad + bc
    complex<double> r1(re, im);
    complex<double> r2(tcomp.re, tcomp.im);
    complex<double> r3 = r1 * r2;
    TComplejo tcom1(r3.real(), r3.imag());

    return tcom1;
}

TComplejo TComplejo::operator+(const double reIn) const
{
    TComplejo tcom(reIn);
    return *this + tcom;
};

TComplejo TComplejo::operator-(const double reIn) const
{
    TComplejo tcom(reIn);
    return *this - tcom;
};

TComplejo TComplejo::operator*(const double reIn) const
{
    TComplejo tcom(reIn);
    return *this * tcom;
};

// OTROS OPERADORES
// IGUALDAD de números complejos
bool TComplejo::operator==(const TComplejo &tcomp) const
{
    if (this == &tcomp)
        return true;
    else if (re == tcomp.re && im == tcomp.im)
        return true;
    else
        return false;
};

// DESIGUALDAD de números complejos
bool TComplejo::operator!=(const TComplejo &tcomp) const
{
    return !(*this == tcomp);
};

// Devuelve PARTE REAL
double TComplejo::Re() const
{
    return re;
};

// Devuelve PARTE IMAGINARIA
double TComplejo::Im() const
{
    return im;
};

// CUSTOM: Devuelve si está vacio o no
bool TComplejo::Empty() const
{
    if (re == 0 && im == 0)
        return true;

    return false;
};

// Modifica PARTE REAL
void TComplejo::Re(const double reIn)
{
    re = reIn;
};

// Modifica PARTE IMAGINARIA
void TComplejo::Im(const double imIn)
{
    im = imIn;
};

// Calcula el Argumento (en Radianes)
double TComplejo::Arg() const
{
    complex<double> comp(re, im);
    double argu = arg(comp);

    return argu;
};

// Calcula el Módulo
double TComplejo::Mod() const
{
    double a = sqrt(pow(re, 2) + pow(im, 2));
    return a;
};

// Sobrecarga del operador SALIDA
ostream &operator<<(ostream &ost, const TComplejo &tcom)
{
    ost << "(" << tcom.re << " " << tcom.im << ")";
    return ost;
};

TComplejo operator+(const double re, const TComplejo &tcom)
{
    const TComplejo temp(re);
    return temp + tcom;
};

TComplejo operator-(const double re, const TComplejo &tcom)
{
    const TComplejo temp(re);
    return temp - tcom;
};

TComplejo operator*(const double re, const TComplejo &tcom)
{
    const TComplejo temp(re);
    return temp * tcom;
};
