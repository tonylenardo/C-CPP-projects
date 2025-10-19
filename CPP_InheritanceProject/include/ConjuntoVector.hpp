#ifndef CONJUNTOVECTOR_HPP
#define CONJUNTOVECTOR_HPP

#include "IConjunto.hpp"
#include <algorithm>
#include <vector>

template <typename T>
class ConjuntoVector : public IConjunto<T>
{
public:
  void insertar(const T &elemento)
  {
    if (!pertenece(elemento))
    {
      elementos.push_back(elemento);
    }
  }

  void eliminar(const T &elemento)
  {
    auto elementoBuscado = std::find(elementos.begin(), elementos.end(), elemento);
    if (elementoBuscado != elementos.end())
    {
      elementos.erase(elementoBuscado);
    }
  }

  bool pertenece(const T &elemento) const
  {
    return std::find(elementos.begin(), elementos.end(), elemento) != elementos.end();
  }

  // Métodos de ordenamiento
  void merge(const T &izq, const T &mid, const T &der)
  {
    auto const arr1 = mid - izq + 1;
    auto const arr2 = der - mid;

    auto *arrIzq = new int[arr1];
    auto *arrDer = new int[arr2];

    for (auto i = 0; i < arr1; i++)
    {
      arrIzq[i] = elementos[izq + i];
    }
    for (auto j = 0; j < arr2; j++)
    {
      arrDer[j] = elementos[mid + 1 + j];
    }
    auto i1 = 0;
    auto i2 = 0;
    int i3 = izq;

    while (i1 < arr1 && i2 < arr2)
    {
      if (arrIzq[i1] <= arrDer[i2])
      {
        elementos[i3] = arrIzq[i1];
        i1++;
      }
      else
      {
        elementos[i3] = arrDer[i2];
        i2++;
      }
      i3++;
    }

    while (i1 < arr1)
    {
      elementos[i3] = arrIzq[i1];
      i1++;
      i3++;
    }

    while (i2 < arr2)
    {
      i2++;
      i3++;
    }
    delete[] arrIzq;
    delete[] arrDer;
  }
  void mergeSort(const T &inicio, const T &fin)
  {
    if (inicio < fin)
    {
      T mid = inicio + (fin - inicio) / 2;
      mergeSort(inicio, mid);
      mergeSort(mid + 1, fin);
      merge(inicio, mid, fin);
    }
  }

  void sort()
  {
    std::sort(elementos.begin(), elementos.end());
  }

  void bubbleSort(int n)
  {
    while (true)
    {
      for (int i = 1; i < n; i++)
      {
        if (std::greater<T>{}(elementos[i - 1], elementos[i]))
        {
          swap(i - 1, i);
        }
      }
      if (!inOrder())
      {
        break;
      }
    }
  }

  void quickSort(int first, int last)
  {
    if (first < last)
    {
      int pivotI = partition(first, last);
      quickSort(first, pivotI - 1);
      quickSort(pivotI - 1, last);
    }
  }

  // Explicacion del algoritmo Heap Sort tomada del video:
  // https://www.youtube.com/watch?v=yXluViYl-DM&ab_channel=KrishnaTeaches

  void heapSort(int n)
  {
    buildHeap(n);
    for (int i = n - 1; i >= 0; i--)
    {
      swap(0, i);
      heapify(i, 0);
    }
  }

private:
  std::vector<T> elementos;

  void buildHeap(int n)
  {
    for (int i = n / 2 - 1; i >= 0; i--)
    {
      heapify(i, n);
    }
  }

  void heapify(int i, int n)
  {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && elementos[left] > elementos[largest])
      largest = left;

    if (right < n && elementos[right] > elementos[largest])
      largest = right;

    if (largest != i)
    {
      swap(i, largest);
      heapify(n, largest);
    }
  }

  bool inOrder()
  {
    for (int i = 1; i < sizeof(elementos); i++)
    {
      if (std::less<T>{}(elementos[i - 1], elementos[i]))
      {
        continue;
      }
      else
      {
        return false;
      }
    }
    return true;
  }

  int partition(int f, int l)
  {
    auto pivot = elementos[l];
    int pivotI = f;
    for (int i = f; i <= l; i++)
    {
      if (elementos[i] <= pivot)
      {
        swap(pivotI, i);
        pivotI++;
      }
    }
    pivotI--;
    return pivotI;
  }

  void swap(int a, int b)
  {
    int temp = elementos[b];
    elementos[b] = elementos[a];
    elementos[a] = temp;
  }
};

#endif
