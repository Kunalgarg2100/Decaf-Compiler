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
static std::map<std::string, llvm::AllocaInst *> Named_Values;

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

	/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
	// the function.  This is used for mutable variables etc.
	/* https://llvm.org/docs/tutorial/LangImpl07.html */
	static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, string &VarName, Type * datatype) {
  		IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
  		return TmpB.CreateAlloca(datatype, 0, VarName.c_str());
	}

 	virtual Value * Codegen(ASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(ExprASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(BinaryExprASTnode& node){
 		// cout << "BINARY" << endl;
 		ExprASTnode * leftexpr = node.getLeft();
		ExprASTnode * rightexpr = node.getRight();
		string binop = node.getOp();
		Value * left = leftexpr->codegen(*this);
		Value * right = rightexpr->codegen(*this);
		Value * val = nullptr;
		/* http://llvm.org/doxygen/classllvm_1_1BinaryOperator.html 
		http://llvm.org/doxygen/classllvm_1_1IRBuilder.html */
		if(!binop.compare("+")){
    		val = Builder.CreateAdd(left,right,"addop");
		}
		else if(!binop.compare("-")){
			// cout << "NE -" << endl;
			val = Builder.CreateSub(left,right,"subop");
		}
		else if(!binop.compare("%")){
			val = Builder.CreateSRem(left,right,"modop");
		}
		else if(!binop.compare("*")){
			val = Builder.CreateMul(left,right,"multop");
		}
		else if(!binop.compare("/")){
			val = Builder.CreateSDiv(left,right,"divop");
		}
		else if(!binop.compare(">")){
			val = Builder.CreateICmpSGT(left,right,"gtop");
		}
		else if(!binop.compare("<")){
			val = Builder.CreateICmpSLT(left,right,"ltvop");
		}
		else if(!binop.compare(">=")){
			val = Builder.CreateICmpSGE(left,right,"gteqop");
		}
		else if(!binop.compare("<=")){
			val = Builder.CreateICmpSLE(left,right,"lteqop");
		}
		else if(!binop.compare("==")){
			val = Builder.CreateICmpEQ(left,right,"eqop");
		}
		else if(!binop.compare("!=")){
			val = Builder.CreateICmpNE(left,right,"neqop");
		}
		else if(!binop.compare("&&")){
			val = Builder.CreateAnd(left,right,"andop");
		}
		else if(!binop.compare("||")){
			val = Builder.CreateOr(left,right,"orop");			
		}
 		return val;
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
		// fprintf(stdout,"IntLitExprASTnode\n");		
 		// cout << node.getIntLit() << endl;
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
 		// fprintf(stdout,"IdASTnode\n");
		int array_size = node.getSize();
		string var_name = node.getId().c_str();
		if(array_size == -1) {
			// fprintf(stdout, "<id = %s >\n" ,var_name.c_str());
			// cout << datatype << endl;
			GlobalVariable * var = new GlobalVariable(*Module_Ob, datatype, false, GlobalValue::CommonLinkage, 0, var_name);
			var->setInitializer(ConstantInt::get(datatype, 0, true)); 
		}
		else {
			ArrayType* arrayType = ArrayType::get(datatype, array_size);
			GlobalVariable * var = new GlobalVariable(*Module_Ob, arrayType , false, GlobalValue::CommonLinkage, 0, var_name);
			var->setInitializer(ConstantAggregateZero::get(arrayType)); 

			// fprintf(stdout, "<id = %s , size = %d >\n", var_name.c_str(), array_size);
		}
 		return NULL; 		
 	}

 	

	virtual Value * Codegen(VarlistASTnode& node, Type * datatype){
		// fprintf(stdout,"VarlistASTnode\n");
		vector<class IdASTnode*> var_names = node.getVarList();
		for(uint i=0; i< var_names.size();i++)
			var_names[i]->codegen(*this, datatype);

 		return NULL;
	}

	virtual Value * Codegen(FielddeclASTnode& node){
 		// fprintf(stdout,"FielddeclASTnode\n");
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
 		// fprintf(stdout,"FielddecllistASTnode\n");
		vector<class FielddeclASTnode*> field_decl_list = node.getFielddeclList();
		for(uint i=0; i<field_decl_list.size();i++)
			field_decl_list[i]->codegen(*this);
		return NULL;

 	}

 	virtual Value * Codegen(IdlistASTnode& node){
 		return NULL;
 	}

 	virtual Value * Codegen(VardeclASTnode &node){
		// fprintf(stdout,"VardeclASTnode\n");
		/* https://llvm.org/docs/tutorial/LangImpl05.html */
		/* The first line gets the current Function object that is being built. It gets this by asking the 
		builder for the current BasicBlock, and asking that block for its “parent” (the function it is currently embedded into).*/
		Function *TheFunction = Builder.GetInsertBlock()->getParent();
		Type * datatype;
		string data_type = node.getdataType().c_str();
		if(data_type == "int")
			datatype = Type::getInt32Ty(mycontext);
		else if (data_type == "boolean")
			datatype = Type::getInt1Ty(mycontext);
		else
			LogErrorV("Invalid return type");

		class IdlistASTnode * varlist = node.getIdlist();
		vector<class IdASTnode*> var_list = varlist->getIdlist();
		for(int i=0;i < sz(var_list);i++){
			string var_name = var_list[i]->getId();
			AllocaInst * alloca = CreateEntryBlockAlloca(TheFunction,var_name, datatype);
			if(data_type == "int"){
  			alloca->setAlignment(4);
  			/* initializing variables to 0 */
  			Value * initval = ConstantInt::get(mycontext, APInt(32,0));
  			Builder.CreateAlignedStore(initval, alloca, 4);
  		}
  		else{
  			Value * initval = ConstantInt::get(mycontext, APInt(1,0));
  			Builder.CreateStore(initval, alloca);
  		}
  			// Old_vals[var] = NamedValues[var];
    		Named_Values[var_name] = alloca;
		}
 		return NULL;
 	}

 	 virtual Value * Codegen(VardecllistASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(MethoddeclASTnode &node){
 		// fprintf(stdout,"MethoddeclASTnode\n");
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

		// fprintf(stdout,"<returntype = %s\n", methodName.c_str());
		// fprintf(stdout,"<methodname = %s\n", return_type.c_str());
		
		vector<Type*> argTypes;
		vector<string> argNames;
		vector<string> arryt;
		class IdtypelistASTnode * vlist = node.getIdlist();
		vector<class IdtypeASTnode*> var_list  = vlist->getIdtypelist();
		
		for(int i=var_list.size()-1; i>=0 ;i--){
			Type * datatype;
			string data_type = var_list[i]->getType().c_str();
			string var_name = var_list[i]->getId().c_str();
			// cout << var_name << endl;
			if(data_type == "int")
		 		datatype = Type::getInt32Ty(mycontext);
			else if (data_type == "boolean")
				datatype = Type::getInt1Ty(mycontext);
			else
				LogErrorV("Invalid data type of Function argument");
			argTypes.push_back(datatype);
			argNames.push_back(var_name);
			arryt.push_back(data_type);
		}


		/* https://llvm.org/docs/tutorial/LangImpl03.html */
		FunctionType * functiontype = FunctionType::get(returntype, argTypes, false);
		Function *TheFunction = Function::Create(functiontype, Function::ExternalLinkage, methodName, Module_Ob);
		// Function::arg_iterator arg_it = TheFunction->arg_begin();
		/*set the name of each of the function’s arguments according to the names given in the Prototype. */
		/* This step isn’t strictly necessary, but keeping the names consistent makes the IR more readable, and allows 
		subsequent code to refer directly to the arguments for their names, rather than having to look up them up in the Prototype AST.*/

  		BasicBlock *BB = BasicBlock::Create(mycontext, "entry", TheFunction);
  		Builder.SetInsertPoint(BB);

  		// Record the function arguments in the NamedValues map.
		unsigned Idx = 0;
  		for (auto &Arg : TheFunction->args()){
  			Arg.setName(argNames[Idx]);
  			AllocaInst * alloca = CreateEntryBlockAlloca(TheFunction, argNames[Idx], argTypes[Idx]);
  			alloca->setAlignment(4);
  			Builder.CreateAlignedStore(&Arg, alloca, 4);
  			// cout << Idx << argNames[Idx] << endl;
  			Named_Values[argNames[Idx]] = alloca;
  			Idx++;
  		}
  		Value * retval = Block->codegen(*this);
  		// if(return_type == "void")
    		// Builder.CreateRet(NULL);

  		if (retval) {
  			if(return_type != "void"){
				Builder.CreateRet(retval);
			}
			else {
				Builder.CreateRet(NULL);
			}
		}
		else
			Builder.CreateRet(NULL);
		
		// verifyFunction(*TheFunction);
    	return TheFunction;
 	}

 	virtual Value * Codegen(MethoddecllistASTnode &node){
 		// fprintf(stdout,"MethoddecllistASTnode\n");
 		vector<class MethoddeclASTnode *> method_decl_list = node.getMethoddeclList();
		for(int i=0; i< sz(method_decl_list) ;i++)
			method_decl_list[i]->codegen(*this);
 		return NULL;
 	}
 	
 	virtual Value * Codegen(StatementlistASTnode &node){
 		// fprintf(stdout,"StatementlistASTnode\n");
		vector<class StatementASTnode*> statements_list = node.getStatementsList();
		Value * v = ConstantInt::get(mycontext, APInt(32, 0));
		for(int i=0; i< sz(statements_list) ;i++){
			// cout << i << " ";
			v = statements_list[i]->codegen(*this);
		}
 		return v;
 	}

 	virtual Value * Codegen(BreakstatementASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(ContinuestatementASTnode &node){
 		return NULL;
 	}

 	virtual Value * Codegen(ReturnstatementASTnode &node){
 		// Function * Func = Module_Ob->getFunction(method_name);
 		class ExprASTnode * expr = node.getExpr();
 		if(expr == NULL){
 			return NULL;
 		}

 		else{
 			Value * v = expr->codegen(*this);
 			return v;
 		}
 	}

 	virtual Value * Codegen(BlockstatementASTnode &node){
 		// fprintf(stdout,"BlockstatementASTnode\n");
		class VardecllistASTnode * vardecllist = node.getVardeclList();
		vector<class VardeclASTnode *> var_decl_list = vardecllist->getVardeclList();
		for(int i=0; i< sz(var_decl_list) ;i++){
			var_decl_list[i]->codegen(*this);
		}
		class StatementlistASTnode * statements_list = node.getStatementsList();
		// cout << "BLOCKS" << endl;
		Value * v = statements_list->codegen(*this);
 		return v;
 	}

 	virtual Value * Codegen(ForstatementASTnode &node){
 		/*https://llvm.org/docs/tutorial/LangImpl07.html#id1*/
 		// cout << "ForstatementASTnode" << endl;
 		string varName = node.getId().c_str();
 		Function *TheFunction = Builder.GetInsertBlock()->getParent();

 		// Create an alloca for the variable in the entry block.
  		AllocaInst * Alloca = CreateEntryBlockAlloca(TheFunction, varName, Type::getInt32Ty(mycontext));

 		 // Emit the start code first, without 'variable' in scope.
  		class ExprASTnode * initial_cond = node.getInitialcond();
		Value * StartVal = initial_cond->codegen(*this);
		
		class ExprASTnode * break_cond = node.getBreakcond();
		Value * EndCond = break_cond->codegen(*this);

		class BlockstatementASTnode * block = node.getBlockstatement();

		if (!StartVal){
		    return nullptr;
		}

		if (!EndCond){
    		return nullptr;
		}

		// Store the value into the alloca.
  		Builder.CreateAlignedStore(StartVal, Alloca, 4);

		// Make the new basic block for the loop header, inserting after current block
  		BasicBlock *pre_header_basic_block = Builder.GetInsertBlock();
  		BasicBlock *LoopBB = BasicBlock::Create(mycontext, "loop", TheFunction);

  		// Insert an explicit fall through from the current block to the LoopBB.
  		Builder.CreateBr(LoopBB);

  		// Start insertion in LoopBB.
  		Builder.SetInsertPoint(LoopBB);

  		PHINode * Variable = Builder.CreatePHI(Type::getInt32Ty(mycontext), 2, varName);
  		Variable->addIncoming(StartVal, pre_header_basic_block);

  		// Within the loop, the variable is defined equal to the PHI node.  If it
  		// shadows an existing variable, we have to restore it, so save it now.
  		AllocaInst *OldVal = Named_Values[varName];
  		Named_Values[varName] = Alloca;

  		block->codegen(*this);

  		//Setting step value of variable to 1
		Value * StepVal = ConstantInt::get(mycontext,APInt(32,1));

		// Reload, increment, and restore the alloca.  This handles the case where
  		// the body of the loop mutates the variable.
  		Value * CurVar = Builder.CreateAlignedLoad(Alloca, 4, varName);
  		Value * NextVar = Builder.CreateAdd(CurVar, StepVal, "nextvar");

  		Builder.CreateAlignedStore(NextVar, Alloca, 4);

		EndCond = Builder.CreateICmpSLT(NextVar, EndCond , "loopcondition");		
		BasicBlock *LoopEndBB = Builder.GetInsertBlock();
		  		// Create the "after loop" block and insert it.
  		BasicBlock *AfterBB = BasicBlock::Create(mycontext, "afterloop", TheFunction);

  		// Insert the conditional branch into the end of LoopEndBB.
  		Builder.CreateCondBr(EndCond, LoopBB, AfterBB);

  		// Any new code will be inserted in AfterBB.
  		Builder.SetInsertPoint(AfterBB);

  		// Restore the unshadowed variable.
  		if (OldVal)
    		Named_Values[varName] = OldVal;
  		else
    		Named_Values.erase(varName);

  		// Add a new entry to the PHI node for the backedge.
  		Variable->addIncoming(NextVar, LoopEndBB);

 		return ConstantInt::get(mycontext, APInt(32,0));
 	}

 	virtual Value * Codegen(IfelseASTnode &node){
 		// cout << "IFELSENODE" << endl;
		class ExprASTnode * cond = node.getCond();
		Value *CondV = cond->codegen(*this);
		if (!CondV){
			// printf("condnull\n");
    		return nullptr;
		}

		class BlockstatementASTnode * ifstatement = node.getIfstatement();
		class BlockstatementASTnode * elsestatement = node.getElsestatement();

		Function *TheFunction = Builder.GetInsertBlock()->getParent();

		// Create blocks for the then and else cases.  Insert the 'then' block at the
		// end of the function.
		BasicBlock *ThenBB = BasicBlock::Create(mycontext, "then", TheFunction);
		BasicBlock *ElseBB = BasicBlock::Create(mycontext, "else");
		BasicBlock *MergeBB = BasicBlock::Create(mycontext, "ifcont");

		Builder.CreateCondBr(CondV, ThenBB, ElseBB);
		// Emit then value.
  		Builder.SetInsertPoint(ThenBB);

  		// cout << "IF" << endl << endl;
  		Value * ThenV = ifstatement->codegen(*this);

  		if (!ThenV){
  			// cout << "NULL" << "HELLO" << endl;
    		return nullptr;
  		}

    	Builder.CreateBr(MergeBB);
  		// Codegen of 'Then' can change the current block, update ThenBB for the PHI.
  		ThenBB = Builder.GetInsertBlock();

  		// Emit else block.
  		TheFunction->getBasicBlockList().push_back(ElseBB);
  		Builder.SetInsertPoint(ElseBB);
  		if(elsestatement != NULL){
			Value * ElseV = elsestatement->codegen(*this);
			if (!ElseV)
    			return nullptr;
		}
  		// elsestatement->codegen(*this);
  		

    	Builder.CreateBr(MergeBB);
  		// Codegen of 'Else' can change the current block, update ElseBB for the PHI.
  		ElseBB = Builder.GetInsertBlock();

  		// Emit merge block.
  		TheFunction->getBasicBlockList().push_back(MergeBB);
  		Builder.SetInsertPoint(MergeBB);
  		// PHINode *PN = Builder.CreatePHI(Type::getDoubleTy(mycontext), 2, "iftmp");

  		// PN->addIncoming(ThenV, ThenBB);
  		// PN->addIncoming(ElseV, ElseBB);
  		Value *V = ConstantInt::get(mycontext, APInt(32, 0));
		return V;
 	}

 	virtual Value * Codegen(LocationASTnode &node){
 		string varname = node.getId();
 		// cout << varname << '\n';
 		Value* v = Named_Values[varname];
 		if(!v){
 			v = Module_Ob->getNamedGlobal(varname);
 		}
 		if(!v){
 			LogErrorV("Unknown variable");
 		}
		class ExprASTnode * expr = node.getExpr();
		if(expr == NULL){
 			// cout << "LOC2" << endl;
			v = Builder.CreateLoad(v);
			return v;
		}
		else{
 			// cout << "LOC1" << endl;

			Value * pos = expr->codegen(*this);

			// cout << "SFSF" << endl;
			if(!pos) {
				// cout << "pro" << endl;
				return NULL;
			}
			vector<Value*> indices;
			indices.push_back(Builder.getInt32(0));
			indices.push_back(pos);
			// v = Builder.CreateGEP(Type::getInt32Ty(mycontext), v, indices);
			v = Builder.CreateGEP(v, indices, varname + "INDEX");
			v = Builder.CreateLoad(v);
			return v;

		}
 		return NULL;
 	}

 	virtual Value * Codegen(AssignstatementASTnode &node){
 		class LocationASTnode * location = node.getLocation();
 		string varname = location->getId();
 		Value* v = Named_Values[varname];
 		if(!v){
 			v = Module_Ob->getNamedGlobal(varname);
 		}
 		if(!v){
 			LogErrorV("Unknown variable");
 		}
 		class ExprASTnode * expr = location->getExpr();
		if(expr != NULL){
			Value * pos = expr->codegen(*this);
			vector<Value*> indices;
			indices.push_back(Builder.getInt32(0));
			indices.push_back(pos);
			v = Builder.CreateGEP(v, indices, varname + "INDEX");
		}
 		Value* cur = v;

 		class ExprASTnode * nodeexpr = node.getExpr();
		Value * val = nodeexpr->codegen(*this);
  	// 	if(cur == 0){
   //  		return LogErrorV("Unknown Variable Name");
  	// 	}

 		// class ExprASTnode * expr = node.getExpr();
  		// cout << "DSDFSD";
 		string op = node.getOp();
 		// cout << op << endl;

 		if(op == "+="){
    		val = Builder.CreateAdd(Builder.CreateLoad(cur,varname), val,"addEqop");
  		}
  		else if (op == "-="){
    		val = Builder.CreateSub(Builder.CreateLoad(cur,varname), val,"subEqop");
  		}

  		return Builder.CreateAlignedStore(val, cur, 4);
 	}

 	virtual Value * Codegen(MethodASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(MethodArgsASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(DefinedMethodASTnode &node){
		string method_name = node.getMethodName();
		class MethodArgsASTnode* argslist = node.getArgsList();
		vector<class ExprASTnode *> arguments_list = argslist->getArgumentsList();

		Function * Func = Module_Ob->getFunction(method_name);
		if(Func == NULL){
			LogErrorV("Function not defined");
		}

		vector<Value* > args;
		
		for(int i=0; i< sz(arguments_list) ;i++){
			Value * v = arguments_list[i]->codegen(*this);
			args.push_back(v);
		}

 		Value * v = Builder.CreateCall(Func,args);
 		return v;
 	}
 	
 	virtual Value * Codegen(CalloutargASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(ExprargASTnode &node){
 		class ExprASTnode * expr_argument = node.getArgument();
		Value * val = expr_argument->codegen(*this);
 		return val;
 	}
 	
 	virtual Value * Codegen(StringargASTnode &node){
 		string argument =  node.getArgument();
 		// cout << "arg" << argument <<endl;
 		Value * v = Builder.CreateGlobalStringPtr(argument);
 		return v;
 	}
 	
 	virtual Value * Codegen(CalloutArgsASTnode &node){
 		return NULL;
 	}
 	
 	virtual Value * Codegen(CalloutMethodASTnode &node){
 		string method_name = node.getMethodName();
 		// cout << "m" << method_name << endl;
 		class CalloutArgsASTnode * arglist = node.getArgsList();
 		vector<class CalloutargASTnode *> arguments_list = arglist->getArgumentsList();

 		vector<Value* > args;
		for(int i=0; i< sz(arguments_list) ;i++){
			Value *v = arguments_list[i]->codegen(*this);
			args.push_back(v);
		}

/*https://stackoverflow.com/questions/35526075/llvm-how-to-implement-print-function-in-my-language*/
		Constant * Func = Module_Ob->getOrInsertFunction(method_name, 
														FunctionType::get(IntegerType::getInt32Ty(mycontext), 
																		PointerType::get(Type::getInt8Ty(mycontext), 0),
																		true));
		if(!Func) return NULL;
 		Value * v = Builder.CreateCall(Func,args,"call");
  		return v;
 	}

 	virtual Value * Codegen(ProgramASTnode& node){
 		// fprintf(stdout,"ProgramASTnode\n");
		class FielddecllistASTnode* field_decl_list = node.getFielddeclList();
		class MethoddecllistASTnode* method_decl_list = node.getMethoddeclList();
		field_decl_list->codegen(*this);
		if(method_decl_list != NULL)
			method_decl_list->codegen(*this);
		freopen ("IR_output.txt","w",stderr);
		Module_Ob->print(llvm::errs(), nullptr);
		fclose (stdout);
 		return NULL;
 	}
};

#endif
