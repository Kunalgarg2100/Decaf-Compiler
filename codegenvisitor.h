#ifndef _CodeGenVisitor_H
#define _CodeGenVisitor_H

#include <cstdio>
#include <cctype>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "ast.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#define sz(a) (int)a.size()
using namespace std;
static LLVMContext mycontext;
static Module *Module_Ob = new Module("Decaff", mycontext);;
static IRBuilder<> Builder(mycontext);
static std::map<std::string, Value*>Named_Values;

class codegenvisitor : public CodeGenvisitor
{
 public:
 	void LogError(const char *Str) {
  		fprintf(stderr, "LogError: %s\n", Str);
	}

 	Value * LogErrorV(const char *Str) {
  		LogError(Str);
  		return nullptr;
	}

 	virtual Value * Codegen(ASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(ExprASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(BinaryExprASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(UnaryExprASTnode& node){
 		ExprASTnode * expr = node.getExpr();
 		Value * val = expr->codegen(*this);
 		string unary_operator = node.getOp();
 		if(unary_operator == "!")
 			return Builder.CreateNot(val,"not");
 		else if(unary_operator == "-")
 			return Builder.CreateNeg(val,"neg");
 		
 		return	LogErrorV("Unknown unary_operator");
 	}

 	virtual Value * Codegen(LitExprASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(IntLitExprASTnode& node){
 		return ConstantInt::get(mycontext, APInt(32,node.getIntLit()));
 	}

 	virtual Value * Codegen(BoolLitExprASTnode& node){
 		bool val;
 		string str = node.getBoolLit();
 		if(str.compare("true") == 0){
 			val = true;
 		}
 		else{
 			val = false;
 		}
 		return ConstantInt::get(mycontext, APInt(32,val));
 	}

 	virtual Value * Codegen(CharLitExprASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(IdASTnode& node, Type * datatype){
 		fprintf(stdout,"IdASTnode\n");
		int array_size = node.getSize();
		string var_name = node.getId().c_str();
		if(array_size == -1) {
			fprintf(stdout, "<id = %s >\n" ,var_name.c_str());
			cout << datatype << endl;
			GlobalVariable * var = new GlobalVariable(*Module_Ob, datatype, false, GlobalValue::CommonLinkage, 0, var_name);
			var->setInitializer(ConstantInt::get(datatype, 0, true)); 
		}
		else {
			ArrayType* arrayType = ArrayType::get(datatype, array_size);
			GlobalVariable * var = new GlobalVariable(* Module_Ob, arrayType , false, GlobalValue::CommonLinkage, 0, var_name);
			var->setInitializer(ConstantAggregateZero::get(arrayType)); 

			// fprintf(stdout, "<id = %s , size = %d >\n", var_name.c_str(), array_size);
		}
 		return NULL; 		
 	}

 	virtual Value * Codegen(IdtypeASTnode& node){
 		return NULL;
	}

	virtual Value * Codegen(VarlistASTnode& node, Type * datatype){
		fprintf(stdout,"VarlistASTnode\n");
		vector<class IdASTnode*> var_names = node.getVarList();
		for(uint i=0; i< var_names.size();i++)
			var_names[i]->codegen(*this, datatype);

 		return NULL;
	}

	virtual Value * Codegen(FielddeclASTnode& node){
 		fprintf(stdout,"FielddeclASTnode\n");
 		Type * datatype;
 		// Value * val = NULL;
		string data_type = node.getdataType();
		if(data_type == "int")
			datatype = Type::getInt32Ty(mycontext);
		else if (data_type == "boolean")
			datatype = Type::getInt1Ty(mycontext);
		else
			datatype = Type::getVoidTy(mycontext);

		class VarlistASTnode * var_names = node.getVarList();
		var_names->codegen(*this,datatype);

 		return NULL;
	}

 	virtual Value * Codegen(FielddecllistASTnode& node){
 		fprintf(stdout,"FielddecllistASTnode\n");
		vector<class FielddeclASTnode*> field_decl_list = node.getFielddeclList();
		for(uint i=0; i<field_decl_list.size();i++)
			field_decl_list[i]->codegen(*this);

		return NULL;

 	}

 	virtual Value * Codegen(IdlistASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(IdtypelistASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(VardeclASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(MethoddeclASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(VardecllistASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(MethoddecllistASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(StatementASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(StatementlistASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(BreakstatementASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(ContinuestatementASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(ReturnstatementASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(BlockstatementASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(ForstatementASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(IfelseASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(LocationASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(AssignstatementASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(MethodASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(MethodArgsASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(DefinedMethodASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(CalloutargASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(ExprargASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(StringargASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(CalloutArgsASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(CalloutMethodASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(ProgramASTnode& node){
 		fprintf(stdout,"ProgramASTnode\n");
 		Value * val = NULL;
		class FielddecllistASTnode* field_decl_list = node.getFielddeclList();
		class MethoddecllistASTnode* method_decl_list = node.getMethoddeclList();
		val = field_decl_list->codegen(*this);
		cout << val << endl;
		//if(method_decl_list != NULL)
		//	val = method_decl_list->codegen(*this);
		Module_Ob->print(llvm::errs(), nullptr);
 		return val;
 	}
};

#endif
