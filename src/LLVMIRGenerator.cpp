#if !defined(LLVMIRGenerator_cpp)
#define LLVMIRGenerator_cpp

#include <llvm/Support/raw_ostream.h>
#include <LLVMIRGenerator.hpp>
#include <Printer.hpp>
#include <iostream>
#include <vector>


LLVMIRGenerator::LLVMIRGenerator()
    : context(),
      builder(context),
      module(new Module("Decaf compiler", context)),
      error(0),
      debug(false) {}

LLVMIRGenerator::~LLVMIRGenerator() {}

void LLVMIRGenerator::LogError(std::string error_message) {
    std::cerr << error_message << std::endl;
    ++error;
}
void LLVMIRGenerator::LogDebugger(std::string debug_message) {
    if (debug) std::cerr << debug_message << std::endl;
}


AllocaInst* LLVMIRGenerator::CreateEntryBlockAlloca(Function* function,
                                                    std::string variable_name,
                                                    std::string type) {
    /* Get the builder for current context */
    IRBuilder<> TmpB(&function->getEntryBlock(),
                     function->getEntryBlock().begin());
    AllocaInst* alloca_instruction = nullptr;
    if (type == "int") {
        alloca_instruction =
            TmpB.CreateAlloca(Type::getInt32Ty(context), 0, variable_name);
    } else if (type == "boolean") {
        alloca_instruction =
            TmpB.CreateAlloca(Type::getInt1Ty(context), 0, variable_name);
    }
    return alloca_instruction;
}


void LLVMIRGenerator::visit(IntLiteral* int_literal) {
    return_value = ConstantInt::get(context, APInt(32, int_literal->data));
}
void LLVMIRGenerator::visit(BoolLiteral* bool_literal) {
    return_value = ConstantInt::get(context, APInt(1, bool_literal->data));
    // std::cout << "BoolLiteral" << std::endl;
}
void LLVMIRGenerator::visit(CharLiteral* char_literal) {
    return_value = ConstantInt::get(context, APInt(32, char_literal->data));
}
void LLVMIRGenerator::visit(Literal* literal) { literal->accept(this); }

void LLVMIRGenerator::visit(UnaryExpression* unary_expression) {
    unary_expression->accept(this);
}
void LLVMIRGenerator::visit(Statement* statement) { statement->accept(this); }

