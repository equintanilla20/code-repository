/**
 	Ezekiel Quintanilla - Data Structures & Algorithms
 **/

#include <memory>
#include <iostream>
#include <random>
#include <list>
#include "BinarySearchTree.h"

void display(int&);

int main() {
    
    // Declare veriables and create tree object
    int forRemoval;
    int forInsertion;
    BinarySearchTree<int>* testTree;
    testTree = new BinarySearchTree<int>();
    
    // Randomize!
    std::random_device rd;                         // Grab random number from OS
    std::mt19937 eng(rd());                        // Seed the number generator
    std::uniform_int_distribution<> distr(1, 100); // Define the range
    
    for (int i = 0; i < 21; i++) {
        forInsertion = distr(eng);
        std::cout << "Inserting: " << forInsertion << std::endl;
        testTree->add(forInsertion);
        if (i == 0) {
            forRemoval = forInsertion;
        }
    }
    
    std::cout << "\nDisplaying tree" << std::endl;
    testTree->inorderTraverse(display);
    
    // Remove the integer that was first added to the list
    std::cout << std::endl << "Removing: " << forRemoval << std::endl;
    testTree->remove(forRemoval);
    
    // Display the list minus the first integer
    std::cout << "\nDisplaying the new tree:" << std::endl;
    testTree->inorderTraverse(display);
    

    return 0;
} // End main

// Display function
void display(int& anItem) {
   std::cout << "Displaying item - " << anItem << std::endl;
}  // end display