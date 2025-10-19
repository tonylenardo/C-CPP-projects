//
//  llist.h
//
# include <iostream>
#ifndef llist_h
#define llist_h

// Nodos de la lista:
template <typename T>
class llnode {
public:
  // Esta clase es para ser usada por otras clases. Por eficiencia los atributos se dejan publicos.
  T key;
  llnode<T> *prev, *next;
  
  // Constructor por omision.
  llnode() {};
  
  // Inicializacion de los datos miembro.
  llnode(const T& k, llnode<T> *w = nullptr, llnode<T> *y = nullptr):key(k), prev(w), next(y) {};
  
  ~llnode() {};
};

// Lista enlazada con nodo centinela:
template <typename T>
class llist
{
public:
  llnode<T> *nil;        // nodo centinela

  llist() {
    // Constructor (crea una lista vacia)
    this->nil = new llnode<T>();
    this->nil->key = -1;
    this->nil->next = this->nil;
    this->nil->prev = this->nil;
  };
  
  ~llist() {
    // Destructor (borra la lista)
    llnode<T>* x = this->nil->next;
    while (x != this->nil) { 
      this->Delete(x);
      x = x->next; 
    }
  };
  
  void Insert(llnode<T>* x) {
    // Inserta el nodo x en la lista.
    if (x) {
      x->next = this->nil->next;
      this->nil->next->prev = x;
      this->nil->next = x;
      x->prev = this->nil;
    } else {
      std::cerr << "ERROR: invalid node" << std::endl;
    }
  };

  llnode<T>* Search(const T& k) {
    // Busca la llave iterativamente. Si la encuentra, devuelve un apuntador al nodo que la contiene; sino devuelve el nodo nil (el centinela).
    llnode<T>* x = this->nil->next;
    while (x->key != k && x != this->nil) { x = x->next; }
    return x;
  };
      
  void Delete(llnode<T>* x) {
    // Saca de la lista la llave contenida en el nodo apuntado por x.
    if (x) {
      x->prev->next = x->next;
      x->next->prev = x->prev;
      //delete x;
    } else {
      std::cerr << "ERROR: invalid node" << std::endl;
    }
  };    
};

#endif /* llist_h */
