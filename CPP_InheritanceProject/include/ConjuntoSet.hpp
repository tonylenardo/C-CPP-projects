#ifndef CONJUNTOSET_HPP
#define CONJUNTOSET_HPP

#include "IConjunto.hpp"
#include <set>

template <typename T>
class ConjuntoSet : public IConjunto<T>
{
private:
  std::set<T> elementos;

public:
  void insertar(const T &elemento)
  {
    elementos.insert(elemento);
  }

  void eliminar(const T &elemento)
  {
    elementos.erase(elemento);
  }

  bool pertenece(const T &elemento) const
  {
    return elementos.find(elemento) != elementos.end();
  }
};
#endif