//*****************************************************************************
// purpose:  Constructors/Destructors and printTo methods
//
//  author: Krunal Patel krp356
//*****************************************************************************

#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <string>

using namespace std;

// Abstract class. Base class for StringNode, IntegerNode, and FloatNode
//
// Do NOT change this class
class DataNode {
public:
    virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
    virtual ~DataNode();                   // labeling the destructor as virtual allows 
	                                       // the subclass destructors to be called
};
ostream& operator<<(ostream&, DataNode&);  // print method
// ---------------------------------------------------------------------
class StringNode : public DataNode {
public:
    string* mystring = nullptr;
    // Add constructor, destructor, and printTo methods
    StringNode(string str) {
        // vector<DataNode*> stringVector;
        mystring = new string(str);
    }
    void printTo(ostream& output_stream) {
        output_stream << "(string: " << *mystring << ") ";
    }
    ~StringNode() {
      
        cout << "Deleting DataNode:StringNode:" << *mystring << endl;
        delete mystring;
    };
};
// ---------------------------------------------------------------------
class IntegerNode : public DataNode {
public:
    int myinteger = 0;

    // Add constructor, destructor, and printTo methods
    IntegerNode(int integer) {
        myinteger = integer;
    }
    void printTo(ostream& output_stream) {
        output_stream << "(integer: " << myinteger << ") ";
    }
    ~IntegerNode() {
         cout << "Deleting DataNode:IntegerNode:" << myinteger << endl;
    }
};
// ---------------------------------------------------------------------
class FloatNode : public DataNode {
public:
    float myfloat = 0.0;
     FloatNode(float float_num) {
        myfloat = float_num;
    }
    void printTo(ostream& output_stream) {
        output_stream << "(float: " << myfloat << ") ";
    }
    ~FloatNode() {
         cout << "Deleting DataNode:FloatNode:" << myfloat << endl;
    }
    // Add constructor, destructor, and printTo methods
};

#endif /* NODES_H */
