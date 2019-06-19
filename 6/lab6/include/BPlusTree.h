#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "Node.h"

template <typename Tkey, typename Tdata>
class BPlusTree
{
	public:
		BPlusTree();
		virtual ~BPlusTree();

		void insert(Tkey key, Tdata* cost);
		Tdata* find(Tkey key);
		void print();

	private:
		int dimension;
		Node<Tkey, Tdata>* root = nullptr;

		Node<Tkey, Tdata>* getLeaf(Tkey key);
		void split(Node<Tkey, Tdata>* node);
		void print(int deep, Node<Tkey, Tdata>* node);
};

#endif // BPLUSTREE_H
