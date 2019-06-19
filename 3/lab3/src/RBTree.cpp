#include "RBTree.h"

#include <iostream>
#include <cmath>

RBTree::RBTree()
{
	//ctor
}

RBTree::~RBTree()
{
	//dtor
}

Node* RBTree::find(double mean){

	if (!root) return nullptr;
	Node* p = root;

	while (!isLeaf(p) && fabs(p->data->mean - mean) > 1e-5) {

		if (p->data->mean > mean) p = p->left;
		else p = p->right;
	}

	if (isLeaf(p)) return nullptr;
	return p;
}

Node* RBTree::findByRank(Node* node, int rank){

	int r = node->left->size+1;

	if (rank == r) return node;
	if (rank < r) return findByRank(node->left, rank);
	return findByRank(node->right, rank-r);
}

Node* RBTree::findByRank(int rank){
	return findByRank(root, rank);
}

int RBTree::getSize(){
	if (!root) return 0;
	return root->size;
}

void RBTree::print(Node* node, int deep){

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

void RBTree::print(){
	print(root, 0);
}

void RBTree::printTab(int k){
	for (int i = 0; i < k; i++)
		std::cout << "        ";
}

void RBTree::insert_(Student* student){

	if (!root) {

		Node* node = new Node(nullptr);
		node->data = student;
		node->size = 1;

		node->left = new Node(node);
		node->right = new Node(node);

		root = node;
		return;
	}

	Node* p = root;

	while (!isLeaf(p)){

		p->size++;

		if (p->data->mean > student->mean) p = p->left;
		else p = p->right;
	}

	Node* node = new Node(p->parent);
	node->color = RED;
	node->data = student;
	node->size = 1;

	if (p->parent->left == p) p->parent->left = node;
	else p->parent->right = node;

	node->left = new Node(node);
	node->right = new Node(node);

	delete p;

	std::cout << "A " << isLeaf(root->left) << " " << isLeaf(root->right) << '\n';
	insert_(node);
}

Node* RBTree::grandparent(Node *n){

	if ((n != nullptr) && (n->parent != nullptr))
		return n->parent->parent;
	else
		return nullptr;
}

Node* RBTree::uncle(Node* n){

	Node *g = grandparent(n);
	if (g == nullptr)
		return nullptr;
	if (n->parent == g->left)
		return (isLeaf(g->right) ? nullptr : g->right);
	else
		return (isLeaf(g->left) ? nullptr : g->left);
}

Node* RBTree::sibling(Node *n){

	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

bool RBTree::isLeaf(Node *n){
	return (n->data == nullptr);
}

void RBTree::replaceNode(Node* n1, Node* n2){

	if (root == n1) root = n2;
	Node* p = n1->parent;

	if (p){
		if (p->left == n1) p->left = n2;
		else p->right = n2;
	}

	n2->parent = p;
	p->size = p->left->size + p->right->size + 1;
	//n2->left = n1->left;
	//n2->right = n1->right;

}

void RBTree::rotateLeft(Node *n){

	if (root == n) root = n->right;
    Node *pivot = n->right;

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

void RBTree::rotateRight(Node *n){

	if (root == n) root = n->left;
    Node *pivot = n->left;

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

void RBTree::insert_(Node *n){

	if (n->parent == nullptr){
		n->color = BLACK;
		return;
	}

	if (n->parent->color == BLACK) return;

	Node *u = uncle(n), *g;
	if ((u != nullptr) && (u->color == RED)) {

		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insert_(g);
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

Node* RBTree::findMax(Node* node){

	if (isLeaf(node->right)) return node;
	return findMax(node->right);
}

void RBTree::decreaseSize(Node* node, double mean){
	Node* p = root;

	while (!isLeaf(p) && fabs(p->data->mean - mean) > 1e-5) {

		p->size--;
		if (p->data->mean > mean) p = p->left;
		else p = p->right;
	}

	p->size = 0;
}

void RBTree::delete_(double mean){
	Node* node = find(mean);
	if (!node) return;

	if (!isLeaf(node->left)){

		Node* nodeToReplace = findMax(node->left);
		decreaseSize(node, nodeToReplace->data->mean);

		delete node->data;
		node->data = nodeToReplace->data;

		deleteChild(nodeToReplace);
		return;
	}
	decreaseSize(node, mean);
	deleteChild(node);
}

void RBTree::deleteChild(Node *n){

	Node *child = (isLeaf(n->right) ? n->left : n->right);

	replaceNode(n, child);
	if (n->color == BLACK) {
		if (child->color == RED)
			child->color = BLACK;
		else
			delete_(child);
	}

	delete n;
}

void RBTree::delete_(Node* n){

	if (n->parent == nullptr) return;

	Node *s = sibling(n);
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
			delete_(n->parent);
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


void RBTree::loadData(std::istream& in){

    int i = 0;
    while (!in.eof()){

		data.push_back(new Student());
        getline(in, data[i]->group, '\t');
        getline(in, data[i]->surname, '\t');
        getline(in, data[i]->name, '\t');

        std::string mean;
        getline(in, mean, '\n');

        data[i]->mean = atof(mean.c_str());
        i++;
    }
    data.erase(data.begin() + data.size()-1);
}

void RBTree::printData(){

	for (int i = 0; i < data.size(); i++){
		data[i]->print();
	}
}

void RBTree::addElements(int l, int r){

	for (int i = std::max(0,l); i <= std::min(r,(int)data.size()-1); i++)
		insert_(data[i]);
}
