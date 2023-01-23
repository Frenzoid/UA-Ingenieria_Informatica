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
		{
			s = sumMaxNaive(valores, n - 1, T);
		}
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
			{
				almacen[n][T] = memoization(valores, n - 1, T, almacen);
			}
		}
		else
		{
			almacen[n][T] = 0;
		}
	}
	return almacen[n][T];
}

void iterative(vector<int> vals, int n, int T, vector<vector<int>> &almacen)
{
	int i, j;

	for (j = 0; j <= T; j++)
		almacen[0][j] = 0; // Primera fila.
	for (i = 0; i <= n; i++)
		almacen[i][0] = 0; // Primera columna.
	for (i = 1; i <= n; i++)
		for (j = 1; j <= T; j++) // Procesamos.
		{
			if (vals[i - 1] <= j)
				almacen[i][j] = max(almacen[i - 1][j], almacen[i - 1][j - vals[i - 1]] + vals[i - 1]);
			else
				almacen[i][j] = almacen[i - 1][j];
		}
}

int iterativeVector(int n, int T, const vector<int> &vals)
{
	vector<vector<int>> almacen = vector<vector<int>>(2, vector<int>(T + 1, -1));
	int filAnt = 0, filAct = 0, i, j;

	for (int i = 0; i <= T; i++)
		almacen[0][i] = 0;

	for (i = 1; i <= n; i++)
	{
		filAct = i % 2;
		filAnt = (i + 1) % 2;
		for (j = 0; j <= T; j++)
		{
			if (vals[i - 1] <= j)
				almacen[filAct][j] = max(almacen[filAnt][j], almacen[filAnt][j - vals[i - 1]] + vals[i - 1]);
			else
				almacen[filAct][j] = almacen[filAnt][j];
		}
	}

	return almacen[filAct][T];
}

vector<int> selections(const vector<vector<int>> &almacen, int n, int T, const vector<int> &vals)
{
	vector<int> solSelections;
	int i = n, j = T;

	while (i > 0)
	{
		if (almacen[i][j] == almacen[i - 1][j])
			i--;
		else
		{
			solSelections.insert(solSelections.begin(), vals[i - 1]);
			j = j - vals[i - 1];
			i--;
		}
	}
	return solSelections;
}

void auxPrintSelections(const vector<int> &selection)
{
	for (uint i = 0; i < selection.size(); i++)
		cout << selection[i] << " ";

	cout << endl;
}

int auxValueOfSelections(const vector<int> &seleccion)
{
	uint sum = 0, i;
	for (i = 0; i < seleccion.size(); i++)
		sum = sum + seleccion[i];

	return sum;
}

void auxPrintTable(const vector<vector<int>> &almacen)
{
	for (uint i = 0; i < almacen.size(); i++)
	{
		for (uint j = 0; j < almacen[i].size(); j++)
			cout << almacen[i][j] << " ";
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	string fileName;			// Nombre del fichero.
	bool errorParams, fileOpen; // Variables que usaremos para revisar parametros y el fichero.
	bool tparam, naive;			// Parametro -t y --ignore_naive.

	vector<int> valores;		 // Valores que se extraen del fichero.
	vector<vector<int>> almacen; // Almacen.
	int T, n;					 // Umbral y cantidad de elementos.
	int sol;					 // Solución.

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

			// Memorization.
			almacen = vector<vector<int>>(n + 1, vector<int>(T + 1, -1));
			cout << "Memoization: " << memoization(valores, n, T, almacen) << endl;

			// Iterative.
			almacen = vector<vector<int>>(n + 1, vector<int>(T + 1, -1));
			iterative(valores, n, T, almacen);
			cout << "Iterative (table): " << almacen[n][T] << endl;
			cout << "Iterative (vector): " << iterativeVector(n, T, valores) << endl;

			// Selection.
			cout << "Selection: ";
			auxPrintSelections(selections(almacen, n, T, valores));
			cout << "Selection value: " << auxValueOfSelections(selections(almacen, n, T, valores)) << endl;

			// Iter table.
			if (tparam)
			{
				cout << "Iterative table:" << endl;
				auxPrintTable(almacen);
			}
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
