#include<iostream>
using namespace std;
#include "TreeType.h"
struct TreeNode
{
  ItemType info;
  TreeNode* left;
  TreeNode* right;
};

TreeType::TreeType()
{
  root = NULL;
}

TreeType::TreeType(const TreeType& originalTree)
{
}

TreeNode* ptrToSuccessor(TreeNode* tree);

void Destroy(TreeNode*& tree);

TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  Destroy(root);
}


bool TreeType::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNode* location;
  try
    {
      location = new TreeNode;
      delete location;
      return false;
    }
  catch(std::bad_alloc exception)
    {
      return true;
    }
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

int CountNodes(TreeNode* tree);

int TreeType::GetLength() const
// Calls recursive function CountNodes to count the 
// nodes in the tree.
{
  return CountNodes(root);
}


int CountNodes(TreeNode* tree)
// Post: returns the number of nodes in the tree.
{
  if (tree == NULL)
    return 0;
  else 
    return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

void Retrieve(TreeNode* tree, 
	      ItemType& item, bool& found);

ItemType TreeType::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}

// helper function for GetItem
void Retrieve(TreeNode* tree, 
	      ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                     // item is not found.
  else if (item < tree->info)      
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item > tree->info)
    Retrieve(tree->right, item, found);// Search right subtree.
  else
    {
      item = tree->info;                 // item is found.
      found = true;
    }
} 

void Insert(TreeNode*& tree, ItemType item);

void TreeType::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}

// helper Function for PutItem
void Insert(TreeNode*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL){// Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item < tree->info)
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
}

void DeleteNode(TreeNode*& tree);

void Delete(TreeNode*& tree, ItemType item);

void TreeType::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
  bool found = false;
  GetItem(item, found);
  if (found)
    Delete(root, item);
  else
    cout << item << " is not in tree\n";
}


void Delete(TreeNode*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item < tree->info)
    Delete(tree->left, item);   // Look in left subtree.
  else if (item > tree->info)
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}   

void GetPredecessor(TreeNode* tree, ItemType& data);

void DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
  ItemType data;
  TreeNode* tempPtr;

  tempPtr = tree;
  if (tree->left == NULL)
    {
      tree = tree->right;
      delete tempPtr;
    }
  else if (tree->right == NULL)
    {
      tree = tree->left;
      delete tempPtr;
    }
  else
    {
      //GetPredecessor(tree->left, data);
      //tree->info = data;
      //Delete(tree->left, data);  // Delete predecessor node.
      //-----new -----
      data = ptrToSuccessor(tree)->info;
      tree->info = data;
      Delete(tree->right,data);
    }
}
//Helper function for DeleteNode
void GetPredecessor(TreeNode* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}
// Helper function for Print
void inOrderTraverse(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
    {
      inOrderTraverse(tree->left);   // Print left subtree.
      cout << tree->info<<"  ";
      inOrderTraverse(tree->right);  // Print right subtree.
    }
}
//Helper Function for PreOrderPrint
void preOrderTraverse(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
    {
      cout << tree->info<<"  ";
      inOrderTraverse(tree->left);   // Print left subtree.
      inOrderTraverse(tree->right);  // Print right subtree.
    }
}

void postOrderTraverse(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
  if (tree != NULL)
    {
      inOrderTraverse(tree->left);   // Print left subtree.
      inOrderTraverse(tree->right);  // Print right subtree.
      cout << tree->info<<"  ";
    }
}

void TreeType::Print() const
// Calls recursive function inOrderTraverse to print items in the tree.
{
  inOrderTraverse(root);
}
void TreeType::PreOrderPrint()const
{// Print Preorder
    preOrderTraverse(root);
    cout <<"\n";
}
void TreeType::PostOrderPrint() const
{
  //prints postorder
  postOrderTraverse(root);
  cout <<"\n";
}
void TreeType::PrintAncestors(int value) {
  //Printsa all the ancestors of a treeNode containing value
  QueType<int> ancestors;
  TreeNode* temp = root;
  bool found = false;
  while(!found){
    if(temp->info == value){
      found = true;
    }
    else{
      if(value > temp->info){
        if(temp->right == NULL){break;}
        else{
          ancestors.Enqueue(temp->info);
          temp = temp ->right;
        }
      }
      else{
        if(temp->left == NULL){break;}
        else{
          ancestors.Enqueue(temp->info);
          temp = temp ->left;
        }
      }
    }
  }
  if(found != false){
    if(ancestors.IsEmpty()){}
    else{
      while(!ancestors.IsEmpty()){
        int item = 0;
        ancestors.Dequeue(item);
        cout << item << " ";
      }
      cout << endl;
    }
  }
}

