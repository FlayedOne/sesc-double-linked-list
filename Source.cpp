#include <iostream>
#include <string>

template <class T>
class LinkedList {
private:
	
	class cell {
	public:
		cell *previous, *following;
		T value;
		cell();
		cell(cell *previous, cell *following, const T & value);
	};
	cell *entry;
	size_t length;

public:

	LinkedList();
	LinkedList(const LinkedList<T> &list);
	~LinkedList();
	T push_front(const T & value);
	T pop_front();
	T push_back(const T & value);
	T pop_back();
	T peek_front() const;
	T peek_back() const;
	void clear();
	size_t size() const { return length; }
	bool isEmpty() const { return length == 0; }
	void dump(std::ostream & out) const;
	void dump_reversed(std::ostream & out) const;
};

int main() {
	std::string str;
	LinkedList<int> *list = new LinkedList<int>();
	for (std::cin >> str; !std::cin.eof(); std::cin >> str) {
		
		if ("push-front" == str) {
			int val;
			std::cin >> val;
			std::cout << list->push_front(val) << std::endl;
		}
		else if ("pop-front"==str) {
			if (list->isEmpty()) std::cout << "empty\n"; 
			else std::cout << list->pop_front() << std::endl;
		}
		else if ("push-back"==str) {
			int val;
			std::cin >> val;
			std::cout << list->push_back(val) << std::endl;
		}
		else if ("pop-back"==str) {
			if (list->isEmpty()) std::cout << "empty\n";
			else std::cout << list->pop_back() << std::endl;
		}
		else if ("peek-front"==str) {
			if (list->isEmpty()) std::cout << "empty\n";
			else std::cout << list->peek_front() << std::endl;
		}
		else if ("peek-back"==str) {
			if (list->isEmpty()) std::cout << "empty\n";
			else std::cout << list->peek_back() << std::endl;
		}
		else if ("size"==str) {
			std::cout << list->size() << std::endl;
		}
		else if ("clear"==str) {
			list->clear();
			std::cout << "empty\n";
		}
		else if ("dump"==str) {
			if (list->isEmpty()) std::cout << "empty\n";
			else list->dump(std::cout);
		}
		else if ("dump-reversed"==str) {
			if (list->isEmpty()) std::cout << "empty\n";
			else list->dump_reversed(std::cout);
		}
		else {
			std::cout << "ERROR: UNKNOWN OPERATION " << str << std::endl;
		}
	}
	delete list;
	return 0;
}

template<class T>
LinkedList<T>::LinkedList() {
	entry = new cell();
	length = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> & list) :LinkedList() {
	for (cell *i = list.entry->following; i != list.entry; i = i->following) this->push_back(i->value);
}

template<class T>
LinkedList<T>::~LinkedList() {
	clear();
	delete entry;
}

template <class T>
T LinkedList<T>::push_front(const T & value) {
	cell *_cell = new cell(entry, entry->following, value);
	_cell->following->previous = _cell;
	entry->following = _cell;
	length++;
	return value;
}

template <class T>
T LinkedList<T>::pop_front() {
	cell *_cell = entry->following;
	_cell->following->previous = entry;
	entry->following = _cell->following;
	T value = _cell->value;
	delete _cell;
	length--;
	return value;
}

template<class T>
T LinkedList<T>::push_back(const T & value) {
	cell *_cell = new cell(entry->previous, entry, value);
	_cell->previous->following = _cell;
	entry->previous = _cell;
	length++;
	return value;
}

template<class T>
T LinkedList<T>::pop_back() {
	cell *_cell = entry->previous;
	_cell->previous->following = entry;
	entry->previous = _cell->previous;
	T value = _cell->value;
	length--;
	return value;
}

template<class T>
T LinkedList<T>::peek_front() const {
	return entry->following->value;
}

template<class T>
T LinkedList<T>::peek_back() const {
	return entry->previous->value;
}

template<class T>
void LinkedList<T>::clear() {
	cell *i = entry->following,
	*j = entry->following->following;
	while (i != entry) {
		delete i;
		i = j;
		j = j->following;
	}
	length = 0;
}

template<class T>
void LinkedList<T>::dump(std::ostream & out) const {
	for (cell *i = entry->following; i != entry; i = i->following)
		out << i->value << " ";
	out << "\n";
}

template<class T>
void LinkedList<T>::dump_reversed(std::ostream & out) const {
	for (cell *i = entry->previous; i != entry; i = i->previous)
		out << i->value << " ";
	out << "\n";
}



template<class T>
LinkedList<T>::cell::cell() {
	following = this;
	previous = this;
}


template<class T>
LinkedList<T>::cell::cell(cell * prev, cell * foll, const T & value) {
	this->following = foll;
	this->previous = prev;
	this->value = value;
}
