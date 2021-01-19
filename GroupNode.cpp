#include <iostream>
#include "GroupNode.h"
using namespace std;

/*string name;                           
ShapeList* myShapeList;                
GroupNode* next;  */                    
    
GroupNode::GroupNode(string n) {
  name = n;
  myShapeList = new ShapeList(); //allocates data already fo the ShapeList
  next = NULL;
}             
// sets group name to n and makes myShapeList point to a new ShapeList; sets next to nullptr

GroupNode::~GroupNode() {
  delete myShapeList; 
} // deletes the myShapeList list. 
//By deleting ptr, you delete what the pointer is pointing to. 

string GroupNode::getName() const {
  return name;
} // returns group name

ShapeList* GroupNode::getShapeList() const {
  return myShapeList;
} // returns myShapeList

void GroupNode::setShapeList(ShapeList* ptr) {
  myShapeList = ptr;
} // sets myShapeList to ptr

GroupNode* GroupNode::getNext() const {
  return next;
} // returns next

void GroupNode::setNext(GroupNode* ptr) {
  next = ptr;
} // sets next to ptr

void GroupNode::print() const {
  myShapeList->print(); //prints the ShapeList in a GroupNode
} // prints the GroupNode





