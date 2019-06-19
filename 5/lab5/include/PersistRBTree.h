#ifndef PERSISTRBTREE_H
#define PERSISTRBTREE_H

#include "Node.h"
#include <vector>

template <typename Tkey, typename Tdata>
class PersistRBTree
{
	public:
		PersistRBTree();
		virtual ~PersistRBTree();

		void insert(Tkey key, Tdata* data);
		void remove(Tkey key);

		Tdata* find(Tkey key);
		Tdata* find(Tkey key, int version);
		Node<Tkey, Tdata>* find_(Tkey key, int version);
		Node<Tkey, Tdata>* findMax(Node<Tkey, Tdata>* node);
		Node<Tkey, Tdata>* grandparent(Node<Tkey, Tdata> *n);
		Node<Tkey, Tdata>* uncle(Node<Tkey, Tdata> *n);
		Node<Tkey, Tdata>* sibling(Node<Tkey, Tdata> *n);
		bool isLeaf(Node<Tkey, Tdata> *n);

        void print();
        void print(int version);
        void print(Node<Tkey, Tdata>* node, int deep);
        void printTab(int k);

	private:
		Node<Tkey, Tdata>* root = nullptr;
		std::vector<Node<Tkey, Tdata>*> versions;

		void rotateLeft(Node<Tkey, Tdata> *n);
		void rotateRight(Node<Tkey, Tdata> *n);
		void insert(Node<Tkey, Tdata> *n);
		void insert(Node<Tkey, Tdata>* parent, Node<Tkey, Tdata>* node);
		void replaceNode(Node<Tkey, Tdata>* n, Node<Tkey, Tdata>* child);
		void makeVersion(Node<Tkey, Tdata>* root, Node<Tkey, Tdata>* node);
};

#endif // PERSISTRBTREE_H
