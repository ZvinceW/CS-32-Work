#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

typedef unsigned long ItemType;

class Sequence
{
public:
	Sequence();
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
	//int subsequence(const Sequence& seq1, const Sequence& seq2);
	//void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
	Sequence(const Sequence& other);
	void operator= (const Sequence& seq);
	~Sequence();

private:
	struct Node
	{
		ItemType value;
		Node* prev;
		Node* next;
	};
	Node* m_head;
	//Node* m_tail;
	void addToFront(ItemType value) {
		Node* n = new Node;
		n->prev = nullptr;
		n->value = value;
		if (m_head != nullptr) {
			n->next = m_head;
			m_head->prev = n;
		}
		else {
			n->next = nullptr;
		}
		m_head = n;
		m_size++;
	}
	bool getPtr(int pos, Node*& node) const {   //find the node at position pos and return true, return false if pos is out of bound
		if (pos >= m_size) {
			return false;
		}
		else {
			Node* ptr = m_head;
			int index = 0;
			while (index != pos) {
				ptr = ptr->next;
				index++;
			}
			node = ptr;
		}
	}
	int m_size;
};

void interleave(const Sequence & seq1, const Sequence & seq2, Sequence & result);
int subsequence(const Sequence & seq1, const Sequence & seq2);

#endif // !SEQUENCE_H

