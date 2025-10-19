//
//  bstree.h
//

#ifndef bstree_h
#define bstree_h

#include <iostream>
#include <stack>

// Nodos del arbol:
template <typename T>
class bstnode {
public:
  // Esta clase es usada por otras clases. Para mayor eficiencia,
  // los atributos se hacen publicos.
  T key;
  bstnode<T> *p, *left, *right;
   
  // Constructor por omision
  bstnode() {};
   
  // Inicializacion de datos miembro
  bstnode(const T& k, bstnode<T> *w = nullptr, bstnode<T> *y = nullptr
	  , bstnode<T> *z = nullptr):key(k), p(w), left(y), right(z) {};
   
  // Destructor
  ~bstnode() {};
};

// Arbol de busqueda binario:
template <typename T>
class bstree {
public:
  bstnode<T> *root;    // raiz del arbol

  bstree() {
    // Constructor (crea un arbol vacio)
    this->root = nullptr;
  };

	~bstree() {
		// Destructor (borra el arbol)
		this->DeleteAll(this->root);
	};
	
	void DeleteAll(bstnode<T>* x) {
		if (x) {
			this->DeleteAll(x->left);
			this->Delete(x);
			this->DeleteAll(x->right);
		}
	};

	void Insert(bstnode<T>* z) {
		// Inserta el nodo z en la posicion que le corresponde en el arbol.

		bstnode<T>* x = this->root;
		bstnode<T>* y = nullptr;
		while (x) {
			y = x;
			if (z->key < x->key) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		z->p = y;
		if (!y) {
			this->root = z;
		} else if (z->key < y->key) {
			y->left = z;
		} else if (z->key > y->key) {
			y->right = z;
		}

	};
	
	void InorderWalk(bstnode<T> *x) {
		// Recorre en orden el sub�arbol con raiz x, imprimiendo la llave de cada nodo en en una nueva linea de la salida estandar despues de recorrido el subarbol izquierdo y antes de recorrer el subarbol derecho.
		if (x) {
			this->InorderWalk(x->left);
			std::cout << x->key << std::endl;
			this->InorderWalk(x->right);
		}
	};
	
	bstnode<T>* Search(bstnode<T> *x, const T& k) {
		// Busca la llave k recursivamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve nullptr.
		if (!x || x->key == k) { return x; }
		if (k < x->key) { return this->Search(x->left, k); }
		else { return this->Search(x->right, k); }
	};
	
	bstnode<T>* IterativeSearch(bstnode<T> *x, const T& k) {
		// Busca la llave k iterativamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve nullptr.
		while (x && x->key != k) {
			if (x->key < k) { x = x->right; }
			else { x = x->left; }
		}
		return x;
	};
	
	bstnode<T>* Minimum(bstnode<T> *x) {
		// Devuelve el nodo que tiene la llave menor. Si el arbol esta� vacio, devuelve nullptr.
		while (x->left) { x = x->left; }
		return x;
	};
	
	bstnode<T>* Maximum(bstnode<T> *x) {
		// Devuelve el nodo que tiene la llave mayor. Si el arbol esta vacio devuelve nullptr.
		while (x->right) { x = x->right; }
		return x;
	};
	
	bstnode<T>* Successor(bstnode<T> *x) {
		// Devuelve el nodo cuya llave es la que le sigue a la del nodo x. Si no existe el nodo, devuelve nullptr.
		if (x->right) {
			this->Minimum(x->right);
		} else {
			bstnode<T>* y = x->p;
			while (y && x == y->right) {
				x = y;
				y = y->p;
			}
			return y;
		}		
	};

	void transplant(bstnode<T>* u, bstnode<T>* v) {
		if (!u->p) { this->root = v; }
		else if (u == u->p->left) { u->p->left = v; }
		else { u->p->right = v; }
		if (v) { v->p = u->p; }
	}
	
	void Delete(bstnode<T>* z) {
		// Saca del arbol la llave contenida en el nodo apuntado por z.
		if (!z->left) {
			this->transplant(z, z->right);
		}
		else if (!z->right) {
			this->transplant(z, z->left);
		}
		else {
			bstnode<T>* y = this->Minimum(z->right);
			if (y && z->right && y->key != z->right->key) {
				this->transplant(y, y->right);
				y->right = z->right;
				y->right->p = y;
			}
			this->transplant(z, y);
			y->left = z->left;
			y->left->p = y;
		}
	};

	void createBSTree(int n) {
		if (!this->root) { this->root = new bstnode<T>(0); }
		bstnode<T>* x = this->root;
		for (int i = 1; i < n; ++i) {
			x->right = new bstnode<T>(i);
			x = x->right;
		}
	}

};

#endif /* bstree_h */