void LLVMIRGenerator::visit(BinaryExpression* binary_expression) {
    LogDebugger("Binary Expression");
    binary_expression->left_operand->accept(this);
    if (return_value == nullptr) {
        return;
    }
    Value* left_operand = return_value;
    if (binary_expression->left_operand->IsLocation()) {
        left_operand = builder.CreateLoad(left_operand);
    }


    binary_expression->right_operand->accept(this);
    if (return_value == nullptr) {
        return;
    }
    Value* right_operand = return_value;
    if (binary_expression->right_operand->IsLocation()) {
        right_operand = builder.CreateLoad(right_operand);
    }


    std::string op = binary_expression->op;
    return_value = nullptr;

    if (op == "+") {
        return_value = builder.CreateAdd(left_operand, right_operand, "addtmp");
    } else if (op == "-") {
        return_value = builder.CreateSub(left_operand, right_operand, "subtmp");
    } else if (op == "*") {
        return_value = builder.CreateMul(left_operand, right_operand, "multmp");
    } else if (op == "/") {
        return_value =
            builder.CreateSDiv(left_operand, right_operand, "divtmp");
    } else if (op == "%") {
        return_value =
            builder.CreateSRem(left_operand, right_operand, "modtmp");
    } else if (op == "<") {
        return_value =
            builder.CreateICmpSLT(left_operand, right_operand, "ltcomparetmp");
    } else if (op == ">") {
        return_value =
            builder.CreateICmpSGT(left_operand, right_operand, "gtcomparetmp");
    } else if (op == "<=") {
        return_value =
            builder.CreateICmpSLE(left_operand, right_operand, "lecomparetmp");
    } else if (op == ">=") {
        return_value =
            builder.CreateICmpSGE(left_operand, right_operand, "gecomparetmp");
    } else if (op == "==") {
        return_value = builder.CreateICmpEQ(left_operand, right_operand,
                                            "equalcomparetmp");

    } else if (op == "!=") {
        return_value = builder.CreateICmpNE(left_operand, right_operand,
                                            "notequalcomparetmp");
    } else if (op == "||") {
        return_value = builder.CreateOr(left_operand, right_operand, "ortmp");
    } else if (op == "&&") {
        return_value = builder.CreateAnd(left_operand, right_operand, "andtmp");
    } else {
        LogError("invalid binary operation: " + op);
        return_value = nullptr;
    }
    LogDebugger("Binary Expression Ended");
}
void LLVMIRGenerator::visit(Location* location) {
    LogDebugger("Location");
    Value* name = nullptr;
    if (named_values.find(location->var_name) != named_values.end()) {
        name = named_values[location->var_name].top();
    }
    if (name == nullptr) {
        name = module->getNamedGlobal(location->var_name);
    }
    if (name == nullptr) {
        return_value = nullptr;
        LogError("Unknown identifier \"" + location->var_name + "\"");
        return;
    }

    if (location->index == nullptr) {
        return_value = name;
        return;
    } else {
    }
    location->index->accept(this);
    Value* index = return_value;
    if (location->index->IsLocation()) {
        index = builder.CreateLoad(index);
    }
    if (index == nullptr) {
        return_value = nullptr;
        LogError("Invalid Array Index");
        return;
    }

    std::vector<Value*> array_index;
    array_index.push_back(builder.getInt32(0));
    array_index.push_back(index);
    return_value =
        builder.CreateGEP(name, array_index, location->var_name + "_Index");
    LogDebugger("Location Ended");
    return;
}
void LLVMIRGenerator::visit(UnaryOperation* unary_operation) {
    LogDebugger("Unary Operation");
    unary_operation->exp->accept(this);
    if (return_value == nullptr) {
        return;
    }
    Value* expr = return_value;
    if (unary_operation->exp->IsLocation()) {
        expr = builder.CreateLoad(expr);
    }
    if (unary_operation->op == "-") {
        return_value = builder.CreateNeg(expr, "negtmp");
    } else if (unary_operation->op == "!") {
        return_value = builder.CreateNot(expr, "nottmp");
    } else {
        return_value = nullptr;
        LogError("Unidentified unary operator: " + unary_operation->op);
    }
    LogDebugger("Unary Operation Ended");
}
void LLVMIRGenerator::visit(NestedUnaryExpression* nested_unary_expression) {
    LogDebugger("Nested Unary Expression");
    nested_unary_expression->exp->accept(this);
    LogDebugger("Nested Unary Expression Ended");
}
void LLVMIRGenerator::visit(SimpleMethod* simple_method) {
    Debug();
    LogDebugger("Simple Method");
    std::string name = simple_method->method_name;
    if (simple_method->argument_list == nullptr) {
        LogDebugger("Debug");
    }
    std::vector<Expression*> arg_list = simple_method->argument_list->exp_list;
    Function* callee = module->getFunction(name);
    if (callee == nullptr) {
        return_value = nullptr;
        LogError("Cannot fine the function named \"" + name + "\"");
        return;
    }
    if (callee->arg_size() != arg_list.size()) {
        return_value = nullptr;
        LogError("Wrong number of argument provided for '" + name + "'");
        return;
    }
    std::vector<Value*> args;
    for (auto& raw_arg : arg_list) {
        raw_arg->accept(this);
        Value* arg = return_value;
        if (raw_arg->IsLocation()) {
            arg = builder.CreateLoad(arg);
        }
        if (arg == nullptr) {
            LogError("Argument not valid");
            return_value = nullptr;
            return;
        }
        args.push_back(arg);
    }

    return_value = builder.CreateCall(callee, args);
    LogDebugger("Simple Method Ends");
    NotDebug();
    return;
}
void LLVMIRGenerator::visit(CalloutMethod* callout_method) {
    std::string name;
    std::vector<CalloutArg*> raw_arg_list =
        callout_method->arg_list->argument_list;
    std::vector<Value*> arg_list;
    std::vector<llvm::Type*> arg_type_list;
    for (auto& raw_arg : raw_arg_list) {
        raw_arg->accept(this);
        Value* arg = return_value;
        if (arg == nullptr) {
            return_value = nullptr;
            return;
        }
        arg_list.push_back(arg);
        arg_type_list.push_back(arg->getType());
    }
    ArrayRef<llvm::Type*> args_ref(arg_type_list);
    ArrayRef<Value*> funcargs(arg_list);
    FunctionType* FType =
        FunctionType::get(Type::getInt32Ty(context), args_ref, false);
    Constant* func = module->getOrInsertFunction(name, FType);
    if (!func) {
        LogError("Error in inbuilt function. Unknown Function name " + name);
        return_value = nullptr;
        return;
    }
    return_value = builder.CreateCall(func, funcargs);
    return;
}
void LLVMIRGenerator::visit(CalloutArg* callout_arg) {
    LogDebugger("Callout Arg");
    if (callout_arg->argument != nullptr) {
        callout_arg->argument->accept(this);
        Value* arg = return_value;
        if (callout_arg->argument->IsLocation()) {
            arg = builder.CreateLoad(arg);
        }
        return_value = arg;
        return;
    } else if (callout_arg->str_arg != "") {
        return_value = builder.CreateGlobalString(callout_arg->str_arg);
        return;
    } else {
        return_value = nullptr;
        LogError("Bad callout argument");
        return;
    }
}
void LLVMIRGenerator::visit(CalloutArgList* callout_arg_list) {
    LogDebugger("Callout Argument List");
}

