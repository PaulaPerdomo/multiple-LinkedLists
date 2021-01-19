#include "ShapeList.h"
using namespace std;

/*ShapeNode* head;*/

ShapeList::ShapeList() {
  head = NULL;
} // sets head to nullptr

ShapeList::~ShapeList() {
  ShapeNode* ptr = head;
  while(head != NULL) {
    ptr = head;
    head = head->getNext();
    delete ptr;
  }
} // deletes all list nodes starting with head plus associated Shapes

ShapeNode* ShapeList::getHead() const {
  return head;
} // returns the head pointer

void ShapeList::setHead(ShapeNode* ptr) {
  head = ptr;
} // sets the head pointer to ptr

ShapeNode* ShapeList::find(string name) const {
  ShapeNode* ptr = head;
  while(ptr != NULL) {
    if(name == ptr->getShape()->getName()) {
      break;
    }
    ptr = ptr->getNext();
  }
  if(ptr == NULL) { //if node is not found, it returns null.
    return NULL;
  }
  return ptr;
} 
// finds a shape node with the specified shape name
// returns a pointer to the node if found, otherwise, returns nullptr if the node is not found

void ShapeList::insert(ShapeNode* s) {
  if(head == NULL) { //considering if the shapeList is empty.
    head = s; 
  }
  else {
    ShapeNode* ptr = head;
    while(ptr->getNext() != NULL) { //traverses the list
      ptr = ptr->getNext();
    }
    ptr->setNext(s);
    ///s->setNext(NULL);
  }
}   // inserts the node pointed to by s at the end of the list; s should never be nullptr.
//Meaning that its a pointer, pointing to nothing.

ShapeNode* ShapeList::remove(string name) {
  if(head == NULL) return NULL; //considering the list is empty.
  ShapeNode* ptr = head;
  ShapeNode* copy = NULL;
  if(head->getShape()->getName() == name) { //if we're trying to delete the head node
    head = head->getNext();
    //ptr->setNext(NULL);
    return ptr;
  }
  while(ptr != NULL) {
    if(name == ptr->getShape()->getName()) {
      break;
    }
    copy = ptr;
    ptr = ptr->getNext();
  }
  if(ptr == NULL) { //no node was found. 
    return NULL;
  }
  copy->setNext(ptr->getNext());
  //ptr->setNext(NULL);
  return ptr; 
}
// removes the node with the shape called name
// returns a pointer to the removed node or
// nullptr is a node with name does not exist

void ShapeList::print() const {
  ShapeNode* ptr = head;
  while(ptr != NULL) {
    ptr->print(); //prints the node shape.
    ptr = ptr->getNext();
  }
}// prints the list






