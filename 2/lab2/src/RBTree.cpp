#include "RBTree.h"

#include <iostream>
#include <cmath>

template <typename Tkey, typename Tdata>
RBTree<Tkey, Tdata>::RBTree()
{
	//ctor
}

template <typename Tkey, typename Tdata>
RBTree<Tkey, Tdata>::~RBTree()
{
	//dtor
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* RBTree<Tkey, Tdata>::find_(Tkey key){

	if (!root) return nullptr;
	Node<Tkey, Tdata>* p = root;

	while (!isLeaf(p) && p->key != key) {

		if (p->key > key) p = p->left;
		else p = p->right;
	}

	if (isLeaf(p)) return nullptr;
	return p;
}

template <typename Tkey, typename Tdata>
Tdata* RBTree<Tkey, Tdata>::find(Tkey key){

	Node<Tkey, Tdata>* p = find_(key);
	if (!p) return nullptr;
	return p->data;
}


template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* RBTree<Tkey, Tdata>::findByRank(Node<Tkey, Tdata>* node, int rank){

	int r = node->left->size+1;

	if (rank == r) return node;
	if (rank < r) return findByRank(node->left, rank);
	return findByRank(node->right, rank-r);
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* RBTree<Tkey, Tdata>::findByRank(int rank){
	return findByRank(root, rank);
}

template <typename Tkey, typename Tdata>
int RBTree<Tkey, Tdata>::getSize(){
	if (!root) return 0;
	return root->size;
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::print(Node<Tkey, Tdata>* node, int deep){

	if (isLeaf(node)) {

		printTab(deep);
		std::cout << "NIL\n";
		return;
	}

	print(node->left, deep+1);

	printTab(deep);
	std::cout << (node->color == BLACK ? "B " : "R ")
			  << "["  << node->size << "] "
			  << node->data->surname
			  << "(" << node->data->mean << ")\n";

	print(node->right, deep+1);
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::print(){
	print(root, 0);
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::printTab(int k){
	for (int i = 0; i < k; i++)
		std::cout << "        ";
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::insert(Tkey key, Tdata* student){

	if (!root) {

		Node<Tkey, Tdata>* node = new Node<Tkey, Tdata>(nullptr);
		node->data = student;
		node->key = key;
		node->size = 1;

		node->left = new Node<Tkey, Tdata>(node);
		node->right = new Node<Tkey, Tdata>(node);

		root = node;
		return;
	}

	Node<Tkey, Tdata>* p = root;

	while (!isLeaf(p)){

		p->size++;

		if (p->key > key) p = p->left;
		else p = p->right;
	}

	Node<Tkey, Tdata>* node = new Node<Tkey, Tdata>(p->parent);
	node->color = RED;
	node->data = student;
	node->key = key;
	node->size = 1;

	if (p->parent->left == p) p->parent->left = node;
	else p->parent->right = node;

	node->left = new Node<Tkey, Tdata>(node);
	node->right = new Node<Tkey, Tdata>(node);

	delete p;

	std::cout << "A " << isLeaf(root->left) << " " << isLeaf(root->right) << '\n';
	insert(node);
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* RBTree<Tkey, Tdata>::grandparent(Node<Tkey, Tdata> *n){

	if ((n != nullptr) && (n->parent != nullptr))
		return n->parent->parent;
	else
		return nullptr;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* RBTree<Tkey, Tdata>::uncle(Node<Tkey, Tdata>* n){

	Node<Tkey, Tdata> *g = grandparent(n);
	if (g == nullptr)
		return nullptr;
	if (n->parent == g->left)
		return (isLeaf(g->right) ? nullptr : g->right);
	else
		return (isLeaf(g->left) ? nullptr : g->left);
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* RBTree<Tkey, Tdata>::sibling(Node<Tkey, Tdata> *n){

	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

template <typename Tkey, typename Tdata>
bool RBTree<Tkey, Tdata>::isLeaf(Node<Tkey, Tdata> *n){
	return (n->data == nullptr);
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::replaceNode(Node<Tkey, Tdata>* n1, Node<Tkey, Tdata>* n2){

	if (root == n1) root = n2;
	Node<Tkey, Tdata>* p = n1->parent;

	if (p){
		if (p->left == n1) p->left = n2;
		else p->right = n2;
	}

	n2->parent = p;
	p->size = p->left->size + p->right->size + 1;
	//n2->left = n1->left;
	//n2->right = n1->right;

}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::rotateLeft(Node<Tkey, Tdata> *n){

	if (root == n) root = n->right;
    Node<Tkey, Tdata> *pivot = n->right;

    n->size -= pivot->right->size + 1;
    pivot->size += n->left->size + 1;

    pivot->parent = n->parent;
    if (n->parent != nullptr) {
        if (n->parent->left==n)
            n->parent->left = pivot;
        else
            n->parent->right = pivot;
    }

    n->right = pivot->left;
 //   if (!isLeaf(pivot->left) /*pivot->left != nullptr*/)
        pivot->left->parent = n;

    n->parent = pivot;
    pivot->left = n;

}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::rotateRight(Node<Tkey, Tdata> *n){

	if (root == n) root = n->left;
    Node<Tkey, Tdata> *pivot = n->left;

    n->size -= pivot->left->size + 1;
    pivot->size += n->right->size + 1;

    pivot->parent = n->parent;
    if (n->parent != nullptr) {
        if (n->parent->left==n)
            n->parent->left = pivot;
        else
            n->parent->right = pivot;
    }

    n->left = pivot->right;
//    if (!isLeaf(pivot->right) /*pivot->right != nullptr*/)
        pivot->right->parent = n;

    n->parent = pivot;
    pivot->right = n;
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::insert(Node<Tkey, Tdata> *n){

	if (n->parent == nullptr){
		n->color = BLACK;
		return;
	}

	if (n->parent->color == BLACK) return;

	Node<Tkey, Tdata> *u = uncle(n), *g;
	if ((u != nullptr) && (u->color == RED)) {

		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insert(g);
		return;
	}

	g = grandparent(n);

	if ((n == n->parent->right) && (n->parent == g->left)){

		rotateLeft(n->parent);
		n = n->left;
	} else if ((n == n->parent->left) && (n->parent == g->right)){

		rotateRight(n->parent);
		n = n->right;
	}

	g = grandparent(n);
	n->parent->color = BLACK;
	g->color = RED;
	if ((n == n->parent->left) && (n->parent == g->left)) {
		rotateRight(g);
	} else {
		rotateLeft(g);
	}
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* RBTree<Tkey, Tdata>::findMax(Node<Tkey, Tdata>* node){

	if (isLeaf(node->right)) return node;
	return findMax(node->right);
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::decreaseSize(Node<Tkey, Tdata>* node, Tkey key){
	Node<Tkey, Tdata>* p = root;

	while (!isLeaf(p) && p->key != key) {

		p->size--;
		if (p->key > key) p = p->left;
		else p = p->right;
	}

	p->size = 0;
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::remove(Tkey key){
	Node<Tkey, Tdata>* node = find_(key);
	if (!node) return;

	if (!isLeaf(node->left)){

		Node<Tkey, Tdata>* nodeToReplace = findMax(node->left);
		decreaseSize(node, nodeToReplace->key);

		delete node->data;
		node->data = nodeToReplace->data;

		deleteChild(nodeToReplace);
		return;
	}
	decreaseSize(node, key);
	deleteChild(node);
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::deleteChild(Node<Tkey, Tdata> *n){

	Node<Tkey, Tdata> *child = (isLeaf(n->right) ? n->left : n->right);

	replaceNode(n, child);
	if (n->color == BLACK) {
		if (child->color == RED)
			child->color = BLACK;
		else
			remove(child);
	}

	delete n;
}

template <typename Tkey, typename Tdata>
void RBTree<Tkey, Tdata>::remove(Node<Tkey, Tdata>* n){

	if (n->parent == nullptr) return;

	Node<Tkey, Tdata> *s = sibling(n);
	if (s->color == RED) {
		n->parent->color = RED;
		s->color = BLACK;
		if (n == n->parent->left)
			rotateLeft(n->parent);
		else
			rotateRight(n->parent);
	}

	s = sibling(n);
	if ((n->parent->color == BLACK) &&
	    (s->color == BLACK) &&
	    (s->left->color == BLACK) &&
	    (s->right->color == BLACK)) {

			s->color = RED;
			remove(n->parent);
			return;
		}

	s = sibling(n);
	if ((n->parent->color == RED) &&
	    (s->color == BLACK) &&
	    (s->left->color == BLACK) &&
	    (s->right->color == BLACK)) {

			s->color = RED;
			n->parent->color = BLACK;
			return;
		}

	s = sibling(n);
	if  (s->color == BLACK) {
		if ((n == n->parent->left) &&
		    (s->right->color == BLACK) &&
		    (s->left->color == RED)) {
				s->color = RED;
				s->left->color = BLACK;
				rotateRight(s);
			}
		else if ((n == n->parent->right) &&
		           (s->left->color == BLACK) &&
		           (s->right->color == RED)) {
						s->color = RED;
						s->right->color = BLACK;
						rotateLeft(s);
				}
	}

	s = sibling(n);
	s->color = n->parent->color;
    n->parent->color = BLACK;

	if (n == n->parent->left) {
        s->right->color = BLACK;
		rotateLeft(n->parent);
	} else {
		s->left->color = BLACK;
		rotateRight(n->parent);
	}
}

template class RBTree<std::string, Student>;
