#ifndef FIBHEAP_H
#define FIBHEAP_H

#include "Node.h"

template <typename Tkey, typename Tdata>
class FibHeap{

	public:
		FibHeap();
		FibHeap(Tkey key, Tdata* cost);
		virtual ~FibHeap();

		void insert(Tkey key, Tdata* cost);
		Tdata* getMinimum();
		Tdata* extractMinimum();
		void print();

	private:
		int size;
		Node<Tkey, Tdata>* root;

		void unionLists(Node<Tkey, Tdata>* first, Node<Tkey, Tdata>* second);
		void merge(FibHeap* heap);
		void consolidate();
		void print(int deep, Node<Tkey, Tdata>* node, Node<Tkey, Tdata>* begin);
};

#endif // FIBHEAP_H
