#ifndef RBTREE_H
#define RBTREE_H

#include "Node.h"

#include <vector>
#include <fstream>

template <typename Tkey, typename Tdata>
class RBTree
{
	public:
		RBTree();
		virtual ~RBTree();

		void insert(Tkey key, Tdata* student);
		void remove(Tkey key);

		Tdata* find(Tkey key);
		Node<Tkey, Tdata>* find_(Tkey key);
		Node<Tkey, Tdata>* findMax(Node<Tkey, Tdata>* node);
		Node<Tkey, Tdata>* findByRank(Node<Tkey, Tdata>* node, int rank);
		Node<Tkey, Tdata>* findByRank(int rank);
		Node<Tkey, Tdata>* grandparent(Node<Tkey, Tdata> *n);
		Node<Tkey, Tdata>* uncle(Node<Tkey, Tdata> *n);
		Node<Tkey, Tdata>* sibling(Node<Tkey, Tdata> *n);
		bool isLeaf(Node<Tkey, Tdata> *n);

        void loadData(std::istream& in);
        void printData();
        void print();
        void print(Node<Tkey, Tdata>* node, int deep);
        void printTab(int k);
		void addElements(int l, int r);
		int getSize();

	private:
		Node<Tkey, Tdata>* root = nullptr;
		int size = 0;

		void rotateLeft(Node<Tkey, Tdata> *n);
		void rotateRight(Node<Tkey, Tdata> *n);
		void insert(Node<Tkey, Tdata> *n);
		void remove(Node<Tkey, Tdata> *n);
		void deleteChild(Node<Tkey, Tdata> *n);
		void replaceNode(Node<Tkey, Tdata>* n, Node<Tkey, Tdata>* child);
		void decreaseSize(Node<Tkey, Tdata>* node, Tkey key);

	public:
	//	std::vector <Tdata*> data;
};

#endif // RBTREE_H
