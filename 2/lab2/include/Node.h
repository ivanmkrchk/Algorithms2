#ifndef NODE_H
#define NODE_H

#include "Student.h"

enum NodeColor {BLACK, RED};

template <typename Tkey, typename Tdata>
class Node
{
	public:
		Node(Node* parent);
		Node();
		virtual ~Node();

		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;
		NodeColor color = BLACK;
		Tkey key;
		Tdata* data = nullptr;
		int size = 0;
};

#endif // NODE_H
