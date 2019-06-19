#include "BPlusTree.h"
#include "Student.h"

#include <iostream>

template <typename Tkey, typename Tdata>
BPlusTree<Tkey, Tdata>::BPlusTree(){

	dimension = 2;
}

template <typename Tkey, typename Tdata>
BPlusTree<Tkey, Tdata>::~BPlusTree()
{
	//dtor
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* BPlusTree<Tkey, Tdata>::getLeaf(Tkey key){

	Node<Tkey, Tdata>* node = root;

	while (!node->leaf){
		for (int i = 0; i <= node->keyNumber; i++){
			if (i == node->keyNumber || key < node->key[i]){
				node = node->child[i];
				break;
			}
		}
	}

	return node;
}

template <typename Tkey, typename Tdata>
void BPlusTree<Tkey, Tdata>::split(Node<Tkey, Tdata>* node){

	Node<Tkey, Tdata>* newNode = new Node<Tkey, Tdata>(dimension);

	if (node->right){
		newNode->right = node->right;
		node->right->left = newNode;
	}

	node->right = newNode;
	newNode->left = node;


	Tkey middleKey = node->key[dimension];
	newNode->keyNumber = dimension - 1;
	node->keyNumber = dimension;

	for (int i = 0; i <= newNode->keyNumber - 1; i++){

		newNode->key[i] = node->key[i + dimension + 1];
		newNode->cost[i] = node->cost[i + dimension + 1];
		newNode->child[i] = node->child[i + dimension + 1];
		if (newNode->child[i]){
			newNode->child[i]->parent = newNode;
		}
	}

	newNode->child[newNode->keyNumber] = node->child[2 * dimension];
	if (newNode->child[newNode->keyNumber]){
		newNode->child[newNode->keyNumber]->parent = newNode;
	}

	if (node->leaf){

		newNode->keyNumber++;
		newNode->leaf = true;

		for (int i = newNode->keyNumber - 1; i > 0; i--){
			newNode->key[i] = newNode->key[i - 1];
			newNode->cost[i] = newNode->cost[i - 1];
		}
		newNode->key[0] = node->key[dimension];
		newNode->cost[0] = node->cost[dimension];
	}

	if (node == root){

		root = new Node<Tkey, Tdata>(dimension);
		root->key[0] = middleKey;
		root->child[0] = node;
		root->child[1] = newNode;
		root->keyNumber = 1;
		node->parent = root;
		newNode->parent = root;
	}
	else{
		newNode->parent = node->parent;
		Node<Tkey, Tdata>* parent = node->parent;

		int position = 0;

		while (position < parent->keyNumber && parent->key[position] < middleKey){
			position++;
		}

		for (int i = parent->keyNumber; i > position; i--){
			parent->key[i] = parent->key[i - 1];
		}
		for (int i = parent->keyNumber + 1; i > position + 1; i--){
			parent->child[i] = parent->child[i - 1];
		}

		parent->key[position] = middleKey;
		parent->child[position + 1] = newNode;

		parent->keyNumber++;

		if (parent->keyNumber == 2 * dimension){
			split(parent);
		}
	}
}

template <typename Tkey, typename Tdata>
void BPlusTree<Tkey, Tdata>::insert(Tkey key, Tdata* cost){

	if (!root){
		root = new Node<Tkey, Tdata>(dimension);
		root->leaf = true;
	}
	Node<Tkey, Tdata>* leaf = getLeaf(key);

	int position = 0;

	while (position < leaf->keyNumber && leaf->key[position] < key){
		position++;
	}

	for (int i = leaf->keyNumber; i > position; i--){
		leaf->key[i] = leaf->key[i - 1];
		leaf->cost[i] = leaf->cost[i - 1];
	}

	leaf->key[position] = key;
	leaf->cost[position] = cost;

	leaf->keyNumber++;

	if (leaf->keyNumber == 2 * dimension) split(leaf);
}

template <typename Tkey, typename Tdata>
void BPlusTree<Tkey, Tdata>::print(int deep, Node<Tkey, Tdata>* node){

	for (int i = 0; i < deep; i++)
		std::cout << '\t';

	std::cout << "{ ";
	for (int i = 0; i < node->keyNumber; i++)
		std::cout << node->key[i] << ' ';

	std::cout << "}\n";

	bool needMargin = false;
	for (int i = 0; i <= node->keyNumber; ++i){
		if (node->child[i]){
			print(deep + 1, node->child[i]);
			needMargin = true;
		}
	}
	if (needMargin) std::cout << '\n';
}

template <typename Tkey, typename Tdata>
Tdata* BPlusTree<Tkey, Tdata>::find(Tkey key){

	Node<Tkey, Tdata>* node = getLeaf(key);

	int oldI = 0;
	for (int i = 0; i < node->keyNumber && node->key[i] <= key; i++){
		if (key == node->key[i]){
			return node->cost[i];
		}
		oldI = i;
	}

	return nullptr;
}

template <typename Tkey, typename Tdata>
void BPlusTree<Tkey, Tdata>::print(){
	print(0, root);
}

template class BPlusTree<std::string, Student>;
