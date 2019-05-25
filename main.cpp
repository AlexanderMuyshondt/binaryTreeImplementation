//  main.cpp
//  BinaryTreeCode
//
//  Created by Alexander Muyshondt on 8/16/17.
//  Copyright © 2017 Alexander Muyshondt. All rights reserved.
//
//  Binary Tree Program: Example using pauls programming
//  Source: https://www.youtube.com/watch?v=3FPjmO3-6IY

#include <iostream>
#include <cstdlib>
#include "BST.h"

using namespace std;

int main()
{
    int TreeKeys[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
    BST myTree;
    int input = 0;
    
    cout << "Printing the tree in order BEFORE adding numbers.\n";
    myTree.printInOrder();
    
    for(int i = 0; i < 16; i++)
    {
        myTree.addLeaf(TreeKeys[i]);
    }
    
    cout << "Printing the tree in order AFTER adding numbers.\n";
    myTree.printInOrder();
    cout << endl << endl;
    
    /* myTree.printChildren(myTree.returnRootKey());

    // Prints parent nodes and children nodes
    for(int i = 0; i < 16; i++)
    {
        myTree.printChildren(TreeKeys[i]);
        cout << endl;
    }
    */
    
    cout << "The smallest value in the tree is " << myTree.findSmallest() << endl;
    
    cout << "Enter a key value to delete. Enter -1 to stop the process.\n";
    
    while(input != -1)
    {
        cout << "Delete Node: ";
        cin  >> input;
        if(input != -1)
        {
            cout << endl;
            myTree.removeNode(input);
            myTree.printInOrder();
            cout << endl;
        }
    }
    
    return 0;
}
