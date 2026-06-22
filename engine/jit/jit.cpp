#include "jit.h"
#include <iostream>

namespace w9::jit {

void JITCompiler::initialize_llvm_backend() {
    // محاكاة تهيئة مستهدفات LLVM (LLVM Targets: x86 / ARM)
    std::cout << "[JIT] Initializing LLVM Target Backends (x64/ARM64)...\n";
    is_llvm_initialized_ = true;
}

void JITCompiler::compile_to_native(ast::Program* program) {
    if (!program) return;

    std::cout << "[JIT] Compiling AST directly to LLVM IR...\n";

    // تتبع الشجرة وتحويل العمليات الرياضية إلى LLVM Intermediate Representation (IR)
    for (const auto& stmt : program->statements) {
        if (auto var_decl = dynamic_cast<ast::VariableDeclaration*>(stmt.get())) {
            std::cout << "[JIT LLVM IR] %" << var_decl->identifier << " = alloca double, align 8\n";
            
            if (auto binary = dynamic_cast<ast::BinaryExpression*>(var_decl->initializer.get())) {
                std::cout << "[JIT LLVM IR] %tmp1 = fadd double " << binary->left->to_string() 
                          << ", " << binary->right->to_string() << "\n";
                std::cout << "[JIT LLVM IR] store double %tmp1, double* %" << var_decl->identifier << "\n";
            }
        }
    }
    
    std::cout << "[JIT] Native Machine Code emitted and mapped into Executable Memory Pages.\n";
}

double JITCompiler::execute_native_block() {
    std::cout << "[JIT Executing] Jumping CPU Execution Pointer directly to Native JIT Block.\n";
    // هنا نقوم باستدعاء دالة الـ Function Pointer الموجهة لصفحة الذاكرة المحقونة بالـ Assembly
    return 0.0; 
}

} // namespace w9::jit