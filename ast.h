#include <cstdio>
#include <vector>
#include <string>
using namespace std;
extern FILE *xml_output;

class ASTnode;
class ExprASTnode;
class BinaryExprASTnode;
class UnaryExprASTnode;
class FieldDeclASTnode;
class LitExprASTnode;
class IntLitExprASTnode;
class BoolLitExprASTnode;
class CharLitExprASTnode;
class IdASTnode;
class VarlistASTnode;
class FieldDecllistASTnode;
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
	virtual void visit(VarlistASTnode& node) = 0;
	virtual void visit(FieldDeclASTnode& node) = 0;
	virtual void visit(FieldDecllistASTnode& node) = 0;
	virtual void visit(ProgramASTnode& node) = 0;
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
		ExprASTnode(){
		}
		~ExprASTnode(){
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
};

class VarlistASTnode : public ASTnode {
private:
	vector<class IdASTnode*> var_names;
	int cnt = 0;
public:
	VarlistASTnode(){}

	void push_varname(class IdASTnode* var_name){
		var_names.push_back(var_name);
		cnt++;
	} 	
	
	vector<class IdASTnode*> getVarList() {
		return var_names;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}
};

class FieldDeclASTnode : public ASTnode {
private:
	string datatype;
	vector<class IdASTnode*> var_names;
public:
	FieldDeclASTnode(string _datatype, class VarlistASTnode* _var_names):
	datatype(_datatype), var_names(_var_names->getVarList()) {}

	string getdataType() {
		return datatype;
	}

	vector<class IdASTnode*> getVarList() {
		return var_names;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}
};

class FieldDecllistASTnode {
private:
	vector<class FieldDeclASTnode*> field_decl_list;
	int cnt = 0;
public:
	FieldDecllistASTnode(){}

	void push_fielddecl(class FieldDeclASTnode* field_decl){
		field_decl_list.push_back(field_decl);
		cnt++;
	} 	
	
	vector<class FieldDeclASTnode*> getFielddeclList() {
		return field_decl_list;
	}

	int getCnt(){
		return cnt;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}
};

class ProgramASTnode : public ASTnode
{
private:
	class FieldDecllistASTnode* field_decl_list;
public:
	ProgramASTnode(class FieldDecllistASTnode* _field_dect_list):
	field_decl_list(_field_dect_list){}

	class FieldDecllistASTnode* getFielddeclList(){
		return field_decl_list;
	}

	virtual void accept(ASTvisitor &v){
		v.visit(*this);
	}
};