#include <iostream>
#include "GroupList.h"
using namespace std;

/*GroupNode* head;   */

GroupList::GroupList() {
  head = NULL;
} // sets head to nullptr

GroupList::~GroupList() {
  GroupNode* ptr;
  while(head != NULL) {
    ptr = head;
    head = ptr->getNext();
    delete ptr;
  }
}       
// deletes all list nodes, including all the ShapeList attached to each GroupNode
    
GroupNode* GroupList::getHead() const {
  return head;
} // returns the head pointer

void GroupList::setHead(GroupNode* ptr) {
  head = ptr;
} // sets the head pointer to ptr

void GroupList::insert(GroupNode* s) {
  if(head == NULL) { //considering if the GroupList is empty.
    head = s; 
  }
  else {
    GroupNode* ptr = head;
    while(ptr->getNext() != NULL) { //traverses the list
      ptr = ptr->getNext();
    }
    ptr->setNext(s);
    s->setNext(NULL);
  }
}   
// inserts the node pointed to by s at the end of the list

GroupNode* GroupList::remove(string name) {
if(head == NULL) return NULL; //considering the list is empty.
  GroupNode* ptr = head;
  GroupNode* copy = NULL;
  if(head->getName() == name) { //if we're trying to delete the head node
    head = head->getNext();
    ptr->setNext(NULL);
    return ptr;
  }
  while(ptr != NULL) {
    if(name == ptr->getName()) {
      break;
    }
    copy = ptr;
    ptr = ptr->getNext();
  }
  if(ptr == NULL) { //no node was found. 
    return NULL;
  }
  copy->setNext(ptr->getNext());
  ptr->setNext(NULL);
  return ptr; 
}
// removes the group with the name "name" from the list and returns a pointer to the removed GroupNode returns nullptr is name is not found on list

void GroupList::print() const {
  GroupNode* ptr = head;
  while(ptr != NULL) {
    cout << ptr->getName() << ":" << endl;
    ptr->print();
    ptr = ptr->getNext();
  }
} // prints the list, one GroupNode at a time




