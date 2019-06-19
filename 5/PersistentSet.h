#pragma once

#include <cassert>
#include <memory>
#include <list>
#include <iomanip>
using namespace std;

template<class T>
class PersistentRbTree;

//*************************PersistentSet*************************//

//клас для реалізації персистентної множини
template <typename T>
class PersistentSet {
private:
	using TreeType = PersistentRbTree<T>;
	list<TreeType> setStates;
public:
	PersistentSet() {
	}

	PersistentSet(const TreeType& tree) {
		setStates = list<TreeType>(tree);
	}

	PersistentSet(const PersistentSet& set) {
		setStates = set.setStates;
	}

	//вставка
	TreeType insert(T val) {
		if (setStates.empty()) 
		{
			setStates.push_back(PersistentRbTree<T>().ins(val));
			return  setStates.back();
		}
		setStates.push_back(setStates.back().inserted(val));
		return  setStates.back();
	}

	TreeType& operator[](size_t index) {
		if (index > setStates.size()) {
			throw  runtime_error("too big index");
		}
		auto it = setStates.begin();
		while (index-- > 0)it++;
		return *it;
	}

	//загальна кількість станів
	size_t states() {
		return setStates.size();
	}

	//очистка списку станів
	void clear() {
		setStates.clear();
	}

	//повертає останній стан
	TreeType& last() {
		return setStates.back();
	}

	bool memeber(T el) {
		return setStates.back().member(el);
	}
};

//*************************PersistentRbTree*************************//

//персистентна множина на основі червоно-чорного дерера (клас для її реалізації)
template<class T>
class PersistentRbTree
{
	struct Node;
	using NodePtr = shared_ptr<const Node>;
	enum Color { RED, BLACK };
private:
	//вузол дерева
	struct Node
	{
		Node(Color c,
			NodePtr const & lft,
			T val,
			NodePtr const & rgt) :
			color(c), lft(lft), val(val), rgt(rgt)
		{
		}
		Color color;
		NodePtr lft;
		NodePtr rgt;
		T val;
	};
private:
	//корінь дерева
	NodePtr root;
public:
	//вставка в червоно-чорне дерево
	PersistentRbTree ins(T x) const
	{
		assert1();
		if (isEmpty())
			return PersistentRbTree(RED, PersistentRbTree(), x, PersistentRbTree());
		T y = rootValue();
		Color c = rootColor();
		if (rootColor() == BLACK) 
		{
			if (x < y)
				return balance(left().ins(x), y, right());
			else if (y < x)
				return balance(left(), y, right().ins(x));
			else
				return *this; // немає дублікатів
		}
		else
		{
			if (x < y)
				return PersistentRbTree(c, left().ins(x), y, right());
			else if (y < x)
				return PersistentRbTree(c, left(), y, right().ins(x));
			else
				return *this;  // немає дублікатів
		}
	}
	// викликається, лише коли батько чорний
	static PersistentRbTree balance(PersistentRbTree const & lft, T x, PersistentRbTree const & rgt)
	{
		if (lft.doubledLeft())
			return PersistentRbTree(RED, lft.left().paint(BLACK)
				, lft.rootValue()
				, PersistentRbTree(BLACK, lft.right(), x, rgt));
		else if (lft.doubledRight())
			return PersistentRbTree(RED
				, PersistentRbTree(BLACK, lft.left(), lft.rootValue(), lft.right().left())
				, lft.right().rootValue()
				, PersistentRbTree(BLACK, lft.right().right(), x, rgt));
		else if (rgt.doubledLeft())
			return PersistentRbTree(RED
				, PersistentRbTree(BLACK, lft, x, rgt.left().left())
				, rgt.left().rootValue()
				, PersistentRbTree(BLACK, rgt.left().right(), rgt.rootValue(), rgt.right()));
		else if (rgt.doubledRight())
			return PersistentRbTree(RED
				, PersistentRbTree(BLACK, lft, x, rgt.left())
				, rgt.rootValue()
				, rgt.right().paint(BLACK));
		else
			return PersistentRbTree(BLACK, lft, x, rgt);
	}
	bool doubledLeft() const
	{
		return !isEmpty()
			&& rootColor() == RED
			&& !left().isEmpty()
			&& left().rootColor() == RED;
	}
	bool doubledRight() const
	{
		return !isEmpty()
			&& rootColor() == RED
			&& !right().isEmpty()
			&& right().rootColor() == RED;
	}
	PersistentRbTree paint(Color c) const
	{
		assert(!isEmpty());
		return PersistentRbTree(c, left(), rootValue(), right());
	}

