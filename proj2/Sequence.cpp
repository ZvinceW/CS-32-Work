#include "Sequence.h"

Sequence::Sequence() //initialized empty sequence, size 0, head and tail point to nullptr
{
	m_size = 0;
	m_head = nullptr;
	//m_tail = nullptr;
}

bool Sequence::empty() const
{
	if (m_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

int Sequence::size() const
{
	return m_size;
}

bool Sequence::insert(int pos, const ItemType & value)
{
	if (pos < 0 || pos > m_size) //add to an empty list
	{
		return false;
	}
	else if (m_head == nullptr && pos == 0)
	{
		addToFront(value);
		return true;
	}
	else if (pos == m_size) //when pos is 1 larger than the max index, add the new node to the end of the list
	{
		Node* target = m_head;
		int counter = 0;
		Node* insert = new Node; //make the new node ready to insert
		insert->value = value;  //put value in new node
		insert->next = nullptr; //set new node's next pointer nullptr
		while (target->next != nullptr) //find the last node
		{
			target = target->next;
		}
		insert->prev = target; //connect the new node after the previously last node
		target->next = insert; //connect to previously last node before the newly created node
		m_size++;   //increase list size
		return true;
	}
	else 
	{
		int counter = 0;
		Node* target = m_head;
		Node* insert = new Node;
		insert->value = value;
		while (counter != pos)  //loop until we have iterated to the desired location
		{
			target = target->next;
			counter++;
		}
		insert->prev = target->prev;
		insert->next = target;
		if (target->prev != nullptr) {
			target->prev->next = insert;  //chain insert behind the node before target
		}
		target->prev = insert;
		if (pos == 0) {
			m_head = insert;
		}
		m_size++; //increase list size
		return true;
	}
}

int Sequence::insert(const ItemType & value)
{
	if (m_head == nullptr) //add to an empty list
	{
		addToFront(value);
		return 0;
	}
	else   //PLS SORT
	{
		Node* target = m_head;
		Node* lastNode = nullptr;   //intialized to nullptr because compiler is complaining about uninitialized pointer
		int p = m_size;
		int count = 0;
		while (target != nullptr)  
		{
			if (target->next == nullptr)
			{
				lastNode = target;   //record the end node for later step
			}
			if (value <= target->value)
			{
				p = count;
				break;
			}
			target = target->next;
			count++;
		}
		if (p < m_size)
		{
			Node* insert = new Node;
			count = 0;  //reset counter to prep for a new count loop
			target = m_head;  //reset target to the first node
			while (count != p)
			{
				target = target->next;  
				count++;
			} //target should now point to the node at position p
			if (p == 0) {
				addToFront(value);
			}
			else {
				insert->prev = target->prev;  //chain the node before target in front of insert
				insert->next = target;  //chain target behind insert
				insert->value = value;  //load in the value, ready for insertion
				if (target->prev != nullptr) {
					target->prev->next = insert;  //chain insert behind the node before target
				}
				target->prev = insert;  //chain insert in front of target
				m_size++;
			}
			return p;
		}
		else //value is bigger than everything in the list
		{
			Node* insert = new Node;
			insert->prev = lastNode;
			insert->next = nullptr;
			insert->value = value;
			lastNode->next = insert;
			m_size++;
			return p;
		}
	}
}

bool Sequence::erase(int pos)
{
	if (pos < 0 || pos >= m_size) //return false if pos is out of bound
	{
		return false;
	}
	else if (m_head == nullptr)
	{
		return false;   //return false if the list is empty
	}
	else if (pos == m_size - 1 && m_size > 1)  //when pos is the last node
	{
		Node* target = m_head;
		while (target->next != nullptr)   //find the "last" node, which has nullptr as its "next" pointer
		{
			target = target->next;
		}
		target->prev->next = nullptr; //the "next" pointer of the node before target node is set to nullptr b/c it would become the new "last " node
		delete target; //disallocate the previously "last" node
		m_size--;
		return true;
	}
	else
	{	
			int counter = 0;
			Node* target = m_head;
			while (counter != pos)
			{
				target = target->next;
				counter++;
			}
			if (pos == 0) {
				if (m_size == 1) {
					delete target;
					m_head = nullptr;
				}
				else {
					target->next->prev = nullptr;
					m_head = target->next;
					delete target;
				}
			}
			else {
				target->prev->next = target->next;  //"cutting away" the target pointer: make the "next" pointer of the node before the target node the "next" pointer of target node. 
				target->next->prev = target->prev;  //same purpose as above: make the "prev" pointer of the node after the target node the "prev" pointer of target node.
				delete target; //disallocate the node at the target position;
			}
			m_size--;
			return true;

	}
}

int Sequence::remove(const ItemType & value)
{
	Node* target = m_head;
	int counter = 0;
	int removed = 0;
	while (target != nullptr) //iterate through every node
	{
		if (target->value == value && target->prev == nullptr) {
			target = target->next;
			erase(counter);
		}
		else {
			if (target->value == value) {
				erase(counter);     //if the node's value equal the value we want to delete, call erase function on that position.		
				counter--;
				removed++;
			}
			if (target != nullptr) {
				target = target->next;
				counter++;
			}
		}
	}
	return removed;
}

bool Sequence::get(int pos, ItemType & value) const
{
	if (pos < 0 || pos >= m_size)
	{
		return false;
	}
	else if (m_head == nullptr) //if the list is empty
	{
		return false;
	}
	else if (pos == 0)
	{
		value = m_head->value;
		return true;
	}
	else
	{
		int counter = 0;
		Node* target = m_head;
		while (counter != pos) //find the node at target position
		{
			target = target->next;  
			counter++;
		} //target node is now the node at desired position
		value = target->value; //assign the stuff at target position to value
		return true;
	}
}

bool Sequence::set(int pos, const ItemType & value)
{
	if (pos < 0 || pos >= m_size)
	{
		return false;
	}
	else if (m_head == nullptr) //if the list is empty
	{
		return false;
	}
	else if (pos == 0)
	{
		m_head->value = value;
		return true;
	}
	else
	{
		int counter = 0;
		Node* target = m_head;
		while (counter != pos) //find the node at target position
		{
			target = target->next;
			counter++;
		} //target node is now the node at desired position
		target->value = value;
		return true;
	}
}

int Sequence::find(const ItemType & value) const
{
	int p = -1;
	Node* target = m_head;
	int counter = 0;
	while (target != nullptr)
	{
		if (target->value == value)
		{
			p = counter;
			break;
		}
		target = target->next;
		counter++;
	}
	return p;
}

void Sequence::swap(Sequence & other)
{
	Node* tempHead = m_head;
	int tempSize = m_size;
	m_head = other.m_head;
	m_size = other.m_size;
	other.m_head = tempHead;
	other.m_size = tempSize;
}





Sequence::Sequence(const Sequence& other)
{
	if (other.m_head == nullptr)
	{
		m_head = nullptr;
		m_size = 0;
	}
	else {
		//actual copying
		Node* target = other.m_head;      //use target to iterate through "other"
		m_size = other.m_size;
		m_head = new Node;   //allocate a new Node as the copy of head node
		m_head->prev = nullptr;    //set the prev pointer to nullptr cuz its a head node
		Node* newTarget = m_head;
		//int counter = 0;
		while (target->next != nullptr)
		{

			newTarget->value = target->value;
			newTarget->next = new Node;
			newTarget->next->prev = newTarget;
			target = target->next;
			newTarget = newTarget->next;
			//counter++;
		}
		newTarget->value = target->value; //set the end node value equal to each other;
		newTarget->next = nullptr; //set the "next" pointer of the new end node to nullptr
	}
}

void Sequence::operator= (const Sequence& seq)
{
	//deallocate existing items
	if (!empty()) {
		Node* target = m_head->next;
		while (target->next != nullptr)
		{
			delete target->prev;
			target = target->next;
		}
		delete target;
	}

	//actual copying
	Node* oldTarget = seq.m_head;      //use target to iterate through "other"
	Node* newHead = new Node;   //allocate a new Node as the copy of head node
	newHead->prev = nullptr;    //set the prev pointer to nullptr cuz its a head node
	Node* newTarget = newHead;  //
	while (oldTarget->next != nullptr)
	{

		newTarget->value = oldTarget->value;
		newTarget->next = new Node;
		newTarget->next->prev = newTarget;
		oldTarget = oldTarget->next;
		newTarget = newTarget->next;
		//counter++;
	}
	newTarget->value = oldTarget->value; //set the end node value equal to each other;
	newTarget->next = nullptr; //set the "next" pointer of the new end node to nullptr
	m_size = seq.m_size;
	m_head = newHead;
}

Sequence::~Sequence()
{
	//when list is not empty
	if (m_head != nullptr) {
		Node* target = m_head->next;
		while (target->next != nullptr)
		{
			delete target->prev;
			target = target->next;
		}
		delete target;
	}
}

void interleave(const Sequence & seq1, const Sequence & seq2, Sequence & result)
{
	if (seq1.empty())
	{
		result = seq2;
	}
	else if (seq2.empty())
	{
		result = seq1;
	}
	if (seq2.size() <= seq1.size()) //when seq2 is the shorter list, seems to work for equal length as well?
	{
		result = seq1;  //use the longer list as the "base"
		int inserted = 0;
		for (int i = 0; i < seq2.size(); i++)
		{
			ItemType value;
			seq2.get(i, value);
			result.insert(i + 1 + inserted, value);
			inserted++;
		}
	}
	else if (seq1.size() < seq2.size())
	{
		result = seq2;
		int inserted = 0;
		for (int i = 0; i < seq1.size(); i++)
		{
			ItemType value;
			seq2.get(i, value);
			result.insert(i + inserted, value);
			inserted++;
		}
	}
}

int subsequence(const Sequence & seq1, const Sequence & seq2)
{
	if (seq2.size() > seq1.size())
	{
		return -1;
	}
	else if (seq2.empty() || seq1.empty())
	{
		return -1;
	}
	else
	{
		ItemType value1;
		ItemType value2;
		seq2.get(0, value2);
		for (int i = 0; i < seq1.size(); i++)
		{
			seq1.get(i, value1);
			if (value1 == value2)
			{
				ItemType value11;
				ItemType value21;
				bool foundIt = true;
				if (seq1.size() - i - 1 < seq2.size())
				{
					return -1;
				}
				for (int j = 0; j < seq2.size(); j++)
				{
					seq1.get(i + j, value11);
					seq2.get(j, value21);
					if (value11 != value21) {
						foundIt = false;
						break;
					}
				}
				if (foundIt) {
					return i;
				}
			}
		}
		return -1;
	}
}
