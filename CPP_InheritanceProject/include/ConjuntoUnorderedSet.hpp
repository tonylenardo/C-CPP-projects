#ifndef CONJUNTOUNORDEREDSET_HPP
#define CONJUNTOUNORDEREDSET_HPP

#include "IConjunto.hpp"
#include <unordered_set>

template <typename T>
class ConjuntoUnorderedSet : public IConjunto<T>
{
private:
  std::unordered_set<T> elementos;

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
