#ifndef AVL_H
#define AVL_H
//-----------------------------------------------------------------------------
//   File: avl.h
//
//   Class: avl
//   Functions: main
//	 Inherited: bst
//-----------------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <exception>
#include <vector>
#include <cmath>
#include <string>
#include "bst.h"

using namespace std;

namespace SL_BST
{
	//-------------------------------------------------------------------------
	//   Title: AVL Tree -- Self balancing binary search tree
	//   Description: This file contains the class definition for a avl balance
	//					tree class
	//
	//   Programmer:  Scott Little
	// 
	//   Date: 6/6/2016
	//   Version: 1.00
	//
	//   Environment: Intel Xeon PC
	//      Software: MS Windows 10 for execution;
	//      Compiles under Microsoft Visual Studio 2013
	//
	//   class list:
	//
	//     Methods:
	// 
	//       inline: 
	//         operator +=; -- adds node to tree
	//		   operator +; -- adds node to tree
	//
	//       non-inline:
	//  public:
	//		   insert(T d); void
	//         insert(T d, node<T>* &cur); void
	//		   popfirst(const T& d, node<T>* np); void
	//         poplow(node<T>* &cur); T
	//         pophigh(node<T>* &cur); T
	//		   operator+=(const bst<T>& t); avl<T>&
	//         getHeightDifference(const node<T> *const nodeN)const; int
	// 
	//	private:
	//		   rotateRight(node<T> *nodeN); node<T>* 
	//		   rotateLeft(node<T> *nodeN); node<T>* 
	//		   rotateRightLeft(node<T> *nodeN); node<T>* 
	//		   rotateLeftRight(node<T> *nodeN);node<T>* 
	//		   rebalance(node<T> *&nodeN); node<T>* 
	//		   deletenode(const T& d, node<T>* &np, node<T>* &match); T
	//
	//   History Log:
	//     June 6, 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template<class T>
	class avl : public bst < T >
	{
	public:
		void insert(T d);
		void insert(T d, node<T>* &cur);
		T popfirst(const T& d, node<T>* np);
		T poplow(node<T>* &cur);
		T pophigh(node<T>* &cur);
		avl<T>& operator+=(const avl<T>& t);
		avl<T>& operator+=(const T d) { insert(d, this->root); return *this; }
		avl<T> operator+(const T d)
		{
			avl<T> temp = *this;
			temp.insert(d, temp.root); return temp;
		}

