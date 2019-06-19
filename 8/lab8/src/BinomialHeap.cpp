#include "BinomialHeap.h"

#include <iostream>

template <typename Tkey, typename Tdata>
BinomialHeap<Tkey, Tdata>::BinomialHeap()
{
	//ctor
}

template <typename Tkey, typename Tdata>
BinomialHeap<Tkey, Tdata>::BinomialHeap(Node<Tkey, Tdata>* node){
	head = node;
	node->next = nullptr;
	node->prev = nullptr;
	node->parent = nullptr;
	node->child = nullptr;
}

template <typename Tkey, typename Tdata>
BinomialHeap<Tkey, Tdata>::~BinomialHeap()
{
	//dtor
}

template <typename Tkey, typename Tdata>
BinomialHeap<Tkey, Tdata>* BinomialHeap<Tkey, Tdata>::merge
	(BinomialHeap<Tkey, Tdata>* heap1, BinomialHeap<Tkey, Tdata>* heap2){

	Node<Tkey, Tdata> *root1 = heap1->head,
					  *root2 = heap2->head;
	BinomialHeap<Tkey, Tdata>* res = new BinomialHeap();
	if (!root1){
		res->head = root2;
		return res;
	}
	if (!root2){
		res->head = root1;
		return res;
	}

	Node<Tkey, Tdata>* lastNode = nullptr;

	while (root1 && root2){

		if (root1->degree < root2->degree) {

			if (!lastNode) {
				res->head = root1;
			}
			else{
				lastNode->next = root1;
			}
			root1->prev = lastNode;
			lastNode = root1;
			root1 = root1->next;
		}
		else {

			if (!lastNode) {
				res->head = root2;
			}
			else{
				lastNode->next = root2;
			}
			root2->prev = lastNode;
			lastNode = root2;
			root2 = root2->next;
		}
	}

	while (root1){
		lastNode->next = root1;
		root1->prev = lastNode;
		lastNode = root1;
		root1 = root1->next;
	}

	while (root2){
		lastNode->next = root2;
		root2->prev = lastNode;
		lastNode = root2;
		root2 = root2->next;
	}

	return res;
}

template <typename Tkey, typename Tdata>
void BinomialHeap<Tkey, Tdata>::binomLink(Node<Tkey, Tdata>* y, Node<Tkey, Tdata>* z){

	y->parent = z;
	y->next = z->child;
	y->prev = nullptr;
	if (z->child) z->child->prev = y;
	z->child = y;
	z->degree++;
}

