//*****************************************************************************
// (part 3)
// purpose: node classes used while building a parse tree for
//              the arithmetic expression
// version: Fall 2022
//  author: Joe Crumpton / Ed Swan
//*****************************************************************************

#include "parse_tree_nodes.h"
#include "parser.h"

bool printDelete = false;   // shall we print deleting the tree?

// ---------------------------------------------------------------------
// Indent according to tree level
static void indent(int level) {
  for (int i = 0; i < level; i++)
    cout << ("|  ");
}
// ---------------------------------------------------------------------
FactorNode::~FactorNode() {}
// Uses double dispatch to call the overloaded method printTo in the 
// FactorNodes: IdNode, IntLitNode, and NestedExprNode
ostream& operator<<(ostream& os, FactorNode& fn) {
  os << endl; indent(fn._level); os << "(factor ";
  fn.printTo(os);
  os << endl; indent(fn._level); os << "factor) ";
	return os;
}
// ---------------------------------------------------------------------
IdNode::IdNode(int level, string name) {
  _level = level;
  id = new string(name);
}
IdNode::~IdNode() {
  if(printDelete) 
    cout << "Deleting FactorNode:IdNode" << endl;
	delete id;
	id = nullptr;
}
void IdNode::printTo(ostream& os) {
	os << "( IDENT: " << *id << " ) ";
}
float IdNode::interpret() {
  symbolTableT::iterator variable = symbolTable.find(*id); 
  return variable->second;
}
// ---------------------------------------------------------------------
IntLitNode::IntLitNode(int level, int value) {
  _level = level;
  int_literal = value;
}
IntLitNode::~IntLitNode() {
  if(printDelete)
    cout << "Deleting FactorNode:IntLitNode" << endl;
	  // Nothing to do since the only members are not pointers
}
void IntLitNode::printTo(ostream& os) {
	os << "( INTLIT: " << int_literal << " ) ";
}
float IntLitNode::interpret() {
  return int_literal;
}
// ---------------------------------------------------------------------
FloatLitNode::FloatLitNode(int level, float value) {
  _level = level;
  float_literal = value;
}
FloatLitNode::~FloatLitNode() {
  if(printDelete)
    cout << "Deleting FactorNode:FloatLitNode" << endl;
	  // Nothing to do since the only members are not pointers
}
void FloatLitNode::printTo(ostream& os) {
	os << "( FLOATLIT: " << float_literal << " ) ";
}
float FloatLitNode::interpret() {
  return float_literal;
}
// ---------------------------------------------------------------------
NotNode::NotNode(int level, FactorNode* fn) {
  _level = level;
  factorPtr = fn;
}
NotNode::~NotNode() {
  if(printDelete)
    cout << "Deleting FactorNode:NotNode" << endl;
  delete factorPtr;
  factorPtr = nullptr;
	  // Nothing to do since the only members are not pointers
}
void NotNode::printTo(ostream& os) {
	os << "(NOT " << *factorPtr << ") ";
}
float NotNode::interpret() {
  if (truth(factorPtr->interpret())) {
    return 0.0;
  }
  else {
    return 1.0;
  }
  
}
// ---------------------------------------------------------------------
MinusNode::MinusNode(int level, FactorNode* fn) {
  _level = level;
  factorPtr = fn;
}
MinusNode::~MinusNode() {
  if(printDelete)
    cout << "Deleting FactorNode:MinusNode" << endl;
  delete factorPtr;
  factorPtr = nullptr;
	  // Nothing to do since the only members are not pointers
}
void MinusNode::printTo(ostream& os) {
	os << "(- " << *factorPtr << ") ";
}
float MinusNode::interpret() {
  return -factorPtr->interpret();
}
// ---------------------------------------------------------------------
NestedExprNode::NestedExprNode(int level, ExprNode* en) {
  _level = level;
	exprPtr = en;
}
void NestedExprNode::printTo(ostream& os) {
	os << "( " << *exprPtr << ")";
}
NestedExprNode::~NestedExprNode() {
  if(printDelete)
    cout << "Deleting FactorNode:NestedExprNode" << endl;
  delete exprPtr;
  exprPtr = nullptr;
}
float NestedExprNode::interpret() {
  return exprPtr->interpret();
}
// ---------------------------------------------------------------------
TermNode::TermNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, TermNode& tn) {
  os << endl; indent(tn._level); os << "(term ";
	os << *(tn.firstFactor);

	int length = tn.restFactorOps.size();
	for (int i = 0; i < length; ++i) {
		int op = tn.restFactorOps[i];
    if (op == TOK_MULTIPLY) {
      os << endl; indent(tn._level); os << "* ";
    } else if (op == TOK_DIVIDE) {
      os << endl; indent(tn._level); os << "/ ";
    }
    else if (op == TOK_AND) {
       os << endl; indent(tn._level); os << "AND ";
    }
		os << *(tn.restFactors[i]);
	}
  os << endl; indent(tn._level); os << "term) ";
	return os;
}
TermNode::~TermNode() {
  if(printDelete)
    cout << "Deleting TermNode" << endl;
	delete firstFactor;
	firstFactor = nullptr;

	int length = restFactorOps.size();
	for (int i = 0; i < length; ++i) {
		delete restFactors[i];
		restFactors[i] = nullptr;
	}
}
float TermNode::interpret() {
  float returnValue = firstFactor->interpret();

  int length = restFactorOps.size();
  for (int i = 0; i < length; ++i) {
    // get the value of the next Term
    float nextValue = restFactors[i]->interpret();

    // perform the operation (+ or -) that separates the Terms
    switch(restFactorOps[i]) {
      case TOK_MULTIPLY:
        returnValue = returnValue * nextValue; 
      break;
      case TOK_DIVIDE:
        returnValue = returnValue / nextValue; 
      break;
      case TOK_AND:
        if (returnValue && nextValue) {
          return 1.0;
        }
        else {
          return 0.0;
        }
      break;
    }
  }
  return returnValue;
}
// ---------------------------------------------------------------------
SimpleExprNode::SimpleExprNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, SimpleExprNode& tn) {
  os << endl; indent(tn._level); os << "(simple_exp ";
	os << *(tn.firstTerm);

	int length = tn.restTermOps.size();
	for (int i = 0; i < length; ++i) {
		int op = tn.restTermOps[i];
    if (op == TOK_PLUS) {
      os << endl; indent(tn._level); os << "+ ";
    } else if (op == TOK_MINUS) {
      os << endl; indent(tn._level); os << "- ";
    }
    else if (op == TOK_OR) {
       os << endl; indent(tn._level); os << "OR ";
    }
		os << *(tn.restTerms[i]);
	}
  os << endl; indent(tn._level); os << "simple_exp) ";
	return os;
}
SimpleExprNode::~SimpleExprNode() {
  if(printDelete)
    cout << "Deleting SimpleExpNode" << endl;
	delete firstTerm;
	firstTerm = nullptr;

	int length = restTermOps.size();
	for (int i = 0; i < length; ++i) {
		delete restTerms[i];
		restTerms[i] = nullptr;
	}
}
float SimpleExprNode::interpret() {
  float returnValue = firstTerm->interpret();

  int length = restTermOps.size();
  for (int i = 0; i < length; ++i) {
    // get the value of the next Term
    float nextValue = restTerms[i]->interpret();

    // perform the operation (+ or -) that separates the Terms
    switch(restTermOps[i]) {
      case TOK_PLUS:
        returnValue = returnValue + nextValue; 
      break;
      case TOK_MINUS:
        returnValue = returnValue - nextValue; 
      break;
      case TOK_OR:
        if (returnValue || nextValue) {
            return 1.0;
          }
          else {
            return 0.0;
          }
      break;
    }
  }
  return returnValue;
}
// ---------------------------------------------------------------------

