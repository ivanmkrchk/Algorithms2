#ifndef NODE_H
#define NODE_H

#include "Student.h"

template <typename Tkey, typename Tdata>
class Node
{
	public:
		Node(Node* parent);
		Node(const Tkey& key, Tdata* data);
		Node();
		virtual ~Node();

		Node* prev = nullptr;
		Node* next = nullptr;
		Node* child = nullptr;
		Node* parent = nullptr;
		Tdata* data = nullptr;
		Tkey key;

		int degree = 0;
};

#endif // NODE_H