void LLVMIRGenerator::visit(AstNode* ast_node) {
    LogDebugger("Ast Node");
    ast_node->accept(this);
}


void LLVMIRGenerator::visit(Expression* expression) {
    LogDebugger("Expression");
    expression->accept(this);
}
void LLVMIRGenerator::visit(ReturnStatement* return_statement) {
    LogDebugger("Return Statement");
    if (return_statement->expression != nullptr) {
        return_statement->expression->accept(this);
        Value* v = return_value;
        if (return_statement->expression->IsLocation()) {
            v = builder.CreateLoad(v);
        }
        return_value = builder.CreateRet(v);
        return;
    } else {
        return_value = builder.CreateRetVoid();
        return;
    }
}
void LLVMIRGenerator::visit(IfStatement* if_statement) {
    // if_statement->exp->accept(new Printer());
    LogDebugger("If Statement");
    if_statement->exp->accept(this);
    Value* expr = return_value;
    if (if_statement->exp->IsLocation()) {
        expr = builder.CreateLoad(expr);
    }
    if (expr == nullptr) {
        LogError("Invalid if expression");
        return_value = nullptr;
        return;
    }
    Function* cur_funtion = builder.GetInsertBlock()->getParent();
    BasicBlock* if_block = BasicBlock::Create(context, "if", cur_funtion);
    BasicBlock* else_block = BasicBlock::Create(context, "else");
    BasicBlock* merge_block = BasicBlock::Create(context, "merge");

    // expr = builder.CreateFCmpONE(expr, ConstantInt::get(context, APInt(32,
    // 0)),
    //                              "ifcond");
    if (if_statement->else_block != nullptr) {
        builder.CreateCondBr(expr, if_block, else_block);
        builder.SetInsertPoint(if_block);
        if_statement->if_block->accept(this);
        Value* if_processed = return_value;
        if (if_processed == nullptr) {
            return_value = nullptr;
            return;
        }
        builder.CreateBr(merge_block);
        if_block = builder.GetInsertBlock();

        cur_funtion->getBasicBlockList().push_back(else_block);
        builder.SetInsertPoint(else_block);
        if_statement->else_block->accept(this);
        Value* else_processed = return_value;
        if (else_processed == nullptr) {
            return_value = nullptr;
            return;
        }
        builder.CreateBr(merge_block);
        else_block = builder.GetInsertBlock();

        cur_funtion->getBasicBlockList().push_back(merge_block);
        builder.SetInsertPoint(merge_block);
        return_value = ConstantInt::get(context, APInt(32, 0));
    } else {
        builder.CreateCondBr(expr, if_block, merge_block);
        builder.SetInsertPoint(if_block);
        if_statement->if_block->accept(this);
        Value* if_processed = return_value;
        if (if_processed == nullptr) {
            return_value = nullptr;
            return;
        }
        builder.CreateBr(merge_block);
        if_block = builder.GetInsertBlock();

        cur_funtion->getBasicBlockList().push_back(merge_block);
        builder.SetInsertPoint(merge_block);
        return_value = ConstantInt::get(context, APInt(32, 0));
    }
}
void LLVMIRGenerator::visit(ForStatement* for_statement) {
    for_statement->start->accept(this);
    Value* start = return_value;
    if (start == nullptr) {
        return_value = nullptr;
        LogError("Bad loop initialization");
        return;
    }
    if (for_statement->start->IsLocation()) {
        start = builder.CreateLoad(start);
    }
    /* Get the parent method of this for loop */
    Function* cur_function = builder.GetInsertBlock()->getParent();
    /* Create memory for the loop variable */
    llvm::AllocaInst* alloca = CreateEntryBlockAlloca(
        cur_function, for_statement->variable_name, "int");
    builder.CreateStore(start, alloca);

    Value* step_val = ConstantInt::get(context, APInt(32, 1));
    BasicBlock* pre_header_basic_block = builder.GetInsertBlock();
    BasicBlock* loop_body = BasicBlock::Create(context, "loop", cur_function);
    BasicBlock* afterBB =
        BasicBlock::Create(context, "afterloop", cur_function);
    builder.CreateBr(loop_body);
    builder.SetInsertPoint(loop_body);


    PHINode* Variable = builder.CreatePHI(Type::getInt32Ty(context), 2,
                                          for_statement->variable_name);
    Variable->addIncoming(start, pre_header_basic_block);
    /* Store the old value */
    for_statement->end->accept(this);
    Value* end = return_value;
    if (end == nullptr) {
        LogError("Invalid Condition");
        return_value = nullptr;
        return;
    }

    // Check if condition is a location
    if (for_statement->end->IsLocation()) {
        end = builder.CreateLoad(end);
    }
    loop_stack.push(new Loop(afterBB, loop_body, end,
                             for_statement->variable_name, Variable));
    if (named_values.find(for_statement->variable_name) == named_values.end()) {
        named_values[for_statement->variable_name] = std::stack<AllocaInst*>();
    }
    named_values[for_statement->variable_name].push(alloca);
    /* Generate the code for the body */
    for_statement->block->accept(this);
    Value* body = return_value;
    if (body == nullptr) {
        return_value = nullptr;
        return;
    }

    Value* cur = builder.CreateLoad(alloca, for_statement->variable_name);
    cur = builder.CreateIntCast(cur, step_val->getType(), true);
    Value* next_val = builder.CreateAdd(cur, step_val, "NextVal");
    builder.CreateStore(next_val, alloca);
    end = builder.CreateIntCast(end, step_val->getType(), true);
    end = builder.CreateICmpSLT(next_val, end, "loopcondition");
    BasicBlock* loopEndBlock = builder.GetInsertBlock();
    builder.CreateCondBr(end, loop_body, afterBB);
    builder.SetInsertPoint(afterBB);
    Variable->addIncoming(next_val, loopEndBlock);
    loop_stack.pop();
    named_values[for_statement->variable_name].pop();
    if (named_values[for_statement->variable_name].empty()) {
        named_values.erase(for_statement->variable_name);
    }
    return_value = ConstantInt::get(context, APInt(32, 1));
    return;
}
void LLVMIRGenerator::visit(ContinueStatement* continue_statement) {
    llvm::Value* V = llvm::ConstantInt::get(context, llvm::APInt(32, 1));
    if (loop_stack.empty()) {
        return_value = nullptr;
        LogError("continue statement must be in a loop");
        return;
    }
    Loop* current_loop = loop_stack.top();
    Expression* condition = nullptr;
    std::string loop_var = current_loop->loop_variable;
    AllocaInst* alloca = named_values[loop_var].top();
    Value* step_val = ConstantInt::get(context, APInt(32, 1));
    Value* cur = builder.CreateLoad(alloca, loop_var);
    Value* next_val = builder.CreateAdd(cur, step_val, "NextVal");
    builder.CreateStore(next_val, alloca);
    llvm::Value* cond = builder.CreateICmpULE(next_val, current_loop->condition,
                                              "loopcondition");
    BasicBlock* loopEndBlock = builder.GetInsertBlock();
    builder.CreateCondBr(cond, current_loop->check_basic_block,
                         current_loop->after_basic_block);
    return_value = V;
    return;
}
void LLVMIRGenerator::visit(BreakStatement* break_statement) {
    return_value = llvm::ConstantInt::get(context, llvm::APInt(32, 1));
    if (loop_stack.empty()) {
        return_value = nullptr;
        LogError("break statement must be in a loop");
        return;
    }
    Loop* currentLoop = loop_stack.top();
    builder.CreateBr(currentLoop->after_basic_block);
    return;
}
void LLVMIRGenerator::visit(MethodCall* method_call) {
    method_call->accept(this);
}
void LLVMIRGenerator::visit(VariableDeclaration* variable_declaration) {
    llvm::Function* cur_function = builder.GetInsertBlock()->getParent();
    for (const auto& var : variable_declaration->id_list->id_list) {
        std::string name = var;
        llvm::Value* initval = nullptr;
        llvm::AllocaInst* Alloca = nullptr;
        if (variable_declaration->type == Int) {
            initval = ConstantInt::get(context, APInt(32, 0));
            Alloca = CreateEntryBlockAlloca(cur_function, var, "int");
        } else if (variable_declaration->type == Bool) {
            initval = ConstantInt::get(context, APInt(1, 0));
            Alloca = CreateEntryBlockAlloca(cur_function, var, "boolean");
        }
        builder.CreateStore(initval, Alloca);
        /* Store the old value to old_vals and new value to named values */
        if (named_values.find(name) == named_values.end()) {
            named_values[name] = std::stack<AllocaInst*>();
        }
        named_values[name].push(Alloca);
        name_stack.top().insert(name);
    }
    return_value = ConstantInt::get(context, APInt(32, 1));
    return;
}
void LLVMIRGenerator::visit(
    VariableDeclarationList* variable_declaration_list) {
    Value* v = ConstantInt::get(context, APInt(32, 1));
    for (auto& decl : variable_declaration_list->var_list) {
        /// Generate the code for each declaration
        decl->accept(this);
        if (return_value == nullptr) {
            return;
        }
    }
    return_value = v;
    return;
}
void LLVMIRGenerator::visit(IdList* id_list) {}