ExprNode::ExprNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, ExprNode& en) {
  os << endl; indent(en._level); os << "(expression ";
	os << *(en.firstSimpleExpr);

	int length = en.restSimpleExprOps.size();
	for (int i = 0; i < length; ++i) {
		int op = en.restSimpleExprOps[i];
    if (op == TOK_EQUALTO) {
      os << endl; indent(en._level); os << "= ";
    } else if (op == TOK_GREATERTHAN) {
      os << endl; indent(en._level); os << "> ";
    }
    else if (op == TOK_LESSTHAN) {
       os << endl; indent(en._level); os << "< ";
    }
    else if (op == TOK_NOTEQUALTO) {
       os << endl; indent(en._level); os << "<> ";
    }
		os << *(en.restSimpleExprs[i]);
	}
  os << endl; indent(en._level); os << "expression) ";
	return os;
}
ExprNode::~ExprNode() {
  if(printDelete)
    cout << "Deleting ExpressionNode" << endl;
	delete firstSimpleExpr;
	firstSimpleExpr = nullptr;

	int length = restSimpleExprOps.size();
	for (int i = 0; i < length; ++i) {
		delete restSimpleExprs[i];
		restSimpleExprs[i] = nullptr;
	}
}
float ExprNode::interpret() {
  float returnValue = firstSimpleExpr->interpret();

  int length = restSimpleExprOps.size();
  for (int i = 0; i < length; ++i) {
    // get the value of the next Term
    float nextValue = restSimpleExprs[i]->interpret();

    // perform the operation (+ or -) that separates the Terms
    switch(restSimpleExprOps[i]) {
      case TOK_EQUALTO:

        if (abs(firstSimpleExpr->interpret() - nextValue) <= EPSILON) 
          return 1.0; 
        else 
          return 0.0; 
      break;
      case TOK_GREATERTHAN:
        if(firstSimpleExpr->interpret() > nextValue + EPSILON) 
          return 1.0; // true 
        else 
          return 0.0; // false 
      case TOK_LESSTHAN:
        if((firstSimpleExpr->interpret() + EPSILON) < nextValue) 
          return 1.0; // true 
        else 
          return 0.0; // false 
      case TOK_NOTEQUALTO:
        if(abs(firstSimpleExpr->interpret() - nextValue) > EPSILON) 
          return 1.0; // true 
        else 
          return 0.0; // false 
      break;
    }
  }
  return returnValue;
}

