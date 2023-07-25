#pragma once

struct Coordinates {
	int x;
	int y;

	Coordinates(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}

	bool operator ==(const Coordinates& c) {
		if (x == c.x && y == c.y)
			return true;
		return false;
	};
};

template
<typename T>
struct Vector2D 
{
	T a, b;

	Vector2D(int a = 0, int b = 0) {
		this->a = a;
		this->b = b;
	}

	bool operator ==(const Vector2D<int>& v) {
		if (a == v.a && b == v.b)
			return true;
		return false;
	};
};

template
<typename T>
struct Vector3D 
{
	T a, b, c;

	Vector3D(int a = 0, int b = 0, int c = 0) {
		this->a = a;
		this->b = b;
		this->c = c;
	}

	bool operator ==(const Vector3D<int>& v) {
		if (a == v.a && b == v.b && c = v.c)
			return true;
		return false;
	};
};

template
<typename T>
class LinkedListItem {
	T item;
	LinkedListItem<T>* next;
	LinkedListItem<T>T* prev;

public:
	LinkedListItem(T i, LinkedListItem<T> n = nullptr, LinkedListItem<T> p = nullptr) {
		item = i;
		next = n;
		prev = p;
	}

	T getItem() { return item; };
	LinkedListItem<T>* getNext() { return next; };
	LinkedListItem<T>* getPrev() { return prev; };

	void setItem(T i) { item = i; };
	void setNext(LinkedListItem<T>* n) { next = n; };
	void setPrev(LinkedListItem<T>* p) { prev = p; };
};

template
<typename T>
class LinkedList {
	LinkedListItem<T>* head;
	LinkedListItem<T>* end;
	int count;
public:
	LinkedList() {
		head = nullptr;
		end = nullptr;
		count = 0;
	}

	void addItemToEnd(T i) {
		LinkedListItem<T>* toBeAdded = new LinkedListItem<T>(i);
		if (head == nullptr) {
			head = toBeAdded;
			end = toBeAdded;
		}
		else {
			toBeAdded->setPrev(end);
			end->setNext(toBeAdded);
		}
		count++;
	}
	void insertItem(T i, int index) {
		if (index < 0 || index >= count) {
			std::cout << "Cannot insert item into index " << index << ". Out of Bounds.\n";
			return;
		}
		LinkedListItem<T>* toBeInserted = new LinkedListItem<T>(i);
		LinkedListItem<T>* prev = head;
		LinkedListItem<T>* next;
		for (int j = 0; j < count; j++) {
			prev = prev->getNext();
		}
		next = prev->getNext();
		prev->setNext(toBeInserted);
		toBeInserted->setPrev(prev);
		toBeInserted->setNext(next);
		next->setPrev(toBeInserted);

		count++;
	}
	T popHead() {
		LinkedListItem<T>* toBeRemoved = head;
		T toBePopped = toBeRemoved.getItem();

		LinkedListItem<T>* newHead = head->getNext();
		newHead->setPrev(nullptr);
		head = newHead;

		delete toBeRemoved;
		count--;
		return toBePopped;
	}

	LinkedListItem<T>* getHead() { return head; };
	int getCount() { return count; };

	void setHead(LinkedListItem<T>* h) { head = h; };
	void setCount(int c) { head = c; };
};