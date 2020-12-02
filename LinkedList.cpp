#include "LinkedList.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class T> LinkedList<T>::LinkedList() : head(NULL), tail(NULL) {};
template <class T> LinkedList<T>::~LinkedList() {
	Node<T>* current = head;

	while (current) {
		Node<T>* next = current->GetNext();
		delete(current);
		current = next;
	}
}

template <class T> bool LinkedList<T>::PushFront(const T& value) {
	Node<T>* node = new Node<T>(value);

	if (node) {
		if (!head) {
			//список пуст
			head = node;
			tail = node;
		}
		else {
			node->SetNext(head);
			head = node;
		}
		return false;
	}
	else {
		return true; //ошибка выделения памяти
	}
}

template <class T> bool LinkedList<T>::PushBack(const T& value) {
	Node<T>* node = new Node<T>(value);

	if (node) {
		if (!head) {
			//список пуст
			head = node;
			tail = node;
		}
		else {
			tail->SetNext(node);
			tail = node;
		}
		return false;
	}
	else {
		return true;
	}
}

template <class T> bool LinkedList<T>::PopFront() {
	if (head) {
		Node<T>* new_head = head->GetNext();
		delete head;
		head = new_head;

		return false;
	}
	else
		return true;
}

template <class T> bool LinkedList<T>::PopBack() {
	if (tail) {
		// особый случай - один узел
		if (head == tail) {
			delete head;
			head = NULL;
			tail = NULL;
		}
		else {
			Node<T>* new_tail;

			new_tail = head;

			while (new_tail->GetNext() != tail) // пропускаем все узлы до узла перед tail
				new_tail = new_tail->GetNext();

			new_tail->SetNext(NULL);
			delete tail;
			tail = new_tail;
		}
		return false;
	}
	else
		return true;
}

template <class T> void LinkedList<T>::Print() const {
	Node<T>* e;
	for (e = head; e; e = e->GetNext())
		e->Print();
}

template <class T> int LinkedList<T>::Length() const {
	Node<T>* e;
	int count = 0;
	for (e = head; e; e = e->GetNext())
		++count;
	return count;
}

template <class T> bool LinkedList<T>::Delete(const int& position) {
	if (position < 0)
		return true;

	if (!head)
		return true; //список пуст

	Node<T>* target = head;

	if (!position) {//особый случай: position=0, т.е. удаляем head
		head = head->GetNext();
		delete target;

		return false;
	}

	Node<T>* node_before = head;
	for (int count = 0; count < position - 1; ++count) {
		node_before = node_before->GetNext();
		if (!node_before)
			return true; // вышли за границы
	}

	target = node_before->GetNext();

	if (!target)
		return true; // вышли за границы

	node_before->SetNext(target->GetNext());

	if (target == tail)
		tail = node_before;

	delete target;

	return false;
}

template <class T> int LinkedList<T>::Find(const int& value) const {
	int position = -1;
	Node<T>* e = head;
	for (int count = 0; e; e = e->GetNext(), ++count) {
		if (e->GetValue() == value) {
			position = count;
			break;
		}
	}
	return position;
}

template <class T> void LinkedList<T>::makeList(int size, string input)
{
	char* cstr = new char[input.length() + 1];
	strcpy(cstr, input.c_str());
	char* token = NULL;
	token = strtok(cstr, " ");
	int count = 0;
	while (token != NULL)
	{
		count++;
		if (count > size)
			break;
		this->PushBack(atoi(token));
		token = strtok(NULL, " ");
	}
}

int main() {
	LinkedList<int>* list = new LinkedList<int>();
	int size = 0;
	string input_list;

	cout << "Enter your list size: " << endl;
	cin >> size;
	cout << "Enter your list (using space): " << endl;
	getline(cin, input_list);
	getline(cin, input_list);
	list->makeList(size, input_list);
	cout << "Your list is: " << endl;
	list->Print();
	cout << "Please, choose the operation." << endl;
	cout << "Press 1 to PushFront." << endl;
	cout << "Press 2 to PushBack." << endl;
	cout << "Press 3 to find out the length." << endl;
	cout << "Press 4 to delete an element." << endl;
	cout << "Press 5 to find out the index of element." << endl;
	cout << "Press 6 to pop front." << endl;
	cout << "Press 7 to pop back." << endl;
	cout << "Press 8 to exit." << endl;
	int operation;
	while (cin >> operation) {
		switch (operation) {
		case 1:
			cout << "Enter the element you want to push front: " << endl;
			int a;
			cin >> a;
			if (list->Find(a) == -1) {
				cout << "Your list:" << endl;
				list->PushFront(a);
				if (list->Length() > size) {
					list->PopBack();
				}
			}
			else {
				cout << "Your list already contains such element." << endl;
			}
			list->Print();
			break;
		case 2:
			cout << "Enter the element you want to push back: " << endl;
			int b;
			cin >> b;
			if (list->Find(b) == -1) {
				cout << "Your list:" << endl;
				list->PushBack(b);
				if (list->Length() > size) {
					list->PopFront();
				}
			}
			else {
				cout << "Your list already contains such element." << endl;
			}
			list->Print();
			break;
		case 3:
			cout << "The length of your list is:  ";
			cout << list->Length();
			cout << endl;
			break;
		case 4:
			cout << "Enter the position of element you want to delete:  ";
			int pos;
			cin >> pos;
			list->Delete(pos);
			cout << "Your list:" << endl;
			list->Print();
			break;
		case 5:
			cout << "Enter the element you want to find:  ";
			int elem;
			cin >> elem;
			if (list->Find(elem) == -1) {
				cout << "No such element." << endl;
			}
			else {
				cout << "Its position: " << list->Find(elem) << endl;
			}
			break;
		case 6:
			cout << "Pop front: " << endl;
			cout << "Your list:" << endl;
			list->PopFront();
			list->Print();
			break;
		case 7:
			cout << "Pop back: " << endl;
			cout << "Your list:" << endl;
			list->PopBack();
			list->Print();
			break;
		case 8:
			exit(0);
		default:
			cout << "No such operation." << endl;
		}
		cout << "Choose next operation: " << endl;
	}
	return 0;
}
