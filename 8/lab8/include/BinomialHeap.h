#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include "Node.h"

template <typename Tkey, typename Tdata>
class BinomialHeap
{
	public:
		BinomialHeap();
		BinomialHeap(Node<Tkey, Tdata>* node);
		virtual ~BinomialHeap();

		static BinomialHeap<Tkey, Tdata>* union_(BinomialHeap<Tkey, Tdata>* heap1, BinomialHeap<Tkey, Tdata>* heap2);
		static BinomialHeap<Tkey, Tdata>* merge(BinomialHeap<Tkey, Tdata>* heap1, BinomialHeap<Tkey, Tdata>* heap2);
		void insert(Tkey key, Tdata* data);
		Tdata* findByKey(Tkey key);
		Tdata* findMin();
		Tdata* extractMin();
		bool remove(Tkey key);
		bool decreaseKey(Tkey key, Tkey newKey);
		void print();
		static void printHeap(BinomialHeap<Tkey, Tdata>* heap);

	private:
		Node <Tkey, Tdata>* head = nullptr;
		const Tkey MIN_KEY = "";

		static void binomLink(Node<Tkey, Tdata>* y, Node<Tkey, Tdata>* z);
		Node<Tkey, Tdata>* findMinNode();
		Node<Tkey, Tdata>* findNodeByKey(Tkey key);
		void remove(Node<Tkey, Tdata>* node);
		static Node<Tkey, Tdata>* findNodeByKey(Node<Tkey, Tdata>* node, Tkey key);
		static void decreaseKey(Node<Tkey, Tdata>* node, Tkey newKey);
		static void printNode(Node<Tkey, Tdata>* node, int deep);
		static void printTab(int k);
};

#endif // BINOMIALHEAP_H
