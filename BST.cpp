//  BST.cpp
//  BinaryTreeCode
//
//  Created by Alexander Muyshondt on 8/16/17.
//  Copyright © 2017 Alexander Muyshondt. All rights reserved.

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "BST.h"

using namespace std;

/************************ Constructor ************************/
BST::BST()
{
    root = nullptr;
}

/************************ Deconstructor ************************/
BST::~BST()
{
    removeSubtree(root);
}

/************************** createLeaf **************************/
BST::node* BST::createLeaf(int key)
{
    node* n = new node;
    n->key = key;
    n->left = nullptr;
    n->right = nullptr;
    
    return n;
    
}

/*************************** addLeaf ***************************/
// Will call addLeafPrivate function from main
void BST::addLeaf(int key)
{
    addLeafPrivate(key, root);
}

/************************ addLeafPrivate ************************/
void BST::addLeafPrivate(int key, node* ptr)
{
    if(root == nullptr)
    {
        root = createLeaf(key);
    }
    // look down left ptr
    else if(key < ptr->key)
    {
        if(ptr->left != nullptr)
        {
            addLeafPrivate(key, ptr->left);
        }
        else
        {
            ptr->left = createLeaf(key);
        }
    }
    // look down right ptr
    else if(key > ptr->key)
    {
        if(ptr->right != nullptr)
        {
            addLeafPrivate(key, ptr->right);
        }
        else
        {
            ptr->right = createLeaf(key);
        }
    }
    else
    {
        cout << "The key ," << key << ", has already been added to the tree.\n";
    }
}

/*************************** printInOrder ***************************/
void BST::printInOrder()
{
    PrintInOrderPrivate(root);
}

/************************ printInOrderPrivate ************************/
void BST::PrintInOrderPrivate(node *ptr)
{
    if(root != nullptr)
    {
        if(ptr->left != nullptr)
        {
            PrintInOrderPrivate(ptr->left);
        }
        cout << ptr->key << " ";
        if(ptr->right != nullptr)
        {
            PrintInOrderPrivate(ptr->right);
        }
    }
    else
    {
        cout << "The tree is empty.\n";
    }
}

/*************************** returnNode ***************************/
BST::node* BST::returnNode(int key)
{
    return returnNodePrivate(key, root);
}

/************************ returnNodePrivate ************************/
BST::node *BST::returnNodePrivate(int key, node* ptr)
{
    if(ptr != nullptr)
    {
        if(ptr->key == key)
        {
            return ptr;
        }
        else
        {
            if(key < ptr->key)
            {
                return returnNodePrivate(key, ptr->left);
            }
            else
            {
                return returnNodePrivate(key, ptr->right);
            }
        }
    }
    else
    {
        return nullptr;
    }
}

/************************ returnRootKey ************************/
int BST::returnRootKey()
{
    if(root != nullptr)
    {
        return root->key;
    }
    else
    {
        return -1000;   // since we know number is not in the tree
    }
}

/************************ printChildren ************************/
void BST::printChildren(int key)
{
    node* ptr = returnNode(key);
    
    if(ptr != nullptr)
    {
        cout << "Parent Node = " << ptr->key << endl;
        
        // Uses a conditional bool operator
        ptr->left == nullptr ?
        cout << "Left child = null.\n" :
        cout << "Left child = " << ptr->left->key << endl;
        
        ptr->right == nullptr ?
        cout << "Right child = null.\n" :
        cout << "Right child = " << ptr->right->key << endl;
        
    }
    else
    {
        cout << "Key " << key << " is not in the tree.\n";
    }
}

/************************ findSmallest ************************/
int BST::findSmallest()
{
    return findSmallestPrivate(root);
}

/************************ findSmallestPrivate ************************/
int BST::findSmallestPrivate(node *ptr)
{
    if(root == nullptr)
    {
        cout << "The tree is empty.\n";
        return -1000;
    }
    else
    {
        if(ptr->left != nullptr)
        {
            return findSmallestPrivate(ptr->left);
        }
        else
        {
            return ptr->key;
        }
    }
}

/************************ removeNode ************************/
void BST::removeNode(int key)
{
    removeNodePrivate(key, root);
}

