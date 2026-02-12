//*****************************************************************************
// (part 3)
// purpose: node classes used while building a parse tree for
//              the arithmetic expression
// version: Spring 2022
//  author: Joe Crumpton / Ed Swan
//*****************************************************************************


// vector<StatementNOde*> statement COMPOUND STATEMENT CAN HAVEM ULTIPLE STATEMENTS
#ifndef PARSE_TREE_NODES_H
#define PARSE_TREE_NODES_H

#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"

using namespace std;

extern bool printDelete;      // shall we print deleting the tree?

// ---------------------------------------------------------------------
// Forward declaration of node types
class ProgramNode;
class BlockNode;
class StatementNode;
class AssignmentStatementNode;
class CompoundStatementNode;
class IfStatementNode;
class WhileStatementNode;
class ReadStatementNode;
class WriteStatementNode;
class ExprNode; 
class SimpleExprNode;
class TermNode;
class FactorNode;
class IdNode;
class IntLItNode;
class FloatLItNode; 
class NestedExprNode;
class NotNode;
class MinusNode;

// ---------------------------------------------------------------------
// <expr> -> <term> {{ (( + || - )) <term> }}
class ProgramNode {
public:
  int _level = 0;          // recursion level of this node
  BlockNode* firstBlock = nullptr;

  ProgramNode(int level);
  ~ProgramNode();
  void interpret();

};
ostream& operator<<(ostream&, ProgramNode&); // Node print operator
// ---------------------------------------------------------------------
// <expr> -> <term> {{ (( + || - )) <term> }}
class BlockNode {
public:
  int _level = 0;          // recursion level of this node
  CompoundStatementNode* firstStatement = nullptr;


  BlockNode(int level);
  ~BlockNode();
  void interpret();
};
ostream& operator<<(ostream&, BlockNode&); // Node print operator
// ---------------------------------------------------------------------
class StatementNode {
public:
  int _level = 0;                        // recursion level of this node
  virtual void interpret() = 0;   
  virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
  virtual ~StatementNode();   
            // labeling the destructor as virtual allows 
	                                       // the subclass destructors to be called
};
ostream& operator<<(ostream&, StatementNode&); // Node print operator
// ---------------------------------------------------------------------
// class IdNode (Identifier Node)
class CompoundStatementNode : public StatementNode {
public:
    vector<StatementNode*> statements;
    // StatementNode* firstStatement = nullptr;
    CompoundStatementNode(int level);
    ~CompoundStatementNode();
    void printTo(ostream & os);
    void interpret();

};
// ---------------------------------------------------------------------
// class IdNode (Identifier Node)
class WriteStatementNode : public StatementNode {
public:
    // vector<StatementNode*> statements;
    
    string* string_literal = nullptr;
    bool is_id = false;
    // Add constructor, destructor, and printTo methods

    WriteStatementNode(int level, string name);
    ~WriteStatementNode();
    void printTo(ostream & os);
    void interpret();
};
// ---------------------------------------------------------------------
// class IdNode (Identifier Node)
class ReadStatementNode : public StatementNode {
public:
    // vector<StatementNode*> statements;
    
    string* string_literal = nullptr;

    // Add constructor, destructor, and printTo methods

    ReadStatementNode(int level, string name);
    ~ReadStatementNode();
    void printTo(ostream & os);
    void interpret();
};
// ---------------------------------------------------------------------
// class IdNode (Identifier Node)
class AssignmentStatementNode : public StatementNode {
public:
    // vector<StatementNode*> statements;
    
    string* string_literal = nullptr;
    ExprNode* expressionPtr = nullptr;
  
    // Add constructor, destructor, and printTo methods

    AssignmentStatementNode(int level, string name);
    ~AssignmentStatementNode();
    void printTo(ostream & os);
    void interpret();
};
// ---------------------------------------------------------------------
// class IdNode (Identifier Node)
class IfStatementNode : public StatementNode {
public:
    // vector<StatementNode*> statements;
    
    
    ExprNode* expressionPtr = nullptr;
    StatementNode* statementPtr = nullptr;
    StatementNode* statementPtr2 = nullptr;
    // Add constructor, destructor, and printTo methods

