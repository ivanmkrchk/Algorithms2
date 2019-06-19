#include "FibHeap.h"

#include <vector>
#include <iostream>

template <typename Tkey, typename Tdata>
FibHeap<Tkey, Tdata>::FibHeap(){
	size = 0;
}

template <typename Tkey, typename Tdata>
FibHeap<Tkey, Tdata>::~FibHeap(){
	//dtor
}


template <typename Tkey, typename Tdata>
FibHeap<Tkey, Tdata>::FibHeap(Tkey key, Tdata* cost){
	size = 0;
	root = new Node<Tkey, Tdata>(key, cost);
}

template <typename Tkey, typename Tdata>
void FibHeap<Tkey, Tdata>::unionLists(Node<Tkey, Tdata>* first, Node<Tkey, Tdata>* second){

	if (!first || !second) return;

	Node<Tkey, Tdata> *left = first->left,
					  *right = second->right;

	second->right = first;
	first->left = second;

	left->right = right;
	right->left = left;
}

template <typename Tkey, typename Tdata>
void FibHeap<Tkey, Tdata>::merge(FibHeap<Tkey, Tdata>* heap){

	if (heap->size == 0) return;

	if (size == 0){

		root = heap->root;
		size = heap->size;
	}
	else{

		unionLists(root, heap->root);
		size += heap->size;

		if (heap->root->key < root->key)
			root = heap->root;
	}
}

template <typename Tkey, typename Tdata>
void FibHeap<Tkey, Tdata>::insert(Tkey key, Tdata* cost){

	Node<Tkey, Tdata>* newNode = new Node<Tkey, Tdata>(key, cost);

	if (size == 0){

		root = newNode;
		root->left = newNode;
		root->right = newNode;
	}
	else{

		root->right->left = newNode;
		newNode->right = root->right;
		root->right = newNode;
		newNode->left = root;
	}

	if (newNode->key < root->key) root = newNode;
	size++;
}

template <typename Tkey, typename Tdata>
void FibHeap<Tkey, Tdata>::consolidate(){

	std::vector<Node<Tkey, Tdata>* > roots(size);
	roots[root->degree] = root;

	Node<Tkey, Tdata>* node = root->right;
	while (roots[node->degree] != node){

		if (!roots[node->degree] || roots[node->degree]->degree != node->degree || roots[node->degree]->parent){

			roots[node->degree] = node;
			node = node->right;
		}
		else{

			Node<Tkey, Tdata>* conflict = roots[node->degree];
			Node<Tkey, Tdata> *addTo,
							  *adding;
			if (conflict->key < node->key){
				addTo = conflict;
				adding = node;
			}
			else{
				addTo = node;
				adding = conflict;
			}

			adding->left->right = adding->right;
			adding->right->left = adding->left;

			adding->parent = addTo;
			if (!addTo->child){
				addTo->child = adding;
				adding->left = adding;
				adding->right = adding;
			}
			else{
				adding->right = addTo->child->right;
				adding->left = addTo->child;
				addTo->child->right->left = adding;
				addTo->child->right = adding;
			}
			addTo->degree++;
			node = addTo;
		}

		if (root->key > node->key) root = node;
	}
}

template <typename Tkey, typename Tdata>
void FibHeap<Tkey, Tdata>::print(int deep, Node<Tkey, Tdata>* node, Node<Tkey, Tdata>* begin){

	for (int i = 0; i < deep; i++)
		std::cout << '\t';

	std::cout << node->key << ' ' << node->degree << '\n';

	if (node->child) print(deep + 1, node->child, node->child->left);

	if (node != begin) print(deep, node->right, begin);
}

template <typename Tkey, typename Tdata>
Tdata* FibHeap<Tkey, Tdata>::getMinimum()
{
	if (size == 0) return nullptr;
	return root->cost;
}

template <typename Tkey, typename Tdata>
Tdata* FibHeap<Tkey, Tdata>::extractMinimum(){

	if (size == 0) return nullptr;

	Node<Tkey, Tdata>* previousMin = root;

	unionLists(root, root->child);

	root->left->right = root->right;
	root->right->left = root->left;

	if (previousMin->right == previousMin)
	{
		root = nullptr;
		size--;
		return previousMin->cost;
	}

	root = root->right;

	consolidate();

	size--;
	return previousMin->cost;
}

template <typename Tkey, typename Tdata>
void FibHeap<Tkey, Tdata>::print(){

	if (size > 0) print(0, root, root->left);
	else std::cout << "Heap is empty\n";
}

template class FibHeap<std::string, Student>;
