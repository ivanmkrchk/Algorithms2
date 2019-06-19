#include "Node.h"

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node()
{
	//ctor
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node(Node* parent){
	this->parent = parent;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node(const Tkey& key, Tdata* data){
	this->key = key;
	this->data = data;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::~Node()
{
	if (left) left->~Node();
	if (right) right->~Node();
	delete data;
}

template class Node<std::string, Student>;
