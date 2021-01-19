#include <iostream>
#include "ShapeNode.h"
using namespace std;

/*private:
Shape* myShape; stores the characterstics of shape
ShapeNode* next; points to the next shape node*/

ShapeNode::ShapeNode() {
  myShape = NULL;
  next = NULL; //THIS WASN'T HERE BEFORE
} // sets myShape and next to nullptr

ShapeNode::~ShapeNode() {
  delete myShape;
} // deletes the shape pointed to by myShape

Shape* ShapeNode::getShape() const {
  return myShape;
} // returns myShape

void ShapeNode::setShape(Shape* ptr) {
  myShape = ptr;
} // sets myShape to ptr

ShapeNode* ShapeNode::getNext() const {
  return next;
} // returns next

void ShapeNode::setNext(ShapeNode* ptr){
  next = ptr;
} // sets next to ptr

void ShapeNode::print() const {
  myShape->draw(); 
} // prints the ShapeNode