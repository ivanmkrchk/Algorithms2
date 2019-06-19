#include "Node.h"
#include <iostream>

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node() : degree(0)
{
	//ctor
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node(Tkey key, Tdata* data){
	this->key = key;
	this->cost = data;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::~Node()
{
}

template class Node<std::string, Student>;
