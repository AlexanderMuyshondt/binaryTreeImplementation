//  BST.h
//  BinaryTreeCode
//
//  Created by Alexander Muyshondt on 8/16/17.
//  Copyright © 2017 Alexander Muyshondt. All rights reserved.

#ifndef BST_h
#define BST_h

class BST
{
private:
    struct node
    {
        int key;
        node *left;
        node *right;
    };
    
    node *root;
    
    void addLeafPrivate(int key, node* ptr);
    void PrintInOrderPrivate(node* ptr);
    node *returnNodePrivate(int key, node *ptr);
    int findSmallestPrivate(node *ptr);
    void removeNodePrivate(int key, node *parent);
    void removeRootMatch();
    void removeMatch(node *parent, node *match, bool left);
    node* createLeaf(int key);
    node* returnNode(int key);
    void removeSubtree(node* ptr);
    
public:
    BST();      // Constructor
    ~BST();     //Deconstructor
    void addLeaf(int key);
    void printInOrder();
    int  returnRootKey();
    void printChildren(int key);
    int  findSmallest();
    void removeNode(int key);
};

#endif /* BST_h */
