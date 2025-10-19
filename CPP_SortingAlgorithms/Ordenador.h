#ifndef Ordenador_h
#define Ordenador_h

#include <iostream>
#include <vector>
#include <math.h>
#include <string>

class Ordenador{
 private:
	// Defina aquí los métodos auxiliares de los algoritmos de ordenamiento solamente.
	// Puede definir cuantos métodos quiera.
	void merge(int *A, int p, int q, int r);
	void sort(int *A, int p, int r);

	void maxHeapify(int* A, int i, int n);
	void buildMaxHeap(int* A, int n);

	int partition(int* A, int p, int r);
	void quicksort(int *A, int p, int r);

	int* countingSort(int* A, int n, int k);
	int change_base(int number, int base, std::vector< int > &result);
 public:
	Ordenador(){};
	~Ordenador(){};
	// Si no implementa algunos de los métodos de ordenamiento no lo borre;
	// déjelo con el cuerpo vacío para evitar errores de compilación, ya
	// que se va a ejecutar el mismo «main» para todas las tareas.
	// Implemente los algoritmos en este archivo, no en un CPP.
	void seleccion(int *A, int n);
	void insercion(int *A, int n);
	void mergesort(int *A, int n);
	void heapsort(int *A, int n);
	void quicksort(int *A, int n);
	void radixsort(int *A, int n);
};

void Ordenador::seleccion(int *A, int n) {
	int least = 0;
	int temp = 0;
	for (int i = 0; i < n; ++i) {
		least = i;
		for (int j = i; j < n; ++j) {
			if (A[j] < A[least]) {
				least = j;
			}
		}
		temp = A[i];
		A[i] = A[least];
		A[least] = temp;
	}
}

void Ordenador::insercion(int *A, int n) {
  for (int i = 1; i < n; ++i) {
    int j = i;
    while (j != 0 && A[j - 1] > A[j]) {
      int temp = A[j - 1];
      A[j - 1] = A[j];
      A[j] = temp;
    	--j;      
  	}
	}
}

void Ordenador::merge(int *A, int p, int q, int r) {
	int nL = q - p + 1;
	int nR = r - q;
	int L[nL];
	int R[nR];
	for (int i = 0; i < nL; ++i) {
		L[i] = A[p + i];
	}
	for (int j = 0; j < nR; ++j) {
		R[j] = A[q + j + 1];
	}
	
	int i = 0;
	int j = 0;
	int k = p;

	while (i < nL  && j < nR) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			++i;
		} else {
			A[k] = R[j];
			++j;
		}
		++k;
	}
	while (i < nL) {
		A[k] = L[i];
		++i;
		++k;
	}
	while (j < nR) {
		A[k] = R[j];
		++j;
		++k;
	}
}

void Ordenador::mergesort(int *A, int n) {
	if (A && n > 1) {
		sort(A, 0, n);
	}
}

void Ordenador::sort(int * A, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		sort(A, p, q);
		sort(A, q + 1, r);
		merge(A, p, q, r);
	}
}

void Ordenador::maxHeapify(int *A, int i, int n) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;

	if (left < n && A[left] > A[largest]) {
		largest = left;
	}
	if (right < n && A[right] > A[largest]) {
		largest = right;
	}
	if (largest != i) {
		int temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;

		maxHeapify(A, largest, n);
	}
}

void Ordenador::buildMaxHeap(int* A, int n) {
	for (int i = n/2 - 1; i >= 0; --i) {
		maxHeapify(A, i, n);
	}
}

void Ordenador::heapsort(int* A, int n) {
	buildMaxHeap(A, n);
	for (int i = n - 1; i > 0; --i) {
		int temp = A[0];
		A[0] = A[i];
		A[i] = temp;

		maxHeapify(A, 0, i);
	}
}

void Ordenador::quicksort(int* A, int n) {
	quicksort(A, 0, n - 1);
}

void Ordenador::quicksort(int *A, int p, int r) {
	if (p < r) {
		int q = partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

int Ordenador::partition(int* A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j <= r; ++j) {
		if (A[j] < x) {
			++i;
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	int temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;
	return i + 1;
}


int* Ordenador::countingSort(int* A, int n, int k) {
	int* B = new int[n];
	int C[k];

	for (int i = 0; i < k; ++i) {
		C[i] = 0;
	}
	for (int j = 1; j < n; ++j) {
		C[A[j]] = C[A[j]] + 1;
	}
	for (int i = 1; i < k; ++i) {
		C[i] = C[i] + C[i - 1];
	}
	for (int j = n - 1; j >= 1; --j) {
		B[C[A[j]]] = A[j];
		C[A[j]] = C[A[j]] - 1;
	}
}

int getMax(int* A, int n)  { 
	int mx = A[0]; 
	for (int i = 1; i < n; i++) 
		if (A[i] > mx) 
			mx = A[i]; 
	return mx; 
} 

void Ordenador::radixsort(int* A, int n) {
	int base = pow(2, std::log2(n));
	// guarda el numero de A[i] en base "base";
	std::vector<int> result;
	// Se cambia la base de los numeros de A.
	for (int i = 0; i < 1; ++i) {
		//A[i] = change_base(A[i], base, result);
	}

	//for ... {
		//countingSort(A, n, k);
	//}
}

int Ordenador::change_base(int number, int base, std::vector< int > &result) {
  while (number > 0) {
  	result.insert(result.begin(), number % base);
    number /= base;
  }
	std::string num = "";
	for (int j = 0; j < result.size(); ++j) {
		num.append(std::to_string(result[j]));
	}
	return std::stoi(num);
}

#endif
