// Elvi Mihai Sabau - 51254875L

/*
ADA 2019-20
Pràctica 1: Empirical analysis of Quicksort average-time complexity.
*/

#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace chrono;

//--------------------------------------------------------------
// Middle QuickSort
void middle_QuickSort(int *v, long left, long right)
{

    long i, j;
    int pivot, aux;
    if (left < right)
    {
        i = left;
        j = right;
        pivot = v[(i + j) / 2];
        do
        {
            while (v[i] < pivot)
                i++;
            while (v[j] > pivot)
                j--;
            if (i <= j)
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                i++;
                j--;
            }
        } while (i <= j);
        if (left < j)
            middle_QuickSort(v, left, j);
        if (i < right)
            middle_QuickSort(v, i, right);
    }
}

int main(void)
{

    cout << "# quickSort CPU times in milliseconds:"
         << endl
         << "# Size \t CPU time (ms.)"
         << endl
         << "# ----------------------------"
         << endl;

    // Iterations per size.
    const int iterationsPerSize = 30;

    for (int exp = 15; exp <= 22; exp++)
    {
        // Size of the vector.
        size_t sizeVector = size_t(pow(2, exp));

        // Sum of the total time the algorithm took to sort all the array pack of the same size.
        int totalTime = 0;

        for (size_t i = 0; i < iterationsPerSize; i++)
        {
            int *vector = new int[sizeVector];

            if (!vector)
            {
                cerr << "Error, not enough memory!" << endl;
                exit(EXIT_FAILURE);
            }

            for (size_t j = 0; j < sizeVector; j++)
                vector[j] = rand();

            long start = clock();
            middle_QuickSort(vector, 0, sizeVector);
            long end = clock();

            totalTime += (1000.0 * (end - start) / CLOCKS_PER_SEC);

            for (size_t i = 1; i < sizeVector; i++)
                if (vector[i] < vector[i - 1])
                {
                    cerr << "Panic, array not sorted! " << i << endl;
                    exit(EXIT_FAILURE);
                }

            delete[] vector;
        }

        cout << sizeVector << "\t\t" << (totalTime / iterationsPerSize) << endl;
    }
}
