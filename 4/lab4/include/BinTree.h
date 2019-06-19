#ifndef BINTREE_H
#define BINTREE_H

#include "Node.h"

template <typename Tdata, Tkey>
class BinTree
{
	public:
		BinTree();
		virtual ~BinTree();

		void insert(const Tkey& key, Tdata* data);
		void remove(const Tkey& key);
		Tdata* find(const Tkey& key);

        void print();
        void print(Node<Tkey, Tdata>* node, int deep);
        void printTab(int k);

	private:

		Node<Tkey, Tdata>* root = nullptr;

		Node<Tkey, Tdata>* find_(const Tkey& key);
		Node<Tkey, Tdata>* successor(Node<Tkey, Tdata>* node);
		Node<Tkey, Tdata>* predecessor(Node<Tkey, Tdata>* node);
		void replace(Node<Tkey, Tdata>* localParent, Node<Tkey, Tdata>* localChild);
		Node<Tkey, Tdata>* minimum(Node<Tkey, Tdata>* node);
		Node<Tkey, Tdata>* maximum(Node<Tkey, Tdata>* node);
		void leftRotate(Node<Tkey, Tdata>* n);
		void rightRotate(Node<Tkey, Tdata>* n);
		void splay(Node<Tkey, Tdata>* node);
};

#endif // BINTREE_H
