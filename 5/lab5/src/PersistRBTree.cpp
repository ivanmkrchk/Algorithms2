#include "PersistRBTree.h"

#include <iostream>
#include <cmath>

template <typename Tkey, typename Tdata>
PersistRBTree<Tkey, Tdata>::PersistRBTree()
{
	//ctor
}

template <typename Tkey, typename Tdata>
PersistRBTree<Tkey, Tdata>::~PersistRBTree()
{
	//dtor
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* PersistRBTree<Tkey, Tdata>::find_(Tkey key, int version){

	root = versions[version];
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
Tdata* PersistRBTree<Tkey, Tdata>::find(Tkey key){

	return find(key, versions.size()-1);
}

template <typename Tkey, typename Tdata>
Tdata* PersistRBTree<Tkey, Tdata>::find(Tkey key, int version){

	if (version < 0 || version >= versions.size()) return nullptr;
	auto node = find_(key, version);

	if (!node) return nullptr;
	return node->data;
}

template <typename Tkey, typename Tdata>
void PersistRBTree<Tkey, Tdata>::print(Node<Tkey, Tdata>* node, int deep){

//	std::cout << "IN PRINT, node = " << node << "\n";
	if (isLeaf(node)) {

		printTab(deep);
		std::cout << "NIL\n";
		return;
	}

	print(node->left, deep+1);

	printTab(deep);
	std::cout << (node->color == BLACK ? "B " : "R ")
			  << node->data->surname
			  << "(" << node->data->mean << ")\n";

	print(node->right, deep+1);
}

template <typename Tkey, typename Tdata>
void PersistRBTree<Tkey, Tdata>::print(){
	print(versions.size()-1);
}

template <typename Tkey, typename Tdata>
void PersistRBTree<Tkey, Tdata>::print(int version){
	if (version < 0 || version >= versions.size()) std::cout << "Error. Check data\n";
	else{
		std::cout << "--------------------------------------------------------------------\n";
		print(versions[version], 0);
		std::cout << "--------------------------------------------------------------------\n";
	}
}

template <typename Tkey, typename Tdata>
void PersistRBTree<Tkey, Tdata>::printTab(int k){
	for (int i = 0; i < k; i++)
		std::cout << "        ";
}

template <typename Tkey, typename Tdata>
void PersistRBTree<Tkey, Tdata>::insert(Tkey key, Tdata* data){

	Node<Tkey, Tdata>* node = new Node<Tkey, Tdata>(key, data);
	node->color = RED;

	insert(root, node);
	node->left = new Node<Tkey, Tdata>(node);
	node->right = new Node<Tkey, Tdata>(node);

	if (!node->parent)
	{
		root = node;
		root->color = BLACK;
	}

	makeVersion(root, node);

	insert(node);

	versions.push_back(root);
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* PersistRBTree<Tkey, Tdata>::grandparent(Node<Tkey, Tdata> *n){

	if ((n != nullptr) && (n->parent != nullptr))
		return n->parent->parent;
	else
		return nullptr;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* PersistRBTree<Tkey, Tdata>::uncle(Node<Tkey, Tdata>* n){

	Node<Tkey, Tdata> *g = grandparent(n);
	if (g == nullptr)
		return nullptr;
	if (n->parent == g->left)
		return (isLeaf(g->right) ? nullptr : g->right);
	else
		return (isLeaf(g->left) ? nullptr : g->left);
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* PersistRBTree<Tkey, Tdata>::sibling(Node<Tkey, Tdata> *n){

	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

template <typename Tkey, typename Tdata>
bool PersistRBTree<Tkey, Tdata>::isLeaf(Node<Tkey, Tdata> *n){
	return (n->data == nullptr);
//	return n;
}

template <typename Tkey, typename Tdata>
void PersistRBTree<Tkey, Tdata>::replaceNode(Node<Tkey, Tdata>* n1, Node<Tkey, Tdata>* n2){

	if (root == n1) root = n2;
	Node<Tkey, Tdata>* p = n1->parent;

	if (p){
		if (p->left == n1) p->left = n2;
		else p->right = n2;
	}

	n2->parent = p;
	//n2->left = n1->left;
	//n2->right = n1->right;

}

template <typename Tkey, typename Tdata>
void PersistRBTree<Tkey, Tdata>::rotateLeft(Node<Tkey, Tdata> *n){

	if (root == n) root = n->right;
    Node<Tkey, Tdata> *pivot = n->right;

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
void PersistRBTree<Tkey, Tdata>::rotateRight(Node<Tkey, Tdata> *n){

	if (root == n) root = n->left;
    Node<Tkey, Tdata> *pivot = n->left;

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
void PersistRBTree<Tkey, Tdata>::insert(Node<Tkey, Tdata> *n){

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
Node<Tkey, Tdata>* PersistRBTree<Tkey, Tdata>::findMax(Node<Tkey, Tdata>* node){

	if (isLeaf(node->right)) return node;
	return findMax(node->right);
}

template <typename Tkey, typename Tdata>
void PersistRBTree<Tkey, Tdata>::insert(Node<Tkey, Tdata>* parent, Node<Tkey, Tdata>* node)
{
	if (!parent) return;
	while (!isLeaf(parent)){

		if (node->key >= parent->key){

			if (!isLeaf(parent->right)) parent = parent->right;
			else{

				node->parent = parent;
				delete parent->right;
				parent->right = node;
				return;
			}
		}
		else {
			if (!isLeaf(parent->left)) parent = parent->left;
			else{

				node->parent = parent;
				delete parent->left;
				parent->left = node;
				return;
			}
		}
	}
}

template <typename Tkey, typename Tdata>
void PersistRBTree<Tkey, Tdata>::makeVersion(Node<Tkey, Tdata>* root, Node<Tkey, Tdata>* node){

	if (node == root) return;

	Node<Tkey, Tdata>* parent = node->parent;

	Node<Tkey, Tdata>* newParent = new Node<Tkey, Tdata>();
	newParent->copy(parent);

	if (parent->left){
		parent->left->parent = newParent;
		newParent->left = parent->left;
	}

	if (parent->right){
		parent->right->parent = newParent;
		newParent->right = parent->right;
	}

	if (node == parent->left) parent->left = new Node<Tkey, Tdata>(parent);
	else if (node == parent->right) parent->right = new Node <Tkey, Tdata>(parent);

	while (parent != root){

		Node<Tkey, Tdata>* grandparent = parent->parent;
		Node<Tkey, Tdata>* newGrandparent = new Node<Tkey, Tdata>();
		newGrandparent->copy(grandparent);

		if (grandparent->left == parent){

			newGrandparent->left = newParent;

			if (grandparent->right){
				newGrandparent->right = grandparent->right;
				newGrandparent->right->parent = newGrandparent;
			}
		}
		else{

			newGrandparent->right = newParent;

			if (grandparent->left){
				newGrandparent->left = grandparent->left;
				newGrandparent->left->parent = newGrandparent;
			}
		}
		newParent->parent = newGrandparent;

		parent = parent->parent;
		newParent = newParent->parent;
	}

	this->root = newParent;
}


template class PersistRBTree<std::string, Student>;