	// виведення рівня дерева
	void printLevel(PersistentRbTree lvl, int indent=0)const {
		if (lvl.isEmpty()) {
			return;
		}
		if (!lvl.left().isEmpty())
		{
			printLevel(lvl.left(), indent + 8);
			cout << std::setw(indent) << ' ' << " /\n";
			
		}

		cout << std::setw(indent) << lvl.rootValue();
		if (!lvl.right().isEmpty())
		{
			cout << std::setw(indent) << ' ' << " \\\n";
			printLevel(lvl.right(), indent + 8);
		}

	}

	explicit PersistentRbTree(NodePtr const & node) : root(node) {}

	//повертає корінь вузла
	Color rootColor() const
	{
		assert(!isEmpty());
		return root->color;
	}
public:
	PersistentRbTree() {}
	PersistentRbTree(Color c, PersistentRbTree const & lft, T val, PersistentRbTree const & rgt)
		: root(std::make_shared<const Node>(c, lft.root, val, rgt.root))
	{
		assert(lft.isEmpty() || lft.rootValue() < val);
		assert(rgt.isEmpty() || val < rgt.rootValue());
	}
	PersistentRbTree(std::initializer_list<T> init)
	{
		PersistentRbTree t;
		for (T v : init)
		{
			t = t.inserted(v);
		}
		root = t._root;
	}
	template<class I>
	PersistentRbTree(I b, I e)
	{
		PersistentRbTree t;
		for_each(b, e, [&t](T const & v) {
			t = t.inserted(v);
		});
		root = t._root;
	}

	bool isEmpty() const {
		return !root;
	}

	//повертає значення
	T rootValue() const
	{
		assert(!isEmpty());
		return root->val;
	}

	PersistentRbTree left() const
	{
		assert(!isEmpty());
		return PersistentRbTree(root->lft);
	}

	PersistentRbTree right() const
	{
		assert(!isEmpty());
		return PersistentRbTree(root->rgt);
	}

	//перевірка на членство
	bool member(T x) const
	{
		if (isEmpty())
			return false;
		T y = rootValue();
		if (x < y)
			return left().member(x);
		else if (y < x)
			return right().member(x);
		else
			return true;
	}

	//вставка
	PersistentRbTree inserted(T x) const
	{
		PersistentRbTree t = ins(x);
		return PersistentRbTree(BLACK, t.left(), t.rootValue(), t.right());
	}

	// 1. немає червоного вузла, що має червону дитину
	void assert1() const
	{
		if (!isEmpty())
		{
			auto lft = left();
			auto rgt = right();
			if (rootColor() == RED)
			{
				assert(lft.isEmpty() || lft.rootColor() == BLACK);
				assert(rgt.isEmpty() || rgt.rootColor() == BLACK);
			}
			lft.assert1();
			rgt.assert1();
		}
	}
	// 2. Кожен шлях від кореня до порожнього вузла містить однакову кількість чорних вузлів.
	int countB() const
	{
		if (isEmpty())
			return 0;
		int lft = left().countB();
		int rgt = right().countB();
		assert(lft == rgt);
		return (rootColor() == BLACK) ? 1 + lft : lft;
	}

	void print()const {
		printLevel(*this);
		cout << endl;
	}
};

//пройтися по всьому
template<class T, class F>
void forEach(PersistentRbTree<T> const & t, F f) {
	if (!t.isEmpty()) {
		forEach(t.left(), f);
		f(t.rootValue());
		forEach(t.right(), f);
	}
}

//вставка
template<class T, class Beg, class End>
PersistentRbTree<T> inserted(PersistentRbTree<T> t, Beg it, End end)
{
	if (it == end)
		return t;
	T item = *it;
	auto t1 = inserted(t, ++it, end);
	return t1.inserted(item);
}

//об"єднання 2 дерев
template<class T>
PersistentRbTree<T> treeUnion(PersistentRbTree<T> const & a, PersistentRbTree<T> const & b)
{
	// a u b = a + (b \ a)
	PersistentRbTree<T> res = a;
	forEach(b, [&res, &a](T const & v) {
		if (!a.member(v))
			res.inserted(v);
	});
	return res;
}