/************************ removeNodePrivate ************************/
void BST::removeNodePrivate(int key, node *parent)
{
    if(root != nullptr)
    {
        if(root->key == key)
        {
            removeRootMatch();
        }
        else
        {
            if(key < parent->key && parent->left != nullptr)
            {
                // boolean conditional operator
                // if true, code 1 implements, if false code 2 implements
                parent->left->key == key ?
                removeMatch(parent, parent->left, true) :         // code 1
                removeNodePrivate(key, parent->left);             // code 2
            }
            else if(key < parent->key && parent->right != nullptr)
            {
                // boolean conditional operator
                // if true, code 1 implements, if false code 2 implements
                parent->right->key == key ?
                removeMatch(parent, parent->right, false) :      // code 1
                removeNodePrivate(key, parent->right);           // code 2
            }
            else
            {
                cout << "The key " << key << " was not found in the tree.\n";
            }
        }
    }
    else
    {
        cout << "The tree is empty.\n";
    }
}

/************************ removeRootMatch ************************/
void BST::removeRootMatch()
{
    if(root != nullptr)
    {
        node* delptr = root;
        int rootKey = root->key;
        int smallestInRightSubtree;
        
        // Case 0 - 0 children
        if(root->left == nullptr && root->right == nullptr)
        {
            root = nullptr;
            delete delptr;
        }
        
        // Case 1 - 1 child
        else if(root->left == nullptr && root->right != nullptr)
        {
            root = root->right;
            delptr->right = nullptr;   //completely disconnects old root from the tree
            delete delptr;
            cout << "The root node with key " << rootKey << " was deleted.\n";
            cout << "The new root contains key " << root->key << endl;
        }
        else if(root->left != nullptr && root->right == nullptr)
        {
            root = root->left;
            delptr->left = nullptr;   //completely disconnects old root from the tree
            delete delptr;
            cout << "The root node with key " << rootKey << " was deleted.\n";
            cout << "The new root contains key " << root->key << endl;
        }
        
        // Case 2 - 2 children
        else
        {
            smallestInRightSubtree = findSmallestPrivate(root->right);
            removeNodePrivate(smallestInRightSubtree, root);
            root->key = smallestInRightSubtree;
            cout << "The root key containing " << rootKey << " was overwritten";
            cout << " with key " << root->key << endl;
        }
    }
    else
    {
        cout << "Can not remove root. The tree is empty.\n";
    }
}

/************************ removeMatch ************************/
// bool indicates relationship between parent and child node, if true
// the matching node is the left node of the parent node, if false the
// matching node is the right child of the parent node
void BST::removeMatch(node *parent, node *match, bool left)
{
    if(root != nullptr)
    {
        node* delptr;
        int matchKey = match->key;
        int smallestInRightSubtree;
        
        // Case 0 - 0 children
        if(match->left == nullptr && match->right == nullptr)
        {
            delptr = match;
            // conditional operator, if true executes code on left, if false executes code after colon
            left == true ? parent->left = nullptr : parent->right = nullptr;
            delete delptr;
            cout << "The node containing key " << matchKey << " was removed.\n";
        }
        
        // Case 1 - 1 child
        else if(match->left == nullptr && match->right != nullptr)
        {
            left == true ? parent->left = match->right : parent->right = match->right;
            match->right = nullptr;
            delptr = match;
            delete delptr;
            cout << "The node containing key " << matchKey << " was removed.\n";
        }
        else if(match->left != nullptr && match->right == nullptr)
        {
            left == true ? parent->left = match->left : parent->right = match->left;
            match->left = nullptr;
            delptr = match;
            delete delptr;
            cout << "The node containing key " << matchKey << " was removed.\n";
        }
        
        // Case 2 - 2 children
        else
        {
            smallestInRightSubtree = findSmallestPrivate(match->right);
            removeNodePrivate(smallestInRightSubtree, match);
            match->key = smallestInRightSubtree;
        }
    }
    else
    {
        cout << "Can not remove match. The tree is empty.\n";
    }
}

/************************ removeSubtree ************************/
void BST::removeSubtree(node* ptr)
{
    if(ptr != nullptr)
    {
        if(ptr->left != nullptr)
        {
            removeSubtree(ptr->left);
        }
        if(ptr->right != nullptr)
        {
            removeSubtree(ptr->right);
        }
        cout << "Deleting the node containing key " << ptr->key << endl;
        delete ptr;
    }
}
