// Elvi Mihai Sabau Sabau - 51254875L
#include <iostream>
#include <cstring>
#include <vector>
#include <climits>
#include <fstream>
#include <bits/stdc++.h>
#include <time.h>

using namespace std;

bool args(int argc, char *argv[], string &fileName)
{
	bool errorParams = false;
	for (int i = 1; i < argc && errorParams == false; i++)
	{
		// -f
		if (strcmp(argv[i], "-f") == 0)
		{
			if (i + 1 < argc)
			{
				fileName = argv[i + 1];
				i++;
			}
			else
				errorParams = true;
		}
		else
			errorParams = true;

		if (errorParams)
			cout << "Error: unknown option " << argv[i] << endl;
	}
	return errorParams;
}

bool readFile(string nombreFichero, vector<int> &valores, int &T, int &n)
{
	bool open = false;
	int valor;

	ifstream f;
	f.open(nombreFichero.c_str());

	if (f.is_open())
	{
		open = true;
		f >> n >> T;

		for (int i = 1; i <= n; i++)
		{
			f >> valor;
			valores.push_back(valor);
		}
	}
	else
		open = false;

	return open;
}

void auxPrintSelections(const vector<int> &mSolucion, const vector<int> &valores)
{
	// imprimimos cada valor seleccionado.
	for (uint i = 0; i < mSolucion.size(); i++)
		if (mSolucion[i] == 1)
			cout << valores[i] << " ";

	cout << endl;
}

int voraz(const vector<int> &valores, int T, vector<int> &solucion)
{
	int Tsol = 0;

	for (uint i = 0; i < valores.size(); i++)
	{
		if (valores[i] + Tsol <= T)
		{
			Tsol += valores[i];
			solucion[i] = 1;
		}
	}
	return Tsol;
}

// ignoramos los valores que no caben, saltamos al primero que quepa.
int saltaPodaCabe(const vector<int> &valores,
				  uint k, int T)
{
	uint valorMereceComprobar = 0;

	for (valorMereceComprobar = k; valorMereceComprobar < valores.size() && valores[valorMereceComprobar] > T; valorMereceComprobar++)
	{
		// Un for, para iterar sobre un elemento, y a la vez comprobar si cabe, va de perlas, incluso mejor que un while.
	}

	return valorMereceComprobar;
}

int add_rest(
	const vector<int> &valores,
	const vector<int> &sums,
	uint k, int T)
{
	int Tsol = 0;
	uint valor = 0;

	// 'valor' es la posicion de un valor que cumple los requisitos.
	valor = saltaPodaCabe(valores, k, T);

	if (sums[valor] >= T)
		Tsol = T;
	else
		Tsol = sums[valor];

	return Tsol;
}

// Esto es bastante similar a las transparencias, solo que la poda en las transparencias es demasiado superficial, no?
void backTracking(uint k, int acumulator, int T,
				  int &suma,
				  int &expanded, int &discarted,
				  vector<int> solucion,
				  vector<int> &mSolucion,
				  const vector<int> &valores,
				  const vector<int> &sums)
{
	expanded++;
	if (k == solucion.size())
	{
		mSolucion = solucion;
		suma = acumulator;

		// Se considera nodo descartado tanto los nodos que se han expandido pero que no se han desarollado,
		//   como los nodos que directamente no se han expandido? Mando tutoria.
		// discarted++;
		return;
	}
	else
	{
		for (int j = 0; j < 2; j++)
		{
			solucion[k] = j;
			int current = acumulator + solucion[k] * valores[k];
			if (current <= T && (current + add_rest(valores, sums, k + 1, T - current)) > suma)
				backTracking(k + 1, current, T, suma, expanded, discarted, solucion, mSolucion, valores, sums);
			else
				discarted++;
		}
	}
}

void sumsFun(const vector<int> &valores, vector<int> &sums)
{
	int suma = 0;

	for (uint i = 0; i < valores.size(); i++)
	{
		suma = 0;
		for (uint j = i; j < valores.size(); j++)
		{
			suma = suma + valores[j];
		}
		sums.push_back(suma);
	}
}

int main(int argc, char *argv[])
{
	string fileName;
	bool fileOpen, errorParams;
	int T, n;

	errorParams = args(argc, argv, fileName);

	if (!errorParams)
	{
		vector<int> valores;

		fileOpen = readFile(fileName, valores, T, n);

		if (fileOpen)
		{
			vector<int> mSolucion(valores.size(), 0), solucion(valores.size(), 0), sums;
			int k = 0, acumulator = 0, suma, expanded = 0, discarted = 0;

			sort(valores.begin(), valores.end());
			reverse(valores.begin(), valores.end());

			suma = voraz(valores, T, mSolucion);
			sumsFun(valores, sums);

			double start_t = clock();
			backTracking(k, acumulator, T, suma, expanded, discarted, solucion, mSolucion, valores, sums);
			double end_t = clock();

			cout << "Backtracking: " << suma << endl;
			cout << "Selection: ";
			auxPrintSelections(mSolucion, valores);
			cout << "Expanded nodes: " << expanded << endl;
			cout << "Discarted nodes: " << discarted << endl;
			cout << "CPU Time (ms): " << 1000.0 * (end_t - start_t) / CLOCKS_PER_SEC << endl;
		}
		else
		{
			cout << "ERROR: can't open file: " << fileName << endl;
			cout << "Usage: maxsum [-t] [--ignore_naive] -f file" << endl;
		}
	}
	else
		cout << "Usage: maxsum [-t] [--ignore_naive] -f file" << endl;

	return 0;
}
