#ifndef _AST_H
#define _AST_H
#include <cstdio>
#include <vector>
#include <string>
#include "llvm/IR/Value.h"
using namespace std;
using namespace llvm;

class ASTnode;
class ExprASTnode;
class BinaryExprASTnode;
class UnaryExprASTnode;
class LitExprASTnode;
class IntLitExprASTnode;
class BoolLitExprASTnode;
class CharLitExprASTnode;
class IdASTnode;
class IdtypeASTnode;
class VarlistASTnode;
class FielddeclASTnode;
class FielddecllistASTnode;
class IdlistASTnode;
class IdtypelistASTnode;
class VardeclASTnode;
class MethoddeclASTnode;
class VardecllistASTnode;
class MethoddecllistASTnode;
class StatementASTnode;
class StatementlistASTnode;
class BreakstatementASTnode;
class ContinuestatementASTnode;
class ReturnstatementASTnode;
class BlockstatementASTnode;
class ForstatementASTnode;
class IfelseASTnode;
class LocationASTnode;
class AssignstatementASTnode;
class MethodASTnode;
class MethodArgsASTnode;
class DefinedMethodASTnode;
class CalloutargASTnode;
class ExprargASTnode;
class StringargASTnode;
class CalloutArgsASTnode;
class CalloutMethodASTnode;
class ProgramASTnode;

class ASTvisitor{
public:
	virtual void visit(ASTnode& node) = 0;
	virtual void visit(ExprASTnode& node) = 0;
	virtual void visit(BinaryExprASTnode& node) = 0;
	virtual void visit(UnaryExprASTnode& node) = 0;
	virtual void visit(LitExprASTnode& node) = 0;
	virtual void visit(IntLitExprASTnode& node) = 0;
	virtual void visit(BoolLitExprASTnode& node) = 0;
	virtual void visit(CharLitExprASTnode& node) = 0;
	virtual void visit(IdASTnode& node) = 0;
	virtual void visit(IdtypeASTnode& node) = 0;
	virtual void visit(VarlistASTnode& node) = 0;
	virtual void visit(FielddeclASTnode& node) = 0;
	virtual void visit(FielddecllistASTnode& node) = 0;
	virtual void visit(IdlistASTnode& node) = 0;
	virtual void visit(IdtypelistASTnode& node) = 0;
	virtual void visit(VardeclASTnode &node) = 0;
	virtual void visit(MethoddeclASTnode &node) = 0;
	virtual void visit(VardecllistASTnode &node) = 0;
	virtual void visit(MethoddecllistASTnode &node) = 0;
	virtual void visit(StatementASTnode &node) = 0;
	virtual void visit(StatementlistASTnode &node) = 0;
	virtual void visit(BreakstatementASTnode &node) = 0;
	virtual void visit(ContinuestatementASTnode &node) = 0;
	virtual void visit(ReturnstatementASTnode &node) = 0;
	virtual void visit(BlockstatementASTnode &node) = 0;
	virtual void visit(ForstatementASTnode &node) = 0;
	virtual void visit(IfelseASTnode &node) = 0;
	virtual void visit(LocationASTnode &node) = 0;
	virtual void visit(AssignstatementASTnode &node) = 0;
	virtual void visit(MethodASTnode &node) = 0;
	virtual void visit(MethodArgsASTnode &node) = 0;
	virtual void visit(DefinedMethodASTnode &node) = 0;
	virtual void visit(CalloutargASTnode &node) = 0;
	virtual void visit(ExprargASTnode &node) = 0;
	virtual void visit(StringargASTnode &node) = 0;
	virtual void visit(CalloutArgsASTnode &node) = 0;
	virtual void visit(CalloutMethodASTnode &node) = 0;
	virtual void visit(ProgramASTnode& node) = 0;
};

