#pragma once
#pragma once
#include <iostream>
template <class T> class LinkedList
{
private:
	template <typename T> class Node
	{
	private:
		T data;
		Node<T>* next;
		Node();
	public:
		Node(const T& value) : data(value), next(NULL) {};
		~Node() {};
		void        SetValue(T& value) { data = value; }
		const T& GetValue() { return data; }
		void        SetNext(Node<T>* _next) { next = _next; }
		Node<T>* GetNext() { return next; }
		void        Print() { std::cout << data << std::endl; }
	};
	Node<T>* head;
	Node<T>* tail;
public:
	LinkedList();
	~LinkedList();
	void makeList(int size, std::string input);
	bool PushFront(const T& value);
	bool PushBack(const T& value);
	bool PopFront();
	bool PopBack();
	int  Length() const;
	void Print() const;
	bool Delete(const int& position);
	int  Find(const int& value) const;
};