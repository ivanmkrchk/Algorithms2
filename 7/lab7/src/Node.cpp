#include "Node.h"
#include <iostream>

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
}

template class Node<std::string, Student>;
