#ifndef NODE_H
#define NODE_H

#include "Student.h"
#include <vector>

template <typename Tkey, typename Tdata>
class Node
{
	public:
		Node(int demision);
		Node();
		virtual ~Node();

		bool leaf;
		int keyNumber;
		std::vector<Tkey> key;
		Node<Tkey, Tdata>  *left,
						   *right,
						   *parent;
		std::vector<Node<Tkey, Tdata>*> child;
		std::vector<Tdata*> cost;
};

#endif // NODE_H