template <typename Tkey, typename Tdata>
BinomialHeap<Tkey, Tdata>* BinomialHeap<Tkey, Tdata>::union_
	(BinomialHeap<Tkey, Tdata>* heap1, BinomialHeap<Tkey, Tdata>* heap2){

	BinomialHeap<Tkey, Tdata>* res = merge(heap1, heap2);
//	std::cout << "After MERGE:\n";
//	printHeap(res);

	Node<Tkey, Tdata>  *x = res->head,
					   *x_prev = nullptr,
					   *x_next = x->next;

	while (x_next){

		if (x->degree != x_next->degree || (x_next->next && x_next->next->degree == x->degree)){
				x_prev = x;
				x = x_next;
		}
		else{
			if (x->key <= x_next->key){
				x->next = x_next->next;
				if (x_next->next) x_next->next->prev = x; //**
				binomLink(x_next, x);
			}
			else{
				if (!x_prev) res->head = x_next;
				else x_prev->next = x->next;
				x_next->prev = x->prev;	//**
				binomLink(x, x_next);
				x = x_next;
			}
		}
		x_next = x->next;
	}

//	std::cout << "After UNION:\n";
//	printHeap(res);
	return res;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* BinomialHeap<Tkey, Tdata>::findMinNode(){

	if (!head) return nullptr;
	Node<Tkey, Tdata>  *x = head->next,
					   *res = head;
	while (x){

		if (x->key < res->key) res = x;
		x = x->next;
	}
	return res;
}

template <typename Tkey, typename Tdata>
Tdata* BinomialHeap<Tkey, Tdata>::findMin(){

	Node<Tkey, Tdata>* minNode = findMinNode();
	if (!minNode) return nullptr;
	return minNode->data;
}

template <typename Tkey, typename Tdata>
void BinomialHeap<Tkey, Tdata>::insert(Tkey key, Tdata* data){

	Node<Tkey, Tdata>* newNode = new Node<Tkey, Tdata>(key, data);
	BinomialHeap<Tkey, Tdata>* newBinHeap = new BinomialHeap(newNode);

	head = union_(this, newBinHeap)->head;
}

template <typename Tkey, typename Tdata>
Tdata* BinomialHeap<Tkey, Tdata>::extractMin(){

	auto nodeToDelete = findMinNode();
	if (nodeToDelete == head){
		head = nodeToDelete->next;
		if (head) head->prev = nullptr;
	}
	else{
		nodeToDelete->prev->next = nodeToDelete->next;
		if (nodeToDelete->next) nodeToDelete->next->prev = nodeToDelete->prev;
	}

	auto child = nodeToDelete->child;
	auto data = nodeToDelete->data;
	delete nodeToDelete;

	if (!child) return data;

	BinomialHeap<Tkey, Tdata>* heap = new BinomialHeap();

//	std::cout << "Children in straight order:\n";
	while (child->next){
//		child->data->print();
		child = child->next;
	}
	child->data->print();

	Node<Tkey, Tdata>* lastNode = nullptr;
//	std::cout << "Children:\n";
	while (child){

//		child->data->print();
		auto nextChild = child->prev;
		child->parent = nullptr;
		child->next = nullptr;

		if (!lastNode){
			heap->head = child;
		}
		else{
			lastNode->next = child;
		}
		child->prev = lastNode;
		lastNode = child;
		child = nextChild;
	}
//	std::cout << "Heap of children:\n";
//	printHeap(heap);
	head = union_(this, heap)->head;
	return data;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* BinomialHeap<Tkey, Tdata>::findNodeByKey(Node<Tkey, Tdata>* node, Tkey key){
	if (!node) return nullptr;

	if (node->key == key) return node;
	if (node->key < key) {
		auto res = findNodeByKey(node->child, key);
		if (res) return res;
	}
	return findNodeByKey(node->next, key);
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* BinomialHeap<Tkey, Tdata>::findNodeByKey(Tkey key){
	return findNodeByKey(head, key);
}

template <typename Tkey, typename Tdata>
Tdata* BinomialHeap<Tkey, Tdata>::findByKey(Tkey key){
	auto node = findNodeByKey(key);
	if (!node) return nullptr;
	return node->data;
}

template <typename Tkey, typename Tdata>
void BinomialHeap<Tkey, Tdata>::decreaseKey(Node<Tkey, Tdata>* node, Tkey newKey){
	node->key = newKey;
	node->data->surname = newKey;
	while (node->parent && node->key < node->parent->key){
		std::swap(node->data, node->parent->data);
		std::swap(node->key, node->parent->key);
		node = node->parent;
	}
}

template <typename Tkey, typename Tdata>
bool BinomialHeap<Tkey, Tdata>::decreaseKey(Tkey key, Tkey newKey){
	if (newKey > key) return false;

	auto node = findNodeByKey(key);
	if (!node) return false;

	decreaseKey(node, newKey);
	return true;
}

template <typename Tkey, typename Tdata>
void BinomialHeap<Tkey, Tdata>::remove(Node<Tkey, Tdata>* node){
	decreaseKey(node, MIN_KEY);
	extractMin();
}

template <typename Tkey, typename Tdata>
bool BinomialHeap<Tkey, Tdata>::remove(Tkey key){
	auto node = findNodeByKey(key);
	if (!node) return false;

	remove(node);
	return true;
}

template <typename Tkey, typename Tdata>
void BinomialHeap<Tkey, Tdata>::printNode(Node<Tkey, Tdata>* node, int deep){

	if (!node) return;

	if (deep > 0) std::cout << '|';
	printTab(deep);
	std::cout << ">" << node->data->surname << "(" << node->data->mean << ")\n";

	printNode(node->child, deep+1);
	if (deep > 0) printNode(node->next, deep);
}

template <typename Tkey, typename Tdata>
void BinomialHeap<Tkey, Tdata>::print(){
	printHeap(this);
}

template <typename Tkey, typename Tdata>
void BinomialHeap<Tkey, Tdata>::printTab(int k){
	for (int i = 0; i < k; i++)
		std::cout << "        ";
}

template <typename Tkey, typename Tdata>
void BinomialHeap<Tkey, Tdata>::printHeap(BinomialHeap<Tkey, Tdata>* heap){
	std::cout << "--------------------------------------------------------------------\n";
	auto curNode = heap->head;
	while (curNode){

		if (curNode != heap->head)
			for(int i = 0; i < 3; i++)
				std::cout << "|\n";

		printNode(curNode, 0);
		curNode = curNode->next;
	}
	std::cout << "--------------------------------------------------------------------\n";
}

template class BinomialHeap<std::string, Student>;
