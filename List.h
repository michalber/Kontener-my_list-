#pragma once

#include <memory>
#include <cstddef>

template<class T> class Node;
template<class T> class ListIter;

template<class T>
class List {
public:
	typedef ListIter<T> iterator;
	typedef const ListIter<T> const_iterator;
	typedef std::size_t size_type;


	List() : head(0), sz(0) {}
	List(const List<T>& lst);
	~List() { clear(); }

	iterator begin() { return iterator(head.next); }
	iterator end() { return iterator(&head); }
	iterator insert() {}
	iterator erase() {}
	const_iterator begin() const { return iterator(head.next); }
	const_iterator end() const { return iterator(&head); }

	void push_back(const T& val);
	void push_front(const T& val);
	void clear();
	void pop_front();
	void pop_back();
	size_type size() { return sz; }
	bool empty() { return sz == 0; }

	List& operator=(const List& l);

private:
	Node<T> head;
	size_type sz;

	std::allocator<Node<T>>* alloc;
};

template<class T>
class Node {
public:
	Node() : next(0), prev(0), value(0) {}
	Node(const T& val) : next(0), prev(0), value(val) {}

private:
	Node<T>* next;
	Node<T>* prev;
	T value;

	friend class List<T>;
	friend class ListIter<T>;
};

template<class T>
class ListIter {
public:
	typedef ListIter<T> iterator;

	ListIter(Node<T>* iter) : current_node(iter) {}
	ListIter() : current_node(0) {}
	ListIter(ListIter<T>* iter) : current_node(iter->current_node) {}

	inline T& operator*() { return current_node->value; }
	iterator& operator=(const iterator& rhs) { *this->current_node = rhs.current_node; }
	bool operator==(const iterator& rhs) { return current_node->value == rhs.current_node->value; }
	bool operator!=(const iterator& rhs) { return current_node->value != rhs.current_node->value; }
	iterator& operator++();
	iterator operator++(int);
	iterator& operator--();
	iterator operator--(int);

private:
	Node<T>* current_node;
	friend class List<T>;
};


template<class T>
void List<T>::push_back(const T& val)
{
	Node<T>* temp = alloc->allocate(1);
	alloc->construct(temp, val);
	if (head.next == 0) {
		head = temp;
	}
	else {
		temp->prev = head.next;
		head.next = temp;
		head = temp;
	}
	sz++;
}

template<class T>
void List<T>::push_front(const T &val)
{
	Node<T>* temp = alloc->allocate(1);
	alloc->construct(temp, val);
	if (head.next == 0) {
		head = temp;
	}
	else {
		temp->prev = 0;
		temp->next = head.next;
		head.next->prev = temp;
		head.next = temp;
	}
	sz++;
}


/*
template<class T>
void List<T>::clear()
{
	Node<T>* current = first;
	while (current != 0) {
		Node<T>* next = current->next;
		//delete current
		alloc->deallocate(current, 1);
		alloc->destroy(current);
		current = next;
	}
	first = last = 0;
	sz = 0;
}
*/
template<class T>
List<T>::List(const List &lst)
{
	head = 0;
	sz = 0;
	for (auto it = lst.begin(); it != lst.end(); it++) {
		push_back(it.current_node->value);
	}
	push_back(lst.last->value);
}

template<class T>
List<T>& List<T>::operator=(const List &lst)
{
	head = 0;
	sz = 0;
	for (auto it = lst.begin(); it != lst.end(); ++it) {
		push_back(it.current_node->value);
	}
	push_back(lst.last->value);
	return *this;
}

/*
template<class T>
void List<T>::pop_front()
{
	first = first->next;
	alloc->deallocate(first->prev, 1);
	alloc->destroy(first->prev);
	first->prev = 0;
	sz--;
}

template<class T>
void List<T>::pop_back()
{
	last = last->prev;
	alloc->deallocate(last->next, 1);
	alloc->destroy(last->next);
	last->next = 0;
	sz--;
}
*/
template<class T>
ListIter<T>& ListIter<T>::operator++()
{
	current_node = current_node->next;
	return *this;
}

template<class T>
ListIter<T>& ListIter<T>::operator--()
{
	current_node = current_node->prev;
	return *this;
}

template<class T>
ListIter<T> ListIter<T>::operator++(int)
{
	iterator tmp(*this);
	++*this;
	return tmp;
}

template<class T>
ListIter<T> ListIter<T>::operator--(int)
{
	iterator tmp(*this);
	--*this;
	return tmp;
}

