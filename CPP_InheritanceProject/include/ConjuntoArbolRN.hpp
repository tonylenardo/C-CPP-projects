#ifndef CONJUNTOARBOLRN
#define CONJUNTOARBOLRN

#include "IConjuntoArbol.hpp"
#include <cassert>

enum Color
{
  NEGRO,
  ROJO
};

template <typename T>
class NodoRN : public Nodo<T>
{
public:
  enum Color color;
  NodoRN *padre;
  NodoRN(const T &valor, Color color) : Nodo<T>(valor), color(color), padre(nullptr) {}
};

template <typename T>
class ConjuntoArbolRN : public IConjuntoArbol<T>
{
public:
  void insertar(const T &valor)
  {
    NodoRN<T> *nodoY = nullptr;
    if (this->raiz == nullptr)
    {
      this->raiz = new Nodo<T>(valor);
    }
    NodoRN<T> *nodoX = static_cast<NodoRN<T> *>(this->raiz);
    NodoRN<T> *nuevoNodo = new NodoRN<T>(valor, ROJO); // Nodo a insertar

    while (nodoX != nullptr)
    {
      nodoY = nodoX;

      if (nuevoNodo->valor < nodoX->valor)
      {
        nodoX = static_cast<NodoRN<T> *>(nodoX->izq);
      }
      else
      {
        nodoX = static_cast<NodoRN<T> *>(nodoX->der);
      }
    }
    nuevoNodo->padre = nodoY;

    if (nodoY == nullptr)
    {
      this->raiz = nuevoNodo;
    }
    else if (nuevoNodo->valor < nodoY->valor)
    {
      nodoY->izq = nuevoNodo;
    }
    else
    {
      nodoY->der = nuevoNodo;
    }

    nuevoNodo->izq = nullptr;
    nuevoNodo->der = nullptr;
    nuevoNodo->color = ROJO;
    insertarRN(nuevoNodo);
  }

  void insertarRN(NodoRN<T> *nuevoNodo)
  {
    while (nuevoNodo->padre->color == ROJO)
    { 
      if (nuevoNodo->padre == nuevoNodo->padre->izq)
      {
        Nodo<T> *nodoAbuelo = nuevoNodo->padre->padre->der;

        if (static_cast<NodoRN<T> *>(nodoAbuelo)->color == ROJO)
        {
          nuevoNodo->padre->color = NEGRO;
          static_cast<NodoRN<T> *>(nodoAbuelo)->color = NEGRO;
          nuevoNodo->padre->padre->color = ROJO;
          nuevoNodo = static_cast<NodoRN<T> *>(nuevoNodo)->padre->padre;
        }
        else if (nuevoNodo == nuevoNodo->padre->der)
        {
          nuevoNodo = nuevoNodo->padre;
          rotar_izq(nuevoNodo);
        }
        nuevoNodo->padre->color = NEGRO;
        nuevoNodo->padre->padre->color = ROJO;
        rotar_der(nuevoNodo);
      }
      else
      {
        static_cast<NodoRN<T> *>(this->raiz)->color = NEGRO;
      }
    }
  }

  void eliminar(const T &valor)
  {
    Nodo<T> *nodo = this->buscar(valor);
    NodoRN<T> *nodoY;
    NodoRN<T> *nodoX;

    if (nodo->der != nullptr || nodo->izq != nullptr)
    {
      nodoY = static_cast<NodoRN<T> *>(nodo);
    }
    else
    {
      nodoY = sucesor(static_cast<NodoRN<T> *>(nodo));
    }

    if (nodoY->izq != nullptr)
    {
      Nodo<T> *temp = new Nodo<T>(nodoY->izq->valor, nodoY->izq, nullptr);
      nodoX = static_cast<NodoRN<T> *>(temp);
    }
    else
    {
      Nodo<T> *temp = new Nodo<T>(nodoY->der->valor, nullptr, nodoY->der);
      nodoX = static_cast<NodoRN<T> *>(temp);
    }

    nodoX->padre = nodoY->padre;

    if (nodoY->padre == nullptr)
    {
      this->raiz = nodoX;
    }
    else
    {
      if (nodoY == nodoY->padre->izq)
      {
        nodoY->padre->izq = nodoX;
      }
      else
      {
        nodoY->padre->der = nodoX;
      }
    }

    if (nodoY != static_cast<NodoRN<T> *>(nodo))
    {
      nodo->valor = nodoY->valor;
    }

    if (nodoY->color == NEGRO)
    {
      restaurarARN(nodoX);
    }
  }

