// Test driver

#include <string>
#include <cctype>
#include <cstring>
#include "TreeType.h"
#include<iostream>
using namespace std;
TreeType makeTree(int arr[], int size);
int main()
{
  string command;        // operation to be executed
  
  int item;
  TreeType tree;
  bool found;
  ifstream inFile;
  inFile.open("input.txt");
  inFile >> command;
  cout << "Project completed by Sam Wolfe and Dillon Loubser" <<endl;
  while (command != "Quit")
    {

      //1
      if (command == "PutItem")
	{
	  //cout << "Enter Item to be inserted in the tree  ";
	  inFile >> item;
	  tree.PutItem(item);
	  cout << item;
	  cout << " is inserted" << endl;
	}
      //2
      else if (command == "DeleteItem")
	{
	  inFile >> item;
	  tree.DeleteItem(item);
	}
      //3
      else if (command == "GetItem")
	{
	  inFile >> item;
	  item = tree.GetItem(item, found);
	  if (found)
	    cout << item << " found in tree." << endl;
	  else cout << item << " is not in tree." << endl;
	}
      //4
      else if (command == "GetLength")
	{
	  cout << "Calling GetLength\n";
	  cout << "Number of nodes is " << tree.GetLength() << endl;
	}
      //5
      else if (command == "IsEmpty")
	if (tree.IsEmpty())
	  cout << "Tree is empty." << endl;
	else cout << "Tree is not empty." << endl;
      //6
      else if (command == "IsFull")
	if (tree.IsFull())
	  cout << "Tree is full." << endl;
	else cout << "Tree is not full." << endl;
      //7
      else if (command == "Print")
	{
	  cout << "Printing the tree...InOrder Traversal\n";
	  tree.Print();
	  cout << endl;
	}
      //8
      else if (command == "PreOrderPrint")
	{
	  cout << "PreOrder Print:\n";
	  tree.PreOrderPrint();
	}
      //9
      else if (command == "PostOrderPrint")
	{
	  cout << "PostOrder Print:\n";
	  tree.PostOrderPrint();
	}
      //10
      else if (command == "LevelOrderPrint")
	{
	  cout << "LevelOrder Print:\n";
	  tree.LevelOrderPrint();
	}
      //11
      else if (command == "MakeEmpty")
	{
	  tree.MakeEmpty();
	  std::cout << "Tree has been made empty." << endl;
	}

      //12
      else if (command == "GetSuccessor")
	{
	  inFile >> item;
	  cout << "Logical successor of "<<item<< " is: ";
	  int val = tree.GetSuccessor(item);
	  if(val == -9999)
	    cout << "NULL\n" << val <<endl;
	  else if(val == 9999)
	    cout <<" Item is not in the tree." <<endl;
	  else
	    cout <<val <<endl;
	}
      //13
      else if (command == "PrintAncestorsOf")
	{
	  inFile >> item;
	  cout << "testing Ancestors of " << item << endl;
	  tree.PrintAncestors(item);
	}
      //14
      else if (command == "MirrorImage")
	{
	  cout << "Testing Mirror Image\n";
	  tree.MakeEmpty();
	  tree.PutItem(10);
	  tree.PutItem(13);
	  tree.PutItem(5);
	  tree.PutItem(4);
	  tree.PutItem(7);
	  tree.PutItem(12);
	  tree.PutItem(20);
	  cout << "\nOriginal Tree before mirroring:\n";
	  tree.LevelOrderPrint();
	  TreeType mirrorOftree;
	  tree.mirrorImage(mirrorOftree);
	  cout<< "Original Tree After Mirroring:\n";
	  tree.LevelOrderPrint();
	  cout<< "Mirror Image:\n";
	  mirrorOftree.LevelOrderPrint();
	}
	 
      //15
      else if (command == "MakeTree")
	{
	  
	  int array[100], length;
	  inFile >> length;
	  for (int i = 0; i < length; i++)
	    inFile >> array[i];
	  TreeType balancedTree=makeTree(array, length);
	  cout << "balancedTree.LevelOrderPrint()"<<endl;
	  balancedTree.LevelOrderPrint();
	}
      else
	cout << "Undefined Command!" << command<<endl;
      inFile >> command;
    }
  cout << "Testing completed."  << endl;
 

  return 0;
}

void buildTree(TreeType& bt,int arr[],int start, int end);
// implement this function
// you may define and call helper functions.
// The helper function could be an iterative or a recursive function.
TreeType makeTree(int arr[], int size)
{
  TreeType balancedTree;
  buildTree(balancedTree,arr,0,(size-1));
  balancedTree.LevelOrderPrint();
  return balancedTree;
}

void buildTree(TreeType& bt,int arr[],int start, int end){  
  if(start<=end){
    bt.LevelOrderPrint();
    int mid = (start+end)/2;
    bt.PutItem(arr[mid]);
    buildTree(bt,arr,start,(mid-1));  
    buildTree(bt,arr,(mid+1),end);  
  }
 }