// ---------------------------------------------------------------------

ProgramNode::ProgramNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, ProgramNode& en) {
  os << endl; indent(en._level); os << "(program ";
  
	os << *(en.firstBlock);

	// int length = en.restBlockOps.size();
	// for (int i = 0; i < length; ++i) {
	// 	int op = en.restBlockOps[i];
    
	// 	os << *(en.restBlocks[i]);
	// }
  os << endl; indent(en._level); os << "program) ";
	return os;
}
ProgramNode::~ProgramNode() {
  if(printDelete)
    cout << "Deleting ProgramNode" << endl;
	delete firstBlock;
	firstBlock = nullptr;

}
void ProgramNode::interpret() {
 
  firstBlock->interpret();
}
// ---------------------------------------------------------------------

BlockNode::BlockNode(int level) {
  _level = level;
}
ostream& operator<<(ostream& os, BlockNode& en) {
  os << endl; indent(en._level); os << "(block ";
	os << *(en.firstStatement);

  os << endl; indent(en._level); os << "block) ";
	return os;
}
BlockNode::~BlockNode() {
  if(printDelete)
    cout << "Deleting BlockNode" << endl;
	delete firstStatement;
	firstStatement = nullptr;

}
void BlockNode::interpret() {
  
  firstStatement->interpret();
}
// ---------------------------------------------------------------------
StatementNode::~StatementNode() {}
// Uses double dispatch to call the overloaded method printTo in the 
// FactorNodes: IdNode, IntLitNode, and NestedExprNode
ostream& operator<<(ostream& os, StatementNode& fn) {
  // os << endl; indent(fn._level); os << "(statement ";
  os << endl; indent(fn._level); fn.printTo(os);
  // os << endl; indent(fn._level); os << "statement) ";
	return os;
}
void StatementNode::interpret()  
{ 
  this->interpret(); 
} 
// ---------------------------------------------------------------------
CompoundStatementNode::CompoundStatementNode(int level) {
  _level = level;
  // statements = sn.statements;
  
}
CompoundStatementNode::~CompoundStatementNode() {
  if(printDelete)
    cout << "Deleting StatementNode:CompoundStmtNode" << endl;

	 int length = statements.size();
    for (int i = 0; i < length; ++i) {
      delete statements[i];
      statements[i] = nullptr;
    }
}
void CompoundStatementNode::printTo(ostream& os) {
 
	os << "(compound_stmt"; 
  int length = statements.size();
 
  for (auto i = statements.begin(); i != statements.end(); ++i) {
  
    os << *(*i);
  }
  os << endl; indent(_level); os << "compound_stmt)";
  
  // os << endl; indent(en._level); os << "compound_statement ) ";
}
void CompoundStatementNode::interpret() {
  for (auto i = statements.begin(); i != statements.end(); ++i) {
    (*i)->interpret();
  }
  
}

