#ifndef BST_H
#define BST_H
//-----------------------------------------------------------------------------
//   File: bst.h
//
//	 Class: node
//   Class: bst
//   Functions: main
//-----------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <exception>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

namespace SL_BST
{
	// CLASS DEFINITIONS 
	//-------------------------------------------------------------------------
	//   Title: node class
	//   Description: Defines a node used in bst 
	//
	//   Programmer:  Paul Bladek
	// 
	//   Date: December, 2000
	//   Version: 1.00
	//
	//   Environment: Intel Xeon PC
	//      Software: MS Windows 10 for execution;
	//      Compiled under MS Visual C++.Net 2010
	//
	//     Methods:
	// 
	//       inline: 
	//         T value()const; accessor for m_data
	//	       operator T()const; cast to data type
	//		   void setdata(T d); sets data to value
	//         int getHeight()const; returns m_height
	//
	//       non-inline:
	//  public:
	//		   node(T d = 1); constructor
	//         node(const node<T>& n); copy constructor
	//         operator=(const node<T>& n); node<T>& 
	//         setHeight(); int 
	//		
	//		Members:
	//			
	//	private:
	//         m_data; T: holds current value of node
	//         m_height; int: largest amount of children, grandchildren etc. on 
	//																either side
	//	public: 
	//		   left; node<T>*: left child of parent node
	///		   right; node<T>*: right child of parent node
	//
	//   History Log:
	//     April, 2005,	  PB
	//     May, 2008,	  PB
	//	   May, 2010,     PB
	//-------------------------------------------------------------------------
	template<class T>
	//-------------------------------------------------------------------------
	// BST NODE
	// REQUIRES Type T be able convert from int & have < & == defined
	//-------------------------------------------------------------------------
	class node
	{
	public:
		node(T d = 1) :m_data(d), m_height(1), left(nullptr), right(nullptr) 
			{ }
		node(const node<T>& n); // Copy Constructor
		node<T>& operator=(const node<T>& n);
		T value()const { return m_data; }    // Accessor
		operator T()const { return m_data; }  // cast to data type
		void setdata(T d) { m_data = d; }
		int getHeight()const { return m_height; }
		int setHeight();
	private:
		T m_data;
		int m_height;
	public:  // to freely use these
		node<T>* left;
		node<T>* right;
	};

	//-------------------------------------------------------------------------
	//    Class:			node
	//		method:			node(const node<T>& n)
	//
	//		description:	copy constructor
	// 
	//    Parameters:		const node<T>& n  -- node being copied
	//
	//	  Exceptions:		throws bad_alloc
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	node<T>::node(const node<T>& n)
		:m_data(n.m_data), m_height(n.getHeight()), left(nullptr), 
		 right(nullptr)
	{
		if (n.left != nullptr)
			left = new node<T>(*(n.left));
		if (n.right != nullptr)
			right = new node<T>(*(n.right));
	}

