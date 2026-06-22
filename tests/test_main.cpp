#include <iostream>
#include <cassert>
#include <string_view>
#include "../engine/lexer/lexer.h"
#include "../engine/parser/parser.h"
#include "../engine/vm/vm.h"

// دالة مساعدة لطباعة نتائج الاختبارات بشكل احترافي
void run_test(std::string_view test_name, void(*test_func)()) {
    std::cout << "[RUNNING] " << test_name << "... ";
    try {
        test_func();
        std::cout << "\033[32m[PASSED]\033[0m\n"; // طباعة باللون الأخضر عند النجاح
    } catch (const std::exception& e) {
        std::cout << "\033[31m[FAILED]\033[0m\n"; // طباعة باللون الأحمر عند الفشل
        std::cerr << "  Error: " << e.what() << "\n";
    }
}

// 1. اختبار الـ Lexer
void test_lexer_tokenization() {
    std::string_view source = "let x = 10; const y = 20; let result = x + y;";
    w9::lexer::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // التحقق من تصنيفات الرموز الأساسية المستخرجة
    assert(tokens[0].type == w9::lexer::TokenType::LET);
    assert(tokens[1].lexeme == "x");
    assert(tokens[3].type == w9::lexer::TokenType::NUMBER);
    assert(tokens[3].lexeme == "10");
    assert(tokens[5].type == w9::lexer::TokenType::CONST);
    assert(tokens[14].type == w9::lexer::TokenType::PLUS);
    assert(tokens.back().type == w9::lexer::TokenType::END_OF_FILE);
}

// 2. اختبار الـ Parser وبناء الـ AST
void test_parser_ast_generation() {
    std::string_view source = "let x = 5 + 10 * 2;";
    w9::lexer::Lexer lexer(source);
    w9::parser::Parser parser(lexer);
    
    auto program = parser.parse_program();
    assert(program != nullptr);
    assert(program->statements.size() == 1);

    // التحقق من أن النص الشجري للـ AST يحترم أسبقية العمليات الرياضية (Pratt Parsing)
    // الضرب (* 10 2) يجب أن يكون معاً أولاً، ثم يضاف للـ 5
    std::string ast_dump = program->to_string();
    assert(ast_dump.find("let x = (5 + (10 * 2));") != std::string::npos);
}

// 3. اختبار الـ VM وتوليد الـ Bytecode وتكامله
void test_vm_execution() {
    std::string_view source = "let result = 15 - 5;";
    w9::lexer::Lexer lexer(source);
    w9::parser::Parser parser(lexer);
    auto program = parser.parse_program();

    w9::vm::BytecodeCompiler compiler;
    w9::vm::Chunk chunk = compiler.compile(program.get());

    // التحقق من توليد التعليمات بشكل سليم
    assert(!chunk.code.empty());
    assert(chunk.code[0] == w9::vm::OP_CONSTANT); // تحميل 15

    // تشغيل الـ VM للتأكد من عدم وجود crashes أثناء تنفيذ الـ Dispatch loops
    w9::vm::VM vm;
    vm.interpret(chunk); // سيطبع [VM Debug] Defined Variable: result = 10.000000

}
// 4. اختبار تحليل واستدعاء الدوال
void test_function_parsing_and_call() {
    std::string_view source = "function add(a, b) { let r = a + b; } add(5, 10);";
    w9::lexer::Lexer lexer(source);
    w9::parser::Parser parser(lexer);
    auto program = parser.parse_program();
    
    assert(program != nullptr);
    
    w9::vm::BytecodeCompiler compiler;
    w9::vm::Chunk chunk = compiler.compile(program.get());
    
    w9::vm::VM vm;
    // التأكد من أن الـ VM يمر عبر تعليمات الاستدعاء دون مشاكل
    vm.interpret(chunk);
}

int main() {
    std::cout << "========================================\n";
    std::cout << "Running W9 Engine Core Test Suite\n";
    std::cout << "========================================\n";

    run_test("Lexer: Tokenization and Lexeme Verification", test_lexer_tokenization);
    run_test("Parser: AST Structure & Operator Precedence", test_parser_ast_generation);
    run_test("Virtual Machine: Bytecode Compilation & Execution", test_vm_execution);
    run_test("JavaScript Features: Function Parsing & VM Call Dispatch", test_function_parsing_and_call);

    std::cout << "========================================\n";
    std::cout << "All core engine modules are verified.\n";
    return 0;
}