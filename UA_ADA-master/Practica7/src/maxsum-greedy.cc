// Elvi Mihai Sabau Sabau - 51254875L
#include <iostream>
#include <cstring>
#include <vector>
#include <climits>
#include <fstream>
#include <bits/stdc++.h>

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
			{
				errorParams = true;
			}
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

int maxSumGreedy(vector<int> vals, vector<int> &selection, int T)
{
	int valsum = 0;
	sort(vals.begin(), vals.end());
	reverse(vals.begin(), vals.end());

	// auxPrintSelections(vals);

	for (uint i = 0; i < vals.size() && valsum < T; i++)
	{
		if (vals[i] <= T - valsum)
		{
			selection.push_back(vals[i]);
			valsum += vals[i];
		}
	}

	return valsum;
}

int main(int argc, char *argv[])
{
	string fileName;			// Nombre del fichero.
	bool errorParams, fileOpen; // Variables que usaremos para revisar parametros y el fichero.

	vector<int> valores, selection; // Valores que se extraen del fichero.
	int T, n;						// Umbral y cantidad de elementos.

	errorParams = args(argc, argv, fileName);

	if (!errorParams)
	{
		fileOpen = readFile(fileName, valores, T, n);

		if (fileOpen)
		{
			cout << "Greedy: " << maxSumGreedy(valores, selection, T) << endl;
			cout << "Selection: ";
			auxPrintSelections(selection);
			cout << "Selection value: " << auxValueOfSelections(selection) << endl;
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