void LLVMIRGenerator::visit(Block* block) {
    name_stack.push(std::set<std::string>());
    block->var_list->accept(this);
    if (return_value == nullptr) {
        return;
    }
    block->statement_list->accept(this);
    if (return_value == nullptr) {
        return;
    }
    for (auto name : name_stack.top()) {
        named_values[name].pop();
        if (named_values[name].empty()) {
            named_values.erase(name);
        }
    }
}

void LLVMIRGenerator::visit(StatementList* statement_list) {
    Value* v = ConstantInt::get(context, llvm::APInt(32, 1));
    for (auto& stmt : statement_list->statements) {
        stmt->accept(this);
        v = return_value;
    }
    return_value = v;
    return;
}

void LLVMIRGenerator::visit(AssignmentStatement* assignment_statement) {
    Value* cur = named_values[assignment_statement->location->var_name].top();
    if (cur == nullptr) {
        cur =
            module->getGlobalVariable(assignment_statement->location->var_name);
    }
    if (cur == nullptr) {
        LogError("Unknown Variable Name " +
                 assignment_statement->location->var_name);
        return_value = nullptr;
        return;
    }

    assignment_statement->expression->accept(this);
    Value* val = return_value;
    if (assignment_statement->expression->IsLocation()) {
        val = this->builder.CreateLoad(val);
    }

    assignment_statement->location->accept(this);
    Value* lhs = return_value;
    cur = this->builder.CreateLoad(lhs);

    if (val == nullptr) {
        return_value = nullptr;
        return;
    }
    if (assignment_statement->assignment_op == "+=") {
        val = this->builder.CreateAdd(cur, val, "addEqualToTmp");
    } else if (assignment_statement->assignment_op == "-=") {
        val = this->builder.CreateSub(cur, val, "subEqualToTmp");
    }
    return_value = this->builder.CreateStore(val, lhs);
    return;
}
void LLVMIRGenerator::visit(ExpressionList* e) {}

