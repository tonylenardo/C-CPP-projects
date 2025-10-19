//
//  chtable.h
//

#ifndef chtable_h
#define chtable_h

#include <iostream>
#include <list>
#include <vector>

template <typename T>

// Tabla de dispersión con encadenamiento
class chtable {
public:
  // Constructor que especifica el tamaño de la tabla
  chtable(int sz) {
    this->size = sz;
    this->table.resize(sz);
  };

  // Destructor (borra la tabla)
  ~chtable() {
    for (int i = 0; i < this->size; ++i) {
      if (!this->table[i].empty()) {
        this->table[i].erase(this->table[i].begin(), this->table[i].end());
      }
    }
    this->size = 0;
  };

  // Inserta el elemento en la tabla
  void Insert(const T& k) {
    int q = k % this->size;
    this->table[q].push_front(k);
  };

  // Retorna un puntero a la llave o nullptr si no se encuentra
  T* Search(const T& k) {
    int q = static_cast<int>(k % this->size);
    if (!this->table[q].empty()) {
      for (const auto& e : this->table[q]) {
        if (e == k) {
          T* result = &q;
          return result;
        }
      }
    }
    return nullptr;
  };


private:
  // Número de entradas en la tabla
  int size;

  // La tabla es un vector de listas de STL
  std::vector<std::list<T>> table;
};

#endif /* chtable_h */
