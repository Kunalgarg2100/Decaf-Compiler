#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include "ast.h"
#define sz(a) (int)a.size()
using namespace std;

FILE * ASToutfile = fopen("AST_output.txt", "w+");

class visitor : public ASTvisitor
{
public:
	virtual void visit(ASTnode& node){

	}

	virtual void visit(ExprASTnode& node){
		fprintf(ASToutfile,"ExprASTnode\n");
	}

	virtual void visit(BinaryExprASTnode& node){
		fprintf(ASToutfile,"BinaryExprASTnode\n");
		ExprASTnode * left = node.getLeft();
		ExprASTnode * right = node.getRight();
		string binop = node.getOp();
		left->accept(*this);
		right->accept(*this);
		fprintf(ASToutfile,"binop is %s\n",binop.c_str());
	}
	
	virtual void visit(UnaryExprASTnode& node){
		ExprASTnode * expr = node.getExpr();
		expr->accept(*this);
		string unary_operator = node.getOp();
		fprintf(ASToutfile,"unary_operator is %s\n",unary_operator.c_str());
	}

	virtual void visit(LitExprASTnode& node){

	}
	
	virtual void visit(IntLitExprASTnode& node){
		fprintf(ASToutfile,"IntLitExprASTnode\n");		
		fprintf(ASToutfile,"<integer value = \"%d\">\n",node.getIntLit());
	}

	virtual void visit(BoolLitExprASTnode& node){
		fprintf(ASToutfile,"BoolLitExprASTnode\n");
		fprintf(ASToutfile,"<boolean value = \"%s\">\n",node.getBoolLit().c_str());
	}

	virtual void visit(CharLitExprASTnode& node){
		fprintf(ASToutfile,"CharLitExprASTnode\n");
		fprintf(ASToutfile,"<char value = \"%c\">\n",node.getCharLit());
	}

	virtual void visit(IdASTnode& node){
		fprintf(ASToutfile,"IdASTnode\n");
		int array_size = node.getSize();
		string var_name = node.getId();
		if(array_size == -1){
			fprintf(ASToutfile, "<id = %s >\n" ,var_name.c_str());
		}
		else
			fprintf(ASToutfile, "<id = %s , size = %d >\n", var_name.c_str(), array_size);
	}

	virtual void visit(IdtypeASTnode& node){
		fprintf(ASToutfile,"IdtypeASTnode\n");
		fprintf(ASToutfile,"datatype = %s\n", node.getType().c_str());
		fprintf(ASToutfile,"var_name = %s\n", node.getId().c_str());
	}

	virtual void visit(VarlistASTnode& node){
		fprintf(ASToutfile,"VarlistASTnode\n");
		vector<class IdASTnode*> var_names = node.getVarList();
		for(uint i=0; i< var_names.size();i++)
			var_names[i]->accept(*this);
	}

	virtual void visit(FielddeclASTnode& node){
		fprintf(ASToutfile,"FielddeclASTnode\n");
		class VarlistASTnode * var_names = node.getVarList();
		var_names->accept(*this);
	}

	virtual void visit(FielddecllistASTnode& node){
		fprintf(ASToutfile,"FielddecllistASTnode\n");
		vector<class FielddeclASTnode*> field_decl_list = node.getFielddeclList();
		for(uint i=0; i<field_decl_list.size();i++)
			field_decl_list[i]->accept(*this);
	}

	virtual void visit(IdlistASTnode& node){
		fprintf(ASToutfile,"IdlistASTnode\n");
		vector<class IdASTnode*> var_list = node.getIdlist();
		for(uint i=0; i<var_list.size();i++)
			var_list[i]->accept(*this);
	}

	virtual void visit(IdtypelistASTnode& node){
		fprintf(ASToutfile,"IdtypelistASTnode\n");
		vector<class IdtypeASTnode*> var_list = node.getIdtypelist();
		for(int i=var_list.size()-1; i>=0 ;i--)
			var_list[i]->accept(*this);
	}

	virtual void visit(VardeclASTnode &node){
		fprintf(ASToutfile,"VardeclASTnode\n");
		fprintf(ASToutfile,"<datatype = %s\n",node.getdataType().c_str());
		class IdlistASTnode * var_list = node.getIdlist();
		var_list->accept(*this);
	}

	virtual void visit(VardecllistASTnode &node){
		fprintf(ASToutfile,"VardecllistASTnode\n");
		vector<class VardeclASTnode *> var_decl_list = node.getVardeclList();
		for(int i=0; i< sz(var_decl_list) ;i++)
			var_decl_list[i]->accept(*this);
	}

	virtual void visit(MethoddeclASTnode &node){
		fprintf(ASToutfile,"MethoddeclASTnode\n");
		fprintf(ASToutfile,"<returntype = %s\n",node.getreturnType().c_str());
		fprintf(ASToutfile,"<methodname = %s\n", node.getId().c_str());
		class IdtypelistASTnode * var_list = node.getIdlist();
		var_list->accept(*this);
		class BlockstatementASTnode * block = node.getBlock();
		block->accept(*this);
	}

	virtual void visit(MethoddecllistASTnode &node){
		fprintf(ASToutfile,"MethoddecllistASTnode\n");
		vector<class MethoddeclASTnode *> method_decl_list = node.getMethoddeclList();
		for(int i=0; i< sz(method_decl_list) ;i++)
			method_decl_list[i]->accept(*this);
	}

	virtual void visit(StatementASTnode &node){
		fprintf(ASToutfile,"StatementASTnode\n");
	}

