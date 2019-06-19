#include "BinTree.h"

#include <iostream>

template <typename Tkey, typename Tdata>
BinTree<Tkey, Tdata>::BinTree()
{
	//ctor
}

template <typename Tkey, typename Tdata>
BinTree<Tkey, Tdata>::~BinTree()
{
	delete root;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* BinTree<Tkey, Tdata>::successor(Node<Tkey, Tdata>* node){
	Node<Tkey, Tdata>* resultNode = node;

	if (resultNode->right != nullptr) resultNode = minimum(resultNode->right);
	else {
		while (resultNode != root || resultNode != resultNode->parent->left) {
                resultNode = resultNode->parent;
		}
	}
	return resultNode;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* BinTree<Tkey, Tdata>::predecessor(Node<Tkey, Tdata>* node){
	Node<Tkey, Tdata>* resultNode = node;

	if (resultNode->left != nullptr) resultNode = maximum(resultNode->left);
	else {
		while (resultNode != root || resultNode != resultNode->parent->right) {
			resultNode = resultNode->parent;
		}
	}
	return resultNode;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* BinTree<Tkey, Tdata>::minimum(Node<Tkey, Tdata>* node) {

//	std::cout << "BEGIN  minimum\n";
	Node<Tkey, Tdata>* minNode = node;

	while (minNode->left != nullptr)
		minNode = minNode->left;

//	std::cout << "END  minimum\n";
	return minNode;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* BinTree<Tkey, Tdata>::maximum(Node<Tkey, Tdata>* node) {
	Node<Tkey, Tdata>* maxNode = node;

	while (maxNode->right != nullptr)
		maxNode = maxNode->right;

	return maxNode;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>* BinTree<Tkey, Tdata>::find_(const Tkey & key) {

	Node<Tkey, Tdata>* searchedElement = root;

	while (searchedElement != nullptr) {
		if (searchedElement->key < key) searchedElement = searchedElement->right;
		else if (key < searchedElement->key) searchedElement = searchedElement->left;
		else {
			splay(searchedElement);
			return searchedElement;
		}
	}

	return nullptr;
}

template <typename Tkey, typename Tdata>
void BinTree<Tkey, Tdata>::leftRotate(Node<Tkey, Tdata>* node) {

	Node<Tkey, Tdata>* rightChild = node->right;

	node->right = rightChild->left;
	if (rightChild->left != nullptr)
		rightChild->left->parent = node;

	replace(node, rightChild);

	rightChild->left = node;
	rightChild->left->parent = rightChild;
}

template <typename Tkey, typename Tdata>
void BinTree<Tkey, Tdata>::rightRotate(Node<Tkey, Tdata>* node) {

//	std::cout << "BEGIN rightRotate\n";
	Node<Tkey, Tdata>* leftChild = node->left;

	node->left = leftChild->right;
	if (leftChild->right != nullptr) leftChild->right->parent = node;

	replace(node, leftChild);

	leftChild->right = node;
	leftChild->right->parent = leftChild;

//	std::cout << "END rightRotate\n";
}

template <typename Tkey, typename Tdata>
void BinTree<Tkey, Tdata>::replace(Node<Tkey, Tdata>* localParent, Node<Tkey, Tdata>* localChild) {

//	std::cout << "BEGIN replace\n" << localParent->parent << '\n';
	if (localParent->parent == nullptr) root = localChild;
	else if (localParent == localParent->parent->left)
		localParent->parent->left = localChild;
	else if (localParent == localParent->parent->right)
		localParent->parent->right = localChild;

	if (localChild != nullptr) localChild->parent = localParent->parent;
//	std::cout << "END replace\n";
}

template <typename Tkey, typename Tdata>
void BinTree<Tkey, Tdata>::splay(Node<Tkey, Tdata>* pivotElement) {

//	std::cout << "BEGIN splay\n";
	while (pivotElement != root) {
		if (pivotElement->parent == root) {

			if (pivotElement == pivotElement->parent->left) rightRotate(pivotElement->parent);
			else leftRotate(pivotElement->parent);
		}

			else {

                // Zig-Zig
                if (pivotElement == pivotElement->parent->left &&
                    pivotElement->parent == pivotElement->parent->parent->left) {

                    rightRotate(pivotElement->parent->parent);
                    rightRotate(pivotElement->parent);

                } else if (pivotElement == pivotElement->parent->right &&
                           pivotElement->parent == pivotElement->parent->parent->right) {

                    leftRotate(pivotElement->parent->parent);
                    leftRotate(pivotElement->parent);
                }

                // Zig-Zag
                else if (pivotElement == pivotElement->parent->right &&
                    pivotElement->parent == pivotElement->parent->parent->left) {

                    leftRotate(pivotElement->parent);
                    rightRotate(pivotElement->parent);

                } else if (pivotElement == pivotElement->parent->left &&
                           pivotElement->parent == pivotElement->parent->parent->right) {

                    rightRotate(pivotElement->parent);
                    leftRotate(pivotElement->parent);
                }
            }

    }

//	std::cout << "END splay\n";
}

template <typename Tkey, typename Tdata>
void BinTree<Tkey, Tdata>::insert(const Tkey& key, Tdata* data ) {

//	std::cout << "BEGIN insert\n";
	Node<Tkey, Tdata>* preInsertPlace = nullptr;
	Node<Tkey, Tdata>* insertPlace = root;

	while (insertPlace != nullptr) {
		preInsertPlace = insertPlace;

		if (insertPlace->key < key) insertPlace = insertPlace->right;
		else insertPlace = insertPlace->left;
	}

	Node<Tkey, Tdata>* insertElement = new Node<Tkey, Tdata>(key, data);
	insertElement->parent = preInsertPlace;

	if (preInsertPlace == nullptr) root = insertElement;
	else if (preInsertPlace->key < insertElement->key)
		preInsertPlace->right = insertElement;
	else preInsertPlace->left = insertElement;

	splay(insertElement);
//	std::cout << "END insert\n";
}

template <typename Tkey, typename Tdata>
void BinTree<Tkey, Tdata>::remove(const Tkey& key) {
	Node<Tkey, Tdata>* removeElement = find_(key);

	if (removeElement != nullptr) {
		if (removeElement->right == nullptr) replace(removeElement, removeElement->left);
		else if (removeElement->left == nullptr) replace(removeElement, removeElement->right);
		else {
			Node<Tkey, Tdata>* newLocalRoot = minimum(removeElement->right);

			if (newLocalRoot->parent != removeElement) {

				replace(newLocalRoot, newLocalRoot->right);

				newLocalRoot->right = removeElement->right;
				newLocalRoot->right->parent = newLocalRoot;
			}

			replace(removeElement, newLocalRoot);

			newLocalRoot->left = removeElement->left;
			newLocalRoot->left->parent = newLocalRoot;

			splay(newLocalRoot);
		}

		removeElement->left = nullptr;
		removeElement->right = nullptr;
		delete removeElement;
	}
}

template <typename Tkey, typename Tdata>
Tdata* BinTree<Tkey, Tdata>::find(const Tkey& key){

	Node<Tkey, Tdata>* node = find_(key);

	if (node) return node->data;
	return nullptr;
}

template <typename Tkey, typename Tdata>
void BinTree<Tkey, Tdata>::print(Node<Tkey, Tdata>* node, int deep){

	if (!node) return;

	print(node->left, deep+1);

	printTab(deep);
	std::cout << ">" << node->data->surname << "(" << node->data->mean << ")\n";

	print(node->right, deep+1);
}

template <typename Tkey, typename Tdata>
void BinTree<Tkey, Tdata>::print(){
	std::cout << "--------------------------------------------------------------------\n";
	print(root, 0);
	std::cout << "--------------------------------------------------------------------\n";
}

template <typename Tkey, typename Tdata>
void BinTree<Tkey, Tdata>::printTab(int k){
	for (int i = 0; i < k; i++)
		std::cout << "        ";
}

template class BinTree<std::string, Student>;
