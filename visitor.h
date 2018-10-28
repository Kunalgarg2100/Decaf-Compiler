#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include "ast.h"
using namespace std;

class visitor : public ASTvisitor
{
public:
	virtual void visit(ASTnode& node){

	}

	virtual void visit(ExprASTnode& node){
		
	}

	virtual void visit(BinaryExprASTnode& node){
		// node.getLeft()->accept(this*);
		// node.getRight()->accept(this*);
		// cout << node.getOp() << " ";
	}
	
	virtual void visit(UnaryExprASTnode& node){

	}

	virtual void visit(LitExprASTnode& node){

	}
	
	virtual void visit(IntLitExprASTnode& node){
		cout << "<integer value = \"" <<  node.getIntLit() << "\" >" << endl;
	}

	virtual void visit(BoolLitExprASTnode& node){
		cout << "<boolean value = \"" <<  node.getBoolLit() << "\" >" << endl;
	}

	virtual void visit(CharLitExprASTnode& node){
		cout << "<char value = \"" <<  node.getCharLit() << "\" >" << endl;
	}

	virtual void visit(IdASTnode& node){
		int array_size = node.getSize();
		string var_name = node.getId();

		if(array_size == -1){
			fprintf(stdout, "<id = %s >\n" ,var_name.c_str());
		}
		else
			fprintf(stdout, "<id = %s , size = %d >\n", var_name.c_str(), array_size);
	}

	virtual void visit(VarlistASTnode& node){
		fprintf(stdout,"VarlistASTnode\n");
		vector<class IdASTnode*> var_names = node.getVarList();
		for(uint i=0; i< var_names.size();i++)
			var_names[i]->accept(*this);
	}

	virtual void visit(FieldDeclASTnode& node){
		fprintf(stdout,"FieldDeclASTnode\n");
		vector<class IdASTnode*> var_names = node.getVarList();
		for(uint i=0; i<var_names.size();i++)
			var_names[i]->accept(*this);
	}

	virtual void visit(FieldDecllistASTnode& node){
		fprintf(stdout,"FieldDecllistASTnode\n");
		vector<class FieldDeclASTnode*> field_decl_list = node.getFielddeclList();
		for(uint i=0; i<field_decl_list.size();i++)
			field_decl_list[i]->accept(*this);
		cout << node.getCnt() << endl;
	}

	virtual void visit(ProgramASTnode& node){
		fprintf(stdout,"ProgramASTnode\n");
		class FieldDecllistASTnode* field_decl_list = node.getFielddeclList();	
		field_decl_list->accept(*this);
	}
};