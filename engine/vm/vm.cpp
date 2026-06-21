// engine/vm/vm.cpp
#include "vm.h"
#include <iostream>
#include <stdexcept>

namespace w9::vm {

// === 1. تجميع الـ AST إلى Bytecode ===
Chunk BytecodeCompiler::compile(ast::Program* program) {
    for (const auto& stmt : program->statements) {
        compile_statement(stmt.get());
    }
    chunk_.write(OP_RETURN);
    return chunk_;
}

void BytecodeCompiler::compile_statement(ast::Statement* stmt) {
    if (auto var_decl = dynamic_cast<ast::VariableDeclaration*>(stmt)) {
        if (var_decl->initializer) {
            compile_expression(var_decl->initializer.get());
        } else {
            chunk_.write(OP_CONSTANT);
            size_t const_index = chunk_.add_constant(runtime::JSValue()); // undefined
            chunk_.write(static_cast<uint8_t>(const_index));
        }
        
        chunk_.write(OP_DEFINE_GLOBAL);
        size_t name_index = chunk_.add_constant(runtime::JSValue(std::string(var_decl->identifier)));
        chunk_.write(static_cast<uint8_t>(name_index));
    }
}

void BytecodeCompiler::compile_expression(ast::Expression* expr) {
    if (auto num = dynamic_cast<ast::NumericLiteral*>(expr)) {
        double value = std::stod(std::string(num->value));
        chunk_.write(OP_CONSTANT);
        size_t const_index = chunk_.add_constant(runtime::JSValue(value));
        chunk_.write(static_cast<uint8_t>(const_index));
    } 
    else if (auto binary = dynamic_cast<ast::BinaryExpression*>(expr)) {
        compile_expression(binary->left.get());
        compile_expression(binary->right.get());

        if (binary->op == "+") chunk_.write(OP_ADD);
        else if (binary->op == "-") chunk_.write(OP_SUB);
        else if (binary->op == "*") chunk_.write(OP_MUL);
        else if (binary->op == "/") chunk_.write(OP_DIV);
    }
}

// === 2. الآلة الافتراضية (Execution Engine) ===
void VM::interpret(const Chunk& chunk) {
    size_t ip = 0; // مؤشر التعليمات (Instruction Pointer)

    while (ip < chunk.code.size()) {
        uint8_t instruction = chunk.code[ip++];
        switch (instruction) {
            case OP_CONSTANT: {
                uint8_t const_index = chunk.code[ip++];
                push(chunk.constants[const_index]);
                break;
            }
            case OP_ADD: {
                auto b = pop().as_number();
                auto a = pop().as_number();
                push(runtime::JSValue(a + b));
                break;
            }
            case OP_SUB: {
                auto b = pop().as_number();
                auto a = pop().as_number();
                push(runtime::JSValue(a - b));
                break;
            }
            case OP_MUL: {
                auto b = pop().as_number();
                auto a = pop().as_number();
                push(runtime::JSValue(a * b));
                break;
            }
            case OP_DIV: {
                auto b = pop().as_number();
                auto a = pop().as_number();
                push(runtime::JSValue(a / b));
                break;
            }
            case OP_DEFINE_GLOBAL: {
                uint8_t name_index = chunk.code[ip++];
                auto var_name = chunk.constants[name_index].as_string();
                auto var_value = pop();
                // هنا يمكن ربطها مباشرة بـ Environment الـ Runtime لاحقاً للتخزين الافتراضي
                std::cout << "[VM Debug] Defined Variable: " << var_name << " = " << var_value.to_string() << "\n";
                break;
            }
            case OP_RETURN:
                return;
            default:
                throw std::runtime_error("Unknown Bytecode Instruction");
        }
    }
}

} // namespace w9::vm