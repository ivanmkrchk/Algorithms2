#include "Node.h"

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node()
{
	//ctor
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node(Tkey key, Tdata* data)
{
	this->key = key;
	this->data = data;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node(Node* parent){
	this->parent = parent;
}

template <typename Tkey, typename Tdata>
void Node<Tkey, Tdata>::copy(Node* node){
	this->color = node->color;
	this->key = node->key;
	this->data = node->data;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::~Node()
{
	//dtor
}


template class Node<std::string, Student>;