// ---------------------------------------------------------------------
WriteStatementNode::WriteStatementNode(int level, string name) {
  _level = level;
  string_literal = new string(name);
  // statements = sn.statements;
 
}
WriteStatementNode::~WriteStatementNode() {
  if(printDelete)
    cout << "Deleting StatementNode:WriteStmtNode" << endl;
  delete string_literal;
	string_literal = nullptr;
	  // Nothing to do since the only members are not pointers
}
void WriteStatementNode::printTo(ostream& os) {
  
	os << "(write_stmt ( " << *string_literal << " )"; os << endl; indent(_level); os << "write_stmt)";
}
void WriteStatementNode::interpret() {
  if (is_id == false) {
    
    cout << string_literal->substr(1, string_literal->length()-2) << endl; 
  }
  else {
    symbolTableT::iterator variable = symbolTable.find(*string_literal); 
    cout << variable->second << endl; 
  }
}

// ---------------------------------------------------------------------
AssignmentStatementNode::AssignmentStatementNode(int level, string name) {
  _level = level;
  string_literal = new string(name);
  // statements = sn.statements;
 
}
AssignmentStatementNode::~AssignmentStatementNode() {
  if(printDelete)
    cout << "Deleting StatementNode:AssignmentStmtNode" << endl;
  delete string_literal;
	string_literal = nullptr;
  delete expressionPtr;
  expressionPtr = nullptr;
	  // Nothing to do since the only members are not pointers
}
void AssignmentStatementNode::printTo(ostream& os) {
  
	os << "(assignment_stmt ( " << *string_literal << " := )"; 
  os << *(expressionPtr);
  os << endl; indent(_level); os << "assignment_stmt)";
}
void AssignmentStatementNode::interpret() {
  symbolTableT::iterator variable = symbolTable.find(*string_literal); 
  variable->second = expressionPtr->interpret(); 
}
// ---------------------------------------------------------------------
ReadStatementNode::ReadStatementNode(int level, string name) {
  _level = level;
  string_literal = new string(name);
  // statements = sn.statements;
 
}
ReadStatementNode::~ReadStatementNode() {
  if(printDelete)
    cout << "Deleting StatementNode:ReadStmtNode" << endl;
  delete string_literal;
	string_literal = nullptr;
	  // Nothing to do since the only members are not pointers
}
void ReadStatementNode::printTo(ostream& os) {
  
	os << "(read_stmt ( " << *string_literal << " )"; os << endl; indent(_level); os << "read_stmt)";
}
void ReadStatementNode::interpret() {
    symbolTableT::iterator variable = symbolTable.find(*string_literal); 
   
    cin >> variable->second;
    
    // cout << variable->second << endl; 
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
IfStatementNode::IfStatementNode(int level) {
  _level = level;
  
  // statements = sn.statements;
 
}
IfStatementNode::~IfStatementNode() {
  if(printDelete)
    cout << "Deleting StatementNode:IfStmtNode" << endl;
  
  delete expressionPtr;
  expressionPtr = nullptr;
  delete statementPtr;
  statementPtr = nullptr;
  delete statementPtr2;
  statementPtr2 = nullptr;
	  // Nothing to do since the only members are not pointers
}
void IfStatementNode::printTo(ostream& os) {
  
	os << "(if_stmt "; 
  os << *(expressionPtr);
  os << endl; indent(_level); os << "(then ";
  os << *(statementPtr);
  os << endl; indent(_level); os << "then) ";
  if (statementPtr2 != nullptr) {
    os << endl; indent(_level); os << "(else ";
    os << *(statementPtr2);
    os << endl; indent(_level); os << "else) ";
  }
  os << endl; indent(_level); os << "if_stmt)";
}
void IfStatementNode::interpret() {
  if (truth(expressionPtr->interpret())) {
    statementPtr->interpret();
  }
  else {
    if (statementPtr2 != nullptr) {
      statementPtr2->interpret();
    }
  }
}
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
WhileStatementNode::WhileStatementNode(int level) {
  _level = level;
  
  // statements = sn.statements;
 
}
WhileStatementNode::~WhileStatementNode() {
  if(printDelete)
    cout << "Deleting StatementNode:WhileStmtNode" << endl;
  
  delete expressionPtr;
  expressionPtr = nullptr;
  delete statementPtr;
  statementPtr = nullptr;
  
	  // Nothing to do since the only members are not pointers
}
void WhileStatementNode::printTo(ostream& os) {
  
	os << "(while_stmt "; 
  os << *(expressionPtr);
 
  os << *(statementPtr);

  
  os << endl; indent(_level); os << "while_stmt)";
}
void WhileStatementNode::interpret() {
  while (truth(expressionPtr->interpret())) {
    statementPtr->interpret();
  }
}
// ---------------------------------------------------------------------
