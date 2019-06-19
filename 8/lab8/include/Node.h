#ifndef NODE_H
#define NODE_H

#include "Student.h"

template <typename Tkey, typename Tdata>
class Node
{
	public:
		Node();
		Node(Tkey key, Tdata* cost);
		virtual ~Node();

		Tdata* cost;
		Tkey key;

		Node<Tkey, Tdata> *child = nullptr,
						  *left = nullptr,
						  *right = nullptr,
						  *parent = nullptr;

		int degree = 0;
		bool mark = false;
};

#endif // NODE_H