void LLVMIRGenerator::visit(MethodDeclaration* method_declaration) {
    std::vector<std::string> argNames;
    std::vector<Types> argTypes;
    std::vector<ArgumentDeclaration*> args =
        method_declaration->arg_list->arg_list;
    std::vector<Type*> arguments;
    auto arg_size = args.size();
    for (auto& arg : args) {
        /* Iterate over the arguments and get the types of them in llvm */
        std::string arg_name = arg->arg_name;
        Types arg_type = arg->type;
        switch (arg->type) {
            case Int: {
                arguments.push_back(Type::getInt32Ty(context));
            } break;
            case Bool: {
                arguments.push_back(Type::getInt1Ty(context));
            } break;
            default: {
                LogError("Arguments can only be int or boolean");
                return_function = nullptr;
                return;
            } break;
        }
        argTypes.push_back(arg_type);
        argNames.push_back(arg_name);
    }

    Type* returnType;
    /* Get the return Type */

    switch (method_declaration->return_type) {
        case Int: {
            returnType = Type::getInt32Ty(context);
        } break;
        case Bool: {
            returnType = Type::getInt1Ty(context);
        } break;
        case Void: {
            returnType = Type::getVoidTy(context);
        } break;
    }

    /* Get the function type and create a Function */
    FunctionType* function_type =
        llvm::FunctionType::get(returnType, arguments, false);
    Function* function =
        llvm::Function::Create(function_type, Function::ExternalLinkage,
                               method_declaration->name, module);

    /* Iterate through arguments and set the Names for them */

    unsigned Idx = 0;
    for (Function::arg_iterator AI = function->arg_begin(); Idx != arg_size;
         ++AI, ++Idx) {
        AI->setName(argNames[Idx]);
    }

    /* Create a New block for this Function */
    BasicBlock* BB = BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(BB);
    Idx = 0;

    /* Allocate memory for the arguments passed */
    name_stack.push(std::set<std::string>());
    for (auto& Arg : function->args()) {
        AllocaInst* alloca = nullptr;
        switch (argTypes[Idx]) {
            case Int: {
                alloca = CreateEntryBlockAlloca(function, argNames[Idx], "int");
            } break;
            case Bool: {
                alloca =
                    CreateEntryBlockAlloca(function, argNames[Idx], "boolean");
            } break;
        }
        builder.CreateStore(&Arg, alloca);
        if (named_values.find(argNames[Idx]) == named_values.end()) {
            named_values[argNames[Idx]] = std::stack<AllocaInst*>();
        }
        named_values[argNames[Idx]].push(alloca);
        name_stack.top().insert(argNames[Idx]);
        Idx++;
    }

    method_declaration->body->accept(this);
    if (return_value) {
        /* make this the return value */
        if (method_declaration->return_type != Void)
            builder.CreateRet(return_value);
        else
            builder.CreateRetVoid();
        /// Iterate through each basic block in this function and remove any
        /// dead code
        // for (auto& basicBlock : *function) {
        //     BasicBlock* block = &basicBlock;
        //     removeDeadCode(block);
        // }
        /* Verify the function */
        // verifyFunction(*function);
        // TheFPM->run(*function);
        return_function = function;
        return;
    }

    /* In case of errors remove the function */
    function->eraseFromParent();
    return_function = nullptr;
    return;
}

