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
Node<Tkey, Tdata>::~Node()
{
	//dtor
}

template class Node<std::string, Student>;
