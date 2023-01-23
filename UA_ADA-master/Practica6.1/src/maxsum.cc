// Elvi Mihai Sabau Sabau - 51254875L
#include <iostream>
#include <cstring>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

bool args(int argc, char *argv[], string &fileName, bool &tparam, bool &naive)
{
	bool errorParams = false;
	tparam = false;
	naive = true;

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
			{
				errorParams = true;
			}
		}
		else if (strcmp(argv[i], "-t") == 0)
			tparam = true;
		else if (strcmp(argv[i], "--ignore_naive") == 0)
			naive = false;
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

// Accedemos al elemento n-1 porque las posiciones del vector van de 0 a n-1
int sumMaxNaive(vector<int> valores, int n, int T)
{
	int s = 0, solIn, solOut;
	if (n > 0 && T > 0)
	{
		if (valores[n - 1] <= T)
		{
			solIn = sumMaxNaive(valores, n - 1, T - valores[n - 1]) + valores[n - 1];
			solOut = sumMaxNaive(valores, n - 1, T);

			if (solIn > solOut)
				s = solIn;
			else
				s = solOut;
		}
		else
			s = sumMaxNaive(valores, n - 1, T);
	}

	return s;
}

int memoization(vector<int> valores, int n, int T, vector<vector<int>> &almacen)
{
	int scojo, snocojo;

	if (almacen[n][T] == -1)
	{
		if (n > 0 && T > 0)
		{
			if (valores[n - 1] <= T)
			{
				scojo = memoization(valores, n - 1, T - valores[n - 1], almacen) + valores[n - 1];
				snocojo = memoization(valores, n - 1, T, almacen);
				if (scojo > snocojo)
					almacen[n][T] = scojo;
				else
					almacen[n][T] = snocojo;
			}
			else
				almacen[n][T] = memoization(valores, n - 1, T, almacen);
		}
		else
			almacen[n][T] = 0;
	}

	return almacen[n][T];
}

int main(int argc, char *argv[])
{
	string fileName;						// Nombre del fichero.
	bool errorParams, fileOpen; // Variables que usaremos para revisar parametros y el fichero.
	bool tparam, naive;					// Parametro -t y --ignore_naive.

	vector<int> valores;				 // Valores que se extraen del fichero.
	vector<vector<int>> almacen; // Almacen.
	int T, n;										 // Umbral y cantidad de elementos.
	int sol;										 // Solución.

	errorParams = args(argc, argv, fileName, tparam, naive);

	if (!errorParams)
	{
		fileOpen = readFile(fileName, valores, T, n);

		if (fileOpen)
		{
			if (naive)
			{
				sol = sumMaxNaive(valores, n, T);
				cout << "Naive: " << sol << endl;
			}

			// Crea la matriz de n x T.
			almacen = vector<vector<int>>(n + 1, vector<int>(T + 1, -1));

			cout << "Memoization: " << memoization(valores, n, T, almacen) << endl;
			cout << "Iterative (table): ¿?" << endl;
			cout << "Iterative (vector): ¿?" << endl;
			cout << "Selection: ¿?" << endl;
			cout << "Selection value: ¿?" << endl;
			cout << "Iterative table:" << endl;
			cout << "¿?" << endl;
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
