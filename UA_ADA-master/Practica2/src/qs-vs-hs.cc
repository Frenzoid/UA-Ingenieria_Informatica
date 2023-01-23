/* Elvi Mihai Sabau Sabau - 51254875L


ADA. 2019-20
Pràctica 2 de laboratori: Empirical analysis by means of program-steps account of two sorting algorithms: Middle-Quicksort and Heapsort.

Objectiu de la pràctica (a més dels especificats en la pràctica anterior):
- Conèixer els algorismes d'ordenació quicksort i heapsort
- Utilitzar el mètode del compte de passos de manera empírica per a obtenir la complexitat temporal d'un algorisme.
- Comprender la necesidad de generar un número (significativo desde el punto de vista estadístico) de instancias aleatorias para el cálculo de la complejidad temporal promedio cuando el algoritmo presenta caso mejor y peor.
- Entender que la complejidad temporal (y espacial) de un algoritmo puede depender del tipo de instancias del problema que se le presentan.
*/
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <sstream>

using namespace std;

int _STEPS_ = 0;

//--------------------------------------------------------------
// Middle Quick Sort
void middle_QuickSort(int *v, long left, long right)
{
	long i, j;
	int pivot;
	_STEPS_++;
	if (left < right)
	{
		i = left;
		j = right;
		pivot = v[(i + j) / 2];
		do
		{
			_STEPS_++;

			while (v[i] < pivot)
			{
				i++;
				_STEPS_++;
			}
			while (v[j] > pivot)
			{
				j--;
				_STEPS_++;
			}
			if (i <= j)
			{
				_STEPS_++;
				swap(v[i], v[j]);
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

//--------------------------------------------------------------
//HEAPSORT
// Procedure sink used by Heapsort algorith
// Sink an element (indexed by i) in a tree to keep the heap property. n is the size of the heap.

void sink(int *v, size_t n, size_t i)
{
	size_t largest;
	size_t l, r; //left and right child

	do
	{
		_STEPS_++;
		largest = i;	 // Initialize largest as root
		l = 2 * i + 1; // left = 2*i + 1
		r = 2 * i + 2; // right = 2*i + 2

		// Is left child larger than root?
		if (l < n && v[l] > v[largest])
			largest = l;

		// Is right child larger than largest so far
		if (r < n && v[r] > v[largest])
			largest = r;

		// If largest is still root then the process is done
		if (largest == i)
			break;

		// If not, swap new largest with current node i and repeat the process with childs.
		swap(v[i], v[largest]);
		i = largest;
	} while (true);
}

//--------------------------------------------------------------
// Heapsort algorithm (ascending sorting)
void heapSort(int *v, size_t n)
{
	// Build a MAX-HEAP with the input array
	for (size_t i = n / 2 - 1; i >= 0; i--)
	{
		_STEPS_++;
		sink(v, n, i);
		if (i == 0)
			break; //as size_t is unsigned type
	}

	// A this point we have a HEAP on the input array, let's take advantage of this to sort the array:
	// One by swap the first element, which is the largest (max-heap), with the last element of the vector and rebuild heap by sinking the new placed element on the begin of vector.
	for (size_t i = n - 1; i > 0; i--)
	{
		_STEPS_++;
		// Move current root to the end.
		swap(v[0], v[i]);
		// Now largest element is at the end but do not know if the element just moved to the beginning is well placed, so a sink process is required.
		// Note that, at the same time, the HEAP size is reduced one element by one.
		sink(v, i, 0);
		// The procedure ends when HEAP has only one element, the lower of the input array
	}
}

// Rounds decimals (thanks stack overflow)
string prd(const double x, const int decDigits)
{
	if (decDigits == -1)
		return to_string(x);

	stringstream ss;
	ss << fixed;
	ss.precision(decDigits);
	ss << x;
	return ss.str();
}

int main(void)
{

	// set seed
	srand(getpid());

	// Iterations per size.
	const int iterationsPerSize = 30;

	// Digits to round.
	const int roundDigits = 3;

	// Sum of the total steps of each vector with each algorithm on all loop.
	int StepsRQ, StepsRH, StepsSQ, StepsSH, StepsRSQ, StepsRSH;

	cout << "QUICKSORT VERSUS HEAPSORT."
			 << endl
			 << "Average processing Msteps (millions of program steps)"
			 << endl
			 << "Number of samples (arrays of integer): " << iterationsPerSize
			 << endl
			 << "\t\t RANDOM ARRAYS \t\t   SORTED ARRAYS   \t\t REVERSE SORTED ARRAYS"
			 << endl
			 << "\t\t ------------- \t\t ----------------- \t\t ------------------------"
			 << endl
			 << "Size \t QuickSort \t HeapSort \t QuickSort \t HeapSort  \t QuickSort \t HeapSort"
			 << endl
			 << "=======================================================================================================\n";

	for (int exp = 15; exp <= 21; exp++)
	{
		// Size of the vector.
		size_t sizeVector = size_t(pow(2, exp));

		// Reset of steps
		StepsRQ = 0, StepsRH = 0, StepsSQ = 0, StepsSH = 0, StepsRSQ = 0, StepsRSH = 0;

		for (size_t i = 0; i < iterationsPerSize; i++)
		{
			int *randVectorQ = new int[sizeVector];
			int *sortedUpVectorQ = new int[sizeVector];
			int *sortedDownVectorQ = new int[sizeVector];

			int *randVectorH = new int[sizeVector];
			int *sortedUpVectorH = new int[sizeVector];
			int *sortedDownVectorH = new int[sizeVector];

			if (!randVectorQ || !sortedUpVectorQ || !sortedDownVectorQ || !randVectorH || !sortedUpVectorH || !sortedDownVectorH)
			{
				cerr << "Error, not enough memory!" << endl;
				exit(EXIT_FAILURE);
			}

			for (size_t j = 0; j < sizeVector; j++)
			{
				randVectorQ[j] = rand();
				sortedUpVectorQ[j] = j;
				sortedDownVectorQ[j] = sizeVector - j;

				randVectorH[j] = randVectorQ[j];
				sortedUpVectorH[j] = j;
				sortedDownVectorH[j] = sizeVector - j;
			}

			_STEPS_ = 0;
			middle_QuickSort(randVectorQ, 0, sizeVector);
			StepsRQ += _STEPS_;
			_STEPS_ = 0;

			heapSort(randVectorH, sizeVector);
			StepsRH += _STEPS_;
			_STEPS_ = 0;

			middle_QuickSort(sortedUpVectorQ, 0, sizeVector);
			StepsSQ += _STEPS_;
			_STEPS_ = 0;

			heapSort(sortedUpVectorH, sizeVector);
			StepsSH += _STEPS_;
			_STEPS_ = 0;

			middle_QuickSort(sortedDownVectorQ, 0, sizeVector);
			StepsRSQ += _STEPS_;
			_STEPS_ = 0;

			heapSort(sortedDownVectorH, sizeVector);
			StepsRSH += _STEPS_;
			_STEPS_ = 0;

			for (size_t i = 1; i < sizeVector; i++)
				if (randVectorQ[i] < randVectorQ[i - 1] || sortedUpVectorQ[i] < sortedUpVectorQ[i - 1] ||
						sortedDownVectorQ[i] < sortedDownVectorQ[i - 1] || sortedDownVectorQ[i] < sortedDownVectorQ[i - 1] ||
						randVectorH[i] < randVectorH[i - 1] || sortedUpVectorH[i] < sortedUpVectorH[i - 1] || sortedDownVectorH[i] < sortedDownVectorH[i - 1])
				{
					cerr << "Panic, arrays not sorted! " << i << endl;
					exit(EXIT_FAILURE);
				}

			delete[] randVectorQ;
			delete[] sortedUpVectorQ;
			delete[] sortedDownVectorQ;
			delete[] randVectorH;
			delete[] sortedUpVectorH;
			delete[] sortedDownVectorH;
		}

		//					"\t\t     RANDOM ARRAYS     \t\t     SORTED ARRAYS     \t\t REVERSE SORTED ARRAYS"
		//     "Size \t\t QuickSort \t HeapSort \t\t QuickSort \t HeapSort \t\t QuickSort \t HeapSort"
		cout << sizeVector
				 << "\t" << prd((StepsRQ / iterationsPerSize / 1000000.0), roundDigits) << "\t\t" << prd((StepsRH / iterationsPerSize / 1000000.0), roundDigits)
				 << "\t\t" << prd((StepsRSQ / iterationsPerSize / 1000000.0), roundDigits) << "\t\t" << prd((StepsRSH / iterationsPerSize / 1000000.0), roundDigits)
				 << "\t\t" << prd((StepsSQ / iterationsPerSize / 1000000.0), roundDigits) << "\t\t" << prd((StepsSH / iterationsPerSize / 1000000.0), roundDigits)
				 << endl;
	}
}