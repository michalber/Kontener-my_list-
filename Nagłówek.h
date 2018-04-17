#pragma once

#include <iterator>
#include <cstdlib>


template <typename T>
class my_list
{
	class Iterator;

	class Node
	{
		T p_data;
		Node * p_next;
		Node * p_prev;

		Node(const T & val, Node * next = 0, Node * prev = 0) : p_data(val), p_next(next), p_prev(prev)
		{ }

		friend class my_list<T>;
		friend class Iterator;
	};


	class Iterator
	{
		Element * p_current;

		Iterator(Element * position) : p_current(position)
		{ }

		friend class my_list;

	public:

		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T * pointer;
		typedef T & reference;

		Iterator() : p_current(0)
		{ }


		T & operator*()
		{
			return p_current->p_data;
		}

		T * operator->()
		{
			return &(p_current->p_data);
		}

		Iterator & operator++()     // preinkrementacja
		{
			p_current = p_current->p_next;
			return *this;
		}

		Iterator operator++(int)    // postinkrementacja
		{
			Iterator temp = *this;
			p_current = p_current->p_next;
			return temp;
		}

		bool operator==(const Iterator rhs){ return p_current == rhs.p_current; }

		bool operator!=(const Iterator rhs) { return p_current != rhs.p_current; }
	};

	Element * p_head;
	int size = 0;

public:
	
	typedef T value_type;
	typedef Iterator iterator;

	my_list() : p_head(0)
	{ }

	~my_list();

	void push_front(const T &);

	void push_back(const T &);

	inline int Size() {
		return size;
	}

	inline iterator begin()
	{
		return iterator(p_head);
	}

	inline iterator end()
	{
		return iterator(0);
	}
};

template <typename T>
my_list<T>::~my_list()
{
	Element * p;
	while (p_head) {
		p = p_head;
		p_head = p_head->p_next;
		delete p;
	}
}

template <typename T>
void my_list<T>::push_front(const T & val)
{
	Element * p = new Element(val, p_head);
	p_head = p;
	size++;
}

template <typename T>
void my_list<T>::push_back(const T & val)
{
	Element * p = new Element(val,p_head);
	p_head = p;
	size++;
}





