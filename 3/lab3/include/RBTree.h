#ifndef RBTREE_H
#define RBTREE_H

#include "Node.h"

#include <vector>
#include <fstream>

class RBTree
{
	public:
		RBTree();
		virtual ~RBTree();

		void insert_(Student* student);
		void delete_(double mean);

		Node* find(double mean);
		Node* findMax(Node* node);
		Node* findByRank(Node* node, int rank);
		Node* findByRank(int rank);
		Node* grandparent(Node *n);
		Node* uncle(Node *n);
		Node* sibling(Node *n);
		bool isLeaf(Node *n);

        void loadData(std::istream& in);
        void printData();
        void print();
        void print(Node* node, int deep);
        void printTab(int k);
		void addElements(int l, int r);
		int getSize();

	private:
		Node* root = nullptr;
		int size = 0;

		void rotateLeft(Node *n);
		void rotateRight(Node *n);
		void insert_(Node *n);
		void delete_(Node *n);
		void deleteChild(Node *n);
		void replaceNode(Node* n, Node* child);
		void decreaseSize(Node* node, double mean);

	public:
		std::vector <Student*> data;
};

#endif // RBTREE_H
