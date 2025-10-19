#include <iostream>
#include "ConjuntoVector.hpp"
#include "ConjuntoSet.hpp"
#include "ConjuntoUnorderedSet.hpp"
#include "ConjuntoABB.hpp"
#include "ConjuntoArbolRN.hpp"
#include "IOrdenamiento.hpp"
#include <assert.h>
#include <fstream>
#include <ctime>
#include <chrono>
#include <ratio>
#include <time.h>

using namespace std::chrono;

void PruebaIConjunto(IConjunto<int> &conjunto);

double tiempoInsertarEnOrden(IConjunto<int> &conjunto);
double tiempoBuscarEnOrden(IConjunto<int> &conjunto);
double tiempoEliminarEnOrden(IConjunto<int> &conjunto);

double tiempoInsertarEnDesorden(IConjunto<int> &conjunto);
double tiempoBuscarEnDesorden(IConjunto<int> &conjunto);
double tiempoEliminarEnDesorden(IConjunto<int> &conjunto);

void archivoDePruebaEnOrden(IConjunto<int> &conjunto, std::string nombreArchivo);

double tiempoDeOrdenamientoBubbleSort(ConjuntoVector<int> &conjuntoVector);
double tiempoDeOrdenamientoQuickSort(ConjuntoVector<int> &conjuntoVector);
double tiempoDeOrdenamientoMergeSort(ConjuntoVector<int> &conjuntoVector);
double tiempoDeOrdenamientoSort(ConjuntoVector<int> &conjuntoVector);
double tiempoDeOrdenamientoHeapSort(ConjuntoVector<int> &conjuntoVector);

void archivoDeAlgoritmosDeOrdenamiento(ConjuntoVector<int> &conjunto, std::string nombreArchivo); // Metodo por completar

int main()
{
	srand(time(NULL));
	ConjuntoVector<int> conjuntoArray;
	ConjuntoSet<int> conjuntoSet;
	ConjuntoUnorderedSet<int> conjuntoUnorderedSet;

	archivoDePruebaEnOrden(conjuntoArray, "RendimientoArray.csv");
	archivoDePruebaEnOrden(conjuntoSet, "RendimientoSet.csv");
	archivoDePruebaEnOrden(conjuntoUnorderedSet, "RendimientoUnorderedSet.csv");

	// Parte 2 Estos metodos ban dentro de otro metodo que guarde los datos
	tiempoDeOrdenamientoSort(conjuntoArray);
	tiempoDeOrdenamientoMergeSort(conjuntoArray);

	return 0;
};

void archivoDePruebaEnOrden(IConjunto<int> &conjunto, std::string nombreArchivo)
{
	std::ofstream MyFile(nombreArchivo, std::ios::out);
	if (MyFile.fail())
	{
		std::cout << "Error al crear el archivo" << std::endl;
	}
	else
	{
		MyFile << "Operación"
					 << ","
					 << "Número de Operaciones"
					 << ","
					 << "Rendimiento de cada estructura"
					 << "Tiempo de inserción en orden"
					 << ","
					 << "1000000"
					 << "," << tiempoInsertarEnOrden(conjunto) << std::endl
					 << "Tiempo de busqueda en orden"
					 << ","
					 << "1000000"
					 << "," << tiempoBuscarEnOrden(conjunto) << std::endl
					 << "Tiempo de eliminación en orden"
					 << ","
					 << "1000000"
					 << "," << tiempoEliminarEnOrden(conjunto) << std::endl
					 << "Tiempo de inserción aleatorio"
					 << ","
					 << "1000000"
					 << "," << tiempoInsertarEnDesorden(conjunto) << std::endl
					 << "Tiempo de busqueda aleatorio"
					 << ","
					 << "1000000"
					 << "," << tiempoBuscarEnDesorden(conjunto) << std::endl
					 << "Tiempo de eliminación aleatorio"
					 << ","
					 << "1000000"
					 << "," << tiempoEliminarEnDesorden(conjunto) << std::endl;
		MyFile.close();
	}
}

void crearArchivoDeAlgoritmosDeOrdenamiento(ConjuntoVector<int> &conjunto, std::string nombreArchivo)
{

	std::ofstream MyFile(nombreArchivo, std::ios::out);
	if (MyFile.fail())
	{
		std::cout << "Error al crear el archivo" << std::endl;
	}
	else
	{
		MyFile << "Operación"
					 << ","
					 << "Número de Operaciones"
					 << ","
					 << "Rendimiento de cada estructura"
					 << "Tiempo de inserción en orden"
					 << ","
					 << "1000000"
					 << "," << tiempoInsertarEnOrden(conjunto) << std::endl
					 << "Tiempo de busqueda en orden"
					 << ","
					 << "1000000"
					 << "," << tiempoBuscarEnOrden(conjunto) << std::endl
					 << "Tiempo de eliminación en orden"
					 << ","
					 << "1000000"
					 << "," << tiempoEliminarEnOrden(conjunto) << std::endl
					 << "Tiempo de inserción aleatorio"
					 << ","
					 << "1000000"
					 << "," << tiempoInsertarEnDesorden(conjunto) << std::endl
					 << "Tiempo de busqueda aleatorio"
					 << ","
					 << "1000000"
					 << "," << tiempoBuscarEnDesorden(conjunto) << std::endl
					 << "Tiempo de eliminación aleatorio"
					 << ","
					 << "1000000"
					 << "," << tiempoEliminarEnDesorden(conjunto) << std::endl;
		MyFile.close();
	}
}

