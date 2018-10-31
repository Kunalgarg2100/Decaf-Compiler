#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include "ast.h"
#define sz(a) (int)a.size()
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
		fprintf(stdout,"IdASTnode\n");
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

	virtual void visit(FielddeclASTnode& node){
		fprintf(stdout,"FielddeclASTnode\n");
		class VarlistASTnode * var_names = node.getVarList();
		var_names->accept(*this);
	}

	virtual void visit(FielddecllistASTnode& node){
		fprintf(stdout,"FielddecllistASTnode\n");
		vector<class FielddeclASTnode*> field_decl_list = node.getFielddeclList();
		for(uint i=0; i<field_decl_list.size();i++)
			field_decl_list[i]->accept(*this);
	}

	virtual void visit(IdlistASTnode& node){
		fprintf(stdout,"IdlistASTnode\n");
		vector<class IdASTnode*> var_list = node.getIdlist();
		for(uint i=0; i<var_list.size();i++)
			var_list[i]->accept(*this);
	}

	virtual void visit(VardeclASTnode &node){
		fprintf(stdout,"VardeclASTnode\n");
		fprintf(stdout,"<datatype = %s\n",node.getdataType().c_str());
		class IdlistASTnode * var_list = node.getIdlist();
		var_list->accept(*this);
	}

	virtual void visit(VardecllistASTnode &node){
		fprintf(stdout,"VardecllistASTnode\n");
		vector<class VardeclASTnode *> var_decl_list = node.getVardeclList();
		for(int i=0; i< sz(var_decl_list) ;i++)
			var_decl_list[i]->accept(*this);
	}

	virtual void visit(StatementASTnode &node){
		fprintf(stdout,"StatementASTnode\n");
	}

	virtual void visit(StatementlistASTnode &node){
		fprintf(stdout,"StatementlistASTnode\n");
		vector<class StatementASTnode*> statements_list = node.getStatementsList();
		for(int i=0; i< sz(statements_list) ;i++)
			statements_list[i]->accept(*this);
	}

	virtual void visit(BreakstatementASTnode &node){
		fprintf(stdout,"BreakStatementASTnode\n");
	}

	virtual void visit(ContinuestatementASTnode &node){
		fprintf(stdout,"ContinuestatementASTnode\n");
	}

	virtual void visit(ReturnstatementASTnode &node){
		fprintf(stdout,"ReturnstatementASTnode\n");
		class ExprASTnode * expr = node.getExpr();
		if(expr == NULL){

		}
		else{
			expr->accept(*this);
		}
	}

	virtual void visit(BlockstatementASTnode &node){
		fprintf(stdout,"BlockstatementASTnode\n");
		class VardecllistASTnode * var_decl_list = node.getVardeclList();
		class StatementlistASTnode * statements_list = node.getStatementsList();
		var_decl_list->accept(*this);
		statements_list->accept(*this);
	}

	virtual void visit(ForstatementASTnode &node){
		fprintf(stdout,"ForstatementASTnode\n");
		fprintf(stdout,"<varname = %s\n",node.getId().c_str());
		class ExprASTnode * initial_cond = node.getInitialcond();
		fprintf(stdout,"Initial condn\n");
		initial_cond->accept(*this);
		class ExprASTnode * break_cond = node.getBreakcond();
		fprintf(stdout,"Break condn\n");
		break_cond->accept(*this);
		class BlockstatementASTnode * block = node.getBlockstatement();
		fprintf(stdout,"Block statement\n");
		block->accept(*this);
	}

	virtual void visit(IfelseASTnode &node){
		fprintf(stdout,"IfelseASTnode\n");
		class ExprASTnode * cond = node.getCond();
		fprintf(stdout,"Condition\n");
		cond->accept(*this);
		class BlockstatementASTnode * ifstatement = node.getIfstatement();
		fprintf(stdout,"If statement\n");
		ifstatement->accept(*this);
		class BlockstatementASTnode * elsestatement = node.getElsestatement();
		if(elsestatement != NULL){
			fprintf(stdout,"Else statement\n");
			elsestatement->accept(*this);
		}
	}

	virtual void visit(LocationASTnode &node){
		fprintf(stdout,"LocationASTnode\n");
		fprintf(stdout,"<varname = %s\n",node.getId().c_str());
		class ExprASTnode * expr = node.getExpr();
		if(expr == NULL){

		}
		else{
			expr->accept(*this);
		}
	}

	virtual void visit(AssignstatementASTnode &node){
		fprintf(stdout,"AssignstatementASTnode\n");
		class LocationASTnode * location = node.getLocation();
		location->accept(*this);
		fprintf(stdout,"<operator = %s\n",node.getOp().c_str());
		class ExprASTnode * expr = node.getExpr();
		expr->accept(*this);
	}

	virtual void visit(ProgramASTnode& node){
		fprintf(stdout,"ProgramASTnode\n");
		class FielddecllistASTnode* field_decl_list = node.getFielddeclList();	
		field_decl_list->accept(*this);
	}
};
