#pragma once

template<class T> class Node;
template<class T> class Iterator;

template<class T>
class my_list
{

public:
	typedef Iterator<T> iterator;
	typedef T value_type;

private:
	Node<T> * head;
	int size = 0;

public:

	my_list() : head(0), size(0) { }
	~my_list();

	void push_front(const T &);
	void push_back(const T &);

	int Size() { return size; }

	iterator begin() { return iterator(head); }
	iterator end() { return iterator(0); }
};
//-------------------------------------------------------------------------------------------------------------
template <typename T>
my_list<T>::~my_list()
{
	Node<T> * p;
	while (head) {
		p = head;
		head = head->next;
		delete p;
	}
}

template <typename T>
void my_list<T>::push_front(const T & val)
{
	Node<T> * p = new Node<T>(val, head);
	head = p;
	size++;
}

template <typename T>
void my_list<T>::push_back(const T & val)
{
	Node<T> * p = new Node<T>(val);
	if (head == NULL) {
		head = p;
	}
	else {
		Node<T> * temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = p;
	}
	size++;
}
//-------------------------------------------------------------------------------------------------------------

template <typename T>
class Node
{
	T value;
	Node<T> * next;
	Node<T> * prev;

	Node(const T & val, Node * next = 0, Node * prev = 0) : value(val), next(next), prev(prev)
	{ }

	friend class my_list<T>;
	friend class Iterator<T>;
};

//-------------------------------------------------------------------------------------------------------------
template <typename T>
class Iterator
{
	Node<T> * p_current;

	friend class my_list<T>;

public:
	typedef Iterator<T> iterator;

	Iterator() : p_current(0)
	{ }
	Iterator(Node<T> * position) : p_current(position)
	{ }


	T & operator*() { return p_current->value; }
	T * operator->() { return &(p_current->value); }

	iterator & operator++() {
		p_current = p_current->next;
		return *this;
	}

	iterator operator++(int) {
		Iterator temp = *this;
		p_current = p_current->next;
		return temp;
	}

	bool operator==(const Iterator rhs) { return p_current == rhs.p_current; }
	bool operator!=(const Iterator rhs) { return p_current != rhs.p_current; }
};