#ifndef CONJUNTO_ABB_HPP
#define CONJUNTO_ABB_HPP

#include "IConjuntoArbol.hpp"

template <typename T>
class NodoABB : public Nodo<T>
{
public:
  NodoABB(const T &valor) : Nodo<T>(valor) {}
};

template <typename T>
class ConjuntoABB : public IConjuntoArbol<T>
{
public:
  void insertar(const T &valor)
  {
    if (this->raiz == nullptr)
    {
      this->raiz = new Nodo<T>(valor);
    }
    NodoABB<T> *actual = static_cast<NodoABB<T> *>(this->raiz);

    bool continuar = true;
    while (continuar)
    {
      if (actual->valor > valor)
      {
        if (actual->izq == nullptr)
        {
          actual->izq = new NodoABB<T>(valor);
          continuar = false;
        }
        else
        {
          actual = static_cast<NodoABB<T> *>(actual->izq);
        }
      }
      else if (actual->valor == valor)
      {
        actual->valor = valor;
        continuar = false;
      }
      else
      {
        if (actual->der == nullptr)
        {
          actual->der = new NodoABB<T>(valor);
          continuar = false;
        }
        else
        {
          actual = static_cast<NodoABB<T> *>(actual->der);
        }
      }
    }
  }

  void eliminar(const T &valor)
  {
    NodoABB<T> *parent = static_cast<NodoABB<T> *>(nullptr);
    NodoABB<T> *actual = static_cast<NodoABB<T> *>(this->raiz);
    while (actual != nullptr && actual->valor != valor)
    {
      parent = actual;
      if (valor < actual->valor)
      {
        actual = static_cast<NodoABB<T> *>(actual->izq);
      }
      else
      {
        actual = static_cast<NodoABB<T> *>(actual->der);
      }
    }
    if (actual == nullptr)
    {
      return;
    }
    if (actual->izq == nullptr && actual->der == nullptr)
    {
      if (actual != this->raiz)
      {
        if (parent->izq == actual)
        {
          parent->izq = nullptr;
        }
        else
        {
          parent->der = nullptr;
        }
      }
      else
      {
        this->raiz = nullptr;
      }
      free(actual);
    }
    else if (actual->izq && actual->der)
    {
      NodoABB<T> *sucesor = static_cast<NodoABB<T> *>(this->nodoMinimo(actual->der));
      int tempVal = sucesor->valor;
      eliminar(sucesor->valor);
      actual->valor = tempVal;
    }
    else
    {
      NodoABB<T> *hijo = static_cast<NodoABB<T> *>((actual->izq) ? actual->izq : actual->der);
      if (actual != this->raiz)
      {
        if (actual == parent->izq)
        {
          parent->izq = hijo;
        }
        else
        {
          parent->der = hijo;
        }
      }
      else
      {
        this->raiz = hijo;
      }
      free(actual);
    }
  }
};

#endif