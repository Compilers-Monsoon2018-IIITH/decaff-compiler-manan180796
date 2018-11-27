#if !defined(LLVMIRGenerator_cpp)
#define LLVMIRGenerator_cpp

#include <LLVMIRGenerator.hpp>
#include <iostream>
#include <vector>

LLVMIRGenerator::LLVMIRGenerator()
    : context(),
      builder(context),
      module(new Module("Decaf compiler", context)) {}

LLVMIRGenerator::~LLVMIRGenerator() {}

void LLVMIRGenerator::LogError(std::string error_message) {
    std::cerr << error_message << std::endl;
    return_value = nullptr;
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
    binary_expression->left_operand->accept(this);
    Value* left_operand = return_value;
    if (binary_expression->left_operand->IsLocation()) {
        left_operand = builder.CreateLoad(left_operand);
    }

    binary_expression->right_operand->accept(this);
    Value* right_operand = return_value;
    if (binary_expression->right_operand->IsLocation()) {
        right_operand = builder.CreateLoad(right_operand);
    }


    std::string op = binary_expression->op;
    return_value = nullptr;
    if (left_operand == nullptr || right_operand == nullptr) return;

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
    } else {
        LogError("invalid binary operation: " + op);
    }
}
void LLVMIRGenerator::visit(Location* location) {
    Value* name = named_values[location->var_name].top();
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
    return;
}
void LLVMIRGenerator::visit(UnaryOperation* unary_operation) {
    unary_operation->exp->accept(this);
    Value* expr = return_value;
    if (unary_operation->exp->IsLocation()) {
        expr = builder.CreateLoad(expr);
    }
    if (unary_operation->op == "-") {
        return_value = builder.CreateNeg(expr, "negtmp");
    } else if (unary_operation->op == "!") {
        return_value = builder.CreateNot(expr, "nottmp");
    } else {
        LogError("Unidentified unary operator: " + unary_operation->op);
    }
    return;
}
void LLVMIRGenerator::visit(NestedUnaryExpression* nested_unary_expression) {
    nested_unary_expression->exp->accept(this);
}
void LLVMIRGenerator::visit(SimpleMethod* simple_method) {
    std::string name = simple_method->method_name;
    std::vector<Expression*> arg_list = simple_method->argument_list->GetList();
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
    }
    return_value = builder.CreateCall(func, funcargs);
    return;
}
void LLVMIRGenerator::visit(CalloutArg* callout_arg) {
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
void LLVMIRGenerator::visit(CalloutArgList* callout_arg_list) {}

void LLVMIRGenerator::visit(AstNode* ast_node) { ast_node->accept(this); }

void LLVMIRGenerator::visit(Expression* expression) {
    expression->accept(this);
}
void LLVMIRGenerator::visit(ReturnStatement* return_statement) {
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

    expr = builder.CreateFCmpONE(expr, ConstantFP::get(context, APFloat(0.0)),
                                 "ifcond");
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

        PHINode* PN = builder.CreatePHI(Type::getDoubleTy(context), 2, "iftmp");
        PN->addIncoming(if_processed, if_block);
        PN->addIncoming(else_processed, else_block);
        return_value = PN;
        return;
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
        return;
    }
}
void LLVMIRGenerator::visit(ForStatement* for_statement) {
    for_statement->start->accept(this);
    Value* start = return_value;
    if (start == nullptr) {
        return_value = nullptr;
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
    named_values[for_statement->variable_name].push(alloca);
    /* Generate the code for the body */
    for_statement->block->accept(this);
    Value* body = return_value;
    if (body == nullptr) {
        return_value = nullptr;
        return;
    }

    Value* cur = builder.CreateLoad(alloca, for_statement->variable_name);
    Value* next_val = builder.CreateAdd(cur, step_val, "NextVal");
    builder.CreateStore(next_val, alloca);
    end = builder.CreateICmpSLT(next_val, end, "loopcondition");
    BasicBlock* loopEndBlock = builder.GetInsertBlock();
    builder.CreateCondBr(end, loop_body, afterBB);
    builder.SetInsertPoint(afterBB);
    Variable->addIncoming(next_val, loopEndBlock);
    named_values[for_statement->variable_name].pop();
    if (named_values[for_statement->variable_name].empty()) {
        named_values.erase(for_statement->variable_name);
    }
    return_value = ConstantInt::get(context, APInt(32, 1));
    return;
}
void LLVMIRGenerator::visit(ContinueStatement* continue_statement) {
    llvm::Value* V = llvm::ConstantInt::get(context, llvm::APInt(32, 1));
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

void LLVMIRGenerator::visit(AssignmentStatement* assignment_statement) {
    Value* cur = named_values[assignment_statement->location->var_name].top;
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


#endif  // LLVMIRGenerator_cpp