#include "Sequence.h"

Sequence::Sequence() // Create an empty sequence (i.e., one whose size() is 0).	
{
	m_size = 0;
}

bool Sequence::empty() const  // Return true if the sequence is empty, otherwise false.
{
	if (m_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

int Sequence::size() const    // Return the number of items in the sequence.
{
	return m_size;
}

bool Sequence::insert(int pos, const ItemType& value)
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return true if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// (e.g., because it's implemented using a fixed-size array) and is
// full.)  Otherwise, leave the sequence unchanged and return false.
// Notice that if pos is equal to size(), the value is inserted at the
// end.
{
	if (m_size == DEFAULT_MAX_ITEMS) {
		return false;
	}
	else if (pos < 0 || pos > size()) {
		return false;
	}
	else {
		for (int i = size() - 1; i >= pos; i--) {
			m_array[i + 1] = m_array[i];
		}
		m_array[pos] = value;
		m_size++;
		return true;
	}
}

int Sequence::insert(const ItemType& value)
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
{
	//find p
	if (m_size >= DEFAULT_MAX_ITEMS) {
		return -1;
	}
	else {
		int p = size();
		for (int i = 0; i < size(); i++) {
			if (m_array[i] >= value) {
				p = i;
				break;
			}
		}
		if (p != size()) {
			for (int i = size() - 1; i >= p; i--) {
				m_array[i + 1] = m_array[i];
			}
		}
		m_size++;
		m_array[p] = value;
		return p;
	}
}

bool Sequence::erase(int pos)
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed this item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
{
	if (pos < 0 || pos >= size()) {
		return false;
	}
	else {
		for (int i = pos; i < size() - 1; i++) {
			m_array[i] = m_array[i + 1];
		}
		m_size--;
		return true;
	}
}

int Sequence::remove(const ItemType& value)
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
{
	int removed = 0;
	for (int i = 0; i < size(); i++) {
		while (m_array[i] == value) {
			if (i == size() - 1) {
				removed++;
				m_size--;
				break;
			}
			else {
				for (int j = i; j < size() - 1; j++) {
					m_array[j] = m_array[j + 1];
				}
				removed++;
				m_size--;
			}
		}
	}
	return removed;
}

bool Sequence::get(int pos, ItemType& value) const
// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.
{
	if (pos < 0 || pos >= size()) {
		return false;
	}
	else {
		value = m_array[pos];
		return true;
	}
}

bool Sequence::set(int pos, const ItemType& value)
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
{
	if (pos < 0 || pos >= size()) {
		return false;
	}
	else {
		m_array[pos] = value;
		return true;
	}
}

int Sequence::find(const ItemType& value) const
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
{
	int p = -1;
	for (int i = 0; i < size(); i++) {
		if (m_array[i] == value) {
			p = i;
			break;
		}
	}
	return p;
}

void Sequence::swap(Sequence& other)
// Exchange the contents of this sequence with the other one.
{
	int longerSize;
	if (size() > other.size()) {
		longerSize = size();
	}
	else {
		longerSize = other.size();
	}
	for (int i = 0; i < longerSize; i++) {
		ItemType temp = m_array[i];
		m_array[i] = other.m_array[i];
		other.m_array[i] = temp;
	}
	int tempSize = size();
	m_size = other.size();
	other.m_size = tempSize;
}
