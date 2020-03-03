/*
 * parse_tree.h
 */

#ifndef PASRE_TREE_H_
#define PARSE_TREE_H_

#include <vector>
#include <map>
#include <string>
using std::vector;
using std::map;
using std::string;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

// a "forward declaration" for a class to hold values
class Value;

class ParseTree {
	int		linenum;
	ParseTree	*left;
	ParseTree	*right;
    
     

public:
	ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)
		: linenum(linenum), left(l), right(r) {
    
        
        }

	virtual ~ParseTree() {
		delete left;
		delete right;
	}

	int GetLinenum() const { return linenum; }
	ParseTree *GetLeft() const { return left; }
	ParseTree *GetRight() const { return right; }

    //counts the nodes 
    
	int NodeCount() const {
		int nc = 0;
		if( left ) nc += left->NodeCount();
		if( right ) nc += right->NodeCount();
		return nc + 1;
	}
    
    int ops() const {
		int oc = 0;
		
		if( left ) oc += left->ops();
		if( right ) oc += right->ops();
        
        if(IsOps()){
            oc++;
        }
        
		return oc;
	}
    
    
    int strings() const {
        int sc=0;
        if( left ) sc += left->strings();
		if( right ) sc += right->strings();
        
        if(IsString()){
            sc++;
        }
		
        
		return sc;
		
	}
    
    
    int leaves() const {
        
		int leafCount = 0;
		if(left) {
           leafCount += left ->leaves();
            
        }
        
           if( right ) {
           leafCount += right->leaves();
        } 
        
        if(left==0 && right ==0){
            leafCount++;
        }
        
        
		return leafCount; 
	}
    
     int maxdepth() const {
        
		int depthCountL = 0;
         int depthCountR = 0;
		if( left ) {
            
            depthCountL += left->maxdepth();
        }
        if( right ) {
            depthCountR += right->maxdepth();
        }
         
         if(depthCountL >  depthCountR){
             return depthCountL + 1;
         }
         
         else{
             return depthCountR + 1;
         }
		
	}
   

	virtual bool IsString() const { return false; }
    virtual bool IsOps() const { return false; }
    
    //make more of these and then in operation function get to tru
};

class StmtList : public ParseTree {

public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}

};

class IfStatement : public ParseTree {
public:
	IfStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
};

class SetStatement : public ParseTree {
	string id;

public:
	SetStatement(int line, string id, ParseTree *expr) : ParseTree(line, expr), id(id) {}
};

class PrintStatement : public ParseTree {
public:
	PrintStatement(int line, ParseTree *e) : ParseTree(line, e) {}
};

class LoopStatement : public ParseTree {
public:
	LoopStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
};

class Addition : public ParseTree {
public:
	Addition(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {
   
    }
     bool IsOps() const { return true; }
};

class Subtraction : public ParseTree {
public:
	Subtraction(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    bool IsOps() const { return true; }
};

class Multiplication : public ParseTree {
public:
	Multiplication(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    bool IsOps() const { return true; }
};

class Division : public ParseTree {
public:
	Division(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    bool IsOps() const { return true; }
};

class IConst : public ParseTree {
	int val;

public:
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}
};

class SConst : public ParseTree {
	string val;

public:
	SConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = t.GetLexeme();
	}

	bool IsString() const { return true; }
};

class Ident : public ParseTree {
	string id;

public:
	Ident(Token& t) : ParseTree(t.GetLinenum()), id(t.GetLexeme()) {}

	bool IsIdent() const { return true; }
};

#endif /* PARSE_TREE_H_ */
