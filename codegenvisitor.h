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
		string data_type = node.getdataType().c_str();
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

 // 	virtual Value * Codegen(IdtypeASTnode& node){
 // 		fprintf(stdout,"IdtypeASTnode\n");
 // 		Type * datatype;
	// 	string data_type = node.getType().c_str();
	// 	if(data_type == "int")
	// 		datatype = Type::getInt32Ty(mycontext);
	// 	else if (data_type == "boolean")
	// 		datatype = Type::getInt1Ty(mycontext);

	// 	
 // 		return NULL;
	// }

 	virtual Value * Codegen(IdlistASTnode& node){
 		return NULL;
 	}

 	// virtual Value * Codegen(IdtypelistASTnode& node){
 	// // 	fprintf(stdout,"IdtypelistASTnode\n");
		// // vector<class IdtypeASTnode*> var_list = node.getIdtypelist();
		// // for(uint i=0; i<var_list.size();i++)
		// // 	var_list[i]->codegen(*this);
 	// 	return NULL;
 	// }

 	virtual Value * Codegen(VardeclASTnode &node){
 		return NULL;
 	}

 	 virtual Value * Codegen(VardecllistASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(MethoddeclASTnode &node){
 		fprintf(stdout,"MethoddeclASTnode\n");
		// fprintf(stdout,"<returntype = %s\n",);
		string methodName = node.getId().c_str();
		class BlockstatementASTnode * Block = node.getBlock();
		
		Type * returntype;
		string return_type = node.getreturnType().c_str();
		if(return_type == "int")
			returntype = Type::getInt32Ty(mycontext);
		else if (return_type == "boolean")
			returntype = Type::getInt1Ty(mycontext);
		else if (return_type == "void")
			returntype = Type::getVoidTy(mycontext);
		else
			LogErrorV("Invalid return type");

		fprintf(stdout,"<returntype = %s\n", methodName.c_str());
		fprintf(stdout,"<methodname = %s\n", return_type.c_str());
		
		vector<Type*> argTypes;
		vector<string> argNames;
		class IdtypelistASTnode * vlist = node.getIdlist();
		vector<class IdtypeASTnode*> var_list  = vlist->getIdtypelist();
		
		for(uint i=0; i<var_list.size();i++){
			Type * datatype;
			string data_type = var_list[i]->getType().c_str();
			string var_name = var_list[i]->getId().c_str();
			if(data_type == "int")
		 		datatype = Type::getInt32Ty(mycontext);
			else if (data_type == "boolean")
				datatype = Type::getInt1Ty(mycontext);
			else
				LogErrorV("Invalid data type of Function argument");
			argTypes.push_back(datatype);
			argNames.push_back(var_name);
		}


		/* https://llvm.org/docs/tutorial/LangImpl03.html */
		FunctionType * functiontype = FunctionType::get(returntype, argTypes, false);
		Function *TheFunction = Function::Create(functiontype, Function::ExternalLinkage, methodName, Module_Ob);
		
		/*set the name of each of the function’s arguments according to the names given in the Prototype. */
		/* This step isn’t strictly necessary, but keeping the names consistent makes the IR more readable, and allows 
		subsequent code to refer directly to the arguments for their names, rather than having to look up them up in the Prototype AST.*/

		unsigned Idx = 0;
		for (auto &Arg : TheFunction->args())
  			Arg.setName(argNames[Idx++]);

  		BasicBlock *BB = BasicBlock::Create(mycontext, "entry", TheFunction);
  		Builder.SetInsertPoint(BB);

  		// Record the function arguments in the NamedValues map.
  		Named_Values.clear();
  		for (auto &Arg : TheFunction->args())
    		Named_Values[Arg.getName()] = &Arg;

    	Builder.CreateRet(NULL);


  		/*if (Value *RetVal = Block->codegen(*this)) {
    		// Finish off the function.

    		// Validate the generated code, checking for consistency.
    		verifyFunction(*TheFunction);
    		return TheFunction;
  		}

  		// Error reading body, remove function.
  		TheFunction->eraseFromParent();*/
  		return nullptr;

 	}

 	virtual Value * Codegen(MethoddecllistASTnode &node){
 		fprintf(stdout,"MethoddecllistASTnode\n");
 		vector<class MethoddeclASTnode *> method_decl_list = node.getMethoddeclList();
		for(int i=0; i< sz(method_decl_list) ;i++)
			method_decl_list[i]->codegen(*this);
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
		class FielddecllistASTnode* field_decl_list = node.getFielddeclList();
		class MethoddecllistASTnode* method_decl_list = node.getMethoddeclList();
		field_decl_list->codegen(*this);
		if(method_decl_list != NULL)
			method_decl_list->codegen(*this);
		Module_Ob->print(llvm::errs(), nullptr);
 		return NULL;
 	}
};

#endif
