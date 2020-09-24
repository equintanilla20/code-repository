/** Ezekiel Quintanilla - Data Structures & Algorithms

Link-based implementation of a binary search tree.
@file BinarySearchTree.h */
 
#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include <memory>
#include <vector>
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType> {
// use this->this->rootPtr to access the BinaryNodeTree this->rootPtr
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   // Recursively finds where the given node should be placed and
   // inserts it in a leaf at that point.
   std::shared_ptr<BinaryNode<ItemType>> placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                       std::shared_ptr<BinaryNode<ItemType>> newNodePtr);
   
   // Removes the given target value from the tree while maintaining a
   // binary search tree.
   std::shared_ptr<BinaryNode<ItemType>> removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                     const ItemType targets,
                                     bool& success) override;
   
   // Removes a given node from a tree while maintaining a
   // binary search tree.
   std::shared_ptr<BinaryNode<ItemType>> removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr);
   
   // Removes the leftmost node in the left subtree of the node
   // pointed to by nodePtr.
   // Sets inorderSuccessor to the value in this node.
   // Returns a pointer to the revised subtree.
   std::shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                            ItemType& inorderSuccessor);
   
   // Returns a pointer to the node containing the given value,
   // or nullptr if not found.
   std::shared_ptr<BinaryNode<ItemType>> findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
                                  const ItemType& target) const;
   
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   // inherits from BinaryNodeTree
   
   //------------------------------------------------------------
   // Public Methods Section.
   //------------------------------------------------------------
   void setRootData(const ItemType& newData) override;
   bool add(const ItemType& newEntry) override;
   bool remove(const ItemType& anEntry) override;
   ItemType getEntry(const ItemType& anEntry) const override;
   bool contains(const ItemType& anEntry) const override;
   
}; // end BinarySearchTree


// Recursively finds where the given node should be placed and
// inserts it in a leaf at that point.
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, std::shared_ptr<BinaryNode<ItemType>> newNodePtr) {
   //Places a given node in its proper position in a binary search tree
   if (subTreePtr == nullptr) {
      return newNodePtr;
   } else if (subTreePtr->getItem() > newNodePtr->getItem()) {
      auto tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
      subTreePtr->setLeftChildPtr(tempPtr);
   } else {
      auto tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
      subTreePtr->setRightChildPtr(tempPtr);
   }
   return subTreePtr;
} // end placeNode

// Removes the given target value from the tree while maintaining a
// binary search tree.
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& success) {
   if (subTreePtr == nullptr) {
      // not found
      success == false;
   } else if (subTreePtr->getItem() == target) {
      // found!!
      subTreePtr = removeNode(subTreePtr);
      success = true;
   } else if (subTreePtr->getItem() > target) {
      // if target is less than the tree's item, search left side of tree
      std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
      subTreePtr->setLeftChildPtr(tempPtr);
   } else {
      // target is greater than tree's item, search right side of tree
      std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
      subTreePtr->setRightChildPtr(tempPtr);
   }
   
   return subTreePtr;
} // end removeValue

// Removes a given node from a tree while maintaining a
// binary search tree.
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr) {
   if (nodePtr->isLeaf()) {
      nodePtr.reset();
      return nodePtr;
   } else if (nodePtr->getRightChildPtr() == nullptr || nodePtr->getLeftChildPtr() == nullptr) { // nodePtr->getLeftChildPtr() != nullptr && nodePtr->getRightChildPtr() == nullptr || nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() != nullptr
      if (nodePtr->getLeftChildPtr() != nullptr) {
         std::shared_ptr<BinaryNode<ItemType>> nodeToConnectPtr = nodePtr->getLeftChildPtr();
         nodePtr.reset();
         return nodeToConnectPtr;
      } else {
         std::shared_ptr<BinaryNode<ItemType>> nodeToConnectPtr = nodePtr->getRightChildPtr();
         nodePtr.reset();
         return nodeToConnectPtr;
      }
   } else {
      ItemType newNodeValue;
      std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
      nodePtr->setRightChildPtr(tempPtr);
      nodePtr->setItem(newNodeValue);
      return nodePtr;
   }
   
} // end removeNode

// Removes the leftmost node in the left subtree of the node
// pointed to by nodePtr.
// Sets inorderSuccessor to the value in this node.
// Returns a pointer to the revised subtree.
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType& inorderSuccessor) {
   if (subTreePtr->getLeftChildPtr() == nullptr) {
      inorderSuccessor = subTreePtr->getItem();
      return removeNode(subTreePtr);
   } else {
      std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
      subTreePtr->setLeftChildPtr(tempPtr);
      return subTreePtr;
   }
} // end removeLeftmostNode

// Returns a pointer to the node containing the given value,
// or nullptr if not found.
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType& target) const {
   if (treePtr == nullptr) {
      // not found here
      return treePtr;
   }
   
   if (treePtr->getItem() == target) {
      //success = true;
      return treePtr;
   } else if (treePtr->getItem() > target) {
      std::shared_ptr<BinaryNode<ItemType>> targetNodePtr = findNode(treePtr->getLeftChildPtr(), target);
      return targetNodePtr;
   }  else {
      std::shared_ptr<BinaryNode<ItemType>> targetNodePtr = findNode(treePtr->getRightChildPtr(), target);
      return targetNodePtr;
   } // end if
} // end find node

// Set Root Data
template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) {
   if (this->isEmpty())
      this->rootPtr = std::make_shared<BinaryNode<ItemType>>(newData, nullptr, nullptr);
   else
      this->rootPtr->setItem(newData);
} // end Set Root Data

// Add
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData) {
   std::shared_ptr<BinaryNode<ItemType>> newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);
   this->rootPtr = placeNode(this->rootPtr, newNodePtr);
   return true;
} // end add

// Remove
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& anEntry) {
   bool isSuccessful = false;
   this->rootPtr = removeValue(this->rootPtr, anEntry, isSuccessful);
   return isSuccessful;
} // end remove

// Get Entry
template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const {
   bool isSuccessful = false;
   auto binaryNodePtr = findNode(this->rootPtr, anEntry);
    
   if (isSuccessful)
      return binaryNodePtr->getItem();
   else
      throw NotFoundException("Entry not found in tree!");
} // end getEntry

// Contains
template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const {
   bool isSuccessful = false;
   findNode(this->rootPtr, anEntry);
   return isSuccessful;
} // end contains

#endif