// Se insertan N elementos en orden.
double tiempoInsertarEnOrden(IConjunto<int> &conjunto)
{

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int index = 0; index < 1000000; index++)
	{
		conjunto.insertar(index);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	return time_span.count();
}

// Se buscan N elementos en orden.
double tiempoBuscarEnOrden(IConjunto<int> &conjunto)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int index = 0; index < 1000000; index++)
	{
		conjunto.pertenece(index);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	return time_span.count();
}

// Se eliminan N elementos en orden.
double tiempoEliminarEnOrden(IConjunto<int> &conjunto)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int index = 0; index < 1000000; index++)
	{
		conjunto.eliminar(index);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	return time_span.count();
}

// Se Insertan N elementos en aleatorios.
double tiempoInsertarEnDesorden(IConjunto<int> &conjunto)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int index = 0; index < 1000000; index++)
	{
		conjunto.insertar(rand() % 1000000);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	return time_span.count();
}

// Se buscan N elementos aleatorios.
double tiempoBuscarEnDesorden(IConjunto<int> &conjunto)
{

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int index = 0; index < 1000000; index++)
	{
		conjunto.pertenece(rand() % 1000000);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	return time_span.count();
}

// Se eliminan N elementos aleatorios.
double tiempoEliminarEnDesorden(IConjunto<int> &conjunto)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int index = 0; index < 1000000; index++)
	{
		conjunto.eliminar(rand() % 1000000);
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	return time_span.count();
}

// Algoritmo de ordenamiento BubleSort
double tiempoDeOrdenamientoBubbleSort(ConjuntoVector<int> &conjuntoVector)
{
	tiempoInsertarEnDesorden(conjuntoVector);
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	conjuntoVector.bubbleSort(1000000);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	tiempoEliminarEnOrden(conjuntoVector);
	return time_span.count();
}

double tiempoDeOrdenamientoQuickSort(ConjuntoVector<int> &conjuntoVector)
{
	tiempoInsertarEnDesorden(conjuntoVector);
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	conjuntoVector.quickSort(0, 999999);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	tiempoEliminarEnOrden(conjuntoVector);
	return time_span.count();
}
double tiempoDeOrdenamientoMergeSort(ConjuntoVector<int> &conjuntoVector)
{
	tiempoInsertarEnDesorden(conjuntoVector);
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	conjuntoVector.mergeSort(0, 999999);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	tiempoEliminarEnOrden(conjuntoVector);
	return time_span.count();
}
double tiempoDeOrdenamientoSort(ConjuntoVector<int> &conjuntoVector)
{
	tiempoInsertarEnDesorden(conjuntoVector);
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	conjuntoVector.sort();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	tiempoEliminarEnOrden(conjuntoVector);
	return time_span.count();
}
double tiempoDeOrdenamientoHeapSort(ConjuntoVector<int> &conjuntoVector)
{
	tiempoInsertarEnDesorden(conjuntoVector);
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	conjuntoVector.heapSort(10);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	tiempoEliminarEnOrden(conjuntoVector);
	return time_span.count();
}

void PruebaIConjunto(IConjunto<int> &conjunto)
{

	conjunto.insertar(1);
	conjunto.insertar(2);
	conjunto.insertar(3); // craking the coding review
	assert(conjunto.pertenece(1));
	assert(conjunto.pertenece(2));
	assert(conjunto.pertenece(3));
	assert(!conjunto.pertenece(4));
	conjunto.insertar(2);
	assert(conjunto.pertenece(2));

	conjunto.eliminar(2);
	assert(!conjunto.pertenece(2));
	conjunto.eliminar(1);
	assert(!conjunto.pertenece(1));
	conjunto.insertar(2);
	assert(conjunto.pertenece(2));

	// Pruebas de sobrecarga de operadores.
	conjunto -= 21;
	assert(!conjunto.pertenece(21));
	conjunto += 21;
	assert(conjunto.pertenece(21));
	conjunto += 21;
	assert(conjunto.pertenece(21));
	conjunto -= 21;
	assert(!conjunto.pertenece(21));
	conjunto += 21;
}