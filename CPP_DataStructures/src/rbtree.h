//
//  rbtree.h
//

#ifndef rbtree_h
#define rbtree_h

#include <iostream>

enum colors { RED, BLACK };

// Nodos del arbol:
template <typename T>
class rbtnode
{
public:
	// Esta clase es usada por la clase rbtree. Por eficiencia se hacen los atributos publicos.
	T key;
	rbtnode<T>* p, * left, * right;
	enum colors color;

	// Constructor por omision.
	rbtnode() {
	};

	//Inicializacion de datos miembro.
	rbtnode(const T& k, rbtnode<T>* w = nullptr, rbtnode<T>* y = nullptr
		, rbtnode<T>* z = nullptr, enum colors c = RED) : key(k), p(w), left(y)
		, right(z), color(c) {};

	~rbtnode() {
	};
};

// Arbol rojinegro:
template <typename T>
class rbtree {
public:
	rbtnode<T>* root;    // raiz del arbol
	rbtnode<T>* nil;     // nodo nil (hoja) del arbol

	rbtree() {
		// Constructor (crea un arbol vacio)
		this->nil = nullptr;
		this->root = nullptr;
	};

	~rbtree() {
		// Destructor (borra el arbol)
		this->DeleteAll(this->root);
	};

	void Insert(rbtnode<T>* z) {
		// Inserta el nodo z en la posicion que le corresponde en el arbol.
		rbtnode<T>* x = this->root;
		rbtnode<T>* y = this->nil;
		while (x != this->nil) {
			y = x;
			if (z->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		z->p = y;
		if (y == this->nil) {
			this->root = z;
		}
		else if (z->key < y->key) {
			y->left = z;
		}
		else if (z->key > y->key) {
			y->right = z;
		}
		z->left = this->nil;
		z->right = this->nil;
		z->color = RED;
		InsertFixup(z);
	};

	void InorderWalk(rbtnode<T>* x) {
		// Recorre en orden el subarbol con raiz x, imprimiendo la llave de cada nodo en en una nueva linea de la salida estandar despues de recorrido el subarbol izquierdo y antes de recorrer el subarbol derecho.
		if (x) {
			this->InorderWalk(x->left);
			std::cout << x->key << " : " << x->color << std::endl;
			this->InorderWalk(x->right);
		}
	};

	rbtnode<T>* Search(rbtnode<T>* x, const T& k) {
		// Busca la llave k recursivamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve el nodo nil.
		if (x == this->nil || x->key == k) { return x; }
		if (k < x->key) { return this->Search(x->left, k); }
		else { return this->Search(x->right, k); }
	};

	rbtnode<T>* IterativeSearch(rbtnode<T>* x, const T& k) {
		// Busca la llave k iterativamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve el nodo nil.
		while (x != this->nil && x->key != k) {
			if (x->key < k) { x = x->right; }
			else { x = x->left; }
		}
		return x;
	};

	rbtnode<T>* Minimum(rbtnode<T>* x) {
		// Devuelve el nodo que tiene la llave menor. Si el arbol esta vacio, devuelve el nodo nil.
		while (x->left != this->nil) { x = x->left; }
		return x;
	};

	rbtnode<T>* Maximum(rbtnode<T>* x) {
		// Devuelve el nodo que tiene la llave mayor. Si el arbol esta vacio devuelve el nodo nil.
		while (x->right != this->nil) { x = x->right; }
		return x;
	};

	rbtnode<T>* Successor(rbtnode<T>* x) {
		// Devuelve el nodo cuya llave es la que le sigue a la del nodo x. Si no existe el nodo, devuelve el nodo nil.
		if (x->right != this->nil) {
			this->Minimum(x->right);
		}
		else {
			rbtnode<T>* y = x->p;
			while (y != this->nil && x == y->right) {
				x = y;
				y = y->p;
			}
			return y;
		}
	};

private:
	void LeftRotate(rbtnode<T>* x) {
		rbtnode<T>* y = x->right;
		x->right = y->left;
		if (y->left != this->nil) {
			y->left->p = x;
		}
		y->p = x->p;
		if (x->p == this->nil) {
			this->root = y;
		}
		else if (x == x->p->left) {
			x->p->left = y;
		}
		else {
			x->p->right = y;
		}
		y->left = x;
		x->p = y;
	}

	void RightRotate(rbtnode<T>* x) {
		rbtnode<T>* y = x->left;
		x->left = y->right;
		if (y->right != this->nil) {
			y->right->p = x;
		}
		y->p = x->p;
		if (x->p == this->nil) {
			this->root = y;
		}
		else if (x == x->p->right) {
			x->p->right = y;
		}
		else {
			x->p->left = y;
		}
		y->right = x;
		x->p = y;
	}

	void InsertFixup(rbtnode<T>* z) {
		while (z->p && z->p->color == RED) {
			if (z->p == z->p->p->left) {
				rbtnode<T>* y = z->p->p->right;
				if (y && y->color == RED) {
					z->p->color = BLACK;
					y->color = BLACK;
					z->p->p->color = RED;
					z = z->p->p;
				}
				else {
					if (z == z->p->right) {
						z = z->p;
						this->LeftRotate(z);
					}
					z->p->color = BLACK;
					z->p->p->color = RED;
					this->RightRotate(z->p->p);
				}
			}
			else {
				rbtnode<T>* y = z->p->p->left;
				if (y && y->color == RED) {
					z->p->color = BLACK;
					y->color = BLACK;
					z->p->p->color = RED;
					z = z->p->p;
				}
				else {
					if (z == z->p->left) {
						z = z->p;
						this->RightRotate(z);
					}
					z->p->color = BLACK;
					z->p->p->color = RED;
					this->LeftRotate(z->p->p);
				}
			}
		}
		this->root->color = BLACK;
	}

	void Transplant(rbtnode<T>* u, rbtnode<T>* v) {
		if (!u->p) { this->root = v; }
		else if (u == u->p->left) { u->p->left = v; }
		else { u->p->right = v; }
		if (v) { v->p = u->p; }
	}

	void DeleteAll(rbtnode<T>* x) {
		if (x) {
			this->DeleteAll(x->left);
			this->Delete(x);
			this->DeleteAll(x->right);
		}
	};

	void Delete(rbtnode<T>* z) {
		// Saca del arbol la llave contenida en el nodo apuntado por z.
		if (!z->left) {
			this->Transplant(z, z->right);
		}
		else if (!z->right) {
			this->Transplant(z, z->left);
		}
		else {
			rbtnode<T>* y = this->Minimum(z->right);
			if (y && z->right && y->key != z->right->key) {
				this->Transplant(y, y->right);
				y->right = z->right;
				y->right->p = y;
			}
			this->Transplant(z, y);
			y->left = z->left;
			y->left->p = y;
		}
	};
};

#endif /* rbtree_h */
