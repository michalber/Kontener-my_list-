#pragma once


template<class T>
class my_list
{
	class Iterator;

	class Node
	{
		T value;
		Node * next;
		Node * prev;

		Node(const T & val, Node * next = 0, Node * prev = 0) : value(val), next(next), prev(prev)
		{ }

		friend class my_list<T>;
		friend class Iterator;
	};

	class Iterator
	{
		Node * p_current;

		Iterator(Node * position) : p_current(position)
		{ }

		friend class my_list<T>;

	public:

		
		Iterator() : p_current(0)
		{ }


		T & operator*() { return p_current->value; }
		T * operator->() { return &(p_current->value); }

		Iterator & operator++() {
			p_current = p_current->next;
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			p_current = p_current->next;
			return temp;
		}

		bool operator==(const Iterator rhs) { return p_current == rhs.p_current; }
		bool operator!=(const Iterator rhs) { return p_current != rhs.p_current; }
	};

public:
	typedef Iterator iterator;
	typedef T value_type;
	
private:
	Node * head;
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
	Node * p;
	while (head) {
		p = head;
		head = head->next;
		delete p;
	}
}

template <typename T>
void my_list<T>::push_front(const T & val)
{
	Node * p = new Node(val, head);
	head = p;
	size++;
}

template <typename T>
void my_list<T>::push_back(const T & val)
{
	Node * p = new Node(val);
	if (head == NULL) {
		head = p;
	}
	else {
		Node * temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = p;
	}
	size++;
}
//-------------------------------------------------------------------------------------------------------------

