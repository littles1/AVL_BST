//-----------------------------------------------------------------------------
//	Function:		main()
//	Title:          main
//	Description:    run the whole thing
//	Programmer:		Scott Little
//	Date:			6/2/16
//	Version:        v1.0
//  Environment:    Intel Xeon PC
//      Software:	MS Windows 10 for execution;
//      Compiles under Microsoft Visual Studio 2013
//	
//	Returns:		EXIT_SUCCESS; if no errors
//					EXIT_FAILURE; if errors occured
//
//  History Log:	6/2/2016 SL
//      	
//-----------------------------------------------------------------------------	
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "bst.h"
#include "avl.h"
using namespace std;

//----------------------------------------------------------------------------
// Test Driver for avl, bst, and node classes 
// Compiled under MS Visual C++ 2013
// by Scott Little
// June 6, 2015
// revised June 6, 2015
//----------------------------------------------------------------------------
int main(void)
{
	using SL_BST::node;
	using SL_BST::avl;

	ostream &sout = cout;
	//ofstream sout;
	//sout.open("Test Doc.txt");

	try
	{
		avl<char> tree;
		avl<int> iTree;
		node<int>* marker = NULL;
		int n = 0;
		char c = ' ';
		
		//Test integer input
		//---------------------------------------------------------------------
		sout << "Inserts new data into tree, rebalances tree as input";
		sout << " is recieved (99 to stop): " << endl;
		while (cin >> n)
		{
			if (n == 99)
				break;
			iTree.insert(n);
			iTree.printXlevel(sout);
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;
			sout << endl;
		}
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		cin.ignore(256, '\n');
		while (n != 999)
		{
			sout << "\n Enter character to delete (999 to stop): ";
			cin >> n;
			cin.clear();
			cin.ignore(256, '\n');
			sout << endl;
			n = iTree.popfirst(n, iTree.getroot());

			iTree.printXlevel(sout);
			sout << endl;
		}
		//---------------------------------------------------------------------
		/*
		//---------------------------------------------------------------------
		//Test character input
		sout << "Inserts new data into tree, rebalances tree as input";
		sout << " is recieved" << endl;
		while (c != 't')
		{
			sout << endl << "Enter a new character: ";
			cin >> c;
			tree.insert(c);
			tree.printXlevel(sout);
		}
		sout << "tree 1:" << endl;
		sout << tree << " : " << tree.getNumberOfNodes()
			<< "nodes" << endl;
		tree.printXlevel(sout);
		//---------------------------------------------------------------------

		
		//---------------------------------------------------------------------
		sout << "Test 1: char types, insert, balance left with no child nodes"
		<< endl;
		sout << "Output: inserts nodes, balances when 2 is using left case"
		<< endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 2:  balance right with no child nodes" << endl;
		sout << "Output: inserts nodes, balances when 2 is using right case"
		<< endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 3:  balance right left with no child nodes" << endl;
		sout << "Output: inserts nodes, balances when 2 is using right left ";
		sout << "case" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 4:  balance left right with no child nodes" << endl;
		sout << "Output: inserts nodes, balances when 2 is using left right ";
		sout << "case" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 5:  balance node that isn't root" << endl;
		sout << "Output: balances with left case on a child node" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('4');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('5');
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 6: crossing orphan node left across root" << endl;
		sout << "Output: (3) detaches from parent and re-attches to (2) on ";
		sout << "opposite side of tree" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('4');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('6');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('5');
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 7: crossing orphan node right across root" << endl;
		sout << "Output: (4) detaches from parent and re-attches to (5) on ";
		sout << "opposite side of tree" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('6');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('5');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('4');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();
		
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 8: 50 nodes, 6 lines" << endl;
		sout << "Output: 50 nodes ";
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		for (int i = 1; i <= 50; i++)
			iTree.insert(i);

		iTree.printXlevel(sout);
		sout << endl;

		iTree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;
		
		sout << "Test 1: delete causing right rotation" << endl;
		sout << "Output: deletes (4) and rotates right" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('4');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.popfirst('4', tree.getroot());
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 2: delete causing left rotation" << endl;
		sout << "Output: deletes (1) and rotates left" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('4');
		tree.printXlevel(sout);
		sout << endl;

		tree.popfirst('1', tree.getroot());
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 3: delete causing right left rotation" << endl;
		sout << "Output: deletes (1) and rotates right then left" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('4');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.popfirst('1', tree.getroot());
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 4: delete causing left right rotation" << endl;
		sout << "Output: deletes (4) and rotates left then right" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		tree.insert('1');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('3');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('4');
		tree.printXlevel(sout);
		sout << endl;

		tree.insert('2');
		tree.printXlevel(sout);
		sout << endl;

		tree.popfirst('4', tree.getroot());
		tree.printXlevel(sout);
		sout << endl;

		tree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 5: int types, delete causing rotate right then left ";
		sout << "right child to left parent" << endl;
		sout << "Output: deletes (5) and rotates right and crosses (3) over"
		<< endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		iTree.insert(6);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(4);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(9);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(8);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(10);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(2);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(5);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(7);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(11);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(1);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(3);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.popfirst(5, iTree.getroot());
		iTree.printXlevel(sout);
		sout << endl;

		iTree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 6: delete causing rotate left then right, left child ";
		sout << "to right parent" << endl;
		sout << "Output: deletes (7) and rotates right and crosses (9) over"
		<< endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		iTree.insert(3);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(6);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(8);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(2);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(4);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(7);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(10);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(1);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(5);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(9);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.insert(11);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.popfirst(7, iTree.getroot());
		iTree.printXlevel(sout);
		sout << endl;

		iTree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 7: delete root with childen and grandchildren" << endl;
		sout << "Output: deletes (8) and moves largest of left side to root, ";
		sout << "no rebalance required" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		iTree.insert(8);
		iTree.insert(4);
		iTree.insert(12);
		iTree.insert(2);
		iTree.insert(6);
		iTree.insert(10);
		iTree.insert(14);
		iTree.insert(1);
		iTree.insert(3);
		iTree.insert(5);
		iTree.insert(7);
		iTree.insert(9);
		iTree.insert(11);
		iTree.insert(13);
		iTree.insert(15);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.popfirst(8, iTree.getroot());
		iTree.printXlevel(sout);
		sout << endl;

		iTree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 8: delete left root child with no other child in tree"
		<< endl;
		sout << "Output: deletes (1) and leaves only root with no children, ";
		sout << "no rebalance error" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		iTree.insert(2);
		iTree.insert(1);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.popfirst(1, iTree.getroot());
		iTree.printXlevel(sout);
		sout << endl;

		iTree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 9: delete right root child with no other child in tree"
		<< endl;
		sout << "Output: deletes (2) and leaves only root with no children, ";
		sout << "no rebalance error" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		iTree.insert(1);
		iTree.insert(2);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.popfirst(2, iTree.getroot());
		iTree.printXlevel(sout);
		sout << endl;

		iTree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		sout << "Test 10: delete root with no children"
		<< endl;
		sout << "Output: deletes tree, no height error" << endl;
		sout << "------------------------------------------------------------";
		sout << "---------" << endl;

		iTree.insert(1);
		iTree.printXlevel(sout);
		sout << endl;

		iTree.popfirst(1, iTree.getroot());
		iTree.printXlevel(sout);
		sout << endl;

		iTree.deltree();

		sout << "------------------------------------------------------------";
		sout << "---------" << endl;
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		sout << endl << endl << "Other tests: " << endl;

		iTree.insert(8);
		iTree.insert(4);
		iTree.insert(12);
		iTree.insert(2);
		iTree.insert(6);
		iTree.insert(10);
		iTree.insert(14);
		iTree.insert(1);
		iTree.insert(3);
		iTree.insert(5);
		iTree.insert(7);
		iTree.insert(9);
		iTree.insert(11);
		iTree.insert(13);
		iTree.insert(15);
		iTree.printXlevel(sout);
		sout << endl;

		//---------------------------------------------------------------------
		sout << endl << "Test overload << and print():" << endl;
		sout << "Output: uses << operator overload to print avl types, calls ";
		sout << "print() to display tree" << endl;
		sout << "Result: << is overloaded, print() prints the tree as ";
		sout  << "formatted" << endl;
		sout << "tree 1:" << endl;
		sout << tree << " : " << iTree.getNumberOfNodes()
		<< "nodes" << endl;
		tree.printXlevel(sout);
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		sout << endl << "Test overloaded =:" << endl;
		sout << "Output: copies iTree into tree2, displays iTree nodes, ";
		sout << "prints copy tree" << endl;
		sout << "Result: tree2 is direct copy of iTree" << endl;
		avl<int> tree2 = iTree;
		sout << "iTree modified: " << endl;
		iTree.popfirst(3, iTree.getroot());
		iTree.popfirst(8, iTree.getroot());
		iTree.popfirst(6, iTree.getroot());
		iTree.popfirst(10, iTree.getroot());
		iTree.popfirst(9, iTree.getroot());
		iTree.popfirst(14, iTree.getroot());
		iTree.popfirst(7, iTree.getroot());
		iTree.popfirst(11, iTree.getroot());
		iTree.printXlevel(sout);
		sout << endl << "tree 2, copy of original iTree:" << tree2
		<<iTree.getNumberOfNodes( ) << "nodes" << endl;
		tree2.printXlevel( sout );
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		sout << endl << "Test overloaded +=:" << endl;
		sout << "Output: adds existing trees together into tree2" << endl;
		sout << "Result: tree2 has existing values and new values from iTree";
		sout << endl;
		tree2 += iTree;
		sout << endl << "tree 2:" << tree2
		<< tree.getNumberOfNodes( ) << "nodes" << endl;
		tree2.printXlevel( sout );
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		sout << endl << "Searches tree to find data, returns location if ";
		sout << "found:" << endl;
		sout << "Output: searches tree to find first instance of value, if ";
		sout << "found returns value, if not, report not found" << endl;
		sout << "Result: finds value and returns it, if not found, reports ";
		sout << "message" << endl;
		tree2.printXlevel(sout);
		sout << endl;
		for (int x = 0; x < 2; x++)
		{
		marker = NULL;
		if (x == 0)
		{
		sout << "Search 3:" << endl;
		n = 3;
		tree2.findfirst(n, tree2.getroot(), marker);
		}
		else
		{
		sout << "Search 500:" << endl;
		n = 500;
		tree2.findfirst(n, tree2.getroot(), marker);
		}

		//set marker to first match of n
		if(marker != NULL)
		sout << marker->value();
		else
		sout << "not found";
		sout << endl << endl;
		}
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		sout << "Test popfirst(): " << endl;
		sout << "Output: prints tree after insert, deletes first instance of ";
		sout << "that node" << endl;
		sout << "Result: adds (8) to tree, deletes first (8) it finds, which ";
		sout << "in this case is the root" << endl;
		n = 8;
		tree2.insert( n );
		tree2.printXlevel( sout );
		marker = tree2.getroot( );
		sout << "popfirst(): " << tree2.popfirst( n, marker ) << endl;
		sout << "<" << n << ">  " << tree2 << endl;
		tree2.printXlevel( sout );
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		sout << "Test popnode(): " << endl;
		sout << "Output: sets marker to root (8), pops (8) to bring up ";
		sout << "largest left side value into root" << endl;
		sout << "Result: pops (8), (7) is new root" << endl;
		tree2.printXlevel( sout );
		marker = tree2.getroot( );
		sout << "popnode(): " << tree2.popnode( marker ) << endl;
		tree2.printXlevel( sout );
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		tree2.deltree();
		tree2.insert(1);
		tree2.insert(2);
		tree2.insert(3);
		tree2.insert(4);

		sout << "Test poplow(): " << endl;
		sout << "Output: pops out leftmost child of cur. In this example, (1)";
		sout << " is leftmost" << endl;
		sout << "Result: pops (1) from tree" << endl;
		tree2.printXlevel(sout);
		marker = tree2.getroot();
		sout << "poplow(): " << tree2.poplow(marker) << endl;
		tree2.printXlevel(sout);
		sout << endl;
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		tree2.deltree();
		tree2.insert(4);
		tree2.insert(3);
		tree2.insert(2);
		tree2.insert(1);

		sout << "Test pophigh(): " << endl;
		sout << "Output: pops out rightmost child of cur. In this example, ";
		sout << "(4) is rightmost" << endl;
		sout << "Result: pops (4) from tree" << endl;
		tree2.printXlevel(sout);
		marker = tree2.getroot();
		sout << "pophigh(): " << tree2.pophigh(marker) << endl;
		tree2.printXlevel(sout);
		sout << endl;
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		sout << "Test deltree(): " << endl;
		sout << "Output: deletes tree starting at root" << endl;
		sout << "Result: output blank tree with all nodes set to NULL" << endl;
		iTree.printXlevel(sout);
		sout << endl <<  "Call iTree.deltree()" << endl;
		iTree.deltree();  //delete first tree
		iTree.printXlevel(sout);
		sout << endl;
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		sout << "Test +=: " << endl;
		sout << "Output: add elements to tree using +=, rebalances" << endl;
		sout << "Result: adds nodes to tree then rebalances tree" << endl;
		tree2.printXlevel(sout);
		sout << endl;
		tree2 += 16;
		tree2 += 17;
		tree2 += 18;
		tree2.printXlevel(sout);
		sout << endl;
		//---------------------------------------------------------------------

		//---------------------------------------------------------------------
		sout << "Test +: " << endl;
		sout << "Output: add elements to tree using +, rebalances" << endl;
		sout << "Result: adds nodes to tree then rebalances tree" << endl;
		tree2.printXlevel(sout);
		sout << endl;
		tree2 = tree2 + 19;
		tree2 = tree2 + 20;
		tree2 = tree2 + 21;
		tree2.printXlevel(sout);
		sout << endl;
		//---------------------------------------------------------------------
		*/

		//---------------------------------------------------------------------
		iTree.deltree();
		tree.deltree();
		//tree2.deltree();
		//---------------------------------------------------------------------
	}
	catch (exception e)
	{
		sout << "Exception: " << e.what() << endl;
		sout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch (...)
	{
		sout << "Unknown Exception: " << endl;
		sout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	sout << "press \"Enter\" to continue" << endl;
	cin.clear();
	cin.ignore(256, '\n');
	cin.get(); // keep window open
	return EXIT_SUCCESS;
}