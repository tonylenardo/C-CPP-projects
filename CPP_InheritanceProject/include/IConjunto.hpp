#ifndef ICONJUNTO_HPP
#define ICONJUNTO_HPP
template <typename T>
class IConjunto
{
public:
  virtual void insertar(const T &elemento) = 0;
  virtual void eliminar(const T &elemento) = 0;
  virtual bool pertenece(const T &elemento) const = 0;
  virtual void operator+=(const T& elemento) {
    insertar(elemento);
  }
  virtual void operator-=(const T& elemento) {
    eliminar(elemento);
  }
  virtual ~IConjunto() {}
};

#endif