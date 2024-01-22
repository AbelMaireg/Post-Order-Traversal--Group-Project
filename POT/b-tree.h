#pragma once

extern "C" {
	size_t write(int fd, const void* buf, size_t count);
}

template<typename T>
class BTreeNode
{
public:
	T* m_data;
	BTreeNode* parent;
	BTreeNode* leftChild;
	BTreeNode* rightChild;

	BTreeNode(T* data = nullptr, BTreeNode* parent = nullptr, BTreeNode* leftChild = nullptr, BTreeNode* rightChild = nullptr)
		: m_data(data), parent(parent), leftChild(leftChild), rightChild(rightChild)
	{}
};

template<typename T>
class BTree
{
private:
	using data_t = typename T;
	using ref_data_t = data_t&;
	using rref_data_t = data_t&&;
	using ptr_data_t = data_t*;

	using val_t = typename BTreeNode<T>;
	using ref_t = val_t&;
	using rref_t = val_t&&;
	using ptr_t = val_t*;

private:
	ptr_t m_root;

public:
	BTree(rref_data_t data) : m_root(new val_t(&data))
	{}

	class Iterator
	{
	private:
		ptr_t m_ptr;

	public:
		Iterator() : m_ptr(m_root)
		{}

		Iterator(ptr_t ptr) : m_ptr(ptr)
		{}

		Iterator(Iterator&& it) : m_ptr(Iterator.m_ptr)
		{}

		bool isRoot()
		{
			return m_ptr->parent != nullptr ? false : true;
		}

		bool isLeft()
		{
			return isRoot() ? false : m_ptr->parent->leftChild == m_ptr;
		}

		bool isRight()
		{
			return isRoot() ? false : m_ptr->parent->rightChild == m_ptr;
		}

		bool hasLeft()
		{
			return m_ptr->leftChild != nullptr;
		}

		bool hasRight()
		{
			return m_ptr->rightChild != nullptr;
		}

		bool hasChild()
		{
			return hasLeft() || hasRight();
		}

		bool hasParent()
		{
			return m_ptr->parent != nullptr;
		}

		bool hasLeftBro()
		{
			return !hasParent() ? false : isLeft() ? false : m_ptr->parent->leftChild == nullptr ? false : true;
		}

		bool hasRightBro()
		{
			return !hasParent() ? false : isRight() ? false : m_ptr->parent->rightChild == nullptr ? false : true;
		}

		Iterator& parent()
		{
			if (hasParent())
				m_ptr = m_ptr->parent;

			return *this;
		}

		Iterator& left()
		{
			if (hasLeft())
				m_ptr = m_ptr->leftChild;

			return *this;
		}

		Iterator& right()
		{
			if (hasRight())
				m_ptr = m_ptr->rightChild;

			return *this;
		}

		Iterator& mostParent()
		{
			while (hasParent())
			{
				m_ptr = m_ptr->parent;
			}

			return *this;
		}

		Iterator& mostLeft()
		{
			while (hasLeft())
			{
				left();
			}

			return *this;
		}

		Iterator& mostRight()
		{
			while (hasRight())
			{
				right();
			}

			return *this;
		}

		void setL(rref_data_t data) // set new left node
		{
			if (m_ptr->leftChild != nullptr)
			{
				return;
			}
			ptr_t node = new val_t(&data, m_ptr);
			m_ptr->leftChild = node;
		}

		void setR(rref_data_t data) // set new right node
		{
			if (m_ptr->rightChild != nullptr)
			{
				return;
			}
			ptr_t node = new val_t(&data, m_ptr);
			m_ptr->rightChild = node;
		}

		void log()
		{
			write(1, (m_ptr->m_data), sizeof(data_t));
		}

		Iterator& postOT() // Post-Order Traversal Incrementally
		{
			if (isLeft())
			{
				if (hasRightBro())
				{
					parent();
					right();
					mostLeft();
				}

				else
				{
					parent();
				}
			}

			else if (isRight())
			{
				parent();
			}

			else if (isRoot())
			{
				right();
				mostLeft();
			}

			return *this;
		}

		void print_postOT() // Post-Order Traversal
		{
			if (hasLeft()) {
				Iterator it1(m_ptr);
				it1.left();
				it1.print_postOT();
			}

			if (hasLeft()) {
				Iterator it1(m_ptr);
				it1.right();
				it1.print_postOT();
			}

			log();
		}
	};
	
	Iterator root()
	{
		return Iterator(m_root);
	}
};