TreeNode* find(TreeNode* tree, int value){
  //helper function for getSuccessor
  if(tree->info == value){
    return tree;
  }
  else if(tree->left == NULL && tree->right == NULL){return NULL;}
  if(value > tree->info){
    if(tree->right == NULL){return NULL;}
    else{return find(tree->right, value);}
  }
  else{
    if(tree->left == NULL){return NULL;}
    else{return find(tree->left, value);}
  }
}


int TreeType::GetSuccessor(int value) { 
  // returns the int found at the logical successor node of the value
  bool found = false;
  GetItem(value, found);
  if(!found)
    return 9999;
  else{
    TreeNode* temp = find(root, value);
    temp = ptrToSuccessor(temp);
    if(temp == NULL){
      return -9999;
    }
    else{
      return temp->info;
    }
  }
}

// helper function for Mirror Image
void mirror(TreeNode*& copy, const TreeNode* originalTree)
// Post: copy is the root of a tree that is a mirror Image of originalTree.
{// implement this function
  if(originalTree != NULL){
    copy = new TreeNode;
    copy->info = originalTree->info;
    copy->left = NULL;
    copy->right = NULL;
    mirror(copy->right, originalTree->left);
    mirror(copy->left, originalTree->right);
  }
  else{
    copy = NULL;
    return;
  }
}

//creates a mirror image of the tree
void TreeType::mirrorImage(TreeType& t)
{
  mirror(t.root, root);
  // calls the helper function mirror
}
   


void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
    {
      Destroy(tree->left);
      Destroy(tree->right);
      delete tree;
    }
}

void TreeType::MakeEmpty()
{
  Destroy(root);
  root = NULL;
}
void CopyTree(TreeNode*& copy,
	      const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate
// of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
    {
      copy = new TreeNode;
      copy->info = originalTree->info;
      CopyTree(copy->left, originalTree->left);
      CopyTree(copy->right, originalTree->right);
    }
}

void TreeType::operator= 
(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
  {
    if (&originalTree == this)
      return;             // Ignore assigning self to self
    Destroy(root);      // Deallocate existing tree nodes
    CopyTree(root, originalTree.root);
  }

}

//helper for LevelOrderPrint
int GetHeight(TreeNode* tree){
  if (tree == NULL) {
    return -1;
  }
  int left = GetHeight(tree->left);
  int right = GetHeight(tree->right);
  if (left > right)
    return left + 1;
  else 
    return right + 1;
}

//helper for LevelOrderPrint
void DisplayLevel(TreeNode* tree, int i, int& h);

//prints level order
void TreeType::LevelOrderPrint()const
{
  int h = GetHeight(root)+1;
  int height = h;
  for(int i = 1;i<=height;i++){
    DisplayLevel(root,i,h);
    cout <<"\n";
  }
}

//helper for level order
//prints each individual level
void DisplayLevel(TreeNode* tree, int i, int& h){
  if(tree == NULL){
    cout <<"-";
    return;
  }
  if (i == 1){
    string space;
    for(int j=0;j<h;j++){
      space+= " ";
    }
    cout <<space;
    h--;
    cout <<tree->info << " ";
  }
  else if (i > 1) { 
    DisplayLevel(tree->left, i-1,h); 
    DisplayLevel(tree->right, i-1,h); 
  }
}


//helper for successor
TreeNode* GetMin(TreeNode* node) { 
  TreeNode* temp = node;
  while (temp->left != NULL) { 
    temp = temp->left; 
  } 
  return temp; 
}

//returns a ptr to the successor node
TreeNode* ptrToSuccessor(TreeNode* tree){
  //if(tree->right == NULL){return NULL;}
  //return tree->right;
  if(tree!= NULL){
    if( tree->right != NULL ){
      TreeNode* min = GetMin(tree->right);
      while(min->left!=NULL){
	min =GetMin(min);
      }
      return min;
    }
    else{
      return NULL;
    }
  }
  else{
    return NULL;
  } 
}	
