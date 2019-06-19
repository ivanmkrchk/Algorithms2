#include "Node.h"
#include <iostream>

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node()
{
	leaf = false;
	keyNumber = 0;
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::Node(int dimension){
	leaf = false;
	keyNumber = 0;
	key.resize(2 * dimension);
	cost.resize(2 * dimension);
	child.resize(100);
}

template <typename Tkey, typename Tdata>
Node<Tkey, Tdata>::~Node()
{
}

template class Node<std::string, Student>;