		int getHeightDifference(const node<T> *const nodeN)const;
	private:
		node<T> *rotateRight(node<T> *nodeN);
		node<T>* rotateLeft(node<T> *nodeN);
		node<T>* rotateRightLeft(node<T> *nodeN);
		node<T>* rotateLeftRight(node<T> *nodeN);
		node<T>* rebalance(node<T> *&nodeN);
		T deletenode(const T& d, node<T>* &np, node<T>* &match);
	};

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			rotateRight(node<T> *nodeN)
	//
	//		description:	rotates node right 
	// 
	//    Parameters:		const node<T> *const nodeN -- current node
	//
	//	  Returns:			node<T>* -- altered node
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateRight(node<T> *nodeN)
	{
		node<T> *x = nodeN->left;
		node<T> *y = x->left;

		nodeN->left = x->right;
		x->right = nodeN;

		x->setHeight();
		nodeN->setHeight();

		return x;
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			rotateLeft(node<T> *nodeN)
	//
	//		description:	rotates node left 
	// 
	//    Parameters:		const node<T> *const nodeN -- current node
	//
	//	  Returns:			node<T>* -- altered node
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateLeft(node<T> *nodeN)
	{
		node<T> *x = nodeN->right;
		node<T> *y = x->right;


		nodeN->right = x->left;
		x->left = nodeN;

		nodeN->setHeight();
		x->setHeight();

		return x;
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			rotateRightLeft(node<T> *nodeN)
	//
	//		description:	rotates node right to bring smaller number up, then
	//							calls rotateLeft to shift node over
	// 
	//    Parameters:		const node<T> *const nodeN -- current node
	//
	//	  Returns:			node<T>* -- altered node
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateRightLeft(node<T> *nodeN)
	{
		node<T> *x = nodeN->right;
		node<T> *y = x->left;

		nodeN->right = y;
		x->left = y->right;
		y->right = x;

		return rotateLeft(nodeN);
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			rotateLeftRight(node<T> *nodeN)
	//
	//		description:	rotates node left to bring larger number up, then 
	//							calls rotateRight to shift node over
	// 
	//    Parameters:		const node<T> *const nodeN -- current node
	//
	//	  Returns:			node<T>* -- altered node
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rotateLeftRight(node<T> *nodeN)
	{
		node<T> *x = nodeN->left;
		node<T> *y = x->right;

		nodeN->left = y;
		x->right = y->left;
		y->left = x;

		return rotateRight(nodeN);
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			rebalance(node<T> *&nodeN)
	//
	//		description:	calculates balance of left and right node
	//						determines if balancing of tree is needed
	// 
	//    Parameters:		const node<T> *const nodeN -- current node
	//
	//	  Returns:			node<T>* -- altered node
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template<class T>
	node<T>* avl<T>::rebalance(node<T> *&nodeN)
	{
		int balance = getHeightDifference(nodeN);

		if (balance > 1 && nodeN->right != nullptr &&
			getHeightDifference(nodeN->left) < 0 &&
			getHeightDifference(nodeN->right) < 0)
		{
			nodeN->left = rotateLeft(nodeN->left);
			return rotateRight(nodeN);
		}

		if (balance > 1 && getHeightDifference(nodeN->left) < 0)
			return rotateLeftRight(nodeN);

		if (balance < -1 && getHeightDifference(nodeN->right) > 0)
			return rotateRightLeft(nodeN);

		if (balance > 1)
			return rotateRight(nodeN);

		if (balance < -1)
			return rotateLeft(nodeN);

		return nodeN;
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			getHeightDifference(const node<T> *const nodeN)
	//							const
	//
	//		description:	gets the height difference of the left node minus 
	//							right node
	// 
	//    Parameters:		const node<T> *const nodeN -- current node
	//
	//	  Returns:			int -- height of node
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template<class T>
	int avl<T>::getHeightDifference(const node<T> *const nodeN)const
	{
		if (nodeN == nullptr)
			return 0;
		if (nodeN->left == nullptr && nodeN->right == nullptr)
			return 1;
		if (nodeN->left == nullptr)
			return -(nodeN->right->getHeight());
		if (nodeN->right == nullptr)
			return nodeN->left->getHeight();
		return nodeN->left->getHeight() - nodeN->right->getHeight();
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			insert(T d)
	//
	//		description:	inserts a new element into tree
	// 
	//    Parameters:		T d  -- value to be inserted
	//
	//	  Returns:			void
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	void avl<T>::insert(T d)
	{
		insert(d, this->root);
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			insert(T d, node<T>* &cur)
	//
	//		description:	inserts a new element into tree
	//						rebalances as required
	// 
	//    Parameters:		T d  -- value to be inserted
	//						node<T>* &cur -- current node
	//
	//	  Exceptions:		throws bad_alloc
	//
	//	  Returns:			void
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template<class T>
	void avl<T>::insert(T d, node<T>* &cur)
	{
		if (cur == nullptr)
		{
			cur = new node<T>(d);
			if (this->isempty())
				this->root = cur;
		}
		else
		{
			if (d < cur->value())
			{
				insert(d, cur->left);
			}
			else
			{
				insert(d, cur->right);
			}

			if (this->root != nullptr)
				this->root->setHeight();

			cur = rebalance(cur);
		}
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			operator+=(const avl<T>& t)
	//
	//		description:	overloaded += operator
	// 
	//    Parameters:		const avl<T>& t  -- tree being copied
	//
	//	  Exceptions:		throws bad_alloc
	//
	//	  Returns:			avl<T>& -- new copied tree
	//
	//    History Log:		April, 2005,  PB  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	avl<T>& avl <T>::operator+=(const avl<T>& t)
	{
		this->addtree(t.root);
		return *this;
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
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
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	T avl<T>::poplow(node<T>* &cur)
	{
		if (cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		if (cur->left == nullptr)
		{
			T temp = cur->value();
			node<T>* temptr = cur->right;
			delete cur;
			cur = temptr;
			if (this->root != nullptr)
				this->root->setHeight();
			return temp;
		}
		T temp = poplow(cur->left);
		if (cur != nullptr)
			this->root = rebalance(cur);
		return temp;
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
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
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	T avl<T>::pophigh(node<T>* &cur)
	{
		if (cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		if (cur->right == nullptr)
		{
			T temp = cur->value();
			node<T>* temptr = cur->left;
			delete cur;
			cur = temptr;
			if (this->root != nullptr)
				this->root->setHeight();
			return temp;
		}
		T temp = pophigh(cur->right);
		if (cur != nullptr)
			this->root = rebalance(cur);
		return temp;
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			popfirst(const T& d, node<T>* np)
	//
	//		description:	pops out the rightmost child of cur
	// 
	//    Parameters:		const T& d -- value being popped
	//						node<T>* &cur  -- current node
	//
	//	  Returns:			T -- value popped
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	T avl<T>::popfirst(const T& d, node<T>* np)
	{
		if (np != nullptr)
		{
			if (d == this->root->value())
			{
				if (np->left == nullptr && np->right == nullptr)
				{
					this->deltree();
					return d;
				}
				else if (np->left == nullptr)
				{
					this->root->right = this->root;
					this->root->right = nullptr;
					return d;
				}
				else if (np->right == nullptr)
				{
					this->root->left = this->root;
					this->root->left = nullptr;
					return d;
				}
			}
			node<T>* matchptr = nullptr;
			this->deletenode(d, np, matchptr);

			if (this->root != nullptr)
			{
				this->root = rebalance(this->root);
				this->root->setHeight();
			}
			return d;
		}
		return d;
	}

	//-------------------------------------------------------------------------
	//    Class:			avl
	//		method:			deletenode(const T& d, node<T>* &np, 
	//							node<T>* &match)
	//
	//		description:	recursively finds the first occurance of a data 
	//							item
	//						pre: match must be set to nullptr
	// 
	//    Parameters:		const T& d -- value being popped
	//						node<T>* &np -- current node
	//						node<T>* &match -- returns value when node found
	//
	//	  Returns:			T -- value popped
	//
	//    History Log:		June 6 2016,  SL  completed version 1.0
	//-------------------------------------------------------------------------
	template <class T>
	T avl<T>::deletenode(const T& d, node<T>* &np, node<T>* &match)
	{
		if (match != nullptr)
			return d;
		if (np != nullptr)
		{
			deletenode(d, np->left, match);
			if (d == np->value())
			{
				match = np;
				this->parentptr = &np;
				return this->popnode(np);
			}
			deletenode(d, np->right, match);
		}

		if (np != nullptr)
		{
			if (np->left != nullptr)
				np->left = rebalance(np->left);
			if (np->right != nullptr)
				np->right = rebalance(np->right);
		}
		return d;
	}
} // end SL_BST
#endif  