    IfStatementNode(int level);
    ~IfStatementNode();
    void printTo(ostream & os);
    void interpret();
};
// ---------------------------------------------------------------------
// class IdNode (Identifier Node)
class WhileStatementNode : public StatementNode {
public:
    // vector<StatementNode*> statements;
    
    
    ExprNode* expressionPtr = nullptr;
    StatementNode* statementPtr = nullptr;
    
    // Add constructor, destructor, and printTo methods

    WhileStatementNode(int level);
    ~WhileStatementNode();
    void printTo(ostream & os);
    void interpret();
};
// ---------------------------------------------------------------------
// <expr> -> <term> {{ (( + || - )) <term> }}
class ExprNode {
public:
  int _level = 0;          // recursion level of this node
  SimpleExprNode* firstSimpleExpr = nullptr;
  vector<int> restSimpleExprOps; // 
  vector<SimpleExprNode*> restSimpleExprs;

  ExprNode(int level);
  ~ExprNode();
  float interpret();
};
ostream& operator<<(ostream&, ExprNode&); // Node print operator
// ---------------------------------------------------------------------
// <simple_expression> -> <term> {{ (( + || - )) <term> }}
class SimpleExprNode {
public:
  int _level = 0;              // recursion level of this node
  TermNode* firstTerm = nullptr;
  vector<int> restTermOps;   // TOK_ADD or TOK_MINUS
  vector<TermNode*> restTerms;

  SimpleExprNode(int level);
  ~SimpleExprNode();
  float interpret();
};
ostream& operator<<(ostream&, SimpleExprNode&); // Node print operator
// ---------------------------------------------------------------------
// <term> -> <factor> {{ (( * || / )) <factor> }}
class TermNode {
public:
  int _level = 0;              // recursion level of this node
  FactorNode* firstFactor = nullptr;
  vector<int> restFactorOps;   // TOK_MULT_OP or TOK_DIV_OP
  vector<FactorNode*> restFactors;

  TermNode(int level);
  ~TermNode();
  float interpret();
};
ostream& operator<<(ostream&, TermNode&); // Node print operator
// ---------------------------------------------------------------------
// Abstract class. Base class for IdNode, IntLitNode, NestedExprNode.
// <factor> -> ID || INTLIT || ( <expr> )
class FactorNode {
public:
  int _level = 0;                        // recursion level of this node

  virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
  virtual ~FactorNode();                 // labeling the destructor as virtual allows 
	virtual float interpret() = 0;                                       // the subclass destructors to be called
};
ostream& operator<<(ostream&, FactorNode&); // Node print operator
// ---------------------------------------------------------------------
// class IdNode (Identifier Node)
class IdNode : public FactorNode {
public:
    string* id = nullptr;

    IdNode(int level, string name);
    ~IdNode();
    void printTo(ostream & os);
    float interpret();
};
// ---------------------------------------------------------------------
// class IntLitNode (Integer Literal Node)
class IntLitNode : public FactorNode {
public:
    int int_literal = 0;

    IntLitNode(int level, int value);
    ~IntLitNode();
    void printTo(ostream & os);
    float interpret();
};
// ---------------------------------------------------------------------
// class NestedExprNode (Nested Expression Node)
class NestedExprNode : public FactorNode {
public:
    ExprNode* exprPtr = nullptr;

    NestedExprNode(int level, ExprNode* en);
    void printTo(ostream & os);
    ~NestedExprNode();
    float interpret();
};

// class FloatLitNode (Float Literal Node)
class FloatLitNode : public FactorNode {
public:
    float float_literal = 0;

    FloatLitNode(int level, float value);
    ~FloatLitNode();
    void printTo(ostream & os);
    float interpret();
};

class NotNode : public FactorNode {
public:
    
    FactorNode* factorPtr = nullptr;

    NotNode(int level, FactorNode *fn);
    ~NotNode();
    void printTo(ostream & os);
    float interpret();
};

class MinusNode : public FactorNode {
public:
    
    FactorNode* factorPtr = nullptr;

    MinusNode(int level, FactorNode *fn);
    ~MinusNode();
    void printTo(ostream & os);
    float interpret();
};

#endif /* PARSE_TREE_NODES_H */