class CodeGenvisitor {
public:
	virtual Value * Codegen(ASTnode& node) = 0;
	virtual Value * Codegen(ExprASTnode& node) = 0;
	virtual Value * Codegen(BinaryExprASTnode& node) = 0;
	virtual Value * Codegen(UnaryExprASTnode& node) = 0;
	virtual Value * Codegen(LitExprASTnode& node) = 0;
	virtual Value * Codegen(IntLitExprASTnode& node) = 0;
	virtual Value * Codegen(BoolLitExprASTnode& node) = 0;
	virtual Value * Codegen(CharLitExprASTnode& node) = 0;
	virtual Value * Codegen(IdASTnode& node, Type * datatype) = 0;
	virtual Value * Codegen(VarlistASTnode& node, Type * datatype) = 0;
	virtual Value * Codegen(FielddeclASTnode& node) = 0;
	virtual Value * Codegen(FielddecllistASTnode& node) = 0;
	virtual Value * Codegen(IdlistASTnode& node) = 0;
	virtual Value * Codegen(VardeclASTnode &node) = 0;
	virtual Value * Codegen(MethoddeclASTnode &node) = 0;
	virtual Value * Codegen(VardecllistASTnode &node) = 0;
	virtual Value * Codegen(MethoddecllistASTnode &node) = 0;
	virtual Value * Codegen(StatementASTnode &node) = 0;
	virtual Value * Codegen(StatementlistASTnode &node) = 0;
	virtual Value * Codegen(BreakstatementASTnode &node) = 0;
	virtual Value * Codegen(ContinuestatementASTnode &node) = 0;
	virtual Value * Codegen(ReturnstatementASTnode &node) = 0;
	virtual Value * Codegen(BlockstatementASTnode &node) = 0;
	virtual Value * Codegen(ForstatementASTnode &node) = 0;
	virtual Value * Codegen(IfelseASTnode &node) = 0;
	virtual Value * Codegen(LocationASTnode &node) = 0;
	virtual Value * Codegen(AssignstatementASTnode &node) = 0;
	virtual Value * Codegen(MethodASTnode &node) = 0;
	virtual Value * Codegen(MethodArgsASTnode &node) = 0;
	virtual Value * Codegen(DefinedMethodASTnode &node) = 0;
	virtual Value * Codegen(CalloutargASTnode &node) = 0;
	virtual Value * Codegen(ExprargASTnode &node) = 0;
	virtual Value * Codegen(StringargASTnode &node) = 0;
	virtual Value * Codegen(CalloutArgsASTnode &node) = 0;
	virtual Value * Codegen(CalloutMethodASTnode &node) = 0;
	virtual Value * Codegen(ProgramASTnode& node) = 0;
};

class ASTnode {
	public :
		ASTnode(){
		}
		~ASTnode(){
		}
};


class ExprASTnode : public ASTnode{
	public :
		ExprASTnode(){}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}

};

class BinaryExprASTnode : public ExprASTnode
{
private:
	ExprASTnode * left;
	ExprASTnode * right;
	string bin_operator;
public:
	BinaryExprASTnode(ExprASTnode * _left, ExprASTnode * _right, string _bin_operator) : 
	left(_left) , right(_right), bin_operator(_bin_operator) {}

	ExprASTnode * getLeft(){
		return left;
	}

	ExprASTnode * getRight(){
		return right;
	}

