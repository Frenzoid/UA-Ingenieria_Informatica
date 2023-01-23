#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <climits>
#include <algorithm>
#include <queue>
#include <time.h>
using namespace std;

struct Node
{
	vector<unsigned long long> selection;
	int k; // Siguiente decision.
	unsigned long long sumaAcumulada;
	unsigned long long optimistic;
	unsigned long long pesimistic;
};

struct Solution
{
	unsigned long long sumaAcumulada;
};

struct Problem
{
	vector<unsigned long long> elements;
	unsigned long long T;
	vector<unsigned long long> ss;
};

Solution solution(const Node &n)
{
	Solution sol;
	sol.sumaAcumulada = n.sumaAcumulada;
	return sol;
}

// T = 55 => 5
//
// 50, 20, 10, 3

bool procesarArgumentos(int argc, char *argv[], string &nombreFichero)
{
	bool ok;
	ok = false;
	if (argc == 3 && strcmp(argv[1], "-f") == 0)
	{
		nombreFichero = argv[2];
		ok = true;
	}
	return ok;
}

// elementos = [12, 5, 3, 1]
// ss = [21, 9, 4, 1]
// rellena el vector de sumas del problema, necesario para hacer la cota optimista.
void sumas(Problem &p)
{
	unsigned long long suma = 0;
	for (int i = 0; i < p.elements.size(); i++)
	{
		suma = 0;
		for (int j = i; j < p.elements.size(); j++)
		{
			suma = suma + p.elements[j];
		}
		p.ss.push_back(suma);
	}
}

Node initial_node(const Problem &p)
{
	Node inicial;
	inicial.k = 0;
	inicial.sumaAcumulada = 0;
	return inicial;
}

// parte real + estimacion voraz.
Solution pessimistic_solution(const Problem &p, const Node &node)
{
	Solution sol;
	sol.sumaAcumulada = node.sumaAcumulada;
	// vector de menores a partir de la posicion i, para parar el bucle.
	for (int i = node.k; i < p.elements.size(); i++)
	{
		if (p.elements[i] + sol.sumaAcumulada <= p.T)
		{
			sol.sumaAcumulada += p.elements[i];
		}
	}
	return sol;
}

// Esto nos dice cuando un nodo es mejor que otro
bool operator<(const Node &n1, const Node &n2)
{
	// habria que sacarlo por cota optimista.
	// return n1.optimistic > n2.optimistic;
	return n1.k > n2.k;
	// return n1.pesimistic > n2.pesimistic;
}

bool is_leaf(const Problem &p, const Node &n)
{
	return p.elements.size() == n.k;
}

bool is_better(const Solution &s1, const Solution &s2)
{
	return s1.sumaAcumulada > s2.sumaAcumulada;
}

vector<Node> expand(const Problem &p, const Node &n)
{
	vector<Node> hijos;
	Node nuevo;
	nuevo = n;
	nuevo.k++;
	hijos.push_back(nuevo);
	nuevo.sumaAcumulada += p.elements[n.k];
	nuevo.selection.push_back(p.elements[n.k]);
	hijos.push_back(nuevo);
	return hijos;
}

bool is_feasible(const Problem &p, const Node &n)
{
	return n.sumaAcumulada <= p.T;
}

// 40, 30	T = 60
// sol 40, 20
// --------------------
// 30, 30, 40
//  0  la solucion es 40 y la estimacion 60
// Solo contiene devuelve la parte estimada optimista a partir de k.
unsigned long long greedyContinuo(const Problem &p, const Node &a)
{
	unsigned long long Tsol = 0;
	int i;

	// me salto todos los que no caben
	for (i = a.k; i < p.elements.size() && p.elements[i] > p.T - a.sumaAcumulada; i++)
	{
	}

	// si no cabe lo estoy cogiendo :_(
	if (i < p.ss.size())
	{
		// si la suma de los elementos que me quedan es mayor que el disponible la solucion es el disponible.
		if (p.ss[i] >= p.T - a.sumaAcumulada)
		{
			Tsol = p.T - a.sumaAcumulada;
		}
		else
		{ // si la suma de los elemenot sque me quedan es menor cojo todo lo disponible.
			Tsol = p.ss[i];
		}
	}
	return Tsol;
}

bool is_promissing(const Problem &p, Node &a, const Solution &current_best)
{
	a.optimistic = a.sumaAcumulada + greedyContinuo(p, a);
	cout << a.optimistic << endl;
	return a.optimistic > current_best.sumaAcumulada;
}

Solution branch_and_bound(const Problem &p)
{
	Node initial = initial_node(p);
	Solution current_best = pessimistic_solution(p, initial);
	priority_queue<Node> q;
	q.push(initial);

	while (!q.empty())
	{										// si quedan nodos vivos.
		Node n = q.top(); // guardo el que mas suma tenga.
		q.pop();					// lo quito de la cola.
		// cout << "selected: " << n.sumaAcumulada << ", " << n.k << endl;
		if (is_leaf(p, n))
		{
			Solution act = solution(n);
			if (is_better(act, current_best))
			{
				current_best = act;
			}
			continue; // para que no haga el for y se vaya al while.
		}
		for (Node a : expand(p, n))
		{
			if (is_feasible(p, a))
			{
				Solution pes = pessimistic_solution(p, n);
				n.pesimistic = pes.sumaAcumulada;
				// si mejora la mejor solucion encontrada hasta el momento
				if (is_better(pes, current_best))
				{
					current_best = pes;
				}
				// si puede mejorar la mejor solucion encontrada hasta el momento.
				if (is_promissing(p, a, current_best))
				{
					q.push(a);
				}
			}
		}
	}
	return current_best;
}

bool leerFichero(string nombreFichero, Problem &p)
{
	unsigned long long n, i, valor;
	bool ok;
	ifstream fich;
	fich.open(nombreFichero.c_str());
	if (!fich.is_open())
	{
		ok = false;
	}
	else
	{
		ok = true;
		fich >> n >> p.T;
		for (i = 0; i < n; i++)
		{
			fich >> valor;
			p.elements.push_back(valor);
		}
		fich.close();
		sort(p.elements.begin(), p.elements.end());
		reverse(p.elements.begin(), p.elements.end());
		sumas(p);
	}
	return ok;
}

int main(int argc, char *argv[])
{
	Problem p;
	Solution sol;
	bool ok;
	string nombreFichero;

	ok = procesarArgumentos(argc, argv, nombreFichero);
	if (!ok)
	{
		cout << "Usage: maxsum-bt -f file" << endl;
	}
	else
	{
		ok = leerFichero(nombreFichero, p);
		// ordenar el vector de elementos.

		double start_t = clock();
		sol = branch_and_bound(p);
		double end_t = clock();
		cout << sol.sumaAcumulada << endl;
		cout << (end_t - start_t) / CLOCKS_PER_SEC * 1000 << endl;
	}
	return 0;
}