	//-------------------------------------------------------------------------
	//    Class:			node
	//		method:			operator=(const node<T>& n)
	//
	//		description:	overloaded = operator
	// 
	//    Parameters:		const node<T>& n  -- node being copied
	//
	//	  Exceptions:		throws bad_alloc
	//
	//	  Returns:			node<T>& -- copy of tree
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	node<T>& node<T>::operator=(const node<T>& n)  // overloaded =
	{
		if (this != &n)
		{
			m_data = n.m_data;
			m_height = n.getHeight();
			if (n.left != nullptr)
				left = new node<T>(*(n.left));
			else
				left = nullptr;
			if (n.right != nullptr)
				right = new node<T>(*(n.right));
			else
				right = nullptr;
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	//    Class:			node
	//		method:			setHeight()
	//
	//		description:	recursively sets the Height of the node
	// 
	//	  Returns:			int -- new height of node
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	int node<T>::setHeight()
	{
		int lHeight = 0;
		int rHeight = 0;
		m_height = 1;

		if (left != nullptr)
			lHeight = left->setHeight();
		if (right != nullptr)
			rHeight = right->setHeight();
		return (m_height += (lHeight > rHeight) ? lHeight : rHeight);
	}

	//-------------------------------------------------------------------------
	//   Title: binary search tree class
	//   Description: This file contains the class definition for binary search
	//				  tree class
	//
	//   Programmer:  Paul Bladek
	// 
	//   Date: December, 2000
	//   Version: 1.00
	//
	//   Environment: Intel Xeon PC
	//      Software: MS Windows 10 for execution;
	//      Compiled under MS Visual C++.Net 2010
	//
	//     Methods:
	// 
	//       inline: 
	//         bst(const bst<T>& t); constructor to add new node to tree
	//	       node<T>* &getroot(); get the root of the tree
	//		   bool isempty()const; if root is null the tree is empty
	//         bst<T>& operator+=(const T d); adds node to tree
	//         bst<T> operator+(const T d); addition operator adds node to tree
	//		   void deltree(); deletes current tree
	//		   void print(ostream& out)const; prints node values of tree
	//		   void printXlevel(ostream& out)const; prints formatted tree
	//         int getHeight()const; gets height of node
	//		   void setHeight(); sets height tree
	//		   ~bst(); destructor of bst class
	//
	//       non-inline:
	//  public:
	//		   bst()
	//         operator=(const bst<T>& t); bst<T>& 
	//         operator+=(const bst<T>& t); bst<T>& 
	//         findfirst(const T& d, node<T>* &np, node<T>* &match); void
	//		   insert(T d); void
	//		   print(node<T>* cur, ostream& out)const; void
	//		   printXlevel(node<T>* cur, ostream& out) const; void
	//		   popnode(node<T>* &cur); T
	//         poplow(node<T>* &cur); T
	//         pophigh(node<T>* &cur); T
	//         popfirst(const T& d, node<T>* np); T
	//		   getNumberOfNodes()const; int
	//		   getNumberOfNodes(node<T>* np)const; int
	//
	//  protected:
	//
	//		   setLevel(node<T>* cur, vector<T>& levelVector, int level2print,
	//					int position = 0) const; void
	//		   insert(T d, node<T>* &cur); void
	//		   addtree(const node<T>* np); void
	//
	//  private: 
	//
	//		   deltree(node<T>* &cur); void
	//
	//		Members:
	//			
	//		   root; node<T>*: root of tree
	//		   parentptr; node<T>**: holding pointer needed by some functions
	//
	//	private:
	//
	//         void deltree(node<T>* &cur);
	//
	//   History Log:
	//     April, 2005,	  PB
	//     May, 2008,	  PB
	//	   May, 2010,     PB
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	// Binary Search Tree -- Basic Implementation
	//-------------------------------------------------------------------------
	template <class T>
	class bst
	{
	public:
		bst() :root(nullptr), parentptr(&root) { }
		bst(const bst<T>& t) :root(nullptr), parentptr(&root)
		{
			if (t.root != nullptr) root = new node<T>(*(t.root));
		}

		node<T>* &getroot() { return root; }

		bool isempty()const { return (root == nullptr); }

		bst<T>& operator=(const bst<T>& t);
		bst<T>& operator+=(const bst<T>& t);
		bst<T>& operator+=(const T d) { insert(d, root); return *this; }
		bst<T> operator+(const T d)
		{
			bst<T> temp = *this; temp.insert(d, temp.root); return temp;
		}

		void findfirst(const T& d, node<T>* &np, node<T>* &match);
		void insert(T d);
		void deltree() { deltree(root); }
		void print(ostream& out)const { print(root, out); }
		void print(node<T>* cur, ostream& out)const;
		void printXlevel(ostream& out)const { printXlevel(root, out); }
		void printXlevel(node<T>* cur, ostream& out) const;
		T popnode(node<T>* &cur);
		T poplow(node<T>* &cur);
		T pophigh(node<T>* &cur);
		T popfirst(const T& d, node<T>* np);
		int getHeight()const
		{
			if (isempty()) return 0; return root->getHeight();
		}
		void setHeight() { if (root != nullptr) root->setHeight(); }
		int getNumberOfNodes()const;
		int getNumberOfNodes(node<T>* np)const;
		~bst() { deltree(root); }
	protected:
		void setLevel(node<T>* cur, vector<T>& levelVector, int level2print,
			int position = 0) const;
		void insert(T d, node<T>* &cur);
		node<T>* root; // root of this tree
		node<T>** parentptr; // holding pointer needed by some functions

		void addtree(const node<T>* np); // used by +
	private:
		void deltree(node<T>* &cur);
	};

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			operator=(const bst<T>& t)
	//
	//		description:	overloaded = operator
	// 
	//    Parameters:		const bst<T>& t  -- tree being copied
	//
	//	  Exceptions:		throws bad_alloc
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	bst<T>& bst<T>::operator=(const bst<T>& t)
	{
		if (this != &t)
		{
			if (!isempty())
				deltree(root);
			if (!t.isempty())
			{
				root = new node<T>(*(t.root));
			}
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			operator+=(const bst<T>& t)
	//
	//		description:	overloaded += operator
	// 
	//    Parameters:		const bst<T>& t  -- tree being copied
	//
	//	  Exceptions:		throws bad_alloc
	//
	//	  Returns:			bst<T>& -- new copied tree
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	bst<T>& bst<T>::operator+=(const bst<T>& t)
	{
		addtree(t.root);
		return *this;
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			addtree(const node<T>* np)
	//
	//		description:	recursively adds in the contents of a second tree
	// 
	//    Parameters:		const node<T>* np  -- node being copied
	//
	//	  Returns:			void
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	void bst<T>::addtree(const node<T>* np)
	{
		if (np != nullptr)
		{
			addtree(np->left);
			addtree(np->right);
			insert(np->value(), root);
		}
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			findfirst(const T& d, node<T>* &np, 
	//							node<T>* &match)
	//
	//		description:    recursively finds the first occurance of a data 
	//							item
	//						pre: match must be set to nullptr
	// 
	//    Parameters:		const T& d -- value being searched
	//						node<T>* &np -- current node being searched
	//						node<T>* &match -- matching node when found
	//
	//	  Returns:			void
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	void bst<T>::findfirst(const T& d, node<T>* &np, node<T>* &match)
	{
		if (match != nullptr)
			return;
		if (np != nullptr)
		{
			findfirst(d, np->left, match);
			if (d == np->value())
			{
				match = np;
				parentptr = &np;
				return;
			}
			findfirst(d, np->right, match);
		}
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			insert(T d)
	//
	//		description:	inserts a new element into tree
	// 
	//    Parameters:		T d  -- value to be inserted
	//
	//	  Returns:			void
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	void bst<T>::insert(T d)
	{
		insert(d, root);
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			insert(T d, node<T>* &cur)
	//
	//		description:	inserts a new element into tree
	// 
	//    Parameters:		T d  -- value to be inserted
	//						node<T>* &cur -- current node
	//
	//	  Exceptions:		throws bad_alloc
	//
	//	  Returns:			void
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	void bst<T>::insert(T d, node<T>* &cur)
	{
		if (cur == nullptr)
		{
			cur = new node<T>(d);
			if (isempty())
				root = cur;
		}
		else
		{
			if (d < cur->value())
				insert(d, cur->left);
			else
				insert(d, cur->right);
			if (root != nullptr)
				root->setHeight();
		}
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			print(node<T>* cur, ostream& out)const
	//
	//		description:	recursively prints out the tree inorder
	// 
	//    Parameters:		node<T>* cur  -- current node
	//						ostream& out -- out stream
	//
	//	  Returns:			void
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	void bst<T>::print(node<T>* cur, ostream& out)const
	{
		if (cur != nullptr)
		{
			print(cur->left, out);
			out << cur->value() << "(" << cur->getHeight() << ") ";
			print(cur->right, out);
		}
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			setLevel(node<T>* cur, vector<T>& levelVector,
	//							int level2print, int position) const
	//
	//		description:	recursuively sets levelVector to represent the 
	//							specified level 
	// 
	//    Parameters:		node<T>* cur  -- current node
	//						vector<T>& levelVector -- nodes to print
	//						int level2print -- line printing
	//						int position -- position on line
	//
	//	  Returns:			void
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	void bst<T>::setLevel(node<T>* cur, vector<T>& levelVector,
		int level2print, int position) const
	{
		static int currentLevel = -1;
		if (level2print < 0)
			return;
		if (cur != nullptr)
		{
			currentLevel++;
			if (currentLevel < level2print)
				setLevel(cur->left, levelVector, level2print, position * 2);
			if (currentLevel == level2print)
				levelVector[position] = cur->value();
			if (currentLevel < level2print)
				setLevel(cur->right, levelVector, level2print,
				position * 2 + 1);
			currentLevel--;
		}
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			printXlevel(node<T>* cur, ostream& out) const
	//
	//		description:	prints out the tree in level order
	//						pre: -1 must be able to be cast to T
	// 
	//    Parameters:		node<T>* cur  -- current node
	//						ostream& out -- out stream
	//
	//	  Returns:			void
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	void bst<T>::printXlevel(node<T>* cur, ostream& out) const
	{
		if (cur == nullptr)
			return;
		const size_t SPACER = 64;
		const T NO_NODE = static_cast<T>(-1);
		const int PRINT_MAX = 6;
		vector<vector<T>> treeVector(cur->getHeight());

		for (int i = 0; i < cur->getHeight(); i++)
		{
			out << "level " << i + 1 << ": ";
			if (i < PRINT_MAX)
			{
				int size = static_cast<int>(pow(2.0, i));
				treeVector[i] = vector<T>(size, NO_NODE);
				setLevel(cur, treeVector[i], i);
				out << string(SPACER / (2 * size), ' ');
				for (int j = 0; j < static_cast<int>(treeVector[i].size());
					j++)
				{
					if (treeVector[i][j] != NO_NODE)
						out << treeVector[i][j];
					else
						out << ' ';
					out << string(SPACER / size - 1, ' ');
				}
			}
			else
				out << "  . . .";

			out << endl;
		}
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			deltree(node<T>* &cur)
	//
	//		description:	recursively deletes out the subtree
	// 
	//    Parameters:		node<T>* &cur  -- current node
	//
	//	  Returns:			void
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	void bst<T>::deltree(node<T>* &cur)
	{
		if (cur != nullptr)
		{
			deltree(cur->left);
			deltree(cur->right);
			delete cur;
			cur = nullptr;
			if (root != nullptr)
				root->setHeight();
		}
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			popnode(node<T>* &cur)
	//
	//		description:	pops a given node
	// 
	//    Parameters:		node<T>* &cur  -- current node
	//
	//	  Returns:			T -- value popped
	//
	//	  Exceptions:		throws invalid_argument
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	T bst<T>::popnode(node<T>* &cur)
	{
		if (cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		T contents = cur->value();
		if (cur->left == nullptr && cur->right == nullptr)
		{ // no children
			delete cur;
			cur = nullptr;
		}
		else if (cur->left == nullptr)
		{ // only right child
			node<T>* temp = cur->right;
			delete cur;
			cur = temp;
		}
		else if (cur->right == nullptr)
		{ // only left child
			node<T>* temp = cur->left;
			delete cur;
			cur = temp;
		}
		else
		{ // two children
			cur->setdata(pophigh(cur->left));
			// pops rightmost node of left child and
			// places that value into the current node
		}
		if (root != nullptr)
			root->setHeight();
		return contents;
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			poplow(node<T>* &cur)
	//
	//		description:	pops out the leftmost child of cur
	// 
	//    Parameters:		node<T>* &cur  -- current node
	//
	//	  Returns:			T -- value popped
	//
	//	  Exceptions:		throws invalid_argument
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	T bst<T>::poplow(node<T>* &cur)
	{
		if (cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		if (cur->left == nullptr)
		{
			T temp = cur->value();
			node<T>* temptr = cur->right;
			delete cur;
			cur = temptr;
			if (root != nullptr)
				root->setHeight();
			return temp;
		}
		return poplow(cur->left);
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			pophigh(node<T>* &cur)
	//
	//		description:	pops out the rightmost child of cur
	// 
	//    Parameters:		node<T>* &cur  -- current node
	//
	//	  Returns:			T -- value popped
	//
	//	  Exceptions:		throws invalid_argument
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	T bst<T>::pophigh(node<T>* &cur)
	{
		if (cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		if (cur->right == nullptr)
		{
			T temp = cur->value();
			node<T>* temptr = cur->left;
			delete cur;
			cur = temptr;
			if (root != nullptr)
				root->setHeight();
			return temp;
		}
		return pophigh(cur->right);
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			popfirst(const T& d, node<T>* np)
	//
	//		description:	pops out the rightmost child of cur
	// 
	//    Parameters:		const T& d -- value being popped
	//						node<T>* &cur  -- current node
	//
	//	  Returns:			T -- value popped
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	T bst<T>::popfirst(const T& d, node<T>* np)
	{
		node<T>* matchptr = nullptr;
		findfirst(d, np, matchptr);
		if (*parentptr != nullptr)
		{
			if ((*parentptr)->value() == d)
				return popnode((*parentptr));
		}
		if (root != nullptr)
			root->setHeight();
		return 0;
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			getNumberOfNodes()const
	//
	//		description:	returns the number of nodes in the tree
	//
	//	  Returns:			int -- number of nodes in root
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	int bst<T>::getNumberOfNodes()const
	{
		return getNumberOfNodes(root);

	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			getNumberOfNodes(node<T>* np)const
	//
	//		description:	returns the number of nodes in the tree recursively
	// 
	//    Parameters:		node<T>* np  -- current node
	//
	//	  Returns:			int -- number of child nodes in node
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	int bst<T>::getNumberOfNodes(node<T>* np)const
	{
		int count = 1;
		if (np != nullptr)
		{
			count += getNumberOfNodes(np->left);
			count += getNumberOfNodes(np->right);
			return count;
		}
		return 0;
	}

	//-------------------------------------------------------------------------
	//    Class:			bst
	//		method:			operator<<(ostream& out, bst<T> tree)
	//
	//		description:	overloaded << for bst<T>
	// 
	//    Parameters:		ostream& out -- ostream variable
	//						 bst<T> tree -- tree to print
	//
	//	  Returns:			ostream -- out stream
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	ostream& operator<<(ostream& out, bst<T> tree)
	{
		tree.print(tree.getroot(), out);
		return out;
	}

} // end namespace SL_BST
#endif
