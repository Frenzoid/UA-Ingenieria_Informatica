// Elvi Mihai Sabau Sabau - 51254875L
#include <iostream>
#include <cstring>
#include <vector>
#include <climits>
#include <fstream>
#include <bits/stdc++.h>
#include <time.h>

using namespace std;

struct Node
{
  vector<uint> selection;
  uint k;
  uint acumulator;
  uint optimistic;
  uint pesimistic;
};

struct Problem
{
  uint T;
  vector<uint> valores;
  vector<uint> sums;
};

uint expanded = 0,
     added = 0,
     feasible_discarted = 0,
     promissing_discarted = 0,
     was_promissing_discarted = 0,
     finished = 0,
     best_sol_updated_from_finished = 0,
     best_sol_updated_from_pessimistic_unfinished = 0;

void sumas(Problem &problem)
{
  uint suma = 0;
  for (uint i = 0; i < problem.valores.size(); i++)
  {
    suma = 0;
    for (uint j = i; j < problem.valores.size(); j++)
    {
      suma = suma + problem.valores[j];
    }
    problem.sums.push_back(suma);
  }
}

bool args(uint argc, char *argv[], string &fileName)
{
  bool errorParams = false;
  for (uint i = 1; i < argc && errorParams == false; i++)
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

bool readFile(string nombreFichero, Problem &problem)
{
  uint n, i, valor;
  bool open;
  ifstream f;

  f.open(nombreFichero.c_str());

  if (f.is_open())
  {
    open = true;
    f >> n >> problem.T;

    for (i = 0; i < n; i++)
    {
      f >> valor;
      problem.valores.push_back(valor);
    }

    f.close();
  }
  else
    open = false;

  return open;
}

// -------------- Estrucutra ----------------

uint solution(const Node &node)
{
  uint sol;
  sol = node.acumulator;
  return sol;
}

Node initial_node()
{
  Node inicial;
  inicial.k = 0;
  inicial.acumulator = 0;
  return inicial;
}

uint pessimistic_solution(const Problem &problem, const Node &node)
{
  uint sol;
  sol = node.acumulator;

  for (uint i = node.k; i < problem.valores.size(); i++)
  {
    if (problem.valores[i] + sol <= problem.T)
      sol += problem.valores[i];
  }
  return sol;
}

// Sobrecarga para la decisión interna del priority queue
bool operator<(const Node &node1, const Node &node2)
{
  return node1.k > node2.k;
}

bool is_feasible(const Problem &problem, const Node &node)
{
  return node.acumulator <= problem.T;
}

bool is_better(const uint &solution1, const uint &solution2)
{
  return solution1 > solution2;
}

bool is_leaf(const Problem &problem, const Node &node)
{
  return problem.valores.size() == node.k;
}

vector<Node> expand(const Problem &problem, const Node &node)
{
  vector<Node> branches;
  Node nuevoNodo;

  nuevoNodo = node;
  nuevoNodo.k++;

  branches.push_back(nuevoNodo);

  nuevoNodo.acumulator += problem.valores[node.k];
  nuevoNodo.selection.push_back(problem.valores[node.k]);

  branches.push_back(nuevoNodo);

  return branches;
}

int saltaPodaCabe(const vector<uint> &valores, uint acumulator, uint k, uint T)
{
  uint valorMereceComprobar = 0;

  for (valorMereceComprobar = k; valorMereceComprobar < valores.size() && valores[valorMereceComprobar] > T - acumulator; valorMereceComprobar++)
  {
    // Un for, para iterar sobre un elemento, y a la vez comprobar si cabe, va de perlas, incluso mejor que un while.
  }

  return valorMereceComprobar;
}

// Devuelve el optimista a partir de K
uint add_rest(const Problem &problem, const Node &node)
{
  uint Tsol = 0;
  uint i = saltaPodaCabe(problem.valores, node.acumulator, node.k, problem.T);

  if (i < problem.sums.size())
  {
    if (problem.sums[i] >= problem.T - node.acumulator)
      Tsol = problem.T - node.acumulator;
    else
      Tsol = problem.sums[i];
  }

  return Tsol;
}

bool is_promissing(const Problem &problem, Node &node, const uint &current_best)
{
  node.optimistic = node.acumulator + add_rest(problem, node);
  return node.optimistic > current_best;
}

uint branch_and_bound(const Problem &problem)
{
  priority_queue<Node> q;
  Node inicial = initial_node();
  q.push(inicial);

  uint current_best = pessimistic_solution(problem, inicial);

  while (!q.empty())
  {
    Node node = q.top();
    q.pop();

    if (is_leaf(problem, node))
    {
      finished++;
      uint currentSol = solution(node);

      if (is_better(currentSol, current_best))
      {
        current_best = currentSol;
        best_sol_updated_from_finished++;
      }

      continue;
    }

    vector<Node> expandedBranches;
    expandedBranches = expand(problem, node);

    for (Node nodeExpanded : expandedBranches)
    {
      expanded++;
      if (is_feasible(problem, nodeExpanded))
      {
        uint pessimisticSol = pessimistic_solution(problem, node);
        node.pesimistic = pessimisticSol;

        if (is_better(pessimisticSol, current_best))
        {
          current_best = pessimisticSol;
          best_sol_updated_from_pessimistic_unfinished++;
        }

        if (is_promissing(problem, nodeExpanded, current_best))
        {
          q.push(nodeExpanded);
          added++;
        }
        else
          was_promissing_discarted = promissing_discarted++;
      }
      else
        feasible_discarted++;
    }
  }

  return current_best;
}

// -------------- MAIN -----------------

int main(int argc, char *argv[])
{
  string fileName;
  bool fileOpen, errorParams;

  errorParams = args(argc, argv, fileName);

  if (!errorParams)
  {
    Problem problem;
    fileOpen = readFile(fileName, problem);

    if (fileOpen)
    {
      sort(problem.valores.begin(), problem.valores.end());
      reverse(problem.valores.begin(), problem.valores.end());
      // random_shuffle(problem.valores.begin(), problem.valores.end());

      sumas(problem);

      uint sol;

      double start_t = clock();
      sol = branch_and_bound(problem);
      double end_t = clock();

      cout << sol << endl;
      cout << expanded << " " << added << " " << feasible_discarted << " " << promissing_discarted << " " << was_promissing_discarted << " " << finished << " " << best_sol_updated_from_finished << " " << best_sol_updated_from_pessimistic_unfinished << endl;
      cout << (end_t - start_t) / CLOCKS_PER_SEC * 1000 << endl;
    }
    else
    {
      cout << "ERROR: can't open file: " << fileName << endl;
      cout << "Usage: maxsum-bb -f file" << endl;
    }
  }
  else
    cout << "Usage: maxsum-bb -f file" << endl;

  return 0;
}