void LLVMIRGenerator::visit(MethodStatement* method_statement) {
    method_statement->call->accept(this);
}

void LLVMIRGenerator::visit(ArgumentDeclaration* argument_declaration) {}
void LLVMIRGenerator::visit(
    ArgumentDeclarationList* argument_declaration_list) {}

void LLVMIRGenerator::visit(FieldDeclaration* field_declaration) {
    llvm::Type* ty = nullptr;
    switch (field_declaration->type) {
        case Int: {
            ty = Type::getInt32Ty(context);
        } break;
        case Bool: {
            ty = Type::getInt1Ty(context);
        } break;
    }

    for (auto var : field_declaration->field_list->field_list) {
        /* Allocate one location of global variable for all */
        if (var->size != nullptr) {
            ArrayType* arrType = ArrayType::get(ty, var->size->data);
            GlobalVariable* gv = new GlobalVariable(
                *(module), arrType, false, GlobalValue::ExternalLinkage,
                nullptr, var->name);
            gv->setInitializer(ConstantAggregateZero::get(arrType));
        } else {
            GlobalVariable* gv = new GlobalVariable(
                *(module), ty, false, GlobalValue::ExternalLinkage, nullptr,
                var->name);
            gv->setInitializer(Constant::getNullValue(ty));
        }
    }
    return_value = ConstantInt::get(context, APInt(32, 1));
    return;
}

