#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

//for shapeNode
bool groupNameExists(string name) {
  GroupNode* ptr = gList->getHead();
  while(ptr != NULL) {
    if(name == ptr->getName()) {
      return true;
    }
    ptr = ptr->getNext();
  }
  return false;
}

bool shapeNameExists(string name) {
  GroupNode* ptr = gList->getHead();
  ShapeNode* tptr = ptr->getShapeList()->getHead();
  while(tptr != NULL) {
    if(name == tptr->getShape()->getName()) {
      return true;
    }
    tptr = tptr->getNext();
  }
  return false;
}

bool shapeNameNotFound(string name) {
  GroupNode* ptr = gList->getHead();
  ShapeNode* tptr = ptr->getShapeList()->getHead();
  bool flag = true;
  while(ptr != NULL) {
    tptr = ptr->getShapeList()->getHead();
    while(tptr != NULL) {
      if(name == tptr->getShape()->getName()) {
        flag = false;
      }
      tptr = tptr->getNext();
    }
   ptr = ptr->getNext();
  }
  if(flag) {
    return true;
  }
  return false;
}

bool groupNameNotFound(string name) {
  GroupNode* ptr = gList->getHead();
  bool flag = true;
  while(ptr != NULL) {
    if(name == ptr->getName()) {
      flag = false;
    }
    ptr = ptr->getNext();
  } 
  if(flag) {
    return true;
  }
  return false;
}

bool invalidName(string name) {
  for(int i = 0; i < NUM_KEYWORDS; i++) {
    if(name == keyWordsList[i]) {
      return true;
    }
  }
  for(int j = 0; j < NUM_TYPES; j++) {
    if(name == shapeTypesList[j]) {
      return true;
    }
  }
  return false;
}

int main() {
  // Create the groups list
  gList = new GroupList();
    
  // Create the pool group and add it to the group list
  GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
  gList->insert(poolGroup);

  string line;
  string command;

  cout << "> ";         // Prompt for input
   getline(cin, line);    // Get a line from standard input

  while ( !cin.eof () ) {
  // Put the line in a linestream for parsing
  // Making a new sstream for each line so flags etc. are cleared
  stringstream lineStream (line);
    
  // Read from string stream into the command
  // The only way this can fail is if the eof is encountered
  lineStream >> command;

  /*bool flag = true; //this lab doesn't have this error
  for(int i = 0; i < NUM_KEYWORDS; i++) {
    if(command == keyWordsList[i]) {
      flag = false; 
    }
  }
  if(flag) {
    cout << "Error: invalid command" << endl;
  }*/
  
  // Check for the command and act accordingly
  // ECE244 Student: Insert your code here
  string shapeName = "", t  = "", groupName = "", name = "";
  int x_loc = 0, x_sz = 0, y_loc = 0, y_sz = 0, angle = 0;
   
  //Shapes command -> this creates new shapes.
  if(command == keyWordsList[0]) {
    lineStream >> shapeName >> t >> x_loc >> y_loc >> x_sz >> y_sz;
    if(invalidName(shapeName)){
      cout << "error: invalid name" << endl;
    }
    else if(shapeNameExists(shapeName)) {
      cout << "error: name " << shapeName << " exists" << endl;
    }
    else if(groupNameExists(shapeName)) {
      cout << "error: name " << shapeName << " exists" << endl;
    }
    //other erros needed?
    else {
    Shape* shape = new Shape(shapeName, t, x_loc, y_loc, x_sz, y_sz);
    ShapeNode* shapenode = new ShapeNode();
    shapenode->setShape(shape); //the shapeNode has shape 
    poolGroup->getShapeList()->insert(shapenode);
    shape->draw();
    }
  }

  //Group command -> this creates new groups.
  if(command == keyWordsList[1]) {
    lineStream >> groupName;
    if(invalidName(groupName)){
      cout << "error: invalid name" << endl;
    }
    else if(shapeNameExists(groupName)) {
      cout << "error: name " << groupName << " exists" << endl;
    }
    else if(groupNameExists(groupName)) {
      cout << "error: name " << groupName << " exists" << endl;
    }
    else {
    GroupNode* group = new GroupNode(groupName); //allocates data for the groupNode.
    cout << groupName << ": " << "group" << endl;
    //adds group to gList
    gList->insert(group);
    }
  }

  //Draw command
  if(command == keyWordsList[4]) {
    cout << "drawing:" << endl;
    gList->print();
  }

  //Move command
  if(command == keyWordsList[2]) {
    lineStream >> shapeName >> groupName;
    if(invalidName(shapeName) || invalidName(groupName)){
      cout << "error: invalid name" << endl;
    }
    else if(shapeNameNotFound(shapeName)) {
      cout << "error: shape " << shapeName << " not found" << endl;
    }
    else if(groupNameNotFound(groupName)) {
      cout << "error: group " << groupName << " not found" << endl;
    }
    else {
    //Traversing      
    GroupNode* ptr = gList->getHead();
    ShapeNode* tptr = ptr->getShapeList()->getHead(); 
    //Move pointer
    GroupNode* groupMove;
    ShapeNode* shapeMove;
    while(ptr != NULL) {
      tptr = ptr->getShapeList()->getHead();
      while(tptr != NULL) {
        if(shapeName == tptr->getShape()->getName()) {
          shapeMove = ptr->getShapeList()->remove(shapeName);
          tptr->setNext(NULL);
        }
        tptr = tptr->getNext();
      }
      ptr = ptr->getNext();
    }
    
    ptr = gList->getHead();
    while(ptr != NULL) {
      if(groupName == ptr->getName()) {
        groupMove = ptr;
      }
      ptr = ptr->getNext();
    }
    groupMove->getShapeList()->insert(shapeMove);
    cout << "moved " << shapeName << " to " << groupName << endl;
    }  
  }

  //Delete command
  if(command == keyWordsList[3]) {
    lineStream >> name;
    if(invalidName(name)){
      cout << "error: invalid name" << endl;
    }
    else {
      int flag = 0;//0 means none found
      GroupNode* ptr = gList->getHead();
      ShapeNode* tptr = ptr->getShapeList()->getHead();
      GroupNode* groupFound;
      ShapeNode* shapeFound;
      //finding a shape
      while(ptr != NULL) {
        tptr = ptr->getShapeList()->getHead();
        while(tptr != NULL) {
          if(name == tptr->getShape()->getName()) {
            flag = 1; //shape is found.
            ptr->getShapeList()->remove(name);
            shapeFound = tptr;
          }
          tptr = tptr->getNext();
        }
        ptr = ptr->getNext();
      }
      
      //finding a group
      ptr = gList->getHead();
      while(ptr != NULL) {
        if(name == ptr->getName()) {
          flag = 2; //group is found.
          gList->remove(name);
          groupFound = ptr;
        }
        ptr = ptr->getNext();
      }

      //to delete a shape
      if(flag == 1) {
        delete shapeFound;
        cout << name << ": deleted " << endl;
      }
      //to delete a group
      else if(flag == 2) {
        ShapeNode* ptr = groupFound->getShapeList()->getHead();
        poolGroup->getShapeList()->insert(ptr);
        groupFound->getShapeList()->setHead(NULL);
        delete groupFound;
        cout << name << ": deleted " << endl;
      } 
      else {
        cout << "error: shape " << name << " not found" << endl;
      }
    }
  }
 
  // Once the command has been processed, prompt for the next command
  cout << "> ";          // Prompt for input
  getline(cin, line);
  command = ' ';
    
}  // End input loop until EOF.

return 0;
}