	string getOp(){
		return bin_operator;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class UnaryExprASTnode : public ExprASTnode
{
private:
	ExprASTnode * expr;
	string unary_operator;
public:
	UnaryExprASTnode(ExprASTnode * _expr, string _unary_operator) : 
	expr(_expr) , unary_operator(_unary_operator) {}

	ExprASTnode * getExpr(){
		return expr;
	}

	string getOp(){
		return unary_operator;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class LitExprASTnode : public ExprASTnode
{
public:
	LitExprASTnode(){

	}
	~LitExprASTnode(){
		
	}
};

class IntLitExprASTnode : public LitExprASTnode{
private:
	int intlit;
public:
	IntLitExprASTnode(int _intlit):
	intlit(_intlit){}

	int getIntLit(){
		return intlit;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class BoolLitExprASTnode : public LitExprASTnode{
private:
	string boollit;
public:
	BoolLitExprASTnode(string _boollit):
	boollit(_boollit){}

	string getBoolLit(){
		return boollit;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class CharLitExprASTnode : public LitExprASTnode{
private:
	char charlit;
public:
	CharLitExprASTnode(char _charlit):
	charlit(_charlit) {}

	char getCharLit(){
		return charlit;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class IdASTnode {
private:
	string var_name;
	int array_size = -1;
public:
	IdASTnode(string _var_name):
	var_name(_var_name){}

	IdASTnode(string _var_name, int _array_size):
	var_name(_var_name), array_size(_array_size) {}

	string getId(){
		return var_name;
	}

	int getSize(){
		return array_size;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v,Type * datatype){
		return v.Codegen(*this, datatype);
	}
};

class IdtypeASTnode {
private:
	string datatype;
	string var_name;
public:
	IdtypeASTnode(string _datatype, string _var_name):
	datatype(_datatype), var_name(_var_name){}

	string getId(){
		return var_name;
	}

	string getType(){
		return datatype;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

};

class VarlistASTnode : public ASTnode {
private:
	vector<class IdASTnode*> var_names;
public:
	VarlistASTnode(){}

	void push_varname(class IdASTnode* var_name){
		var_names.push_back(var_name);
	} 	
	
	vector<class IdASTnode*> getVarList() {
		return var_names;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v, Type * datatype){
		return v.Codegen(*this, datatype);
	}
};

class FielddeclASTnode : public ASTnode {
private:
	string datatype;
	class VarlistASTnode* var_names;
public:
	FielddeclASTnode(string _datatype, class VarlistASTnode* _var_names):
	datatype(_datatype), var_names(_var_names) {}

	string getdataType() {
		return datatype;
	}

	class VarlistASTnode * getVarList() {
		return var_names;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class FielddecllistASTnode {
private:
	vector<class FielddeclASTnode*> field_decl_list;
public:
	FielddecllistASTnode(){}

	void push_fielddecl(class FielddeclASTnode* field_decl){
		field_decl_list.push_back(field_decl);
	} 	
	
	vector<class FielddeclASTnode*> getFielddeclList() {
		return field_decl_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class IdlistASTnode {
private:
	string datatype;
	vector<class IdASTnode*> var_list;
public:
	IdlistASTnode(){}

	void push_id(class IdASTnode* id){
		var_list.push_back(id);
	}

	vector<class IdASTnode*> getIdlist() {
		return var_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class IdtypelistASTnode {
private:
	vector<class IdtypeASTnode*> var_list;
public:
	IdtypelistASTnode(){}

	void push_idtype(class IdtypeASTnode* id){
		var_list.push_back(id);
	}

	vector<class IdtypeASTnode*> getIdtypelist() {
		return var_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}
};

class VardeclASTnode {
private:
	string datatype;
	class IdlistASTnode * var_list;
public:
	VardeclASTnode(string _datatype, class IdlistASTnode * _var_list):
	datatype(_datatype), var_list(_var_list) {}

	string getdataType(){
		return datatype;
	}

	class IdlistASTnode * getIdlist(){
		return var_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class MethoddeclASTnode {
private:
	string returntype;
	string id;
	class IdtypelistASTnode * var_list;
	class BlockstatementASTnode * block;
public:
	MethoddeclASTnode(string _datatype, string _id, class IdtypelistASTnode * _var_list, class BlockstatementASTnode * _block):
	returntype(_datatype), id(_id), var_list(_var_list), block(_block) {}

	string getreturnType(){
		return returntype;
	}

	class IdtypelistASTnode * getIdlist(){
		return var_list;
	}

	string getId(){
		return id;
	}

	class BlockstatementASTnode * getBlock(){
		return block;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class VardecllistASTnode {
private:
	vector<class VardeclASTnode *> var_decl_list;
public:
	VardecllistASTnode(){}

	void push_vardecl(class VardeclASTnode* var_decl){
		var_decl_list.push_back(var_decl);
	} 	
	
	vector<class VardeclASTnode*> getVardeclList() {
		return var_decl_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class MethoddecllistASTnode {
private:
	vector<class MethoddeclASTnode *> method_decl_list;
public:
	MethoddecllistASTnode(){}

	void push_methoddecl(class MethoddeclASTnode* method_decl){
		method_decl_list.push_back(method_decl);
	} 	
	
	vector<class MethoddeclASTnode*> getMethoddeclList() {
		return method_decl_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class StatementASTnode : public ASTnode{
public:
	StatementASTnode(){}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class StatementlistASTnode : public ASTnode{
private:
	vector<class StatementASTnode*> statements_list;
public:
	StatementlistASTnode(){}

	void push_statement(class StatementASTnode* statement){
		statements_list.push_back(statement);
	}

	vector<class StatementASTnode*> getStatementsList(){
		return statements_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class BreakstatementASTnode : public StatementASTnode{
public:
	BreakstatementASTnode(){}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class ContinuestatementASTnode : public StatementASTnode{
public:
	ContinuestatementASTnode(){}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class ReturnstatementASTnode : public StatementASTnode{
private:
	class ExprASTnode * expr;
public:
	ReturnstatementASTnode(class ExprASTnode * _expr):
	expr(_expr) {}

	class ExprASTnode * getExpr(){
		return expr;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class BlockstatementASTnode : public StatementASTnode{
private:
	class VardecllistASTnode * var_decl_list;
	class StatementlistASTnode * statements_list;
public:
	BlockstatementASTnode(class VardecllistASTnode * _var_decl_list, class StatementlistASTnode * _statements_list):
	var_decl_list(_var_decl_list), statements_list(_statements_list) {}

	class VardecllistASTnode * getVardeclList(){
		return var_decl_list;
	}

	class StatementlistASTnode * getStatementsList(){
		return statements_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class ForstatementASTnode : public StatementASTnode{
private:
	string id;
	class ExprASTnode * initial_cond;
	class ExprASTnode * break_cond;
	class BlockstatementASTnode * block;
public:
	ForstatementASTnode(string _id, class ExprASTnode * _initial_cond, class ExprASTnode * _break_cond, class BlockstatementASTnode * _block):
	id(_id), initial_cond(_initial_cond), break_cond(_break_cond), block(_block) {}

	class ExprASTnode * getInitialcond(){
		return initial_cond;
	}

	class ExprASTnode * getBreakcond(){
		return break_cond;
	}

	class BlockstatementASTnode * getBlockstatement(){
		return block;
	}

	string getId(){
		return id;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class IfelseASTnode : public StatementASTnode{
private:
	class BlockstatementASTnode * ifstatement;
	class ExprASTnode * cond;
	class BlockstatementASTnode * elsestatement;
public:
	IfelseASTnode(class BlockstatementASTnode * _ifstatement, class ExprASTnode * _cond , class BlockstatementASTnode * _elsestatement):
	ifstatement(_ifstatement), cond(_cond), elsestatement(_elsestatement) {}

	class BlockstatementASTnode * getIfstatement(){
		return ifstatement;
	}

	class BlockstatementASTnode * getElsestatement(){
		return elsestatement;
	}

	class ExprASTnode * getCond(){
		return cond;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class LocationASTnode : public ExprASTnode{
private:
	string id;
	class ExprASTnode * expr;
public:
	LocationASTnode(string _id, class ExprASTnode * _expr):
	id(_id), expr(_expr) {}

	string getId(){
		return id;
	}

	class ExprASTnode *  getExpr(){
		return expr;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class AssignstatementASTnode : public StatementASTnode{
private:
	class LocationASTnode * location;
	string op;
	class ExprASTnode * expr;
public:
	AssignstatementASTnode(class LocationASTnode * _location, string _op, class ExprASTnode * _expr):
	location(_location), op(_op), expr(_expr) {}

	class LocationASTnode * getLocation(){
		return location;
	}

	string getOp(){
		return op;
	}

	class ExprASTnode * getExpr(){
		return expr;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class MethodASTnode :  public StatementASTnode, public ExprASTnode {
public:
	MethodASTnode(){}
	
};

class MethodArgsASTnode : public ExprASTnode {
private:
	vector<class ExprASTnode *> arguments_list;
public:
	MethodArgsASTnode(){}

	void push_argument(class ExprASTnode * expr){
		arguments_list.push_back(expr);
	}

	vector<class ExprASTnode *> getArgumentsList(){
		return arguments_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};	


class DefinedMethodASTnode : public MethodASTnode{
private:
	string method_name;
	class MethodArgsASTnode* arguments_list;
public:
	DefinedMethodASTnode(string _method_name, class MethodArgsASTnode* _arguments_list):
	method_name(_method_name), arguments_list(_arguments_list) {}

	string getMethodName(){
		return method_name;
	}
	
	class MethodArgsASTnode*  getArgsList(){
		return arguments_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class CalloutargASTnode {
public:
	CalloutargASTnode(){}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class ExprargASTnode : public CalloutargASTnode{
private:
	class ExprASTnode * expr_argument;
public:
	ExprargASTnode(class ExprASTnode* _expr):
	expr_argument(_expr) {};

	class ExprASTnode * getArgument(){
		return expr_argument;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class StringargASTnode : public CalloutargASTnode{
private:
	string argument;
public:
	StringargASTnode(string _str):
	argument(_str) {};

	string getArgument(){
		return argument;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class CalloutArgsASTnode : public ASTnode{
private:
	vector<class CalloutargASTnode *> arguments_list;
public:
	CalloutArgsASTnode(){}

	void push_argument(class CalloutargASTnode  * argument){
		arguments_list.push_back(argument);
	}

	vector<class CalloutargASTnode *> getArgumentsList(){
		return arguments_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
	
};

class CalloutMethodASTnode : public MethodASTnode{
private:
	string method_name;
	class CalloutArgsASTnode* arguments_list;
public:
	CalloutMethodASTnode(string _method_name, class CalloutArgsASTnode* _arguments_list):
	method_name(_method_name), arguments_list(_arguments_list) {}

	string getMethodName(){
		return method_name;
	}
	
	class CalloutArgsASTnode*  getArgsList(){
		return arguments_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};

class ProgramASTnode : public ASTnode
{
private:
	class FielddecllistASTnode* field_decl_list;
	class MethoddecllistASTnode* method_decl_list;
public:

	ProgramASTnode(class FielddecllistASTnode* _field_dect_list, class MethoddecllistASTnode* _method_decl_list):
	field_decl_list(_field_dect_list), method_decl_list(_method_decl_list) {}

	class FielddecllistASTnode* getFielddeclList(){
		return field_decl_list;
	}

	class MethoddecllistASTnode* getMethoddeclList(){
		return method_decl_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}

	virtual Value * codegen(CodeGenvisitor &v){
		return v.Codegen(*this);
	}
};
#endif