void LLVMIRGenerator::visit(Field* f) {}
void LLVMIRGenerator::visit(FieldList* f) {}
void LLVMIRGenerator::visit(FieldDeclarationList* field_declaration_list) {
    for (auto& i : field_declaration_list->decl_list) {
        i->accept(this);
    }
    return_value = ConstantInt::get(context, APInt(32, 1));
    return;
}

void LLVMIRGenerator::visit(MethodDeclarationList* method_declaration_list) {
    Value* V = ConstantInt::get(context, APInt(32, 0));
    for (auto& i : method_declaration_list->decl_list) {
        i->accept(this);
        V = return_value;
        if (return_value == nullptr) return;
    }
    return;
}

void LLVMIRGenerator::visit(Program* program) {
    Value* V;
    // Generate code for field Declarations
    program->field_list->accept(this);
    V = return_value;
    if (V == nullptr) {
        LogError("Invalid field Declarations");
        return_value = nullptr;
        return;
    }
    // Generate the code for method Declarations
    program->method_list->accept(this);
    V = return_value;
    if (V == nullptr) {
        return_value = nullptr;
        LogError("Invalid method Declarations");
        return;
    }
    return;
}

void LLVMIRGenerator::GenerateCodeDump() {
    if (error > 0) {
        LogError("Found " + std::to_string(error) +
                 " errors while compilation");
    }
    std::cerr << "Generating LLVM IR Code\n" << std::endl;
    module->print(llvm::outs(), nullptr);
}

#endif  // LLVMIRGenerator_cpp