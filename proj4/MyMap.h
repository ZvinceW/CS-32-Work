#ifndef MY_MAP
#define MY_MAP

#include "support.h"

// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.

template<typename KeyType, typename ValueType>
class MyMap
{
public:
	MyMap();
	~MyMap();
	void clear();
	int size() const;
	void associate(const KeyType& key, const ValueType& value);

	  // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
	}

	  // C++11 syntax for preventing copying and assignment
	MyMap(const MyMap&) = delete;
	MyMap& operator=(const MyMap&) = delete;

private:
	int m_size;
	struct Node
	{
		Node(KeyType key, ValueType value)
		{
			nodeKey = key;
			nodeValue = value;
			left = nullptr;
			right = nullptr;
		}
		KeyType nodeKey;
		ValueType nodeValue;
		Node* left;
		Node* right;
	};
	Node* root;
	void freeTree(Node* node);
};

template<typename KeyType, typename ValueType>
inline MyMap<KeyType, ValueType>::MyMap()
{
	m_size = 0;
	root = nullptr;
}

template<typename KeyType, typename ValueType>
inline MyMap<KeyType, ValueType>::~MyMap()
{
	clear();
}

template<typename KeyType, typename ValueType>
inline void MyMap<KeyType, ValueType>::clear()
{
	freeTree(root);
	m_size = 0;
	root = nullptr;
}

template<typename KeyType, typename ValueType>
inline int MyMap<KeyType, ValueType>::size() const
{
	return m_size;
}

template<typename KeyType, typename ValueType>
inline void MyMap<KeyType, ValueType>::associate(const KeyType & key, const ValueType & value)
{
	Node* current = root;
	if (current == nullptr)
	{
		Node* insert = new Node(key, value);
		m_size++;
		root = insert;
		return;
	}
	else
	{
		while (current != nullptr)
		{
			if (current->nodeKey == key) //if we found the key, simply replace the nodeValue
			{
				current->nodeValue = value;
				return;
			}
			else if (key < current->nodeKey)
			{
				if (current->left == nullptr) //if the left branch doesnt exist, get ready to attach new branch
				{
					Node* insert = new Node(key, value);
					m_size++; //increase the size whenever a new node is created
					current->left = insert;
					return;
				}
				else //if the branch is there, follow that branch
				{
					current = current->left; 
				}
			}
			else
			{
				if (current->right == nullptr) //if the right branch doesnt exist, get read to attach new branch
				{
					Node* insert = new Node(key, value);
					m_size++; //increase the size whenever a new node is created
					current->right = insert;
					return;
				}
				else //if the branch is there, follow the branch
				{
					current = current->right;
				}
			}
		}
	
	}
}

template<typename KeyType, typename ValueType>
inline const ValueType * MyMap<KeyType, ValueType>::find(const KeyType & key) const
{
	Node* current = root;
	while (current != nullptr) //keeps looping while we dont hit a nullptr
	{
		if (current->nodeKey == key) //if we found the key return pointer to current node's value
		{
			return &(current->nodeValue);
		}
		else if (key < current->nodeKey) //if the key is less than the current key go to the left branch
		{
			current = current->left;
		}
		else //if the key is more than the current key go to the right branch
		{
			current = current->right;
		}
	}
	return nullptr; //return nullptr if we failed to find the key (current == nullptr)	}
}

template<typename KeyType, typename ValueType>
inline void MyMap<KeyType, ValueType>::freeTree(Node * node)
{
	if (node == nullptr)
		return;
	freeTree(node->left);
	freeTree(node->right);
	delete node;
}

#endif // 



