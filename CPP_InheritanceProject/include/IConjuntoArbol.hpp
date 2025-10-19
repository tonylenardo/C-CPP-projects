#ifndef I_CONJUNTO_ARBOL_HPP
#define I_CONJUNTO_ARBOL_HPP

#include "IConjunto.hpp"

template <typename T>
class Nodo
{
public:
  T valor;
  Nodo *izq;
  Nodo *der;
  Nodo(const T &valor) : valor(valor), izq(nullptr), der(nullptr){};
};

template <typename T>
class IConjuntoArbol : public IConjunto<T>
{
public:
protected:
  Nodo<T> *raiz;

  Nodo<T> *buscar(const T &valor) const
  {
    Nodo<T> *actual = raiz;
    while (actual != nullptr)
    {
      if (valor == actual->valor)
      {
        return actual;
      }
      else if (std::less<T>{}(valor, actual->valor))
      {
        actual = actual->izq;
      }
      else
      {
        actual = actual->der;
      }
    }
    return nullptr;
  }

  Nodo<T> *nodoMinimo(Nodo<T> *nodo) const
  {
    Nodo<T> *actual = nodo;
    while (actual->izq != nullptr)
    {
      actual = actual->izq;
    }
    return actual;
  }

  bool pertenece(const T &valor) const
  {
    Nodo<T> *actual = raiz;
    while (actual != nullptr)
    {
      if (valor == actual->valor)
      {
        return true;
      }
      else if (std::less<T>{}(valor, actual->valor))
      {
        actual = actual->izq;
      }
      else
      {
        actual = actual->der;
      }
    }
    return false;
  }

public:
  virtual void insertar(const T &valor) = 0;
  virtual void eliminar(const T &valor) = 0;
  virtual ~IConjuntoArbol() {}
};

#endif