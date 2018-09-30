#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_

template<typename Comparable>
class BinarySearchTree
{
private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode* left;
		BinaryNode* right;
		BinaryNode* parent;

		BinaryNode(const Comparable& theElement, BinaryNode* lt,
			BinaryNode* rt, BinaryNode* p)
			:element(theElement), left(lt), right(rt), parent(p)
		{

		}
	};
public:
	class const_iterator
	{
		friend class BinarySearchTree;
	protected:
		BinaryNode* cur;
		const BinarySearchTree* tree;

		const_iterator(BinaryNode* node, const BinarySearchTree* t) :cur(node), tree(t)
		{

		}
	public:
		const_iterator() :cur(nullptr), tree(nullptr)
		{

		}
		const Comparable& operator*()
		{
			return cur->element;
		}

		const_iterator& operator++ ()
		{
			cur = tree->successor(cur);
			return *this;
		}
		const_iterator operator++ (int)
		{
			const_iterator result;
			result.cur = cur;
			result.tree = tree;
			cur = tree->successor(cur);
			return result;
		}

		bool operator==(const const_iterator& rhs) const
		{
			if (cur == rhs.cur && tree == rhs.tree)
				return true;
			return false;
		}
		bool operator!=(const const_iterator& rhs) const
		{
			return !operator==(rhs);
		}
	};
	class iterator : public const_iterator
	{
		friend class BinarySearchTree;
	protected:
		iterator(BinaryNode* node, BinarySearchTree* t) :
			const_iterator(node, t)
		{

		}
	public:
		iterator()
		{}
		Comparable& operator*()
		{
			return const_iterator::cur->element;
		}

		const Comparable& operator*() const
		{
			return const_iterator::cur->element;
		}

		iterator& operator++()
		{
			const_iterator::cur = const_iterator::tree->successor(const_iterator::cur);
			return *this;
		}

		iterator operator++(int)
		{
			iterator result;
			result.cur = const_iterator::cur;
			result.tree = const_iterator::tree;
			const_iterator::cur = const_iterator::tree->successor(const_iterator::cur);
			return result;
		}
	};
public:
	BinarySearchTree() :mRoot(nullptr), mSize(0)
	{

	}

	BinarySearchTree(const BinarySearchTree& rhs)
	{
		mRoot = clone(rhs.mRoot);
		mSize = rhs.mSize();
	}

	~BinarySearchTree()
	{
		makeEmpty(mRoot);
		mSize = 0;
	}

	const BinarySearchTree& operator=(const BinarySearchTree& rhs)
	{
		if (this != &rhs)
		{
			makeEmpty(mRoot);
			mRoot = clone(rhs.mRoot);
			mSize = rhs.mSize;
		}
		return *this;
	}

	const Comparable& findMin() const
	{
		if (mRoot == nullptr)
			throw "tree is empty";
		BinaryNode* node = mRoot;
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node->element;
	}

	const Comparable& findMax() const
	{
		if (mRoot == nullptr)
			throw "tree is empty";
		BinaryNode* node = mRoot;
		while (node->right != nullptr)
		{
			node = node->right;
		}
		return node->element;
	}
	bool contains(const Comparable& x) const
	{
		if (mRoot == nullptr)
			throw "tree is empty";
		BinaryNode* node = mRoot;
		while (node != nullptr)
		{
			if (node->element < x)
			{
				node = node->right;
			}
			else if (node->element > x)
			{
				node = node->left;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	bool isEmpty() const
	{
		return mRoot == nullptr;
	}

	void printTree() const
	{
		printTree(mRoot);
	}

	void makeEmpty()
	{
		makeEmpty(mRoot);
		mSize = 0;
	}

	unsigned int size() const
	{
		return mSize;
	}
	void insert(const Comparable& x)
	{
		if (mRoot == nullptr)
		{
			mRoot = new BinaryNode(x, nullptr, nullptr, nullptr);
			mSize++;
			return;
		}
		else
		{
			insert(x, mRoot, nullptr);
		}
	}

	void remove(const Comparable& x)
	{
		remove(x, mRoot);
	}

	iterator begin()
	{
		BinaryNode* node = mRoot;
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return iterator(node, this);
	}
	const_iterator begin() const
	{
		BinaryNode* node = mRoot;
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return const_iterator(node, this);
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}
	const_iterator end() const
	{
		return const_iterator(nullptr, this);
	}
private:

	BinaryNode* mRoot;
	unsigned int mSize;

	void insert(const Comparable& x, BinaryNode* &node, BinaryNode* parent)
	{
		if (node == nullptr)
		{
			node = new BinaryNode(x, nullptr, nullptr, parent);
			mSize++;
			return;
		}
		if (x == node->element)
			return;
		if (x < node->element)
		{
			insert(x, node->left, node);
		}
		else
		{
			insert(x, node->right, node);
		}
	}

	void remove(const Comparable& x, BinaryNode* &node)
	{
		if (node == nullptr)
			return;
		if (x < node->element)
			remove(x, node->left);
		else if (x > node->element)
			remove(x, node->right);
		else
		{
			BinaryNode* delNode = node;
			if (node->left != nullptr && node->right != nullptr)
			{
				BinaryNode* replNode = node->right;
				while (replNode->left != nullptr)
					replNode = replNode->left;

				node->element = replNode->element;
				delNode = replNode;
				BinaryNode* parent = replNode->parent;
				replNode->parent->right == replNode ? replNode->parent->right = replNode->right :
					replNode->parent->left = replNode->right;
				replNode = replNode->right;

				if (replNode != nullptr)
				{
					replNode->parent = parent;
				}
			}
			else
			{
				BinaryNode* parent = node->parent;
				node = node->left != nullptr ? node->left : node->right;
				if (node != nullptr)
				{
					node->parent = parent;
				}
			}
			delete delNode;
			mSize--;
		}
	}

	void makeEmpty(BinaryNode* &node)
	{
		if (node == nullptr)
			return;
		makeEmpty(node->left);
		makeEmpty(node->right);
		delete node;
		node = nullptr;
	}

	void printTree(BinaryNode* node)const
	{

	}

	BinaryNode* clone(BinaryNode* node, BinaryNode* parent = nullptr) const
	{
		if (node == nullptr)
			return;

		BinaryNode* newNode = new BinaryNode(node->element, nullptr, nullptr, parent);

		BinaryNode* left = clone(node->left, newNode);
		BinaryNode* right = clone(node->right, newNode);

		newNode->left = left;
		newNode->right = right;

		return newNode;
	}

	//find the successor of node, if node has right child, then go right down
	//1 step, then go left down till the bottom; if node has not right child
	//then go left up, until tree turn to up left(if the tree never turn up left
	//it means this node has no successor)
	BinaryNode* successor(BinaryNode* node) const
	{
		if (node == nullptr)
			return nullptr;
		if (node->right != nullptr)
		{
			node = node->right;
			while (node->left != nullptr)
			{
				node = node->left;
			}
			return node;
		}

		BinaryNode* parent = node->parent;
		while (parent != nullptr && parent->right == node)
		{
			node = parent;
			parent = node->parent;
		}
		return parent;
	}

	//similiar with successor
	BinaryNode* predecessor(BinaryNode* node) const
	{
		if (node == nullptr)
			return nullptr;
		if (node->left != nullptr)
		{
			node = node->left;
			while (node->right != nullptr)
			{
				node = node->right;
			}
			return node;
		}

		BinaryNode* parent = node->parent;
		while (parent != nullptr && parent->left == node)
		{
			node = parent;
			parent = node->parent;
		}
		return parent;
	}
};
#endif