  void restaurarARN(NodoRN<T> *nodo)
  {
    while (nodo != this->raiz && nodo->color == NEGRO)
    {
      if (nodo == nodo->padre->izq)
      {
        NodoRN<T> *nodoTemp = static_cast<NodoRN<T> *>(nodo->padre->der);

        // Caso 1
        if (nodoTemp->color == ROJO)
        {
          nodoTemp->color = NEGRO;
          nodo->padre->color = ROJO;
          rotar_izq(nodo->padre);
          nodoTemp = static_cast<NodoRN<T> *>(nodo->padre->der);
        }

        // Caso 2
        if (static_cast<NodoRN<T> *>(nodoTemp->izq)->color == NEGRO && static_cast<NodoRN<T> *>(nodoTemp->der)->color == NEGRO)
        {
          nodoTemp->color = ROJO;
          nodo = nodo->padre;
        }
        else
        {
          // Caso 3
          if (static_cast<NodoRN<T> *>(nodoTemp->der)->color == NEGRO)
          {
            static_cast<NodoRN<T> *>(nodoTemp->izq)->color = NEGRO;
            nodoTemp->color = ROJO;
            rotar_der(nodoTemp);
            nodoTemp = static_cast<NodoRN<T> *>(nodo->padre->der);
          }
          // Caso 4
          nodoTemp->color = nodo->padre->color;
          nodo->padre->color = NEGRO;
          static_cast<NodoRN<T> *>(nodoTemp->der)->color = NEGRO;
          rotar_izq(nodo->padre);
          nodo = static_cast<NodoRN<T> *>(this->raiz);
        }
      }
      else
      {
        NodoRN<T> *nodoTemp = static_cast<NodoRN<T> *>(nodo->padre->der);

        if (nodoTemp->color == ROJO)
        {
          nodoTemp->color = NEGRO;
          nodo->padre->color = ROJO;
          rotar_der(nodo->padre);
          nodoTemp = static_cast<NodoRN<T> *>(nodo->padre->izq);
        }

        if (static_cast<NodoRN<T> *>(nodoTemp->der)->color == NEGRO && static_cast<NodoRN<T> *>(nodoTemp->izq)->color == NEGRO)
        {
          nodoTemp->color = ROJO;
          nodo = nodo->padre;
        }
        else
        {
          if (static_cast<NodoRN<T> *>(nodoTemp->izq)->color == NEGRO)
          {
            static_cast<NodoRN<T> *>(nodoTemp->der)->color = NEGRO;
            nodoTemp->color = ROJO;
            rotar_der(nodoTemp);
            nodoTemp = static_cast<NodoRN<T> *>(nodo->padre->izq);
          }
          nodoTemp->color = nodo->padre->color;
          nodo->padre->color = NEGRO;
          static_cast<NodoRN<T> *>(nodoTemp->der)->color = NEGRO;
          rotar_der(nodo->padre);
          nodo = static_cast<NodoRN<T> *>(this->raiz);
        }
      }
    }

    nodo->color = NEGRO;
  }

  NodoRN<T> *sucesor(NodoRN<T> *nodo)
  {

    if (nodo->der != nullptr)
    {
      return static_cast<NodoRN<T> *>(this->nodoMinimo(nodo->der));
    }
    NodoRN<T> *temp = nodo->padre;

    while (temp != nullptr && nodo == temp->der)
    {
      nodo = temp;
      temp = temp->padre;
    }
    return temp;
  }

private:
  void rotar_izq(NodoRN<T> *nodo)
  {
    NodoRN<T> *nodoTemp = static_cast<NodoRN<T> *>(nodo->der);
    nodo->der = nodoTemp->izq;

    if (nodoTemp->izq != nullptr)
    {
      static_cast<NodoRN<T> *>(nodoTemp->izq)->padre = nodo;
    }

    static_cast<NodoRN<T> *>(nodoTemp)->padre = nodo->padre;

    if (nodo->padre == nullptr)
    {
      this->raiz = nodoTemp;
    }
    else if (nodo == nodo->padre->izq)
    {
      nodo->padre->izq = nodoTemp;
    }
    else
    {
      nodo->padre->der = nodoTemp;
    }

    nodoTemp->izq = nodo;
    nodo->padre = nodoTemp;
  }

  void rotar_der(NodoRN<T> *nodo)
  {
    NodoRN<T> *nodoTemp = static_cast<NodoRN<T> *>(nodo->izq);
    nodo->izq = nodoTemp->der;

    if (nodoTemp->der != nullptr)
    {
      static_cast<NodoRN<T> *>(nodoTemp->der)->padre = nodo;
    }

    static_cast<NodoRN<T> *>(nodoTemp)->padre = nodo->padre;

    if (nodo->padre == nullptr)
    {
      this->raiz = nodoTemp;
    }
    else if (nodo == nodo->padre->der)
    {
      nodo->padre->der = nodoTemp;
    }
    else
    {
      nodo->padre->izq = nodoTemp;
    }

    nodoTemp->der = nodo;
    nodo->padre = nodoTemp;
  }
};

#endif