	virtual void visit(StatementlistASTnode &node){
		fprintf(ASToutfile,"StatementlistASTnode\n");
		vector<class StatementASTnode*> statements_list = node.getStatementsList();
		for(int i=0; i< sz(statements_list) ;i++){
			statements_list[i]->accept(*this);
		}
	}

	virtual void visit(BreakstatementASTnode &node){
		fprintf(ASToutfile,"BreakStatementASTnode\n");
	}

	virtual void visit(ContinuestatementASTnode &node){
		fprintf(ASToutfile,"ContinuestatementASTnode\n");
	}

	virtual void visit(ReturnstatementASTnode &node){
		fprintf(ASToutfile,"ReturnstatementASTnode\n");
		class ExprASTnode * expr = node.getExpr();
		if(expr == NULL){

		}
		else{
			expr->accept(*this);
		}
	}

	virtual void visit(BlockstatementASTnode &node){
		fprintf(ASToutfile,"BlockstatementASTnode\n");
		class VardecllistASTnode * var_decl_list = node.getVardeclList();
		class StatementlistASTnode * statements_list = node.getStatementsList();
		var_decl_list->accept(*this);
		statements_list->accept(*this);
	}

	virtual void visit(ForstatementASTnode &node){
		fprintf(ASToutfile,"ForstatementASTnode\n");
		fprintf(ASToutfile,"<varname = %s\n",node.getId().c_str());
		class ExprASTnode * initial_cond = node.getInitialcond();
		fprintf(ASToutfile,"Initial condn\n");
		initial_cond->accept(*this);
		class ExprASTnode * break_cond = node.getBreakcond();
		fprintf(ASToutfile,"Break condn\n");
		break_cond->accept(*this);
		class BlockstatementASTnode * block = node.getBlockstatement();
		fprintf(ASToutfile,"Block statement\n");
		block->accept(*this);
	}

	virtual void visit(IfelseASTnode &node){
		fprintf(ASToutfile,"IfelseASTnode\n");
		class ExprASTnode * cond = node.getCond();
		fprintf(ASToutfile,"Condition\n");
		cond->accept(*this);
		class BlockstatementASTnode * ifstatement = node.getIfstatement();
		fprintf(ASToutfile,"If statement\n");
		ifstatement->accept(*this);
		class BlockstatementASTnode * elsestatement = node.getElsestatement();
		if(elsestatement != NULL){
			fprintf(ASToutfile,"Else statement\n");
			elsestatement->accept(*this);
		}
	}

	virtual void visit(LocationASTnode &node){
		fprintf(ASToutfile,"LocationASTnode\n");
		fprintf(ASToutfile,"<varname = %s\n",node.getId().c_str());
		class ExprASTnode * expr = node.getExpr();
		if(expr == NULL){

		}
		else{
			expr->accept(*this);
		}
	}

	virtual void visit(AssignstatementASTnode &node){
		fprintf(ASToutfile,"AssignstatementASTnode\n");
		class LocationASTnode * location = node.getLocation();
		location->accept(*this);
		fprintf(ASToutfile,"<operator = %s\n",node.getOp().c_str());
		class ExprASTnode * expr = node.getExpr();
		expr->accept(*this);
	}


	virtual void visit(MethodASTnode &node){
		fprintf(ASToutfile,"MethodASTnode\n");
	}

	virtual void visit(MethodArgsASTnode &node){
		fprintf(ASToutfile,"MethodArgsASTnode\n");
		vector<class ExprASTnode *> arguments_list = node.getArgumentsList();
		for(int i=0; i< sz(arguments_list) ;i++)
			arguments_list[i]->accept(*this);
	}

	virtual void visit(DefinedMethodASTnode &node){
		fprintf(ASToutfile,"DefinedMethodASTnode\n");
		string method_name = node.getMethodName();
		class MethodArgsASTnode* arguments_list = node.getArgsList();
		fprintf(ASToutfile,"defined method name = %s\n",method_name.c_str());
		arguments_list->accept(*this);
	}

	virtual void visit(CalloutargASTnode &node){
		fprintf(ASToutfile,"CalloutargASTnode\n");
	}

	virtual void visit(ExprargASTnode &node){
		fprintf(ASToutfile,"ExprargASTnode\n");
		class ExprASTnode * expr_argument = node.getArgument();
		expr_argument->accept(*this);
	}

	virtual void visit(StringargASTnode &node){
		fprintf(ASToutfile,"StringargASTnode\n");
		string argument =  node.getArgument();
		fprintf(ASToutfile,"<string arg = %s\n", argument.c_str());
	}
	virtual void visit(CalloutArgsASTnode &node){
		fprintf(ASToutfile,"CalloutArgsASTnode\n");
		vector<class CalloutargASTnode *> arguments_list = node.getArgumentsList();
		for(int i=0; i< sz(arguments_list) ;i++)
			arguments_list[i]->accept(*this);
	}

	virtual void visit(CalloutMethodASTnode &node){
		fprintf(ASToutfile,"CalloutMethodASTnode\n");
		fprintf(ASToutfile,"<call out methodname = %s\n",node.getMethodName().c_str());
		class CalloutArgsASTnode* arguments_list = node.getArgsList();
		arguments_list->accept(*this);
	}

	virtual void visit(ProgramASTnode& node){
		fprintf(ASToutfile,"ProgramASTnode\n");
		class FielddecllistASTnode* field_decl_list = node.getFielddeclList();
		class MethoddecllistASTnode* method_decl_list = node.getMethoddeclList();
		field_decl_list->accept(*this);
		if(method_decl_list != NULL)
			method_decl_list->accept(*this);
	}
};
