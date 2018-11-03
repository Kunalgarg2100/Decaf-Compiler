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
static Module *Module_Ob;
static LLVMContext mycontext;
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
 			return NULL;
 		else if(unary_operator == "-")
 			return NULL;
 		
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

 	virtual Value * Codegen(IdASTnode& node){
 		return NULL; 		
 	}

 	virtual Value * Codegen(IdtypeASTnode& node){
 		return NULL;
	}

	virtual Value * Codegen(VarlistASTnode& node){
 		return NULL;
	}

	virtual Value * Codegen(FielddeclASTnode& node){
 		return NULL;
	}

 	virtual Value * Codegen(FielddecllistASTnode& node){
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
 		return NULL;
 	}
};

#endif
